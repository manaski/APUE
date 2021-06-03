//
// Created by lifan on 2021/6/3.
//
#include "apue.h"

int main(void) {
    char buf[MAXLINE];
    FILE *fpin;

    if ((fpin = popen("./myuclc", "r")) == NULL)
        err_sys("popen error");

    for(;;) {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if ((fgets(buf, MAXLINE, fpin)) == NULL)
            break;
        if (fputs(buf, stdout) == EOF)
            err_sys("fputs error to pipe");
    }
    if (pclose(fpin) == -1)
        err_sys("pclose error");
    putchar('\n');
    exit(0);
}
