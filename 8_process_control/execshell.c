//
// Created by lifan on 2021/5/17.
//

#include "apue.h"
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    if ((pid = vfork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {  //子进程
        if (execl("/home/lifan/bin/echoargs","echoall", "hello", "huahua", (char*)0) < 0)
            err_sys("execl error");
    }

    exit(0);
}