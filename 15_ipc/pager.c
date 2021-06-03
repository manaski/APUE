//
// Created by lifan on 2021/6/3.
//

#include "apue.h"
#include <sys/wait.h>

#define DEF_PAGER  "/usr/bin/more"

int main(int argc, char *argv[]) {
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;

    if (argc != 2)
        err_quit("usage: pager <pathname>");

    if ((fp = fopen(argv[1], "r")) == NULL)
        err_sys("can't open %s", argv[1]);
    if (pipe(fd) < 0)
        err_sys("pipe error");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        close(fd[0]);

        while (fgets(line, MAXLINE, fp) != NULL) { //父进程不断读取数据
            n = strlen(line);
            if (write(fd[1], line, n) != n)  //写数据到写端，子进程会从读端读到
                err_sys("write error to pipe");
        }
        if (ferror(fp))
            err_sys("fgets error");

        close(fd[1]);  //关闭写端，子进程会关闭读端

        if (waitpid(pid, NULL, 0) < 0)  //获取子进程退出状态
            err_sys("waitpid error");
        exit(0);
    } else {
        close(fd[1]);   //子进程关闭写端
        if (fd[0] != STDIN_FILENO) {  //如果读端不等于标准输入
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)  //使标准输入成为管道的读端
                err_sys("dup2 error to stdin");
            close(fd[0]); //原来的fd不再需要
        }

        if ((pager = getenv("PAGER")) == NULL)
            pager = DEF_PAGER;
        if ((argv0 = strrchr(pager, '/')) != NULL)
            argv0++;
        else
            argv0 = pager;

        //启动分页程序，能从标准输入获取到父进程传来的数据
        if (execl(pager, argv0, (char*)0) < 0)
            err_sys("execl error for %s", pager);
    }
    exit(0);
}