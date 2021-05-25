//
// Created by lifan on 2021/5/22.
//

#include "apue.h"
#include <sys/wait.h>

static void sig_cld(int );

int main(void)
{
    pid_t pid;

    if (signal(SIGUSR1, sig_cld) == SIG_ERR)
        err_sys("cannot catch sigusr1");
    if (signal(SIGUSR2, sig_cld) == SIG_ERR)
        err_sys("cannot catch sigusr1");

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        pause();
        _exit(0);
    }

    kill(pid, SIGUSR1);
    raise(SIGUSR2);
    kill(getpid(), SIGUSR2);
    exit(0);

}

static void sig_cld(int signo) {
    if (signo == SIGUSR1)
        printf("received sigusr1 %d, pid %d\n", signo, getpid());
    else if (signo == SIGUSR2)
        printf("received sigusr2 %d, pid %d\n", signo, getpid());
}