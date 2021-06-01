//
// Created by lifan on 2021/5/28.
//
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include "apue.h"

extern char **environ;

pthread_mutex_t env_mutex;

static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static void thread_init(void) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE); //可重入锁，防止死锁
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf, int buflen) {
    int i, len, olen;

    pthread_once(&init_once, thread_init); //保证初始化函数只执行一次
    len = strlen(name);
    pthread_mutex_lock(&env_mutex);
    for (i = 0;  environ[i] != NULL; i++) {
        if ((strncmp(name, environ[i], len) == 0) &&
        (environ[i][len] == '=')) {
            olen = strlen(&environ[i][len+1]); //数组名等同于指着，下标取值等于取内容
            if (olen >= buflen) {
                pthread_mutex_unlock(&env_mutex);
                return(ENOSPC);
            }
            strcpy(buf, &environ[i][len+1]);
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return ENOENT;
}

int main(void ) {
    char* name = "LOGNAME";
    char buf[1024];
    int err;

    if ((err = getenv_r(name, buf, 1024)) != 0)
        err_exit(err, "getenv error");

    printf("LOGNAME: %s\n", buf);
}