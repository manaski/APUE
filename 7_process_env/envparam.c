//
// Created by lifan on 2021/5/12.
//

#include <stdio.h>
#include <stdlib.h>
#include "apue.h"
int main(int argc, char* argv[]) {
    char *name = "HUAHUA";
    char *value = getenv(name);  //读取
    printf("%s\n", value);
    char *huahua = "HUAHUA=OK";
    if (putenv(huahua) == -1)
        err_sys("putenv error");
    printf("%s\n", getenv("HUAHUA"));
    if (setenv("HUAHUA", "OOKK", 0) == -1) //不覆盖
        err_sys("setenv error");
    printf("%s\n", getenv("HUAHUA"));
    if (setenv("HUAHUA", "OOKK", 1) == -1)  //覆盖
        err_sys("setenv error");
    printf("%s\n", getenv("HUAHUA"));
    if (unsetenv("HUAHUA") == -1)  //删除
        err_sys("unset error");
    printf("%s\n", getenv("HUAHUA"));
    exit(0);
}