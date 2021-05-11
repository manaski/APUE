//
// Created by lifan on 2021/5/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("%d\n", getpid());
    printf("%d\n", getppid());
    printf("%d\n", getuid());
    printf("%d\n", geteuid());
    printf("%d\n", getgid());
    printf("%d\n", getegid());
    exit(0);
}