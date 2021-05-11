//
// Created by lifan on 2021/5/11.
//

#include "apue.h"

static void hello();
static void byebye();

int main(void) {
    if (atexit(hello) != 0)
        err_sys("atexit error");
    if (atexit(hello) != 0)
        err_sys("atexit error");
    if (atexit(byebye) != 0)
        err_sys("atexit error");

    printf("main is done\n");
    exit(0);
}

static void hello() {
    printf("hello\n");
}

static void byebye() {
    printf("byebye\n");
}