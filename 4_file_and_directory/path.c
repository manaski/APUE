//
// Created by lifan on 2021/5/8.
//

#include "apue.h"

int main(void) {
    char buf[1024];
    getcwd(buf, 1024);
    printf("%s\n", buf);
    if(chdir("/Users/lifan/VmShare/APUE/APUE/4_file_and_directory") < 0) {
        err_sys("chdir error");
    }
    getcwd(buf, 1024);
    printf("%s\n", buf);
    exit(0);
}