//
// Created by lifan on 2021/5/4.
//

#include "apue.h"

int main(void) {
    char buf[1024];
    int len;
    char* actualPath = "~/bin2";
    char* symPath = "fakebin";
    if (symlink(actualPath, symPath) == -1) {
        err_sys("link error");
    }
    if ((len = readlink(symPath, buf, 1024)) == -1) {
        err_sys("read link error");
    }
    buf[len] = '\0';
    printf("%s", buf);
    exit(0);
}