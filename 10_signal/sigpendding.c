//
// Created by lifan on 2021/5/23.
//
#include "apue.h"

static void sig_quit(int);
int main(void)
{
    sigset_t newmask, oldmask, penmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
        err_sys("signal error");

    sigemptyset(&newmask);    //清空信号集
    sigaddset(&newmask, SIGQUIT); //添加quit信号
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) //用newmask新增阻塞的信号集，oldmask保存原始屏蔽信号集
        err_sys("sigblock error");

    sleep(5);  //这次期间发出quit会阻塞

    if (sigpending(&penmask) < 0)    //查询阻塞的信号集
        err_sys("sig pending error");

    if (sigismember(&penmask, SIGQUIT))  //查看sigquit是否被阻塞
        printf("pending quit\n");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL))  //恢复原来的屏蔽信号集
        err_sys("sig setmask error");

    printf("sigquit unblock\n");
    sleep(5);   //这期间quit可以生效
    exit(0);
}

static void sig_quit(int signo) {
    printf("receive sigquit\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        err_sys("sigquit error");
}