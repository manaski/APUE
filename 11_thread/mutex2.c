//
// Created by lifan on 2021/5/26.
//

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id)%NHASH)

typedef struct foo {
    int f_count;
    int f_id;
    struct foo* next;
    pthread_mutex_t f_lock;
} foo;

foo* fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;  //列表锁

/*
 * 创建一个结构体，使用malloc，使对象分配在堆上，调用结束后地址仍然可用
 */
foo* foo_alloc(int id) {
    foo* fp;
    int idx;

    if ((fp = malloc(sizeof(struct foo))) != NULL){
        fp->f_count = 1;
        fp->f_id = id;
        if ((pthread_mutex_init(&fp->f_lock, NULL)) != 0) { //初始化互斥量
            free(fp);
            return NULL;
        }
        idx = HASH(id);

        pthread_mutex_lock(&hashlock);
        pthread_mutex_lock(&fp->f_lock);
        fp->next = fh[idx];
        fh[idx] = fp;
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_unlock(&hashlock);
    }
    return fp;
}

void foo_hold(foo* fp) {
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_release(foo* fp) {
    foo* tfp;
    int idx;

    pthread_mutex_lock(&hashlock);
    if (--fp->f_count == 0) {
        idx = HASH(fp->f_id);
        tfp = fh[idx];
        if (tfp == fp) {
            fh[idx] = fp->next;
        } else {
            while (tfp->next != fp)
                tfp = tfp->next;
            tfp->next = fp->next;
        }
        pthread_mutex_unlock(&hashlock);
        pthread_mutex_destroy(&fp->f_lock);  //销毁互斥量
        free(fp); //释放内存
    } else {
        pthread_mutex_unlock(&hashlock);
    }
}

foo* foo_find(int id) {
    int idx;
    foo* tfp;
    idx = HASH(id);
    pthread_mutex_lock(&hashlock);
    tfp = fh[idx];
    while (tfp != NULL && tfp->f_id != id) {
        tfp = tfp->next;
    }
    if (tfp != NULL)
        tfp->f_count++;
    pthread_mutex_unlock(&hashlock);

    return tfp;
}

void do_hold(foo* fp) {
    for (int i = 0; i < 100; ++i) {
        foo_hold(fp);
    }
}

int main() {
    foo* fp = foo_alloc(1);
    pthread_t pt;
    pthread_t pt2;
    do_hold(fp);
    pthread_create(&pt, NULL, do_hold, fp);
    pthread_create(&pt2, NULL, do_hold, fp);
    pthread_join(pt, NULL);
    pthread_join(pt, NULL);

    printf("%d", fp->f_count);
    free(fp);
}