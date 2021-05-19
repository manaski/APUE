//
// Created by lifan on 2021/5/16.
//

#include "apue.h"
#include "sys/wait.h"

void pr_exit(int status) {
    if (WIFEXITED(status))
        printf("normal exit, exit status= %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number= %d%s\n", WTERMSIG(status),

#ifdef WCOREDUMP
                WCOREDUMP(status)? "core file exits" : "");
#else
               "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));

}

int main(void) {
    int status;
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);  //正常退出

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        abort();  //异常退出

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        status /= 0;  //异常退出

    if (wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    exit(0);
}