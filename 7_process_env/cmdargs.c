//
// Created by lifan on 2021/5/11.
//
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        printf("%d, %s\n", i, argv[i]);
    }
    exit(0);
}
