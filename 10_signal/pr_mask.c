//
// Created by lifan on 2021/5/23.
//
#include "apue.h"
#include <errno.h>

void pr_mask(const char* str) {
    sigset_t sigset;
    int errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0)
        err_sys("sigmask error");
    else {
        printf("%s\n", str);
        if (sigismember(&sigset, SIGINT)) {
            printf("SIGINT\n");
        }
        if (sigismember(&sigset, SIGQUIT))
            printf("SIGQUIT\n");
        if (sigismember(&sigset, SIGALRM))
            printf("SIGALRM\n");
    }
    errno = errno_save;
}
int main(void)
{
    pr_mask("mask");

    exit(0);
}