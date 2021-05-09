//
// Created by lifan on 2021/4/30.
//

#include "apue.h"
#include "fcntl.h"

int main(void) {
    char *file1 = "huahua1.txt";
    char *file2 = "huahua2.txt";

    //设置新生成的文件为rwxrwxrwx
    umask(0);
    if ((open(file1, O_RDONLY|O_CREAT, 0777)) == -1)
        err_sys("open error");
    else
        printf("open good");

    //设置新生成文件为rwx--x--x
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

    if ((open(file2, O_RDONLY|O_CREAT, 0777)) == -1)
        err_sys("open error");
    else
        printf("open with write ok");

    //修改file1为rw-r--r--
    chmod(file1, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    exit(0);
}
