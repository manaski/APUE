//
// Created by lifan on 2021/6/9.
//
#include "apue.h"
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define BUFLEN  128
#define TIMEOUT  20

void sigalrm(int signo) {

}

void print_uptime(int sockfd, struct addrinfo *aip) {
  int n;
  char buf[BUFLEN];

  buf[0] = 0;
  if (sendto(sockfd, buf, 1, 0, aip->ai_addr, aip->ai_addrlen) < 0) //向服务器地址发送数据，服务器向sockfd返回数据
    err_sys("sendto error");
  alarm(TIMEOUT);  //设置定时器
  if ((n = recvfrom(sockfd, buf, BUFLEN, 0, NULL, NULL)) < 0) {  //等待从sockfd返回数据，直到超时
    if (errno != EINTR)
      alarm(0);
    err_sys("recv error");
  }
  alarm(0);
  write(STDOUT_FILENO, buf, n);  //写入标准输出
}

int main(int argc, char *argv[]) {
  struct addrinfo *ailist, *aip;
  struct addrinfo hint;
  int sockfd, err;
  struct sigaction sa;

  if (argc != 2)
    err_quit("usage: ruptime hostname");

  sa.sa_handler = sigalrm;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);  //清空设置
  if (sigaction(SIGALRM, &sa, NULL) < 0)  //添加对警告时钟的处理函数
    err_sys("sigaction error");

  memset(&hint, 0, sizeof(hint));
  hint.ai_socktype = SOCK_DGRAM;  //数据报
  hint.ai_canonname = NULL;
  hint.ai_addr = NULL;
  hint.ai_next = NULL;
  if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0) //获取提供数据报服务的地址
    err_quit("getaddrinfo error: %s", gai_strerror(err));

  for (aip = ailist; aip != NULL; aip = aip->ai_next) {
    if ((sockfd = socket(aip->ai_family, SOCK_DGRAM, 0)) < 0) {  //创建socket
      err = errno;
    } else {
      print_uptime(sockfd, aip);
      exit(0);
    }
  }

  fprintf(stderr, "can't contact %s: %s\n", argv[1], strerror(err));
  exit(1);
}