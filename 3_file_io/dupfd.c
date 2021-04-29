//
// Created by lifan on 2021/4/30.
//

#include "apue.h"

int main(void) {
    FILE *fp;

    int fd0 = fileno(stdout);
    int fd = dup(fd0);

    printf("该文本重定向到 stdout\n");
    fflush(stdout);

    fp = freopen("file.txt", "a", stdout);
    printf("该文本重定向到 file.txt\n");
    fflush(fp);
    int fd1 = fileno(stdout);
    //fd1指向的文件表已经改变了
    int fd2 = dup2(fd, fd1);
    printf("该文本重定向到 stdout\n");

    exit(0);
}