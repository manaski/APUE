//
// Created by lifan on 2021/5/26.
//

#include <pthread.h>

typedef struct job {
    struct job* j_next;
    struct job* j_prev;
    pthread_t pid;
} job;

typedef struct queue {
    job* q_head;
    job* q_tail;
    pthread_rwlock_t q_lock;
} queue;

int queue_init(queue *qp) {
    int err;
    qp->q_head = NULL;
    qp->q_tail = NULL;
    err = pthread_rwlock_init(&qp->q_lock, NULL);
    if (err != 0)
        return err;
    return 0;
}

/*
 * 在头部插入job
 */
void job_insert(queue* qp, job* jp) {
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = qp->q_head;
    jp->j_prev = NULL;
    if (qp->q_head != NULL)
        qp->q_head->j_prev = jp;
    else
        qp->q_tail = jp;
    qp->q_head = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * 在尾部插入job
 */
void job_append(queue* qp, job* jp) {
    pthread_rwlock_wrlock(&qp->q_lock); //写锁
    jp->j_prev = qp->q_tail;
    jp->j_next = NULL;

    if (qp->q_tail != NULL)
        qp->q_tail->j_next = jp;
    else
        qp->q_head = jp;
    qp->q_tail = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * 删除job
 */
void job_remove(queue* qp, job* jp) {
    pthread_rwlock_wrlock(&qp->q_lock); //读锁
    if (qp->q_head == jp) {
        qp->q_head = jp->j_next;
        if (qp->q_tail == jp)
            qp->q_tail = NULL;
        else
            jp->j_next->j_prev = jp->j_prev;
    } else if (qp->q_tail == jp) {
        qp->q_tail = jp->j_prev;
        jp->j_prev->j_next = jp->j_next;
    } else {
        jp->j_prev->j_next = jp->j_next;
        jp->j_next->j_prev = jp->j_prev;
    }
    pthread_rwlock_unlock(&qp->q_lock);
}

/*
 * find job
 */
job* job_find(queue* qp, pthread_t job_id) {
    if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
        return NULL;

    job* jp = qp->q_head;
    while (jp != NULL && jp->pid != job_id)
        jp = jp->j_next;
    pthread_rwlock_unlock(&qp->q_lock);
    return jp;
}