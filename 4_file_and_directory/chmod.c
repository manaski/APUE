//
// Created by lifan on 2021/4/30.
//
#include "apue.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
    int fd;
    char *file = "huahua.txt";

    if ((fd = open(file, O_RDONLY|O_CREAT, 0400)) == -1)
        err_sys("open error");
    else
        printf("open good");

    if (access(file, W_OK) < 0)
        err_sys("can not write");
    else
        printf("write access good");

    close(fd);

    if ((fd = open(file, O_RDWR)) == -1)
        err_sys("open error");
    else
        printf("open with write ok");

    if (access(file, W_OK) < 0)
        err_sys("can not write");
    else
        printf("write access ok");

    exit(0);
}
