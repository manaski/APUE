//
// Created by lifan on 2021/5/10.
//

#include "apue.h"
#include <errno.h>

void make_temp(char *template);

int main(void)
{
    //字符串分配在栈上，可以被函数修改
    char	good_template[] = "/tmp/dirXXXXXX";	/* right way */
    //指针在栈上，字符串在只读段，无法被修改
    char	*bad_template = "/tmp/dirXXXXXX";	/* wrong way*/

    printf("trying to create first temp file...\n");
    make_temp(good_template);
    printf("trying to create second temp file...\n");
    make_temp(bad_template);
    exit(0);
}

void
make_temp(char *template)
{
    int			fd;
    struct stat	sbuf;

    if ((fd = mkstemp(template)) < 0)
        err_sys("can't create temp file");
    printf("temp name = %s\n", template);
    close(fd);
    if (stat(template, &sbuf) < 0) {
        if (errno == ENOENT)
            printf("file doesn't exist\n");
        else
            err_sys("stat failed");
    } else {
        printf("file exists\n");  //关闭文件后不会删除
        unlink(template);
    }
}
