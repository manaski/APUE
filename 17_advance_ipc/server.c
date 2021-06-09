//
// Created by lifan on 2021/6/10.
//
#include "apue.h"

int main(int argc, char *argv[]) {
  int fd, fd2;
  uid_t uid;

  fd = serv_listen(argv[1]);
  uid = 123;
  fd2 = serv_accept(fd, &uid);
  printf("accept %d\n", fd2);
}
