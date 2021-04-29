//
// Created by lifan on 2021/4/29.
//

#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefg";
char buf2[] = "ABCDEFG";

int main(void) {
    char *file = "huahua3.txt";
    int fd;

    //以读写方式打开文件，若不存在则创建文件，文件权限wr
    if ((fd = open(file, O_RDWR | O_CREAT, 0600)) == -1)
        err_sys("open error");

    //向文件中写入数据长度10
    if (write(fd, buf1, 10) == -1)
        err_sys("write error");

    //将当前位置定位到16384
    lseek(fd, 16384, SEEK_SET);

    //向文件中写入数据
    if (write(fd, buf2, 10) == -1)
        err_sys("write error");

    exit(0);
}