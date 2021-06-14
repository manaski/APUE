//
// Created by lifan on 2021/6/13.
//

#include "apue.h"

int main(int argc, char *argv[]) {
  int fd;
  if (argc != 2)
    err_sys("usage server hostname");

    if ((fd = cli_conn(argv[1])) < 0) {
      err_ret("cli_conn error");
    }

  exit(0);
}

