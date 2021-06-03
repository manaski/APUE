//
// Created by lifan on 2021/6/3.
//

#include "apue.h"

#define DEF_PAGER  "${PAGER:-more}"

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc != 2)
        err_quit("usage: pager <pathname>");

    if ((fpin = fopen(argv[1], "r")) == NULL)
        err_sys("popen error");

    if ((fpout = popen(DEF_PAGER, "w")) == NULL)
        err_sys("popen error");

    while (fgets(line, MAXLINE, fpin) != NULL) { //父进程不断读取数据
        if (fputs(line, fpout) == EOF)
            err_sys("fputs error to pipe");
    }
    if (ferror(fpin))
        err_sys("fgets error");
    if (pclose(fpout) == -1)
        err_sys("pclose error");

    exit(0);
}