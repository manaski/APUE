## 0. 配置环境

IDE： clion 2020.3  mac

编译工具： cmake

源代码下载：http://www.apuebook.com/ 选择对应版本下载源代码

clion创建c项目

将源代码中的include复制到项目目录下，修改MakeList.txt文件

每次新加.c文件之后，在CMakeList上点击reload一下。


# APUE

## 1. unix基础知识

### 1.2 Unix体系

内核的接口被称为系统调用。公用函数库构建在系统调用接口之上。shell和公共函数都能直接进行系统调用，
应用程序可以直接进行系统调用，也可以使用shell和公共函数库里的函数，从而间接进行系统调用。

### 1.3 登录

shell是一个命令行解释器，它读取用户输入然后执行命令。shell的用户输入通常来自于终端（交互式shell），
有时则来自于文件（称为shell脚本）。

### 1.4 文件和目录

除了斜线(/)和空格之外，都可以用于文件名；由斜线分隔的多个文件名构成路径名。

```
//输入目录名，输出目录下一级文件名和目录名
ls1.c
```



### 1.5 输入输出

每当运行一个新程序的时候，所有的shell都会为其打开三个文件描述符，即标准输入、标准输出和标准错误.

函数open、 read、 write、 lseek以及close提供了不带缓冲的I/O。 这些函数都使用文件描述符。

按照字节读取和写入，借助于缓冲区。标准I/O函数为那些不带缓冲的I/O函数提供了一个带缓冲的接口。

```echo.c
//按照字符读取和写入
getcputc.c
```

### 1.6 程序和进程

程序（program）是一个存储在磁盘上某个目录中的可执行文件。内核使用exec函数将程序读入内存并执行程序。

UNIX系统确保每个进程都有一个唯一的数字标识符，称为进程ID，进程ID总是一个非负整数。

```c
getpid.c
//获得进程ID
```

有三个用户进程控制的主要函数：fork、exec和waitpid。

```
process.c
```

### 1.7 出错处理

当UNIX系统函数出错时通常会返回一个负值，而且整型变量errno通常被设置为具有特定信息的值。
而有些函数对于出错则使用另一种约定而不是返回负值，比如返回null指针。

对于errno是一个左值，可以使一个整形或是一个函数指针。

对于errno，第一条规则是：如果没有出错其值不会被例程清除。因此仅当函数的返回值指明出错时才检验其值。
第二条规则是：任何函数都不会将errno值设置为0，而且在<errno.h>中定义的所有常量都不为0。

```c
//perror.c
strerror(EAGAIN); //将错误码映射为信息
perror(argv[0]);  //打印当前errno对应的错误信息
```

致命性错误：无法恢复
非致命错误：通常是临时错误，比如资源问题

### 1.8 用户标识

用户ID为0的用户为根用户.

```
//获取用户ID，组ID
getuid(), getgid()
```

### 1.9 信号

信号通知进程发生了事件。进程处理信号的方式：

1. 忽略， 2. 按照系统默认方式， 3.调用预设函数

```c
//捕捉信号
signal.c
```

### 1.10  时间

时间类型：日历时间，进程时间

进程时间包括：
时钟时间又称为墙上时钟时间（wall clock time），它是进程运行的时间总量。
用户CPU时间是执行用户指令所用的时间量。系统CPU时间是为该进程执行内核程序所经历的时间。

### 1.11 系统调用

在Unix中为每个系统调用在标准C库中设置一个具有同名的函数。用户进程用标准C调用序列来调用这些函数，
然后，函数又用系统所要求的技术调用相应的内核服务。

从实现者的角度来看，系统调用和库函数之间有根本的区别，但从用户角度来看其区别并不重要。

系统调用提供最小接口，而库函数可以更复杂。

## 2. unix标准和实现

### 2.1 标准化

ISO C  C程序设计语言标准

POSIX指的是可移植操作系统接口(Portable Operating System Interface）。该标准的目的是提升应
用程序在各种UNIX系统环境之间的可移植性。

Single UNIX Specification（SUS，单一UNIX规范）是POSIX.1标准的一个超集。 它定义了一些附加接口，扩展了POSIX.1规范提供的功能。POSIX.1相当于Single UNIX Specification中的基本规范部分

### 2.2 实现

对标准的实现有多种，比如Free BSD, Mac OS, Linux, Solaris等

标准中规定了一些限制，包括编译时限制和运行时限制，比如类型范围等

### 2.3 限制

UNIX 系统实现定义了很多幻数和常量， 其中有很多已被硬编码到程序中或用特定的技术确定。 由于大量标准化工作的努力， 已有若干种可移植的方法用以确定这些幻数和具体实现定义的限制。 这非常有助于改善UNIX环境下软件的可移植性。

以下两种类型的限制是必需的。
（1） 编译时限制（例如， 短整型的最大值是什么？）
（2） 运行时限制（例如， 文件名有多少个字符？）

编译时限制可在头文件中定义。 程序在编译时可以包含这些头文件。 但是 运行时限制则要求进程调用一个函数获得限制值。

## 3. 文件IO

### 3.2 文件描述符

对于内核而言，所有打开的文件都通过文件描述符引用。文件描述符是一个非负整数。

例子: 0表示stdin, 1表示stdout, 2表示stderr.

文件描述符的变化范围是0～OPEN_MAX-1，早期是19，即允许每个进程打开19个文件。对很多系统来说，文件描述符范围是无限的。

### 3.3 open和openat

调用open或openat函数可以打开或创建一个文件。

```c
 int open(const char *path, int oflag, ...);
 int openat(int fd, const char *path, int oflag, ...);

//如果path参数指定的是绝对路径名， 在这种情况下fd参数被忽略， openat函数就相当于open函数。
//path参数指定的是相对路径名，则openat要传入fd参数， fd参数是通过打开相对路径名所在的目录来获取。
//path参数指定了相对路径名， fd参数具有特殊值AT_FDCWD。 在这种情况下， 路径名在当前工作目录中获取。
```

### 3.4 create

基本不用，等价于

```c
open(path, O_WRONLY｜ O_CREAT｜ O_TRUNC, mode) //O_WRONLY 只读打开，O_CREAT 不存在就创建，O_TRUNC 文件清空
```

### 3.5 lseek

每个打开文件都有一个偏移量，通常是一个非负整数，表示从文件开始处计算的字节数。 读、写操作通常都从当前文件偏移量处开始， 并使偏移量增加所读写的字节数。

lseek显式地为一个打开文件设置偏移量，如果设置失败返回-1。

```c
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence)
/*whence指定偏移基准
  SEEK_SET   从开头
  SEEK_CUR  从当前
  SEEK_END  从结尾
  */
```

文件偏移量可以大于文件的当前长度， 在这种情况下 对该文件的下一次写将加长该文件， 并在文件中构成一个空洞，空洞内容被置为0.

例子

```c
//offset.c
#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefg";
char buf2[] = "ABCDEFG";

int main(void) {
char *file = "huahua3.txt";
int fd;

//以读写方式打开文件，若不存在则创建文件，文件权限wr
if ((fd = open(file, O_RDWR | O_CREAT, 0600)) == -1)
err_sys("open error");

//向文件中写入数据长度10
if (write(fd, buf1, 10) == -1)
err_sys("write error");

//将当前位置定位到16384
lseek(fd, 16384, SEEK_SET);

//向文件中写入数据
if (write(fd, buf2, 10) == -1)
err_sys("write error");

exit(0);
}
```

验证空洞

```
ls -l huahua3.txt  //查看文件大小
od -c huahua3.txt //以字符格式打印内容
```



### 3.6 read

```
ssize_t read(int, void *, size_t) 
```

可能有多种原因使读取的字节少于指定大小。返回结果可能是

- 读取成功，返回读物字节数
- 文件到达结尾，返回0
- 读取失败，返回-1

### 3.7 write

```
ssize_t write(int __fd, const void *__buf, size_t __nbyte)
```

向文件写入指定大小数据，返回实际写入大小。

读写操作的例子

```c
#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 128

int main(void) {
char *file = "huahua.txt";
char *file2 = "huahua2.txt";
char *dir = "./";
int fd;
int dir_fd;

char buf[BUFFSIZE];
char *msg = "hello, huahua!";
ssize_t read_bytes;

//以读写方式打开文件，若不存在则创建文件，文件权限wr
if ((fd = open(file, O_RDWR | O_CREAT, 0600)) == -1)
err_sys("open error");

//向文件中写入数据
if (write(fd, msg, strlen(msg)) == -1)
err_sys("write error");
//将当前位置定位到开头
lseek(fd, 0, SEEK_SET);
//读取文件内容，写入控制台
while ((read_bytes = read(fd, buf, strlen(msg))) > 0) {
if (write(STDOUT_FILENO, buf, read_bytes) != read_bytes)
err_sys("write error");
}

if (read_bytes < 0)
err_sys("read error");

//使用打开目录
if ((dir_fd = open(dir, O_RDONLY)) == -1)
err_sys("open error");
//openat 打开目录中的文件
int fd2 = openat(dir_fd, file2, O_RDWR|O_CREAT, 0600);
if (fd2 == -1)
err_sys("openat error");

//向文件中写入数据
if (write(fd2, msg, strlen(msg)) == -1)
err_sys("write error");
//将当前位置定位到开头
lseek(fd2, 0, SEEK_SET);
//读取文件内容，写入控制台
while ((read_bytes = read(fd2, buf, strlen(msg))) > 0) {
if (write(STDOUT_FILENO, buf, read_bytes) != read_bytes)
err_sys("write error");
}

exit(0);
}
```



### 3.8 IO效率

缓冲区的大小影响IO效率。当缓冲区达到磁盘块大小时，系统CPU时间最小；由于文件的预读取机制，缓冲区达到32字节之后，进行顺序读取的时钟时间都相差不大。

### 3.9 文件相关数据结构

内核使用三种数据结构描述一个打开的文件

- 每个进程在进程表中都有一个记录项， 记录项中包含一张打开文件描述符表（文件描述符标志，文件表指针）。
- 内核为所有打开文件维持一张文件表（文件状态标志，偏移量，v节点指针）。
- 每个打开文件或设备都有一个 v 节点结构（文件的具体信息）。

```
打开该文件的每个进程都获得各自的一个文件表项， 但对一个给定的文件只有一个v节点表项。每个进程维护自己的偏移量。

可能有多个文件描述符指向同一个文件表项，就是多个进程共享一个文件。
```

### 3.10 原子操作

由于通常每个进程维护自己的偏移量，定位+读写，两个动作经常需要保持原子执行，否则在多进程下会带来意外结果。

APPEND，在打开文件时指定，能够在每次写的时候自动定位到结尾，而不需要显式调用lseek

pread，pwrite，在执行读取时指定位置并且不会修改文件偏移量。

```c
ssize_t pread(int d, void *buf, size_t nbyte, off_t offset);
```



### 3.11 复制文件描述符

```c
dup(fd)   //生成一个文件描述符和fd指向同一个文件表项，返回的一定是进程未使用的最小的文件描述符
dup2(fd1, fd2)  //使fd2指向fd1, 返回文件描述符和fd1指向同一个文件表项。如果fd1和fd2相等，直接返回fd2; 如果fd2是打开的文件，则先关闭fd2
```

例子

```c
#include "apue.h"

int main(void) {
FILE *fp;
int fd;
//生成fd，指向stdout
fd = dup(fileno(stdout));

printf("该文本重定向到 stdout\n");
fflush(stdout);

//重新打开stdout, 关联到file.txt，原来的stdout被关闭了
fp = freopen("file.txt", "a", stdout);
printf("该文本重定向到 file.txt\n");
fflush(fp);

//把新的stdout指向保存的旧stdout,重定向回去
dup2(fd, fileno(stdout));
printf("该文本重定向到 stdout\n");

exit(0);
}
```

### 3.12 刷新缓存

当我们向文件写入数据时， 内核通常先将数据复制到缓冲区中， 然后排入队列， 晚些时候再写入磁盘。 这种方式被称为延迟写.

sync,  fsync, fdatasync 用来通知系统进行缓存刷新，把缓存中的数据写入磁盘。不过作用的对象和使用场景不同。



### 3.13  fcntl和ioctl

内容太杂乱了，先空着。

fcntl函数可以改变已经打开文件的属性。

ioctl函数一直是I/O操作的杂物箱。 









