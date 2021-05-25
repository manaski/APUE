//
// Created by lifan on 2021/5/25.
//

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct foo {
    int f_count;
    int f_id;
    pthread_mutex_t f_lock;
} foo;

/*
 * 创建一个结构体，使用malloc，使对象分配在堆上，调用结束后地址仍然可用
 */
foo* foo_alloc(int id) {
    foo* fp;
    if ((fp = malloc(sizeof(struct foo))) != NULL){
        fp->f_count = 1;
        fp->f_id = id;
        if ((pthread_mutex_init(&fp->f_lock, NULL)) != 0) { //初始化互斥量
            free(fp);
            return NULL;
        }
    }
    return fp;
}

void foo_hold(foo* fp) {
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_release(foo* fp) {
    pthread_mutex_lock(&fp->f_lock);
    if (--fp->f_count == 0) {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);  //销毁互斥量
        free(fp); //释放内存
    } else {
        pthread_mutex_unlock(&fp->f_lock);
    }
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