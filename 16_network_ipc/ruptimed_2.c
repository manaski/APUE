//
// Created by lifan on 2021/6/8.
//


#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>

#define BUFLEN    128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void
serve(int sockfd) {
  int clfd, status;
  pid_t pid;

  set_cloexec(clfd);
  for (;;) {
    if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
      syslog(LOG_ERR, "ruptimed: accept error: %s", strerror(errno));
      exit(1);
    }
    if ((pid = fork()) < 0) {
      syslog(LOG_ERR, "ruptimed: fork error, %s", strerror(errno));
      exit(1);
    } else if (pid == 0) {
      //重定向标准输出和错误，父进程因为调用了daemonize，所以无需检查，可以直接close
      if (dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO ||
          dup2(clfd, STDERR_FILENO) != STDERR_FILENO) {
        syslog(LOG_ERR, "ruptimed: unexpected error");
        exit(1);
      }
      close(clfd);
      //调用exec，uptime 标准输出和错误都会写到clfd
      execl("/usr/bin/uptime", "uptime", (char *) 0);
      syslog(LOG_ERR, "ruptimed: unexpected return from exec: %s", strerror(errno));
    } else {
      close(clfd);
      waitpid(pid, &status, 0);  //父进程等待子进程结束，如果子进程运行时间很长会影响父进程接受下一个请求
    }
  }
}

int
main(int argc, char *argv[]) {
  struct addrinfo *ailist, *aip;
  struct addrinfo hint;
  int sockfd, err, n;
  char *host;

  if (argc != 1)
    err_quit("usage: ruptimed");
  if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
    n = HOST_NAME_MAX;    /* best guess */
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