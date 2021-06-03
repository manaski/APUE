//
// Created by lifan on 2021/6/2.
//

#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR 1024*1024*1024  //控制每次复制最大1G

int main(int argc, char *argv[]) {
    int fdin, fdout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;

    if (argc != 3)
        err_quit("usage: %s infile outfile", argv[0]);
    if ((fdin = open(argv[1], O_RDONLY)) < 0)
        err_sys("cannot open %s", argv[1]);
    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
        err_sys("cannot open %s", argv[2]);

    if (fstat(fdin, &sbuf) < 0)
        err_sys("fstat failed");

    if (ftruncate(fdout, sbuf.st_size) < 0)
        err_sys("ftruncate failed");

    while (fsz < sbuf.st_size) {
        if (sbuf.st_size - fsz > COPYINCR)
            copysz = COPYINCR;
        else
            copysz = sbuf.st_size - fsz;

        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED)
            err_sys("map src failed");
        if ((dst = mmap(0, copysz, PROT_WRITE | PROT_READ, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
            err_sys("map dst failed");

        memcpy(dst, src, copysz);  //执行复制，把文件读取变成了内存复制
        munmap(src, copysz);  //释放映射
        munmap(dst, copysz);
        fsz += copysz;
    }
    exit(0);
}