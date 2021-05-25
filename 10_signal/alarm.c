//
// Created by lifan on 2021/5/22.
//

#include "apue.h"
#include <sys/wait.h>

static void sig_alarm(int);

int main(void)
{
    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        err_sys("cannot catch sigalarm");

    alarm(2);
    pause();
    exit(alarm(0));
}

static void sig_alarm(int signo) {
    if (signo == SIGALRM)
        printf("received %d, pid %d\n", signo, getpid());
}