//
// Created by lifan on 2021/5/26.
//
#include <pthread.h>
#include <stdio.h>

struct msg {
    struct msg* next;
    int id;
};

struct msg* workq;

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

void enqueue_msg(struct msg* mp) {
    pthread_mutex_lock(&qlock);
    mp->next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}

void process_msg(void) {
    struct msg* mp;
    for(;;) {
        pthread_mutex_lock(&qlock);
        while (workq == NULL)
            pthread_cond_wait(&qready, &qlock);
        mp = workq;
        printf("id: %d\n", mp->id);
        workq = mp->next;
        pthread_mutex_unlock(&qlock);
    }
}

int main(void) {
    pthread_t pid;
    pthread_create(&pid, NULL, process_msg, NULL);
    struct msg m = {.id = 1, .next = NULL};
    enqueue_msg(&m);
    struct msg m2 = {.id = 2, .next = NULL};
    enqueue_msg(&m2);
    pthread_join(pid, NULL);
}
