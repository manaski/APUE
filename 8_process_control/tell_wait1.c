//
// Created by lifan on 2021/5/16.
//

#include "apue.h"

static void charatatime(char *);

int main(void)
{
    pid_t	pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        charatatime("output from child,output from child,output from child,output from child,output from child,output from child,output from child\n");
    } else {
        charatatime("output from parent,output from parent,output from parent,output from parent,output from parent,output from parent,output from parent\n");
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
