//
// Created by lifan on 2021/6/6.
//

#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>

#define BUFLEN	128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void
serve(int sockfd)
{
  int		clfd;
  FILE	*fp;
  char	buf[BUFLEN];

  set_cloexec(sockfd);   //fork子进程并执行exec之后，删除无用的fd
  for (;;) {
    if ((clfd = accept(sockfd, NULL, NULL)) < 0) {  //接受请求，返回客户端fd
      syslog(LOG_ERR, "ruptimed: accept error: %s",
             strerror(errno));
      exit(1);
    }
    set_cloexec(clfd);
    if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {  //创建到uptime的管道
      sprintf(buf, "error: %s\n", strerror(errno));
      send(clfd, buf, strlen(buf), 0);
    } else {
      while (fgets(buf, BUFLEN, fp) != NULL)  //从uptime管道读取数据
        send(clfd, buf, strlen(buf), 0);   //发送到客户端
      pclose(fp); //关闭管道
    }
    close(clfd);  //关闭客户端fd
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
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_canonname = NULL;
  hint.ai_addr = NULL;
  hint.ai_next = NULL;
  if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {  //查询本机服务信息，这里需要提前添加ruptime到/etc/services
    syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
           gai_strerror(err));
    exit(1);
  }
  for (aip = ailist; aip != NULL; aip = aip->ai_next) {
    if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
                             aip->ai_addrlen, QLEN)) >= 0) { //初始化服务器监听socket
      serve(sockfd); //接受请求并响应
      exit(0);
    }
  }
  exit(1);
}
