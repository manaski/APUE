//
// Created by lifan on 2021/6/1.
//

#include "apue.h"
#include <fcntl.h>

static void lockabyte(const char *name, int fd, off_t offset) {
    if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
        err_sys("%s: writew_lock error", name);
    printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

int main(void) {
    int fd;
    pid_t pid;

    /*
     * 创建一个文件，写入两个字节
     */
    if ((fd = creat("templock", FILE_MODE)) < 0)
        err_sys("create error");
    if (write(fd, "ab", 2) != 2)
        err_sys("write error");

    TELL_WAIT();  //初始化信号
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        lockabyte("child", fd, 0); //子进程加锁 0
        TELL_PARENT(getpid()); //给父进程发信号
        WAIT_PARENT();  //父进程加完锁才到这里
        lockabyte("child", fd, 1); //子进程加锁 1
    } else {
        lockabyte("parent", fd, 1);  //父进程加锁 1
        TELL_CHILD(pid);
        WAIT_CHILD();  //子进程加完锁才到这里
        lockabyte("parent", fd, 0);  //父进程加锁 0
    }
    exit(0);
}