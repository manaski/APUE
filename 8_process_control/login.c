//
// Created by lifan on 2021/5/18.
//

#include "unistd.h"
#include "apue.h"

int main(void) {
    char* user;

    if ((user = getlogin()) != NULL)
        printf("%s", user);

    exit(0);
}