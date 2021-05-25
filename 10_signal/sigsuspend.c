//
// Created by lifan on 2021/5/24.
//

#include "apue.h"
#include <errno.h>
static void sig_int(int);

void pr_mask(const char* str) {
    sigset_t	sigset;
    int			errno_save;

    errno_save = errno;		/* we can be called by signal handlers */
    if (sigprocmask(0, NULL, &sigset) < 0) {
        err_ret("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");

        /* remaining signals can go here  */
        printf("\n");
    }

    errno = errno_save;		/* restore errno */
}

int main(void)
{
    sigset_t newmask, oldmask, waitmask;

    pr_mask("program start");
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("error");

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)  //设置阻塞int
        err_sys("sigprocmask error");

    pr_mask("in critical region");

    if (sigsuspend(&waitmask) != -1)   //设置成阻塞usr1并休眠进程，其他信号不阻塞
        err_sys("sigsuspend error");

    pr_mask("after return from sigsuspend");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)  //恢复原来的屏蔽信号集
        err_sys("setmask error");

    pr_mask("program exit");

    exit(0);
}

static void sig_int(int signo) {
    pr_mask("\nint sig_int: ");
}