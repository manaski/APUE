//
// Created by lifan on 2021/6/4.
//

#include "apue.h"

static void sig_pipe(int);

int main(void) {
    int n, fd1[2], fd2[2];
    pid_t pid;
    char line[MAXLINE];

    if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
        err_sys("signal error");

    if (pipe(fd1) < 0 || pipe(fd2) < 0)  //建立两个管道
        err_sys("pipe error");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0){
        close(fd1[0]);
        close(fd2[1]);

        while (fgets(line, MAXLINE, stdin) != NULL) {  //父进程读数据
            n = strlen(line);
            if (write(fd1[1], line, n) != n) //写管道
                err_sys("write error to pipe");
            if ((n = read(fd2[0], line, n)) < 0) //从管道读
                err_sys("read error");
            if (n == 0) {  //没有读到数据，管道已关闭
                err_msg("child close pipe");
                break;
            }
            line[n] = 0;
            if (fputs(line, stdout) == EOF)  //输出
                err_sys("fputs error");
        }

        if (ferror(stdin))
            err_sys("fgets error on stdin");
        exit(0);
    } else {
        close(fd1[1]);
        close(fd2[0]);

        if (fd1[0] != STDIN_FILENO) {  //保证对应的输入输出是标准输入和标准输出
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)   //dup2 重定向标准输入输出到管道
                err_sys("dup2 error");
            close(fd1[0]);
        }

        if (fd2[1] != STDOUT_FILENO) {
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
                err_sys("dup2 error");
            close(fd2[1]);
        }

        if (execl("./add2", "add2", (char *)0) < 0)
            err_sys("execl error");
    }
    exit(0);
}

static void sig_pipe(int signo) {
    printf("SIGPIPE caught\n");
    exit(1);
}