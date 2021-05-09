//
// Created by lifan on 2021/4/30.
//
#include "apue.h"
#include "fcntl.h"

int main(void) {
    char *file = "huahua.txt";
    char *file2 = "huahua2.txt";
    int fd;
    char buf[] = "hello world";

    if ((fd = open(file, O_RDWR|O_CREAT, 0600)) == -1)
        err_sys("open error\n");

//    if (write(fd, buf, strlen(buf)) < 0)
//        err_sys("write error\n");

    printf("open done\n");

//    sleep(5);

    //复制file->file2
//    if (link(file, file2) == -1)
//        err_sys("link error\n");
//    else
//        printf("link done\n");
//
//    sleep(5);
    //删除file2
//    if (unlink(file2) == -1)
//        err_sys("unlink error\n");
//    else
//        printf("unlink file done\n");
//
//    sleep(5);
    //删除file
    if (unlink(file) == -1)
        err_sys("unlink error\n");
    else
        printf("unlink file2 done\n");

    sleep(5);

    printf("done\n");

    exit(0);
}
