//
// Created by lifan on 2021/5/20.
//
#include "apue.h"
static void sig_usr(int );
int main(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) //安装信号处理程序
        err_sys("cannot catch sigusr1");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("cannot catch sigusr2");

    for (;;) {
        pause();  //使进程在后台运行直到收到一个信号
    }
}

static void sig_usr(int signo) {
    if (signo == SIGUSR1)
        printf("receive SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("receive SIGUSR2\n");
    else
        err_dump("receive signal %d\n", signo);
}
