//
// Created by lifan on 2021/6/9.
//

#include <sys/socket.h>
#include "apue.h"
#include <errno.h>

int initserver(int type, struct sockaddr *addr, socklen_t alen, int qlen) {
  int fd, err;
  int reuse = 1;

  if ((fd = socket(addr->sa_family, type, 0)) < 0)  //创建套接字
    return -1;
  //SOL_SOCKET  通用套接字选项
  //IPPROTO_TCP  TCP选项
  //IPPROTO_IP  IP选项
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)))
  if (bind(fd, addr, alen) < 0) {  //把套接字和传入的地址绑定，传入的地址对应对外提供的服务
    printf("bind error");
    goto errout;
  }

  if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
    if (listen(fd, qlen) < 0) {  //表示套接字可以进行监听请求，qlen指定监听队列长度
      printf("listen error");
      goto errout;
    }
  }
  return fd;  //返回创建好的套接字
  errout:
  err = errno;
  close(fd);
  errno = err;
  return -1;
}