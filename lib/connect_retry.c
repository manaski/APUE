//
// Created by lifan on 2021/6/6.
//

#include <sys/socket.h>
#include "apue.h"

#define MAXSLEEP 128

int connect_retry(int domain, int type, int protocol,
                  const struct sockaddr *addr, socklen_t alen) {
  int numsec, fd;

  for (numsec = 1; numsec <= MAXSLEEP ; numsec<<=1) { //休眠时间指数增长
    if ((fd = socket(domain, type, protocol)) < 0)   //创建socket
      return(-1);

    if (connect(fd, addr, alen) == 0) {  //建立连接
      return(fd);
    }
    close(fd);  //失败要删除原来的socket

    if (numsec <= MAXSLEEP/2)
      sleep(numsec);
  }

  return(-1);
}