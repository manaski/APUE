//
// Created by lifan on 2021/4/28.
//

#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 128

int main(void) {
    char *file = "huahua.txt";
    char *file2 = "huahua2.txt";
    char *dir = "./";
    int fd;
    int dir_fd;

    char buf[BUFFSIZE];
    char *msg = "hello, huahua!";
    ssize_t read_bytes;

    //以读写方式打开文件，若不存在则创建文件，文件权限wr
    if ((fd = open(file, O_RDWR | O_CREAT, 0600)) == -1)
        err_sys("open error");

    //向文件中写入数据
    if (write(fd, msg, strlen(msg)) == -1)
        err_sys("write error");
    //将当前位置定位到开头
    lseek(fd, 0, SEEK_SET);
    //读取文件内容，写入控制台
    while ((read_bytes = read(fd, buf, strlen(msg))) > 0) {
        if (write(STDOUT_FILENO, buf, read_bytes) != read_bytes)
            err_sys("write error");
    }

    if (read_bytes < 0)
        err_sys("read error");

    //使用打开目录
    if ((dir_fd = open(dir, O_RDONLY)) == -1)
        err_sys("open error");
    //openat 打开目录中的文件
    int fd2 = openat(dir_fd, file2, O_RDWR|O_CREAT, 0600);
    if (fd2 == -1)
        err_sys("openat error");

    //向文件中写入数据
    if (write(fd2, msg, strlen(msg)) == -1)
        err_sys("write error");
    //将当前位置定位到开头
    lseek(fd2, 0, SEEK_SET);
    //读取文件内容，写入控制台
    while ((read_bytes = read(fd2, buf, strlen(msg))) > 0) {
        if (write(STDOUT_FILENO, buf, read_bytes) != read_bytes)
            err_sys("write error");
    }

    exit(0);
}
