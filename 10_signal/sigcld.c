//
// Created by lifan on 2021/5/22.
//

#include "apue.h"
#include <sys/wait.h>

static void sig_cld(int );

int main(void)
{
    pid_t pid;

    if (signal(SIGCHLD, sig_cld) == SIG_ERR) //安装信号处理程序
        err_sys("cannot catch sigusr1");

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        sleep(2);
        _exit(0);
    }

    pause();
    exit(0);

}

static void sig_cld(int signo) {
    pid_t pid;
    int status;

    printf("SIGCLD received\n");

    if (signal(SIGCHLD, sig_cld) == NULL)
        perror("signal error");

    if ((pid = wait(&status)) < 0)
        perror("wait error");

    printf("pid = %d\n", pid);
}

