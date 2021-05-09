//
// Created by lifan on 2021/4/30.
//

#include "apue.h"

int main(int argc, char *argv[]) {
    int i;
    struct stat s;
    char *ptr;

    for (i = 1; i < argc; i++) {
        if (lstat(argv[i], &s) == -1)
            err_sys("lstat error");

        if (S_ISREG(s.st_mode)) {
            ptr = "regular file";
        } else if (S_ISDIR(s.st_mode)) {
            ptr = "directory";
        } else if (S_ISLNK(s.st_mode)) {
            ptr = "link";
        } else if (S_ISCHR(s.st_mode)) {
            ptr = "character";
        } else if (S_ISBLK(s.st_mode)) {
            ptr = "block";
        } else {
            ptr = "unknown type";
        }
        printf("%s is %s\n", argv[i], ptr);
    }
    if (S_ISUID&s.st_mode){
        printf("set uid");
    }
    if (S_ISGID&s.st_mode){
        printf("set gid");
    }
    printf("uid: %d, gid: %d, file uid: %d, file gid: %d", getuid(), getgid(), s.st_uid, s.st_gid);
}