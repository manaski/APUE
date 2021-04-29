//
// Created by lifan on 2021/4/27.
//

#include "apue.h"
#include <sys/wait.h>

#define	BUFFSIZE	1024

static void sig_int(int);

int main(void)
{
    char	buf[BUFFSIZE];
    pid_t  pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");

    while ((fgets(buf, BUFFSIZE, stdin)) != NULL)
    {
        if (buf[strlen(buf) -1] == '\n')
            buf[strlen(buf) -1] = 0;

        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid == 0 ) {
            /*
             * int execlp(const char * file,const char * arg,....);
             * 传入参数可执行文件名，会从PATH路径下去寻找，agr0和file同名，最后一个参数必须是NULL
             */
            execlp(buf, buf, NULL);
            err_ret("exec %s error", buf);
            exit(127);
        }
        //父进程等待子进程退出
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("wait error");

        printf("%% ");

    }

    exit(0);
}

void sig_int(int sig) {
    printf("interuppted by %d\n%%", sig);
}