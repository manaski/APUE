//
// Created by lifan on 2021/5/21.
//
#include "apue.h"
#include <pwd.h>
static void my_alarm(int signo) {
    struct passwd *ptr;

    printf("in signal handler \n");
    if ((ptr = getpwnam("root")) == NULL)
        err_sys("getpwan error");
    alarm(1);
}

int main(void)
{
    struct passwd *ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);
    for (;;) {
        if ((ptr = getpwnam("lifan")) == NULL)
            err_sys("error");
        if (strcmp(ptr->pw_name, "lifan") != 0)
            printf("return value wrong, %s\n", ptr->pw_name);
    }
}
