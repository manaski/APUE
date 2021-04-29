//
// Created by lifan on 2021/4/27.
//
#include "apue.h"
#include <errno.h>

int main(int argc, char*argv[]) {
    printf("EGAIN: %s\n", strerror(EAGAIN));
    errno = EAGAIN;
    perror(argv[0]);
}