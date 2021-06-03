//
// Created by lifan on 2021/6/3.
//
#include "apue.h"

int main(void) {
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    //传入两个fd, fd[0]作为读，fd[1]作为写端
    if (pipe(fd) < 0)
        err_sys("pipe error");
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0) {
        close(fd[0]);
        write(fd[1], "hello, world\n", 12); //父进程写管道，子进程接收
    } else {
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
    exit(0);
}
