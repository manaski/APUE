//
// Created by lifan on 2021/5/18.
//

#include "unistd.h"
#include "apue.h"
#include <errno.h>

int main(void) {
    int pri;
    pri = nice(0);
    printf("nice: %d, errno: %d\n", pri, errno);  //0, 0

    pri = nice(100);
    printf("nice: %d, errno: %d\n", pri, errno); //19, 0

    pri = nice(-100);
    printf("nice: %d, errno: %d\n", pri, errno); //-1, 1

    exit(0);
}