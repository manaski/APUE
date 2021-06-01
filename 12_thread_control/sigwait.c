//
// Created by lifan on 2021/5/27.
//
#include <pthread.h>
#include <signal.h>
#include "apue.h"

sigset_t mask;
int quitflag;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait_loc = PTHREAD_COND_INITIALIZER;

void* thr_fn(void* arg) {
    int err, signo;

    for(;;) {
        err = sigwait(&mask, &quitflag);
        if (err != 0)
            err_exit(err, "sigwait error");

        switch (signo) {
            case SIGINT:
                printf("quit");
                break;
            case SIGQUIT:
                pthread_mutex_lock(&lock);
                quitflag = 1;
                pthread_mutex_unlock(&lock);
                pthread_cond_signal(&wait_loc);
                return 0;
            default:
                printf("signo: %d", signo);
                exit(1);
        }

    }
}

int main(void) {
    int err;
    sigset_t oldmask;
    pthread_t tid;

    sigemptyset(&mask);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGINT);
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
        err_exit(err, "sigmask error");

    err = pthread_create(&tid, NULL, thr_fn, NULL);
    if(err != 0)
        err_exit(err, "create error");

    pthread_mutex_lock(&lock);
    while (quitflag == 0)
        pthread_cond_wait(&wait_loc, &lock);
    pthread_mutex_unlock(&lock);

    quitflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) != 0)
        err_quit("sigprocmask error");

    exit(0);
}
