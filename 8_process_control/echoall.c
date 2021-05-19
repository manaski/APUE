//
// Created by lifan on 2021/5/17.
//

#include "apue.h"

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("arg[%d]=%s\n", i, argv[i]);
    }

    exit(0);
}