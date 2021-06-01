//
// Created by lifan on 2021/6/2.
//

#include <aio.h>
#include <ctype.h>
#include "apue.h"
#include <fcntl.h>
#include <errno.h>

#define BSZ 4096
#define NBUF 8

enum rwop {
    UNUSED = 0,     //未使用的缓冲区
    READ_PENDING = 1,  //正在读
    WRITE_PENDING = 2  //正在写
};

struct buf {
    enum rwop op;
    int last;
    struct aiocb aiocb;
    unsigned char data[BSZ];
};

struct buf bufs[NBUF];

unsigned char translate(unsigned char c) {
    if (isalpha(c)) {
        if (c >= 'n')
            c -= 13;
        else if (c >= 'a')
            c += 13;
        else if (c >= 'N')
            c -= 13;
        else
            c += 13;
    }
    return c;
}

int main(int argc, char *argv[]) {
    int ifd, ofd, i, j, n, err, numop;
    struct stat sbuf;
    const struct aiocb *aiolist[NBUF];
    off_t off = 0;  //全局文件偏移量

    if (argc != 3)
        err_quit("usage: rot13 infile outfile");
    if ((ifd = open(argv[1], O_RDONLY)) < 0)
        err_sys("cannot open %s", argv[1]);

    if ((ofd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
        err_sys("cannot open %s", argv[2]);

    if (fstat(ifd, &sbuf) < 0)
        err_sys("fstat failed");

    //初始化buffer
    for (i = 0; i < NBUF; ++i) {
        bufs[i].op = UNUSED;
        bufs[i].aiocb.aio_buf = bufs[i].data; //数据buf
        bufs[i].aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;  //不适用异步信号通知
        aiolist[i] = NULL;
    }

    numop = 0;
    for (;;) {
        for (i = 0; i < NBUF; ++i) {  //轮询每个缓冲区
            switch (bufs[i].op) {
                case UNUSED:
                    if (off < sbuf.st_size) { //如果空闲，并且未读完，则加入读操作中
                        bufs[i].op = READ_PENDING;
                        bufs[i].aiocb.aio_fildes = ifd;
                        bufs[i].aiocb.aio_offset = off;
                        off += BSZ;
                        if (off > sbuf.st_size)
                            bufs[i].last = 1;  //读到了文件末尾
                        bufs[i].aiocb.aio_nbytes = BSZ;
                        if (aio_read(&bufs[i].aiocb) < 0)  //调用函数后马上返回
                            err_sys("aio read failed");
                        aiolist[i] = &bufs[i].aiocb;
                        numop++;
                    }
                    break;

                case READ_PENDING:
                    if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)  //检查操作状态
                        continue;
                    if (err != 0) {
                        if (err == -1)
                            err_sys("aio_error failed");
                        else
                            err_exit(err, "read failed");
                    }

                    if ((n = aio_return(&bufs[i].aiocb)) < 0) //操作完成，获取结果
                        err_sys("aio_return failed");
                    if (n != BSZ && !bufs[i].last) //不是最后一次读，长度不够
                        err_quit("short read (%d/%d)", n, BSZ);

                    for (j = 0; j < n; ++j)
                        bufs[i].data[j] = translate(bufs[i].data[j]);
                    bufs[i].op = WRITE_PENDING;
                    bufs[i].aiocb.aio_fildes = ofd;
                    bufs[i].aiocb.aio_nbytes = n;
                    if (aio_write(&bufs[i].aiocb) < 0) //读成功之后提交到异步写操作
                        err_sys("aio_write failed");

                    break;

                case WRITE_PENDING:
                    if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)
                        continue;
                    if (err != 0) {
                        if (err == -1)
                            err_sys("aio_error failed");
                        else
                            err_exit(err, "write failed");
                    }

                    if ((n = aio_return(&bufs[i].aiocb)) < 0)
                        err_sys("aio_return failed");
                    if (n != bufs[i].aiocb.aio_nbytes)
                        err_quit("short write (%d/%d)", n, BSZ);
                    aiolist[i] = NULL;  //操作完成，置为空
                    bufs[i].op = UNUSED;
                    numop--;
                    break;
            }
        }
        if (numop == 0) {  //没有在运行的buf
            if (off >= sbuf.st_size)  //处理完了返回
                break;
        } else {
            if (aio_suspend(aiolist, NBUF, NULL) < 0)  //还有未完成的aoi，阻塞等待aiolist
                err_sys("aio_suspend failed");
        }
    }
    bufs[0].aiocb.aio_fildes = ofd;
    if (aio_fsync(O_SYNC, &bufs[0].aiocb) < 0) //同步内容到磁盘
        err_sys("aio_fsync failed");
    exit(0);
}