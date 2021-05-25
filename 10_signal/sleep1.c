//
// Created by lifan on 2021/5/23.
//

#include "apue.h"
#include "setjmp.h"
#include <sys/wait.h>

typedef void Sigfunc(int);

static void sig_alarm(int);
unsigned int sleep1(unsigned int);

static jmp_buf env_alrm;

int main(void)
{
    printf("begin\n");
    sleep1(2);
    printf("end\n");
}

static void sig_alarm(int signo) {
    longjmp(env_alrm, 0);  //保证信号发生后返回主进程
}

unsigned int sleep1(unsigned int seconds) {
    unsigned int old_sec;
    Sigfunc *sigPtr;
    if ((sigPtr = signal(SIGALRM, sig_alarm)) == SIG_ERR)
        return(seconds);

    if (setjmp(env_alrm) == 0) {
        printf("set alarm\n");
        if ((old_sec = alarm(seconds)) > seconds) {  //如果以前设置过alarm，则判断一下余下的超时时间
            alarm(old_sec);
        }
        pause();
        signal(SIGALRM, sigPtr);  //恢复原始的处理函数
    }

    return(alarm(0));
}