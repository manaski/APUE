//
// Created by lifan on 2021/6/9.
//

#include "apue.h"
#include <netdb.h>
#include <sys/msg.h>
#include <poll.h>
#include <pthread.h>

#define NQ  3    /*队列长度*/
#define MAXMSZ  512   /*最大消息数*/
#define KEY  0x123    /* 第一个消息队列编号*/

struct threadinfo {
  int qid;
  int fd;
};

struct mymesg {
  long mtype;
  char mtext[MAXMSZ];
};

void * helper(void *arg)
{
  int n;
  struct mymesg  m;
  struct threadinfo *tip = arg;

  for(;;) {
    memset(&m, 0, sizeof(m));
    if ((n = msgrcv(tip->qid, &m, MAXMSZ, 0, MSG_NOERROR)) < 0)
      err_sys("msgrcv error");
    if (write(tip->fd, m.mtext, n) < 0)
      err_sys("write error");
  }
}

int main() {
  int i, n, err;
  int fd[2];
  int qid[NQ];
  struct pollfd pfd[NQ];
  struct threadinfo ti[NQ];
  pthread_t tid[NQ];
  char buf[MAXMSZ];

  for (i = 0; i < NQ; i++) {
    if ((qid[i] = msgget(KEY + i, IPC_CREAT|0666)) < 0)
      err_sys("msgget error");

    printf("queue ID %d is %d\n", i, qid[i]);

    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, fd) < 0)  //创建连接，fd[0], fd[1]通过匿名套接字双向连接
      err_sys("socketpair error");

    pfd[i].fd = fd[0]; //访问读端
    pfd[i].events = POLLIN;  //关注的事件是IN
    ti[i].qid = qid[i];  //每个消息队列一个线程
    ti[i].fd = fd[1];   //消息队列使用写端
    if ((err = pthread_create(&tid[i], NULL, helper, &ti[i])) != 0)  //创建线程，并执行helper
      err_exit(err, "pthread_create error");
  }

  for(;;) {
    if (poll(pfd, NQ, -1) < 0)  //poll监听事件，看读端是否可以读数据
      err_sys("poll error");

    for (i = 0; i < NQ; ++i) {
      if ((pfd[i].revents & POLLIN)) {  //如果接收到了输入
        if ((n = read(pfd[i].fd, buf, sizeof(buf))) < 0)  //从对应fd读取数据到buf
          err_sys("read error");
        buf[n] = 0; //添加结尾\0
        printf("queue id %d, message %s\n", qid[i], buf);
      }
    }
  }

  exit(0);
}