//
// Created by lifan on 2021/5/19.
//

#include "unistd.h"
#include "apue.h"

int main(void) {
    pid_t pgrp;
    pgrp = getpgrp();
    printf("pgrp: %d\n", pgrp);

    pid_t pid = getpid();
    pgrp = getpgid(pid);
    printf("pid: %d, pgrp: %d\n", pid, pgrp);

    if (setpgid(pid, 1234) == -1)
        err_sys("setpgid error");

    pgrp = getpgrp();
    printf("pgrp: %d\n", pgrp);

    exit(0);
}