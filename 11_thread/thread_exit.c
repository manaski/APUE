//
// Created by lifan on 2021/5/25.
//

#include "apue.h"
#include <pthread.h>

void clean_up(void* arg) {
    printf("clean up, %s\n", (char*)arg);
}

void* thr_fn1(void* arg) {
    printf("thread1 start\n");
    printf("thread1 exit\n");
    return (void*)1;
}

void* thr_fn2(void* arg) {
    printf("thread2 start\n");
    pthread_cleanup_push(clean_up, "clean push");  //设置线程清理函数，线程退出时执行
    printf("thread2 exit\n");
    pthread_exit((void*)2);
    pthread_cleanup_pop(0);  //传入参数0时不会调用清理函数，这里是为了编译通过
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    void* tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        err_exit(err, "cannot exit thread1\n");

    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        err_exit(err, "cannot exit thread2\n");

    err = pthread_join(tid1, &tret);
    if (err != 0)
        err_exit(err, "cannot join thread1");
    printf("thread1 exit code, %ld\n", (long)tret);

    err = pthread_join(tid2, &tret);
    if (err != 0)
        err_exit(err, "cannot join thread2");
    printf("thread2 exit code, %ld\n", (long)tret);

    exit(0);
}