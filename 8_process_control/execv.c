//
// Created by lifan on 2021/5/17.
//

#include "apue.h"
#include <sys/wait.h>

char* env_init[] = {"PATH=/tmp", "USER=UNKNOWN", NULL};

int main(void) {
    pid_t pid;

    if ((pid = vfork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {  //子进程
        if (execle("./echoall", "echoall", "hello", "huahua", (char*)0, env_init) < 0)
            err_sys("execle error");
    }

    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");

    if ((pid = vfork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        if (execlp("echoall", "achoall", "hello", "huahua", (char *)0) < 0)
            err_sys("execlp error");
    }

    exit(0);
}