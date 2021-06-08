//
// Created by lifan on 2021/6/9.
//

#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>

#define BUFLEN	128
#define MAXADDRLEN 256

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void
serve(int sockfd)
{
  int		n;
  socklen_t alen;
  FILE	*fp;
  char	buf[BUFLEN];
  char abuf[MAXADDRLEN];  //数组内存已经分配好了
  struct sockaddr  *addr = (struct sockaddr *)abuf; //转换为sockaddr类型

  set_cloexec(sockfd);
  for(;;) {
    alen = MAXADDRLEN;
    if ((n = recvfrom(sockfd, buf, BUFLEN, 0, addr, &alen)) <0) { //从监听套接字读取数据，addr保存客户端地址
      syslog(LOG_ERR, "ruptimed: recvfrom error: %s", strerror(errno));
      exit(1);
    }

    if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
      sprintf(buf, "error: %s\n", strerror(errno));
      sendto(sockfd, buf, strlen(buf), 0, addr, alen);  //向客户端地址发送数据，sockfd指服务端套接字
    } else {
      if (fgets(buf, BUFLEN, fp) != NULL)
        sendto(sockfd, buf, strlen(buf), 0, addr, alen);
      pclose(fp);
    }
  }
}

int
main(int argc, char *argv[])
{
  struct addrinfo	*ailist, *aip;
  struct addrinfo	hint;
  int				sockfd, err, n;
  char			*host;

  if (argc != 1)
    err_quit("usage: ruptimed");
  if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
    n = HOST_NAME_MAX;	/* best guess */
  if ((host = malloc(n)) == NULL)
    err_sys("malloc error");
  if (gethostname(host, n) < 0)
    err_sys("gethostname error");
  daemonize("ruptimed");   //服务进程设置成守护进程
  memset(&hint, 0, sizeof(hint));
  hint.ai_flags = AI_CANONNAME;  //返回标准名
  hint.ai_socktype = SOCK_DGRAM;
  hint.ai_canonname = NULL;
  hint.ai_addr = NULL;
  hint.ai_next = NULL;
  if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {  //查询本机服务信息，这里需要提前添加ruptime到/etc/services
    syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
           gai_strerror(err));
    exit(1);
  }
  for (aip = ailist; aip != NULL; aip = aip->ai_next) {
    if ((sockfd = initserver(SOCK_DGRAM, aip->ai_addr,
                             aip->ai_addrlen, 0)) >= 0) { //初始化服务器监听socket
      serve(sockfd); //接受请求并响应
      exit(0);
    }
  }
  exit(1);
}