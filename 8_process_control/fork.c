//
// Created by lifan on 2021/5/13.
//

#include "apue.h"

int globalvar = 6;
char buf[] = "hello, huahua\n";

int main(void) {
    int var;
    pid_t pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) -1) != sizeof(buf) - 1) //sizeof包含了最后的null
        err_sys("write error");

    printf("before fork\n");
    //写入缓冲区，如果是在shell运行是行缓冲，被换行符刷新；
    // 如果是写入到文件是全缓冲，不会刷新，缓冲内容会带到子进程

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {  //子进程
        globalvar++;  //数据空间独立
        var++;
    } else {  //父进程
        sleep(2);
    }
    printf("pid: %d, global var: %d, var: %d\n", pid, globalvar, var);
    exit(0);
}