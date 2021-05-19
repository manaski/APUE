//
// Created by lifan on 2021/5/13.
//

#include "apue.h"

int globalvar = 6;

int main(void) {
    int var;
    pid_t pid;

    var = 88;

    printf("before fork\n");

    if ((pid = vfork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {  //子进程
        globalvar++;  //会修改父进程的数据
        var++;
        _exit(0); //退出时不会刷新缓冲区
    }
    printf("pid: %d, global var: %d, var: %d\n", pid, globalvar, var);
    exit(0);
}