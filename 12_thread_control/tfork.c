//
// Created by lifan on 2021/5/27.
//

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "apue.h"

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void) {
    int err;

    printf("preparing lock....\n");
    if ((err = pthread_mutex_lock(&lock1)) != 0)
        printf("cannot lock1\n");
    if ((err = pthread_mutex_lock(&lock2)) != 0)
        printf("cannot lock2\n");
}

void parent(void) {
    int err;

    printf("parent unlock....\n");
    if ((err = pthread_mutex_unlock(&lock1)) != 0)
        err_cont(err, "parent cannot lock1\n");
    if ((err = pthread_mutex_unlock(&lock2)) != 0)
        err_cont(err, "parent cannot lock2\n");
}

void child(void) {
    int err;

    printf("child unlock....\n");
    if ((err = pthread_mutex_unlock(&lock1)) != 0)
        err_cont(err, "child cannot lock1\n");
    if ((err = pthread_mutex_unlock(&lock2)) != 0)
        err_cont(err, "child cannot lock2\n");
}

void* thrd_fn(void* arg) {
    printf("thread start\n");
    pause();
    return 0;
}

int main(void ) {
    int err;
    pid_t pid;
    pthread_t tid;

    if ((err = pthread_atfork(prepare, parent, child)) != 0)
        err_exit(err, "cannot install fork handler\n");
    if ((err = pthread_create(&tid, NULL, thrd_fn, NULL)) != 0)
        err_exit(err, "cannot create thread\n");

    sleep(2);
    printf("parent about fork....\n");
    if ((pid = fork()) < 0)
        err_sys("fork error\n");
    else if (pid == 0)
        printf("child return from fork");
    else
        printf("parent return from fork");

    exit(0);
}