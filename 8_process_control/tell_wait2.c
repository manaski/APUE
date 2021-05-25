//
// Created by lifan on 2021/5/16.
//

#include "apue.h"

static void charatatime(char *);

int main(void)
{
    pid_t	pid;

    TELL_WAIT();  //设置当前进程阻塞usr1, usr2信号

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        WAIT_PARENT();		/* parent goes first */  //等待信号处理程序设置全局变量
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);  //向子进程发送usr1信号
    }
    exit(0);
}

static void charatatime(char *str)
{
    char	*ptr;
    int		c;

    setbuf(stdout, NULL);			/* set unbuffered */
    for (ptr = str; (c = *ptr++) != 0; )
        putc(c, stdout);
}
