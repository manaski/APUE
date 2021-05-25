//
// Created by lifan on 2021/5/23.
//

#include "apue.h"
#include "setjmp.h"
#include <sys/wait.h>

static void sig_alarm(int);
static jmp_buf env_alrm;

int main(void)
{
    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        err_sys("cannot catch sigalarm");

    if (setjmp(env_alrm) != 0)
        err_quit("timeout");

    alarm(10);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
        err_sys("read error");
    alarm(0);

    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void sig_alarm(int signo) {
    if (signo == SIGALRM)
        printf("received %d, pid %d\n", signo, getpid());
    longjmp(env_alrm, 0);
}