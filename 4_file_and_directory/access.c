//
// Created by lifan on 2021/4/30.
//

#include "apue.h"
#include "fcntl.h"

int main(void) {
    int fd;
    char *file = "huahua.txt";

    if ((fd = open(file, O_RDONLY|O_CREAT, 0400)) == -1)
        err_sys("open error");
    else
        printf("open good");

    if (chown(file, 0, 0) == -1)
        err_sys("chown error");

     exit(0);
}