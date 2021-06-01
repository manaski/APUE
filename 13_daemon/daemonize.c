//
// Created by lifan on 2021/5/31.
//

#include <fcntl.h>
#include "apue.h"
#include <sys/resource.h>
#include <syslog.h>

void daemonize(const char *cmd) {
    int  i, fd0, fd1, fd2;
    pid_t  pid;
    struct rlimit  rl;
    struct sigaction sa;

    /*
     * 清空文件创建屏蔽字
     */
    umask(0);

    /*
     * 获得最大文件描述符数量
     */
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_quit("%s: can't get file limit", cmd);

    /*
     * 称为会话leader
     */
    if ((pid = fork()) < 0)
        err_quit("%s: can't fork", cmd);
    else if (pid != 0) //父进程直接退出
        exit(0);
    setsid();

    /*
     * 确保后续打开操作不会分配控制终端
     */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: cannot ignore SIGHUP", cmd);
    if ((pid = fork()) < 0)
        err_quit("%s: can't fork", cmd);
    else if (pid != 0) //父进程直接退出
        exit(0);

    /*
     * 将当前目录作为工作目录
     */
    if (chdir("/") < 0)
        err_quit("%s: cannot change directory to /", cmd);

    /*
     * 关闭所有打开的文件描述符
     */
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; ++i) {
        close(i);
    }

    /*
     * 绑定fd 0， 1， 2到/dev/null
     */
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    /*
     * 初始化日志文件
     */
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptor %d, %d, %d",
               fd0, fd1, fd2);
        exit(1);
    }
}

int main() {
    daemonize("pwd");
    for (;;) {
        sleep(1);
    }
}