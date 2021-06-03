# APUE

## 0. 配置环境

**准备工作**

IDE： clion 2020.3  mac

编译工具： cmake

源代码下载：http://www.apuebook.com/  选择对应版本下载源代码

**创建项目**

1. clion创建c项目

2. 将源代码中的include和lib复制到项目根目录下
3. 修改MakeLists.txt文件

```cmake
cmake_minimum_required(VERSION 3.12)

#获取项目目录名称
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)

message(${ProjectId})

project(${ProjectId} C)

set(CMAKE_C_STANDARD 99)

#添加所有依赖头文件
include_directories(../include)

#把所有c文件添加到files
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

foreach(file ${files})
    get_filename_component(name ${file} NAME)
    string(REPLACE ".c" "" name ${name})
    #添加到可执行文件中，把lib中用到的一些c文件添加到后面
    add_executable(${name} ${file} ../include/error.c
            ../lib/clrfl.c ../lib/setfl.c
            ../lib/tellwait.c ../lib/lockreg.c) 
endforeach()
```

4. 右键CMakeLists.txt选择Load CMake Project；每次新加.c文件之后，在CMakeList上点击reload一下



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



## 4. 文件和目录

### 4.2 stat

stat/lstat函数返回文件的信息结构体stat。st_mode中包含了文件的格式信息。

例子

判断文件或目录类型

```c
#include "apue.h"

int main(int argc, char *argv[]) {
    int i;
    struct stat s;
    char *ptr;

    for (i = 1; i < argc; i++) {
        if (lstat(argv[i], &s) == -1)
            err_sys("lstat error");

        if (S_ISREG(s.st_mode)) {
            ptr = "regular file";
        } else if (S_ISDIR(s.st_mode)) {
            ptr = "directory";
        } else if (S_ISLNK(s.st_mode)) {
            ptr = "link";
        } else if (S_ISCHR(s.st_mode)) {
            ptr = "character";
        } else if (S_ISBLK(s.st_mode)) {
            ptr = "block";
        } else {
            ptr = "unknown type";
        }
        printf("%s is %s\n", argv[i], ptr);
    }
}
```

### 4.3 设置用户ID组ID

ID分类

```
实际用户ID组ID   表示我们实际是谁
有效用户ID组ID  用于文件权限检查
保存用户ID组ID  由exec保存
```

通常， 有效用户ID等于实际用户ID， 有效组ID等于实际组ID。

可以通过设置st_mode中的标志位，在进程执行文件时将有效用户ID组ID修改为文件所有者的用户ID组ID，从而使执行文件的进程拥有超过进程本身的权限。



### 4.4 文件访问权限

st_mode值也包含了对文件的访问权限位。分为用户（所有者）权限位，组权限位，其他用户权限位。

对文件的权限比较好理解。对目录的读权限允许我们获得在该目录中所有文件名的列表。对目录的执行权限使我们可进入该目录，访问目录中的文件。为了在一个目录中创建或删除一个文件， 必须对该目录具有写权限和执行权限。

访问文件的时候都会进行权限校验。对比文件的权限属性和进程的有效用户ID和组ID。

- 若有效用户ID为0，则允许访问
- 有效用户ID等于文件所有者ID，且权限位满足设置
- 有效组ID属于文件组ID，且权限位设置满足
- 其他用户权限位设置满足



### 4.5 新文件和目录所有权

新文件目录的所有者ID是当前进程的有效用户ID，组ID可以是进程的有效组ID，可以是当前目录的组ID。在mac下默认是后者，Linux下取决于目录的设置组ID位是否被设置。

```
查看有效用户ID，组ID
查看文件ID
```



### 4.6 access和faccessat

使用实际用户ID和组ID检验文件权限

```c
#include "apue.h"
#include "fcntl.h"

int main(void) {
    int fd;
    char *file = "huahua.txt";

    //以只读打开
    if ((fd = open(file, O_RDONLY|O_CREAT, 0400)) == -1)
        err_sys("open error");
    else
        printf("open good");
  //没有写权限
    if (access(file, W_OK) < 0)
        err_sys("can not write");
    else
        printf("write access good");

    close(fd);

  //以读写权限打开
    if ((fd = open(file, O_RDWR)) == -1)
        err_sys("open error");
    else
        printf("open with write ok");

  //可写
    if (access(file, W_OK) < 0)
        err_sys("can not write");
    else
        printf("write access ok");

     exit(0);
}
```



### 4.7 umask 权限屏蔽

每个进程都有一个文件模式创建屏蔽字，在进程创建一个新文件或新目录时一定会使用文件模式创建屏蔽字指定哪些权限被关闭。

umask 函数为进程设置文件模式创建屏蔽字。



### 4.8 chmod

chmod、 fchmod和fchmodat这3个函数使我们可以更改现有文件的访问权限。

```c
int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int fd, const char *pathname, mode_t mode, int flag);
```

为了改变一个文件的权限位， 进程的有效用户ID必须等于文件的所有者ID， 或者该进程必须具有超级用户权限。

例子

```c
#include "apue.h"
#include "fcntl.h"
int main(void) {
    char *file1 = "huahua1.txt";
    char *file2 = "huahua2.txt";
    
    //设置新生成的文件为rwxrwxrwx
    umask(0);
    if ((open(file1, O_RDONLY|O_CREAT, 0777)) == -1)
        err_sys("open error");
    else
        printf("open good");

    //设置新生成文件为rwx--x--x
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

    if ((open(file2, O_RDONLY|O_CREAT, 0777)) == -1)
        err_sys("open error");
    else
        printf("open with write ok");

    //修改file1为rw-r--r--
    chmod(file1, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    exit(0);
}
```

### 4.9 黏着位

S_ISVTX 黏着位，是为了让文件保留在交换区提高可执行程序的执行效率。设置了黏着位的目录，只有对目录有写权限并且拥有此文件/拥有此目录/是超级用户，才能删除或重命名目录下的文件。



### 4.10 修改文件所有者

```
#include <unistd.h>
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int fchownat(int fd, const char *pathname, uid_t owner, gid_t group, int flag)
```

基于BSD的系统一直规定只有超级用户才能更改一个文件的所有者。 这样做的原因是防止用户改变其文件的所有者从而摆脱磁盘空间限
额对他们的限制。 System V则允许任一用户更改他们所拥有的文件的所有者。



### 4.11 文件长度

stat结构成员st_size表示以字节为单位的文件的长度。 此字段只对普通文件、 目录文件和符号链接有意义。

对于目录， 文件长度通常是一个数（如16或512） 的整倍数.

对于符号链接， 文件长度是在文件名中的实际字节数。

```
du -s file //文件占用的512字节块的块数
ls -l file //显示实际字节数
```

对于含有空洞的文件会看到ls出来的大小更大。如果使用io对文件进行复制，空洞会被填满为0，du的大小变大。



### 4.12 截断文件

```c
#include <unistd.h>
int truncate(const char *pathname, off_t length);
int ftruncate(int fd, off_t length)
```

把给定文件截断为指定长度，如果length大于实际长度还会扩展。



### 4.13 HFS文件系统

文件系统的层次：

```
磁盘的每个分区可以包含一个单独的文件系统。
文件系统由自举块，超级块和多个柱面组构成。
柱面组内包括多个i节点和数据块。
```

从文件表目录项指向i节点的链接是硬链接。每个i节点中都有一个链接计数， 其值是指向该i节点的目录项数。 只有当链接计数减少至0时才可删除该文件。在stat结构中， 链接计数包含在st_nlink成员中。

符号链接文件的实际内容（在数据块中）包含了该符号链接所指向的文件的名字。

因为目录项中的i节点编号指向同一文件系统中的相应i节点， 一个目录项不能指向另一个文件系统的i节点。

目录文件的链接计数大于等于2，每个子目录都会增加一个链接计数。



### 4.14  link和unlink

任何一个文件可以有多个目录项指向其i节点。 创建一个指向现有文件的链接的方法是使用link函数或linkat函数。

```c
#include <unistd.h>
int link(const char *existingpath, const char *newpath);
int linkat(int efd, const char *existingpath, int nfd, const char *newpath, int flag)
```

这两个函数创建一个新目录项newpath，它引用现有文件existingpath。



为了删除一个现有的目录项， 可以调用unlink函数。

```c
#include <unistd.h>
int unlink(const char *pathname);
int unlinkat(int fd, const char *pathname, int flag);
```

这两个函数删除目录项，并将由pathname所引用文件的链接计数减1。为了解除对文件的链接，必须对包含该目录项的目录具有写和执行权限。

给出符号链接名的情况下，没有一个函数能删除由该链接所引用的文件。

例子

```c
#include "apue.h"
#include "fcntl.h"

int main(void) {
    char *file = "huahua.txt";
    char *file2 = "huahua2.txt";
    int fd;
    char buf[] = "hello world";

    if ((fd = open(file, O_RDWR|O_CREAT, 0600)) == -1)
        err_sys("open error\n");

    if (write(fd, buf, strlen(buf)) < 0)
        err_sys("write error\n");
    printf("open done\n");

    sleep(5);
    //复制file->file2
    if (link(file, file2) == -1)
        err_sys("link error\n");
    else
        printf("link done\n");

    sleep(5);
    //删除file2
    if (unlink(file2) == -1)
        err_sys("unlink error\n");
    else
        printf("unlink file done\n");

    sleep(5);
    //删除file
    if (unlink(file) == -1)
        err_sys("unlink error\n");
    else
        printf("unlink file2 done\n");

    sleep(5);
    printf("done\n");
    exit(0);
}
```

关闭文件的条件：

- 打开该文件的进程个数为0
- 文件的链接计数为0

我们也可以用 remove函数解除对一个文件或目录的链接。对于文件，remove 的功能与unlink相同。 对于目录，remove的功能与rmdir相同。



### 4.15 重命名

文件或目录可以用rename函数或者renameat函数进行重命名。

```c
#include <stdio.h>
int rename(const char *oldname, const char *newname);
int renameat(int oldfd, const char *oldname, int newfd, const char *newname);
```

在重命名时根据oldname是目录还是文件，newname已经存在是否，有不同的操作。

oldname是文件，newname若存在必须是文件，则先删除new目录项再重命名。

oldname是目录，newname如果存在必须是个空目录，会删除new目录然后重命名。

不能对.和..重命名。



### 4.16 符号链接

硬链接直接指向文件的i节点，硬链接通常要求链接和文件位于同一文件系统中，只有超级用户才能创建指向目录的硬链接。

对符号链接以及它指向何种对象并无任何文件系统限制，任何用户都可以创建指向目录的符号链接。 符号链接一般用于将一个文件或整个目录结构移到系统中另一个位置。

一些函数会跟随符号链接到达它所链接的文件。



### 4.17 创建和读取符号链接

创建符号链接的源路径不一定存在；读取符号链接拿到实际路径名称。

```c
#include "apue.h"

int main(void) {
    char buf[1024];
    int len;
    char* actualPath = "~/bin2";
    char* symPath = "fakebin";
    if (symlink(actualPath, symPath) == -1) {
        err_sys("link error");
    }
    if ((len = readlink(symPath, buf, 1024)) == -1) {
        err_sys("read link error");
    }
    buf[len] = '\0';
    printf("%s", buf);
    exit(0);
}
```



### 4.18  文件时间

每个文件维护三个时间，最近访问时间（st_atim），修改时间（st_mtim）和状态更改时间（st_ctim）。

修改时间是文件内容最后一次被修改的时间。 状态更改时间是该文件的i节点最后一次被修改的时间。修改文件权限，所有者都只修改i节点状态，没有修改内容。



### 4.19 mkdir和rmdir

```c
int mkdir(const char *pathname, mode_t mode);int mkdirat(int fd, const char *pathname, mode_t mode);
```

对于目录通常至少要设置一个执行权限位， 以允许访问该目录中的文件名。

基于BSD的系统中，新创建的文件和目录总是继承父目录的组ID， 这与是否设置了设置组ID位无关。

用rmdir函数可以删除一个空目录。 空目录是只包含.和..这两项的目录。

```c
#include <unistd.h>int rmdir(const char *pathname);
```

如果调用此函数使目录的链接计数成为 0， 并且也没有其他进程打开此目录， 则释放由此目录占用的空间。 如果在链接计数达到0时， 有一个或多个进程打开此目录， 则在此函数返回前删除最后一个链接及.和..项。 另外，在此目录中不能再创建新文件。



### 4.20 读目录

只有内核才能写目录。

一个目录的写权限位和执行权限位决定了在该目录中能否创建新文件以及删除文件，它们并不表示能否写目录本身。

目录的实际格式依赖于 UNIX 系统实现和文件系统的设计。 系统提供了接口用于屏蔽底层的具体实现。

```c
DIR *opendir(const char *pathname);DIR *fdopendir(int fd);
```



### 4.21 工作目录

每个进程都有一个当前工作目录， 此目录是搜索所有相对路径名的起点。

修改当前进程的工作目录。

```c
#include <unistd.h>int chdir(const char *pathname);
```

获得当前目录的绝对路径

```c
#include <unistd.h>char *getcwd(char *buf, s i z e_t size);
```

```c
int main(void) {    char buf[1024];    getcwd(buf, 1024);    printf("%s\n", buf);    if(chdir("/Users/lifan/VmShare/APUE/APUE/4_file_and_directory") < 0) {        err_sys("chdir error");    }    getcwd(buf, 1024);    printf("%s\n", buf);    exit(0);}
```



### 4.23 设备文件

每个文件系统所在的存储设备都由其主、 次设备号表示。设备号所用的数据类型是基本系统数据类型dev_t。主设备号标识设备驱动程序，有时编码为与其通信的外设板；次设备号标识特定的子设备。



## 5. IO

### 5.1 流和FILE

所有I/O函数都是围绕文件描述符的。 当打开一个文件时， 即返回一个文件描述符， 然后该文件描述符就用于后续的I/O操作。而对于标准I/O库， 它们的操作是围绕流（stream） 进行的。

标准I/O文件流可用于单字节或多字节（“宽” ）字符集。 流的定向决定了所读、写的字符是单字节还是多字节的，这取决于流打开之后的初始IO函数。fwide函数可用于对未定向的流设置定向。

当打开一个流时标准I/O函数fopen返回一个指向FILE对象的指针。



### 5.2 缓冲

标准I/O库提供缓冲的目的是尽可能减少使用read和write调用的次数。

标准I/O提供了以下3种类型的缓冲：

（1）全缓冲。在填满缓冲区之后才进行IO操作。对磁盘上的文件时通常使用全缓冲。在标准I/O库方面，调用fflush可以刷新缓冲区，把缓冲区内的内容写入磁盘。

（2）行缓冲。当在输入和输出中遇到换行符时，标准I/O库执行I/O操作。由于行缓冲的缓冲区大小是固定的，所以如果超过缓冲区也会进行刷新。

（3）不缓冲。立刻输出。

通常来说：标准错误不带缓冲；若是指向终端设备的流，则是行缓冲的； 否则是全缓冲。

setvbuf可以设置缓冲类型。_IOFBF



### 5.3 打开流

打开文件流返回的都是FILE指针。打开类型使用w, r, a, +等描述符，b表示二进制打开，在unix系统中b没有作用。除非流引用终端设备， 否则按系统默认， 流被打开时是全缓冲的。若流引用终端设备， 则该流是行缓冲。

```c
#include <stdio.h>//按照文件名打开文件FILE *fopen(const char *restrict pathname, const char *restrict type);//重定向文件流到新的文件FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);//从fd打开文件流FILE *fdopen(int fd, const char *type);
```

关闭文件流使用fclose。在文件被关闭之前， 冲洗缓冲中的输出数据， 缓冲区中的任何输入数据被丢弃。 如果标准I/O库已经为该流自动分配了一个缓冲区， 则释放此缓冲区。

当一个进程正常终止时，所有带未写缓冲数据的标准I/O流都被冲洗，所有打开的标准I/O流都被关闭。



### 5.4 读和写流

三种读和写流的方式

```c
1. 每次一个字符的IO，getc, putc2. 每次一行的IO，gets, puts3. 以二进制直接IO, fwrite, fread
```

**读取字符**

```c
#include <stdio.h>int getc(FILE *fp);int fgetc(FILE *fp);int getchar(void);
```

函数getchar等同于getc(stdin)。 前两个函数的区别是，getc可被实现为宏，而fgetc不能实现为宏。 返回整型的理由是要返回所有可能的字符值再加上一个已出错或已到达文件尾端的指示值。

**出错标志**

在<stdio.h>中的常量EOF被要求是一个负值， 其值经常是−1。无论是出错还是到达末尾都返回同一个值，使用函数判断。

```c
#include <stdio.h>int ferror(FILE *fp);int feof(FILE *fp);
```

从流中读取数据以后， 可以调用ungetc将字符再压送回流中。一次成功的ungetc调用会清除该流的文件结束标志。

**写字符**

```c
#include <stdio.h>int putc(int c, FILE *fp);int fputc(int c, FILE *fp);int putchar(int c);
```



### 5.5 按行IO

**读**

```c
char *fgets(char *restrict buf, int n， FILE *restrict fp);char *gets(char *buf);
```

两个区别

1. fgets必须指定缓冲的长度n，一直读取到下一个换行符。缓冲区始终以null结尾，gets读取时没有指定长度，可能会造成缓冲区溢出。
2. gets并不将换行符存入缓冲区中。

**写**

```c
#include <stdio.h>int fputs(const char *restrict str, FILE *restrict fp);int puts(const char *str);
```

两个区别

1. 函数fputs将一个以null字节终止的字符串写到指定的流。
2. puts最后会将一个换行符写到标准输出。



### 5.5 IO效率

对比getc, fgetc, fgets, read：

系统CPU时间几乎相同，原因是因为所有这些程序对内核提出的读、写请求数基本相同。标准IO会自己决定最佳IO长度。

用户CPU时间相差很多，和函数调用次数有关。fgets会比fgetc快。调用同样次数的read和fgetc，前者的时间更久。因为前者每次都是系统调用，而后者系统调用次数更少。系统调用与普通的函数
调用相比需要花费更多的时间。



### 5.6 二进制IO

因为按照按字符或行读取有很多限制，不适合复杂的结构体的读写。

```c
#include <stdio.h>size_t fread(void *restrict ptr, size_t size, size_t nobj,FILE *restrict fp);size_t fwrite(const void *restrict ptr, size_t size,size_t nobj, FILE *restrict fp);
```

使用二进制I/O的基本问题是， 它只能用于读在同一系统上已写的数据。对不同系统之间的IO，比如网络IO需要借助互认的某种协议。



### 5.7 定位流

```c
#include <stdio.h>long ftell(FILE *fp); //返回值： 若成功， 返回当前文件位置指示； 若出错， 返回-1Lint fseek(FILE *fp, long offset, int whence); //返回值： 若成功， 返回0； 若出错， 返回−1void rewind(FILE *fp); //重新定位到开头
```



### 5.8  格式化IO

**格式化输出**

```c
#include <stdio.h>int printf(const char *restrict format, ...);
```

printf将格式化数据写到标准输出，fprintf写至指定的流，dprintf写至指定的文件描述符，sprintf 将格式化的字符送入数组buf中。sprintf在该数组的尾端自动加一个 null字节， 但该字符不包括在返回值中。

**格式化输入**

```c
#include <stdio.h>int scanf(const char *restrict format, ...);
```



### 5.9 临时文件

下面的函数创建可用的临时路径名，然后创建临时文件。临时文件在关闭或程序退出时自动删除。

```c
#include<stdio.h>char *tmpnam(char *ptr);FILE *tmpfile(void);
```

下面的方式创建，临时文件不会自动删除。

```c
mkdtemp和mkstemp
```



### 5.10 内存流

所有的I/O都是通过在缓冲区与主存之间来回传送字节来完成。

创建者提供缓冲区用于内存流。

```c
#include <stdio.h>FILE *fmemopen(void *restrict buf, size_t size, const char *restrict type)
```

一些特性：

1. 以追加方式打开时，总是定位到第一个null字节位置，或者最后一个字节。
2. 以非追加方式打开时，定位到第一个字节。
3. 如果buf是null，任何操作都没有意义。
4. 任何时候需要增加流缓冲区中数据量以及调用fclose、fflush、 fseek、 fseeko以及fsetpos时都会在当前位置写入一个null字节。

内存流只在linux上支持，在mac上运行结果不同。



## 7. 进程环境

### 7.1 main函数

在调用main前先调用一个特殊的启动例程，可执行程序文件将此启动例程指定为程序的起始地址。启动例程从内核取得命令行参数和环境变量值， 然后调用main函数。

### 7.2 进程终止

**正常终止**

```c
（1） 从main返回；（2） 调用exit；（3） 调用_exit或_Exit；（4） 最后一个线程从其启动例程返回（5） 从最后一个线程调用pthread_exit
```

\_exit和\_Exit立即进入内核， exit则先执行一些清理处理，对于所有打开流调用fclose函数，然后返回内核。

**返回值**

退出函数都带一个整型参数，称为终止状态。

如果调用这些函数时不带终止状态， 或main执行了一个无返回值的return语句，或main没有声明返回类型为整型，则该进程的终止状态是未定义的。

**函数atexit**

```c
#include <stdlib.h>int atexit(void (*func)(void));
```

exit调用这些函数的顺序与它们登记时候的顺序相反。 同一函数如若登记多次， 也会被调用多次。

**异常终止**

```
（6） 调用abort（7） 接到一个信号（8） 最后一个线程对取消请求做出响应
```



### 7.3 命令行参数

当执行一个程序时，调用exec的进程可将命令行参数传递给该新程序。

```c
#include <stdio.h>#include <stdlib.h>int main(int argc, char* argv[]) {    for (int i = 0; i < argc; ++i) {        printf("%d, %s\n", i, argv[i]);    }    exit(0);}
```

### 7.4 环境表

每个程序都接收到一张环境表，环境表也是一个字符指针数组，其中每个指针包含一个以null结束的C字符串的地址。全局变量environ则包含了该指针数组的地址。



### 7.5 C程序的存储空间布局

c程序的组成：

- 正文段。这是由CPU执行的机器指令部分，是可以共享的和只读的。
- 初始化数据段，也叫数据段，包含了程序中需明确地赋初值的变量。 指定了初值。
- 未初始化数据段。在程序开始前内核将此段中的数据初始化为0或空指针。 未指定初值。
- 栈。 自动变量以及每次函数调用时所需保存的信息都存放在此段中。
- 堆。 通常在堆中进行动态存储分配。

栈地址从高到低，堆地址从低到高。未初始化数据段的内容并不存放在磁盘程序文件中。需要存放在磁盘程序文件中的段只有正文段和初始化数据段。

从高地址到低地址

```
命令行参数和环境变量栈|堆未初始化数据段（bss）  --由exec初始化为0初始化数据段  --exec从程序文件读取正文
```

size命令报告正文段、 数据段和bss段的长度。



### 7.6 共享库

共享库使得可执行文件中不再需要包含公用的库函数，而只需在所有进程都可引用的存储区中保存这种库例程的一个副本。

程序第一次执行或者第一次调用某个库函数时，用动态链接方法将程序与共享库函数相链接。 这减少了每个可执行文件的长度，但增加了一些运行时间开销。



### 7.7 存储空间分配

三种分配方式

- malloc，分配指定字节数的存储区。 此存储区中的初始值不确定。
- calloc，为指定数量指定长度的对象分配存储空间。 该空间中的每一位都初始化为0。
- realloc，增加或减少以前分配区的长度。新增区域内的初始值则不确定。

这3个分配函数所返回的指针一定是适当对齐的，使其可用于任何数据对象。

### 7.8 环境变量

环境变量操作函数

```c
#include <stdlib.h>char *getenv(const char *name);int putenv(char *str);int setenv(const char *name, const char *value, int rewrite);int unsetenv(const char *name);
```

由于环境变量位于栈顶，所以在增加和修改环境变量时，可能需要再堆上重新分配空间。



### 7.9 栈帧跳转

goto语句是不能跨越函数的, 使用函数setjmp和longjmp能实现更深层次的跳转。

每个进程都有一组资源限制， 其中一些可以用getrlimit和setrlimit函数查询和更改。



## 8. 进程控制

### 8.1 进程标识

每个进程都有一个非负整型表示的唯一进程ID。进程ID是可重用的。

ID为 0的进程通常是调度进程，常常被称为交换进程（swapper）。 该进程是内核的一部分，它并不执行任何磁盘上的程序。
ID 1通常是init进程， 在自举过程结束时由内核调用。

```c
#include <stdio.h>#include <stdlib.h>#include <unistd.h>int main(int argc, char* argv[]) {    printf("%d\n", getpid());    printf("%d\n", getppid());    printf("%d\n", getuid());    printf("%d\n", geteuid());    printf("%d\n", getgid());    printf("%d\n", getegid());    exit(0);}
```



### 8.2 fork

一个现有的进程可以调用fork函数创建一个新进程。子进程获得父进程数据空间、堆和栈的副本。 父进程和子进程共享正文段。

作为优化，某些实现中不完全创建副本，使用写时复制技术。父进程和子进程共享这些区域，但是如果任一个试图修改这些区域，则内核只为修改区域的那块内存制作一个副本。

例子

```c
#include "apue.h"int globalvar = 6;char buf[] = "hello, huahua\n";int main(void) {    int var;    pid_t pid;    var = 88;    if (write(STDOUT_FILENO, buf, sizeof(buf) -1) != sizeof(buf) - 1) //sizeof包含了最后的null        err_sys("write error");    printf("before fork\n");    //写入缓冲区，如果是在shell运行是行缓冲，被换行符刷新；    // 如果是写入到文件是全缓冲，不会刷新，缓冲内容会带到子进程    if ((pid = fork()) < 0)        err_sys("fork error");    else if (pid == 0) {  //子进程        globalvar++;  //数据空间独立，只有子进程的变量会被修改        var++;    } else {  //父进程        sleep(2);    }    printf("pid: %d, global var: %d, var: %d\n", pid, globalvar, var);    exit(0);}
```



父进程和子进程每个相同的打开描述符共享一个文件表项。父进程和子进程共享同一个文件偏移量。

在fork之后处理文件描述符的方式：

- 在fork之后处理文件描述符
- 父进程和子进程各自关闭它们不需使用的文件描述符

使fork失败的两个主要原因：

- 系统中已经有了太多的进程
- 该实际用户ID的进程总数超过了系统限制。

fork有以下两种用法：

- 一个父进程希望复制自己， 使父进程和子进程同时执行不同的代码段。
- 一个进程要执行一个不同的程序。

### 8.3 vfork

vfork与fork一样都创建一个子进程，但是它并不将父进程的地址空间完全复制到子进程中，因为子进程会立即调用exec或exit。

在子进程调用exec或exit之前，它在父进程的空间中运行。

vfork保证子进程先运行，在它调用exec或exit之后父进程才可能被调度运行。

```c
#include "apue.h"int globalvar = 6;int main(void) {    int var;    pid_t pid;    var = 88;    printf("before fork\n");    if ((pid = vfork()) < 0)        err_sys("fork error");    else if (pid == 0) {  //子进程        globalvar++;  //会修改父进程的数据        var++;        _exit(0); //退出时不会刷新缓冲区,如果同时关闭了fd，则不会输出任何内容    }    printf("pid: %d, global var: %d, var: %d\n", pid, globalvar, var);    exit(0);}
```



### 8.4 exit函数

进程终止的情况

```
（1） 从main返回；（2） 调用exit, 执行各种终止处理程序（3） 调用_exit或_Exit，不执行终止处理程序或信号处理程序（4） 最后一个线程从其启动例程返回。线程的返回值不是进程的终止值。（5） 从最后一个线程调用pthread_exit（6） 调用abort，它产生SIGABRT信号。（7） 接到一个信号，信号可由进程自身（如调用abort函数）、其他进程或内核产生（8） 最后一个线程对取消请求做出响应
```

不管进程如何终止，最后都会执行内核中的同一段代码。这段代码为相应进程关闭所有打开描述符，释放它所使用的存储器等。该终止进程的父进程都能用wait或waitpid函数取得其终止状态。

**孤儿进程**

对于父进程已经终止的所有进程，它们的父进程都改变为 init 进程。只要有一个子进程终止，init 就会调用一个wait函数取得其终止状态。所以init的子进程不会成为僵尸进程。

**僵尸进程**

一个已经终止、但是其父进程尚未对其进行善后处理（获取终止子进程的有关信息、释放它仍占用的资源）的进程被称为僵死进程（zombie）。



### 8.5 函数wait和waitpid

调用wait或waitpid的进程时：

- 如果其所有子进程都还在运行则阻塞。
- 如果一个子进程已终止，正等待父进程获取其终止状态，则取得该子进程的终止状态立即返回。
- 如果它没有任何子进程，则立即出错返回。

```c
#include "apue.h"#include "sys/wait.h"void pr_exit(int status) {    if (WIFEXITED(status))        printf("normal exit, exit status= %d\n", WEXITSTATUS(status));    else if (WIFSIGNALED(status))        printf("abnormal termination, signal number= %d%s\n", WTERMSIG(status),#ifdef WCOREDUMP                WCOREDUMP(status)? "core file exits" : "");#else               "");#endif    else if (WIFSTOPPED(status))        printf("child stopped, signal number = %d\n", WSTOPSIG(status));}int main(void) {    int status;    pid_t pid;    if ((pid = fork()) < 0)        err_sys("fork error");    else if (pid == 0)        exit(7);  //正常退出    if (wait(&status) != pid)        err_sys("wait error");    pr_exit(status);    if ((pid = fork()) < 0)        err_sys("fork error");    else if (pid == 0)        abort();  //异常退出    if (wait(&status) != pid)        err_sys("wait error");    pr_exit(status);    if ((pid = fork()) < 0)        err_sys("fork error");    else if (pid == 0)        status /= 0;  //异常退出    if (wait(&status) != pid)        err_sys("wait error");    pr_exit(status);    exit(0);}
```

waitpid通过指定pid设置不同选项。

```
pid > 0, 等待指定pidpid == -1 等待任一子进程pid == 0 等待组ID等于调用进程组ID的任一子进程pid < -1 等待组ID等于pid绝对值的任一子进程
```



### 8.6 竞争条件

fork之后执行的操作如果对子进程和父进程的执行顺序有要求，则会产生竞争条件。为了处理竞争条件，需要子进程和父进程之间通过信号传递。

例子1，进程竞争展示，输出的字符顺序可能会混乱。

```c
#include "apue.h"static void charatatime(char *);int main(void){    pid_t	pid;    if ((pid = fork()) < 0) {        err_sys("fork error");    } else if (pid == 0) {        charatatime("output from child,output from child,output from child,output from child,output from child,output from child,output from child\n");    } else {        charatatime("output from parent,output from parent,output from parent,output from parent,output from parent,output from parent,output from parent\n");    }    exit(0);}static void charatatime(char *str){    char	*ptr;    int		c;    setbuf(stdout, NULL);			/* set unbuffered */    for (ptr = str; (c = *ptr++) != 0; )        putc(c, stdout);}
```

添加同步控制

```c
#include "apue.h"static void charatatime(char *);int main(void){    pid_t	pid;    TELL_WAIT();    if ((pid = fork()) < 0) {        err_sys("fork error");    } else if (pid == 0) {        WAIT_PARENT();		/* parent goes first */        charatatime("output from child\n");    } else {        charatatime("output from parent\n");        TELL_CHILD(pid);    }    exit(0);}static void charatatime(char *str){    char	*ptr;    int		c;    setbuf(stdout, NULL);			/* set unbuffered */    for (ptr = str; (c = *ptr++) != 0; )        putc(c, stdout);}
```

这里用到的信号处理函数包含在time_wait.c中

```makefile
    #添加到可执行文件中    add_executable(${name} ${file} ../include/error.c            ../lib/tellwait.c)
```



### 8.7 exec函数

当进程调用一种exec函数时，该进程执行的程序完全替换为新程序，而新程序则从其main函数开始执行。

exec只是用磁盘上的一个新程序替换了当前进程的正文段、数据段、堆段和栈段。

```c
#include <unistd.h>
int execl(const char *pathname, const char *arg0, ... /*(char *)0 */ );
int execv(const char *pathname, char *const argv[]);
int execle(const char *pathname, const char *arg0, .../* (char *)0, char *const envp[] */ );
int execve(const char *pathname, char *const argv[], char *const envp[]);
int execlp(const char *filename, const char *arg0, ... /*(char *)0 */ );
int execvp(const char *filename, char *const argv[]);
int fexecve(int fd, char *const argv[], char *const envp[]);
```

有7种不同的exec函数，这7个函数中只有execve是内核的系统调用。不同之处在于：

- 可执行文件通过路径名/文件名/fd查找
- 参数列表传入方式的不同
- 传入环境表的方式不同

他们相互之间存在调用关系

```c
execlp->execvp->execv->execve
execl->execv->execve
execle->execve
fexecve->execve
```

例子

```c
#include "apue.h"#include <sys/wait.h>char* env_init[] = {"PATH=/tmp", "USER=UNKNOWN", NULL};int main(void) {    pid_t pid;    if ((pid = vfork()) < 0)        err_sys("fork error");    else if (pid == 0) {  //子进程        if (execle("./echoall", "echoall", "hello", "huahua", (char*)0, env_init) < 0)            err_sys("execle error");    }    if (waitpid(pid, NULL, 0) < 0)        err_sys("wait error");        if ((pid = vfork()) < 0)        err_sys("fork error");    else if (pid == 0) {        if (execlp("echoall", "achoall", "hello", "huahua", (char *)0) < 0)            err_sys("execlp error");    }    exit(0);}
```



### 8.8 解释器文件

就是解释器脚本文件，初始行的格式通常是

```
#! pathname [ optional-argument ]
```

pathname指定解释器路径。

内核使调用exec函数的进程实际执行的并不是该解释器文件，而是在该解释器文件第一行中pathname所指定的文件。

解释器文件的好处：

- 隐藏脚本文件的细节
- 提高执行效率。执行过程比较复杂。
- 允许使用其他shell来编写shell脚本。



### 8.9 system函数

system函数执行传入的命令，在其实现中调用了fork、exec和waitpid。使用system的优点是system进行了所需的各种出错处理以及各种信号处理。

```c
#include <stdlib.h>int system(const char *cmdstring);
```

例子

```c
#include <unistd.h>#include <sys/wait.h>#include <errno.h>#include "apue.h"int system(const char* cmd) {    pid_t pid;    int status;    if (cmd == NULL)        return(1);    if ((pid = fork()) < 0)        status = -1;    else if (pid == 0) { //子进程执行传入命令        execl("/bin/sh", "sh", "-c", cmd, (char*)0);        _exit(127);    } else {        while (waitpid(pid, &status, 0) < 0) { //父进程等待子进程退出            if (errno != EINTR) {                status = -1;                break;            }        }    }    return status;}void pr_exit(int status) {    if (WIFEXITED(status))        printf("normal exit, exit status= %d\n", WEXITSTATUS(status));    else if (WIFSIGNALED(status))        printf("abnormal termination, signal number= %d%s\n", WTERMSIG(status),#ifdef WCOREDUMP               WCOREDUMP(status)? "core file exits" : "");#else        "");#endif    else if (WIFSTOPPED(status))        printf("child stopped, signal number = %d\n", WSTOPSIG(status));}int main(void) {    int status;    if ((status = system("date")) < 0)        err_sys("system error");    pr_exit(status);    if ((status = system("nosuchcommand")) < 0)        err_sys("system error");    pr_exit(status);    if ((status = system("who; exit 44")) < 0)        err_sys("system error");    pr_exit(status);    exit(0);}
```

注意，设置用户ID或设置组ID程序决不应调用system函数，有安全问题。如果一个进程正以特殊的权限（设置用户ID或设置组ID） 运行，它又想生成另一个进程执行另一个程序， 则它应当直接使用fork和exec， 而且在fork之后、 exec之前要更改回普通权限。

### 8.10 用户标识

获取用户登录名。

```c
#include <unistd.h>char *getlogin(void);
```

例子

```c
#include "unistd.h"#include "apue.h"int main(void) {    char* user;    if ((user = getlogin()) != NULL)        printf("%s", user);    exit(0);}
```



### 8.11 进程调度

进程的调度策略和调度优先级是由内核确定的。 可以通过nice获得和调整进程的优先级。

进程可以降低优先级，只有特权进程可以提高优先级。

例子

```c
#include "unistd.h"#include "apue.h"#include <errno.h>int main(void) {    int pri;    pri = nice(0);    printf("nice: %d, errno: %d\n", pri, errno);  //0, 0    pri = nice(100);    printf("nice: %d, errno: %d\n", pri, errno); //19, 0    pri = nice(-100);    printf("nice: %d, errno: %d\n", pri, errno); //-1, 1    exit(0);}
```

其他函数

```c
#include <sys/resource.h>int getpriority(int which, id_t who);int setpriority(int which, id_t who, int value);
```

### 8.12 进程时间

获取进程的系统CPU时间，用户CPU时间和时钟时间。

```c
#include <sys/times.h>clock_t times(struct tms *buf));
```

例子

```c
static voiddo_cmd(char *cmd)		/* execute and time the "cmd" */{    struct tms	tmsstart, tmsend;    clock_t		start, end;    int			status;    printf("\ncommand: %s\n", cmd);    if ((start = times(&tmsstart)) == -1)	/* starting values */        err_sys("times error");    if ((status = system(cmd)) < 0)			/* execute command */        err_sys("system() error");    if ((end = times(&tmsend)) == -1)		/* ending values */        err_sys("times error");    pr_times(end-start, &tmsstart, &tmsend);    pr_exit(status);}
```



## 9. 进程关系

### 9.1 终端登录

这里终端是本地的或者是远程的。登录unix系统都经由内核中的终端设备驱动程序。

BSD系统的过程：init读取文件/etc/ttys，对每一个允许登录的终端设备调用一次fork，它所生成的子进程则exec getty程序。getty打开终端设备，exec login程序。至此，登录用户的登录shell开始运行。

### 9.2 网络登录

网络登录时 在终端和计算机之间的连接不再是点到点的。在网络登录情况下，login仅仅是一种可用的网络服务。

为使同一个软件既能处理终端登录又能处理网络登录，系统使用了一种称为伪终端。

BSD系统过程：init调用shell脚本启动一个守护进程inetd。当一个TCP/IP连接请求到达主机时，inetd执行一次fork，生成的子进程exec适当的程序，如telnetd。获得登录shell连接到终端或伪终端。

### 9.3 进程组

每个进程还属于一个进程组。进程组是一个或多个进程的集合。通常它们是在同一作业中结合起来的 ，同一进程组中的各进程接收来
自同一终端的各种信号。每个进程组有一个唯一的进程组ID。

每个进程组有一个组长进程。组长进程的进程组ID等于其进程ID。进程组组长可以创建一个进程组、创建该组中的进程然后终止。从进程组创建开始到其中最后一个进程离开为止的时间区间称为进程组的生命期。



### 9.4 会话

会话（session）是一个或多个进程组的集合。

```c
pid_t setsid(void);pid_t getsid(pid_t pid);
```

**终端设备**

1. 一个会话可以有一个控制终端，包括终端设备或伪终端。

2. 建立与控制终端连接的会话首进程被称为控制进程。

3. 一个会话中的几个进程组可被分成一个前台进程组和一个或多个后台进程组。

### 9.5 孤儿进程组

孤儿进程组：该组中每个成员的父进程要么是该组的一个成员，要么不是该组所属会话的成员（不属于同会话的其他进程组）。

```c
#include "apue.h"#include <errno.h>static void sig_hup(int signo){    printf("SIGHUP received, pid = %ld\n", (long)getpid());}static void pr_ids(char *name){    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",           name, (long)getpid(), (long)getppid(), (long)getpgrp(),           (long)tcgetpgrp(STDIN_FILENO));    fflush(stdout);}int main(void){    char	c;    pid_t	pid;    pr_ids("parent");    if ((pid = fork()) < 0) {        err_sys("fork error");    } else if (pid > 0) {	/* parent */        sleep(5);		/* sleep to let child stop itself */    } else {			/* child */        pr_ids("child");        signal(SIGHUP, sig_hup);	/* establish signal handler */        kill(getpid(), SIGTSTP);	/* stop ourself */        pr_ids("child");	/* prints only if we're continued */        if (read(STDIN_FILENO, &c, 1) != 1)            printf("read error %d on controlling TTY\n", errno);    }    exit(0);}
```



## 10. 信号

### 10.1 信号概念

每个信号都有一个名字。mac和linux都支持31种信号。不存在编号为0的信号。

产生信号的方式：

- 当用户按某些终端键时，引发终端产生的信号
- 硬件异常产生信号： 除数为0、 无效的内存引用等
- 用户可用kill(1)命令将信号发送给其他进程
- 进程调用kill(2)函数可将任意信号发送给另一个进程或进程组
- 当检测到某种软件条件已经发生，并应将其通知有关进程时也产生信号。

处理信号的方式：

- 忽略此信号。SIGKILL和SIGSTOP这两种信号不能被忽略的原因是：它们向内核和超级用户提供了使进程终止或停止的可靠方法。
- 捕捉信号。不能捕捉SIGKILL和SIGSTOP信号。
- 执行系统默认动作。对大多数信号的系统默认动作是终止该进程。



### 10.2 signal函数

用来指定信号处理程序，返回值为上一次设置的处理程序指针。signal函数的限制是不改变信号的处理方式就不能确定信号的当前处理方式。

例子

```c
#include "apue.h"static void sig_usr(int );int main(void){    if (signal(SIGUSR1, sig_usr) == SIG_ERR) //安装信号处理程序        err_sys("cannot catch sigusr1");    if (signal(SIGUSR2, sig_usr) == SIG_ERR)        err_sys("cannot catch sigusr2");    for (;;) {        pause();  //使进程在后台运行直到收到一个信号    }}static void sig_usr(int signo) {    if (signo == SIGUSR1)        printf("receive SIGUSR1\n");    else if (signo == SIGUSR2)        printf("receive SIGUSR2\n");    else        err_dump("receive signal %d\n", signo);}
```

处理信号方式

当执行一个程序时，所有信号的状态都是系统默认或忽略。

exec函数将原先设置为要捕捉的信号都更改为默认动作，其他信号的状态则不变.

shell自动将后台进程对中断和退出信号的处理方式设置为忽略。

当一个进程调用fork时，其子进程继承父进程的信号处理方式。



### 10.3 中断的系统调用

早期unix系统，如果进程在执行一个低速系统调用而阻塞期间捕捉到一个信号，则该系统调用就被中断不再继续执行。

低速系统调用是可能会使进程永远阻塞的一类系统调用，如等待读取某些类型的文件，pause函数，某些ioctl操作等。

为了不必处理被中断的系统调用，引入了自动重启动的系统调用。包括ioctl、 read、 readv、 write、 writev、 wait 和waitpid。



### 10.4 可重入函数

指在信号处理程序中保证调用安全的函数。进程捕捉到信号时，正在执行的正常指令序列就被临时中断。在信号处理程序中不能判断捕捉到信号时进程执行到何处。如果在信号处理程序中调用不可重入函数，可能造成预期外的结果。

不可重入函数通常是：

- 使用静态数据结构
- 调用malloc或free
- 标准I/O函数，使用全局数据结构

getpwnam是非可冲入函数。

例子

```c
#include "apue.h"
#include <pwd.h>
static void my_alarm(int signo) {
    struct passwd *ptr;

    printf("in signal handler \n");
    if ((ptr = getpwnam("root")) == NULL)
        err_sys("getpwan error");
    alarm(1);
}

int main(void)
{
    struct passwd *ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);
    for (;;) {
        if ((ptr = getpwnam("lifan")) == NULL)
            err_sys("error");
        if (strcmp(ptr->pw_name, "lifan") != 0)
            printf("return value wrong, %s\n", ptr->pw_name);
    }
}
```



### 10.5 SIGCHILD

SIGCLD和SIGCHLD这两个信号很容易被混淆。SIGCLD是System V的一个信号名，其语义与名为SIGCHLD的BSD信号不同。

对于SIGCLD的早期处理方式是:

- 若设置为SIG_IGN，则丢弃所有子进程状态，不会产生僵死进程
- 若设置为捕捉，则在有子进程准备好被等待时，调用SIGCLD处理程序

macos上不支持SIGCLD，以下程序运行没问题。

例子

```c
#include "apue.h"
#include <sys/wait.h>

static void sig_cld(int );

int main(void)
{
    pid_t pid;

    if (signal(SIGCHLD, sig_cld) == SIG_ERR) //安装信号处理程序
        err_sys("cannot catch sigusr1");

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        sleep(2);
        _exit(0);
    }

    pause();
    exit(0);

}

static void sig_cld(int signo) {
    pid_t pid;
    int status;

    printf("SIGCLD received\n");

    if (signal(SIGCHLD, sig_cld) == NULL)
        perror("signal error");

    if ((pid = wait(&status)) < 0)
        perror("wait error");

    printf("pid = %d\n", pid);
}
```

### 10.6 信号术语

1. 当一个信号产生时，内核通常在进程表中以某种形式设置一个标志。

2. 在信号产生和递送之间的时间间隔内，称信号是未决的。

3. 进程可以阻塞信号递送 。内核在递送一个原来被阻塞的信号给进程时才决定对它的处理方式。

4. 对于发生多次的信号，大多数UNIX并不对信号排队， 而是只递送这种信号一次。

5. 同时发生的多个信号，建议先递送与进程当前状态有关的信号，如SIGSEGV。

6. 每个进程都有一个信号屏蔽字，规定了当前要阻塞递送到该进程的信号集。



### 10.7 kill和raise

kill函数将信号发送给进程或进程组，raise函数则允许进程向自身发送信号。

例子

```c
#include "apue.h"
#include <sys/wait.h>

static void sig_cld(int );

int main(void)
{
    pid_t pid;

    if (signal(SIGUSR1, sig_cld) == SIG_ERR)
        err_sys("cannot catch sigusr1");
    if (signal(SIGUSR2, sig_cld) == SIG_ERR)
        err_sys("cannot catch sigusr1");

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        pause();
        _exit(0);
    }

    kill(pid, SIGUSR1);
    raise(SIGUSR2);
    kill(getpid(), SIGUSR2);
    exit(0);

}

static void sig_cld(int signo) {
    if (signo == SIGUSR1)
        printf("received sigusr1 %d, pid %d\n", signo, getpid());
    else if (signo == SIGUSR2)
        printf("received sigusr2 %d, pid %d\n", signo, getpid());
}
```

进程将信号发送给其他进程需要权限。超级用户可将信号发送给任一进程。对于非超级用户，其基本规则是发送者的实际用户ID 或有效用户 ID 必须等于接收者的实际用户 ID或有效用户ID。

pid不同取值的区别：

1. pid >0，发送对应的pid进程
2. pid = -1, 发送给进程有权限的所有的进程
3. pid = 0, 发送给同一进程组的进程
4. pid < 0，发送给进程组id等于pid绝对值的

### 10.8 alarm和pause

alarm函数可以设置一个定时器。当定时器超时时产生 SIGALRM 信号。如果忽略或不捕捉此信号，则其默认动作是终止调用该alarm函数的进程。

每个进程只能有一个闹钟时间。多次调用则用新的时间代替旧的时间。

pause函数使调用进程挂起直至捕捉到一个信号。只有执行了一个信号处理程序并从其返回时，pause才返回。

alarm被用来实现sleep函数，或者为可能发生阻塞的调用设置超时时间。



例子1, sleep

```c
#include "apue.h"
#include <sys/wait.h>

typedef void Sigfunc(int);

static void sig_alarm(int);
unsigned int sleep1(unsigned int);

int main(void)
{
    printf("begin\n");
    sleep1(2);
    printf("end\n");
}

static void sig_alarm(int signo) {}

unsigned int sleep1(unsigned int seconds) {
    unsigned int old_sec;
    Sigfunc *sigPtr;
    if ((sigPtr = signal(SIGALRM, sig_alarm)) == SIG_ERR)
        return(seconds);

    if ((old_sec = alarm(seconds)) > seconds) {  //如果以前设置过alarm，则判断一下余下的超时时间
        alarm(old_sec);
    }
    pause();
    signal(SIGALRM, sigPtr);  //恢复原始的处理函数
    return(alarm(0));
}
```

例子2 超时读

```c
#include "apue.h"
#include "setjmp.h"
#include <sys/wait.h>

static void sig_alarm(int);
static jmp_buf env_alrm;

int main(void)
{
    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        err_sys("cannot catch sigalarm");

    if (setjmp(env_alrm) != 0)
        err_quit("timeout");

    alarm(10);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
        err_sys("read error");
    alarm(0);

    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void sig_alarm(int signo) {
    if (signo == SIGALRM)
        printf("received %d, pid %d\n", signo, getpid());
    longjmp(env_alrm, 0);
}
```



### 10. 9 信号集

表示一组信号。

```c
#include <signal.h>
int sigemptyset(sigset_t *set); //清空
int sigfillset(sigset_t *set); //初始化所有信号
int sigaddset(sigset_t *set, int signo); //添加
int sigdelset(sigset_t *set, int signo); //删除
int sigismember(const sigset_t *set, int signo); //判断是否是信号集的成员
```

所有应用程序在使用信号集前，要对该信号集调用sigemptyset或sigfillset一次。

如果实现的信号数目少于一个整型量所包含的位数，则可用一位代表一个信号的方法实现信号集。



### 10.10 sigprocmask

进程的信号屏蔽字规定了当前阻塞而不能递送给该进程的信号集。

调用函数sigprocmask可以检测或更改， 或同时进行检测和更改进程的信号屏蔽字。

进程的信号屏蔽字规定了当前阻塞而不能递送给该进程的信号集。



### 10.11 sigpending

sigpending函数返回一信号集，对于调用进程而言， 其中的各信号是阻塞不能递送的，因而也一定是当前未决的。

例子

```c
#include "apue.h"

static void sig_quit(int);
int main(void)
{
    sigset_t newmask, oldmask, penmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
        err_sys("signal error");

    sigemptyset(&newmask);    //清空信号集
    sigaddset(&newmask, SIGQUIT); //添加quit信号
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) //用newmask新增阻塞的信号集，oldmask保存原始屏蔽信号集
        err_sys("sigblock error");

    sleep(5);  //这次期间发出quit会阻塞

    if (sigpending(&penmask) < 0)    //查询阻塞的信号集
        err_sys("sig pending error");

    if (sigismember(&penmask, SIGQUIT))  //查看sigquit是否被阻塞
        printf("pending quit\n");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL))  //恢复原来的屏蔽信号集
        err_sys("sig setmask error");

    printf("sigquit unblock\n");
    sleep(5);   //这期间quit可以生效
    exit(0);
}

static void sig_quit(int signo) {
    printf("receive sigquit\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        err_sys("sigquit error");
}
```



### 10.12 sigaction

sigaction函数的功能是检查或修改与指定信号相关联的处理动作。此函数取代了UNIX早期版本使用的不可靠的signal函数。不可靠在这里
指的是信号可能会丢失：一个信号发生了，但进程却可能一直不知道这一点。同时没办法控制阻塞信号的传递。

在信号处理程序被调用时，操作系统建立的新信号屏蔽字包括正被递送的信号。这样，在调用信号处理程序时就能阻塞某些信号。

一旦对给定的信号设置了一个动作，那么在调用sigaction显式地改变它之前，该设置就一直有效。



### 10.13 sigsetjmp和siglongjmp

在信号处理程序中经常调用longjmp函数以返回到程序的主循环中，而不是从该处理程序返回。在进入信号处理程序时当前信号会加入信号屏蔽字中，从longjmp中返回时不一定会恢复原始的屏蔽字。sigsetjmp和siglongjmp则能保存和恢复原始屏蔽字。



### 10.14 sigsuspend

sigsuspend在一个原子操作中先恢复信号屏蔽字，然后使进程休眠。这样能避免在恢复信号屏蔽字之后调用pause之前有信号到达。

例子

```c
#include "apue.h"
#include <errno.h>
static void sig_int(int);

void pr_mask(const char* str) {
    sigset_t	sigset;
    int			errno_save;

    errno_save = errno;		/* we can be called by signal handlers */
    if (sigprocmask(0, NULL, &sigset) < 0) {
        err_ret("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");

        /* remaining signals can go here  */
        printf("\n");
    }

    errno = errno_save;		/* restore errno */
}

int main(void)
{
    sigset_t newmask, oldmask, waitmask;

    pr_mask("program start");
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("error");

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)  //设置阻塞int
        err_sys("sigprocmask error");

    pr_mask("in critical region");

    if (sigsuspend(&waitmask) != -1)   //设置成阻塞usr1并休眠进程，其他信号不阻塞
        err_sys("sigsuspend error");

    pr_mask("after return from sigsuspend");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)  //恢复原来的屏蔽信号集
        err_sys("setmask error");

    pr_mask("program exit");

    exit(0);
}

static void sig_int(int signo) {
    pr_mask("\nint sig_int: ");
}
```

sigsuspend的另一种应用是等待一个信号处理程序设置一个全局变量。还可以用信号实现父、子进程之间的同步，在进程控制中使用的tellwait的实现就是基于上面的方法。

```c
int main(void)
{
    pid_t	pid;

    TELL_WAIT();  //设置当前进程阻塞usr1, usr2信号

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        WAIT_PARENT();		/* parent goes first */  //等待信号处理程序设置全局变量
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);  //向子进程发送usr1信号
    }
    exit(0);
}
```



具体实现是通过suspend阻塞等待进程，而被等待的进程发送信号触发信号处理函数修改全局变量，从而释放阻塞进程。`WAIT_PARENT`和`TELL_CHILD`是一组，`TELL_PARENT`和`WAIT_CHILD`是一组。

```c
#include "apue.h"

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void
sig_usr(int signo)	/* one signal handler for SIGUSR1 and SIGUSR2 */
{
	sigflag = 1;
}

void
TELL_WAIT(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR2) error");
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	/* Block SIGUSR1 and SIGUSR2, and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
}

void
TELL_PARENT(pid_t pid)
{
	kill(pid, SIGUSR2);		/* tell parent we're done */
}

void
WAIT_PARENT(void)
{
	while (sigflag == 0)
		sigsuspend(&zeromask);	/* and wait for parent */
	sigflag = 0;

	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
}

void
TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1);			/* tell child we're done */
}

void
WAIT_CHILD(void)
{
	while (sigflag == 0)
		sigsuspend(&zeromask);	/* and wait for child */
	sigflag = 0;

	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
}
```



### 10.15 函数abort

abort函数的功能是使程序异常终止。函数将SIGABRT信号发送给调用进程。abort并不理会进程对此信号的阻塞和忽略。



太多了，以后有时间再补充。



## 11. 线程

### 11. 1 线程概念

进程可以有多个控制线程，每个线程处理各自独立的任务。

和进程的区别：

1. 多个进程必须使用操作系统提供的复杂机制才能实现内存和文件描述符的共享，而多个线程自动地可以访问相同的存储地址空间和文件描述符。

2. 通过为每种事件类型分配单独的处理线程，可以简化处理异步事件的代码。

3. 有些问题可以分解从而提高整个程序的吞吐量。

4. 交互的程序可以通过使用多线程来改善响应时间。

一个进程的所有信息对该进程的所有线程都是共享的，包括可执行程序的代码、程序的全局内存和堆内存、栈以及文件描述符。

### 11.2 线程标识

进程 ID在整个系统中是唯一的，但线程ID不同，线程ID只有在它所属的进程上下文中才有意义。

线程ID是用pthread_t数据类型来表示的，不一定是整形。

```c
#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
    pid_t		pid;
    pthread_t	tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
           (unsigned long)tid, (unsigned long)tid);
}

void * thr_fn(void *arg)
{
    printf("%s\n", (char*)arg);
    printids("new thread: ");
    return((void *)0);
}

int main(void)
{
    int		err;

    err = pthread_create(&ntid, NULL, thr_fn, "huahua");
    if (err != 0)
        err_exit(err, "can't create thread");
    printids("main thread:");
    sleep(1);
    exit(0);
}
```



### 11.3 线程终止

如果进程中的任意线程调用了exit、 \_Exit 或者_exit，整个进程就会终止。

如果默认的动作是终止进程，则发送到线程的信号就会终止整个进程。

单个线程正常终止的方式：

1. 线程返回。
2. 被其他线程取消。
3. 线程调用pthread_exit

```c
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
```

### 11.4 线程同步

#### 11.4.1 互斥量

多个线程使用互斥量控制访问共同变量的顺序。

例子

```c
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
```



#### 11.4.2 避免死锁

在同时需要两个互斥量时，总是让它们以相同的顺序加锁，这样可以避免死锁。

需要在满足锁需求的情况下，在代码复杂性和性能之间找到正确的平衡。

例子

```c
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
```

#### 11.4.3 带超时的加锁

```c
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex, const struct timespec *restrict tsptr);
```

指定超时的绝对时间，mac上不支持。



#### 11.4.4 读写锁

一次只有一个线程可以占有写模式的读写锁，但是多个线程可以同时占有读模式的读写锁。

当读写锁处于读模式锁住的状态，而这时有一个线程试图以写模式获取锁时，读写锁通常会阻塞随后的读模式锁请求。

在释放读写锁占用的内存之前，需要调用 pthread_rwlock_destroy 做清理工作。

```c
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
```



#### 11.4.5 带超时的读写锁

```
pthread_rwlock_timedrdlock 和 pthread_rwlock_timedwrlock
```

传入的参数指绝对时间



#### 11.4.6 条件信号

条件变量与互斥量一起使用时，允许线程以无竞争的方式等待特定的条件发生。就是等待和通知机制。

例子

```c
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
```



#### 11.4.7 自旋锁

自旋锁适用于锁被持有的时间短，而且线程并不希望在重新调度上花费太多的成本的情况。

使用方式可以和互斥量直接替换。mac上不支持。

```c
#include <pthread.h>
int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);
```



## 12. 线程控制

### 12. 1 线程属性

1. 如果在创建线程时就知道不需要了解线程的终止状态，就可以使用pthread_attr_setdetachstate
2. pthread_attr_init对线程属性进行初始化，pthread_attr_destroy执行清理工作。
3. 对于进程来说虚地址空间的大小是固定的，但对于线程来说，同样大小的虚地址空间必须被所有的线程栈共享。如果线程栈的虚地址空间都用完了，用pthread_attr_setstack函数来改变新建线程的栈位置。
4. 如果希望改变默认的栈大小但又不想自己处理线程栈的分配问题，使用pthread_attr_setstacksize函数就非常有用。
5. 线程属性guardsize控制着线程栈末尾之后用以避免栈溢出的扩展内存的大小



### 12. 2 同步属性

#### 12.2.1 互斥量属性

进程共享属性、健壮属性以及类型属性。

1.进程共享属性

```
PTHREAD_PROCESS_PRIVATE  在进程中，多个线程可以访问同一个同步对象。
PTHREAD_PROCESS_SHARED   多个进程访问共享数据通常也需要同步
```

2.互斥量健壮属性与在多个进程间共享的互斥量有关。

```
PTHREAD_MUTEX_STALLED   持有互斥量的进程终止时不需要采取特别的动作
PTHREAD_MUTEX_ROBUST  返回EOWNERDEAD
```

3.类型属性：

```
PTHREAD_MUTEX_NORMAL     重复加锁会死锁
PTHREAD_MUTEX_ERRORCHECK  重复加锁返回错误
PTHREAD_MUTEX_RECURSIVE  可重入锁
PTHREAD_MUTEX_DEFAULT   未定义
```

#### 12.2.2 读写锁属性

读写锁支持的唯一属性是进程共享属性，与互斥量的进程共享属性是相同的。

#### 12.2.3 条件变量属性

进程共享属性和时钟属性。

#### 12.2.4 屏障属性

目前定义的屏障属性只有进程共享属性，它控制着屏障是可以被多进程的线程使用，还是只能被初始化屏障的进程内的多线程使用。



### 12.3 重入

**1. 线程安全：**

如果一个函数在相同的时间点可以被多个线程安全地调用，就称该函数是线程安全的。

实现方式包括：

- 使用互斥量保护全局变量
- 不适用全局变量

**2. 可重入：**

一个函数能够被多次安全调用，称为可重入的。

分为两种情况

- 多个线程可以同时调用函数，称为对多个线程可重入。
- 同一个线程因为信号处理程序多次调用同一个函数，称为对信号处理程序可重入。

实现方式：

- 不使用全局变量，每个调用者传入自己的缓存区。

**3. 两者的关系：**

如果一个函数对多个线程来说是可重入的，就说这个函数就是线程安全的。但这并不能说明对信号处理程序来说该函数也是可重入的。

如果函数对异步信号处理程序的重入是安全的，那么就可以说函数是异步信号安全的。

必须使用递归互斥量（可重入锁）保证线程安全，还要阻止来自信号处理程序的死锁。

例子：

```c
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
```



### 12.4 线程和信号

每个线程都有自己的信号屏蔽字，但是信号的处理是进程中所有线程共享的。

进程中的信号是递送到单个线程的。如果信号与硬件故障相关，那么一般会被发送到引起该事件的线程中去，而其他的信号
则被发送到任意一个线程。

如果多个线程在sigwait 的调用中因等待同一个信号而阻塞，那么在信号递送的时候就只有一个线程可以从 sigwait 中返回。

要把信号发送给进程可以调用kill。要把信号发送给线程可以调用pthread_kill。

闹钟定时器是进程资源， 并且所有的线程共享相同的闹钟。

例子

```c
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
```



### 12.5 线程和fork

当线程调用fork时， 就为子进程创建了整个进程地址空间的副本。

在子进程内部只存在一个线程，是由父进程中调用fork的线程的副本构成的。如果父进程中的线程占有锁，子进程将同样占有这些锁。

在fork之后可能会出现同步状态不一致的问题。可以通过调用pthread_atfork函数建立fork处理程序，清除锁状态，

例子

```c
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
```



### 12.6 线程与IO

pread和pwrite能够使偏移量的设定和数据的读取成为一个原子操作，适用于多线程环境。进程中的所有线程共享相同的文件描述符。



## 13. 守护进程

例子

```c
#include <fcntl.h>
#include "apue.h"
#include <sys/resource.h>
#include <syslog.h>

void daemonize(const char *cmd) {
    int  i, fd0, fd1, fd2;
    pid_t  pid;
    struct rlimit  rl;
    struct sigaction sa;

    /*
     * 清空文件创建屏蔽字
     */
    umask(0);

    /*
     * 获得最大文件描述符数量
     */
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_quit("%s: can't get file limit", cmd);

    /*
     * 称为会话leader
     */
    if ((pid = fork()) < 0)
        err_quit("%s: can't fork", cmd);
    else if (pid != 0) //父进程直接退出
        exit(0);
    setsid();

    /*
     * 确保后续打开操作不会分配控制终端
     */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: cannot ignore SIGHUP", cmd);
    if ((pid = fork()) < 0)
        err_quit("%s: can't fork", cmd);
    else if (pid != 0) //父进程直接退出
        exit(0);

    /*
     * 将当前目录作为工作目录
     */
    if (chdir("/") < 0)
        err_quit("%s: cannot change directory to /", cmd);

    /*
     * 关闭所有打开的文件描述符
     */
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; ++i) {
        close(i);
    }

    /*
     * 绑定fd 0， 1， 2到/dev/null
     */
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    /*
     * 初始化日志文件
     */
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptor %d, %d, %d",
               fd0, fd1, fd2);
        exit(1);
    }
}

int main() {
    daemonize("pwd");
    for (;;) {
        sleep(1);
    }
}
```

可以查看到后台运行的进程

```
ps -efj
```

syslog可以用于守护进程的日志收集。

文件和记录锁机制为单例守护进程提供了基础，该方法保证一个守护进程只有一个副本在运行。

守护进程常常用作服务器进程。客户进程向服务器进程发送请求，服务器进程则向客户进程回送应答。在服务器进程中调用fork然后exec另一个程序来向客户进程提供服务是很常见的。

## 14 高级IO

### 14.1 非阻塞IO

设置非阻塞的方式

1. 如果调用open获得描述符， 则可指定O_NONBLOCK标志

2. 对于已经打开的一个描述符，则可调用fcntl打开O_NONBLOCK 文件状态标志

非阻塞I/O可以发出open、read和write这样的I/O操作，并使这些操作不会永远阻塞。如果这种操作不能完成则调用立即出错返回，表示该操作如继续执行将阻塞。

```c
#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char buf[500000];

int main(void) {
    int ntowrite, nwrite;
    char *ptr;

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));  //读取固定大小到buf
    fprintf(stderr, "read %d bytes\n", ntowrite);

    set_fl(STDOUT_FILENO, O_NONBLOCK);  //设置fd属性为非阻塞

    ptr = buf;
    while (ntowrite > 0) {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);  //输出，非阻塞
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

        if (nwrite > 0) {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }

    clr_fl(STDOUT_FILENO, O_NONBLOCK);  //关闭fd属性非阻塞
    exit(0);
}
```

如果写出是普通文件，则只输出一次。

```
./write < /etc/services > temp.file
read 500000 bytes
nwrite = 500000, errno = 0
```

如果是输出到终端，则会分多次输出，有时返回错误。这种形式的循环称为轮询。

```
./write < /etc/services 2>stderr.out
```

### 14.2 记录锁

记录锁的功能是当第一个进程正在读或修改文件的某个部分时，可以阻止其他进程修改同一文件区。也称为字节范围锁，因为它锁定的只是文件中的一个区域。

不同unix系统实现的记录锁有不同。fcntl记录锁是POSIX.1标准中的实现。

如果一个进程对一个文件区间已经有了一把锁，又企图在同一文件区间再加一把锁，那么新锁将替换已有锁。

fcntl函数的3种命令：

```
F_GETLK  判断要加的锁是否会被另一把锁阻塞
F_SETLK  添加锁，如果失败直接返回
F_SETLKW 添加锁，如果无法加锁则阻塞等待
```

死锁

```c
#include "apue.h"
#include <fcntl.h>

static void lockabyte(const char *name, int fd, off_t offset) {
    if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
        err_sys("%s: writew_lock error", name);
    printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

int main(void) {
    int fd;
    pid_t pid;

    /*
     * 创建一个文件，写入两个字节
     */
    if ((fd = creat("templock", FILE_MODE)) < 0)
        err_sys("create error");
    if (write(fd, "ab", 2) != 2)
        err_sys("write error");

    TELL_WAIT();  //初始化信号
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        lockabyte("child", fd, 0); //子进程加锁 0
        TELL_PARENT(getpid()); //给父进程发信号
        WAIT_PARENT();  //父进程加完锁才到这里
        lockabyte("child", fd, 1); //子进程加锁 1
    } else {
        lockabyte("parent", fd, 1);  //父进程加锁 1
        TELL_CHILD(pid);
        WAIT_CHILD();  //子进程加完锁才到这里
        lockabyte("parent", fd, 0);  //父进程加锁 0
    }
    exit(0);
}
```

**记录锁的自动继承和释放**

锁与进程和文件两者相关联。当一个进程终止时它所建立的锁全部释放；描述符关闭时，进程通过描述符引用的文件上的任何一把锁都会释放。

由fork产生的子进程不继承父进程所设置的锁。

在执行exec后， 新程序可以继承原执行程序的锁。

**建议锁和强制锁**

建议性锁并不能阻止对数据库文件有写权限的任何其他进程写这个数据库文件。

强制性锁会让内核检查每一个open、read 和 write，验证调用进程是否违背了正在访问的文件上的某一把锁。

**文本编辑器**

UNIX系统文本编辑器并不使用记录锁，该文件的最后结果取决于写该文件的最后一个进程。

### 14.3 IO多路转接

阻塞式IO无法实现同时从多个文件描述符读取，使用多进程或多线程则会增加程序复杂度。

使用非阻塞IO的问题是轮询浪费CPU资源。使用异步IO的进程无法用于多个描述符。

I/O多路转接使用构造一张描述符的列表来管理多个描述符。

#### 14.3.1 函数select和pselect

1. 传给select的参数告诉内核

我们所关心的描述符；对于每个描述符我们所关心的条件；愿意等待多长时间

2. 从select返回时内核告诉我们

已准备好的描述符的总数量；对于读、写或异常这3个条件中的每一个，哪些描述符已准备好。

3. 返回值

返回值-1表示出错；返回值0表示没有描述符准备好；一个正返回值说明了已经准备好的描述符数。

#### 14.3.2 poll

与select不同，poll不是为每个条件（可读性、可写性和异常条件）构造一个描述符集，而是构造一个pollfd结构的数组，每个数组元素指定一个描述符编号以及我们对该描述符感兴趣的条件。

与select一样， 一个描述符是否阻塞不会影响poll是否阻塞。



### 14.4 异步IO

POSIX异步I/O接口使用AIO控制块来描述I/O操作。

1. 在进行异步I/O之前需要先初始化AIO控制块
2. 调用aio_read函数来进行异步读操作或调用aio_write函数来进行异步写操作。

```
当这些函数返回成功时，异步I/O请求便已经被操作系统放入等待处理的队列中了。
I/O操作在等待时，必须注意确保AIO控制块和数据库缓冲区对应的内存始终是合法的，除非I/O操作完成，否则不能被复用。
```

3. 为了获知一个异步读、写或者同步操作的完成状态，需要调用aio_error函数。
4. 如果异步操作成功， 可以调用aio_return函数来获取异步操作的返回值。

```
对每个异步操作只调用一次aio_return。一旦调用了该函数，操作系统就可以释放掉包含了I/O操作返回值的记录。
```

5. 可以调用aio_suspend函数来阻塞进程，等待异步IO操作完成。
6. 不想再等待异步I/O操作时，可以尝试使用aio_cancel函数来取消。

例子

```c
#define BSZ 4096
#define NBUF 8

enum rwop {
    UNUSED = 0,     //未使用的缓冲区
    READ_PENDING = 1,  //正在读
    WRITE_PENDING = 2  //正在写
};

struct buf {
    enum rwop op;
    int last;
    struct aiocb aiocb;
    unsigned char data[BSZ];
};

struct buf bufs[NBUF];

unsigned char translate(unsigned char c) {
    if (isalpha(c)) {
        if (c >= 'n')
            c -= 13;
        else if (c >= 'a')
            c += 13;
        else if (c >= 'N')
            c -= 13;
        else
            c += 13;
    }
    return c;
}

int main(int argc, char *argv[]) {
    int ifd, ofd, i, j, n, err, numop;
    struct stat sbuf;
    const struct aiocb *aiolist[NBUF];
    off_t off = 0;  //全局文件偏移量

    if (argc != 3)
        err_quit("usage: rot13 infile outfile");
    if ((ifd = open(argv[1], O_RDONLY)) < 0)
        err_sys("cannot open %s", argv[1]);

    if ((ofd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
        err_sys("cannot open %s", argv[2]);

    if (fstat(ifd, &sbuf) < 0)
        err_sys("fstat failed");

    //初始化buffer
    for (i = 0; i < NBUF; ++i) {
        bufs[i].op = UNUSED;
        bufs[i].aiocb.aio_buf = bufs[i].data; //数据buf
        bufs[i].aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;  //不适用异步信号通知
        aiolist[i] = NULL;
    }

    numop = 0;
    for (;;) {
        for (i = 0; i < NBUF; ++i) {  //轮询每个缓冲区
            switch (bufs[i].op) {
                case UNUSED:
                    if (off < sbuf.st_size) { //如果空闲，并且未读完，则加入读操作中
                        bufs[i].op = READ_PENDING;
                        bufs[i].aiocb.aio_fildes = ifd;
                        bufs[i].aiocb.aio_offset = off;
                        off += BSZ;
                        if (off > sbuf.st_size)
                            bufs[i].last = 1;  //读到了文件末尾
                        bufs[i].aiocb.aio_nbytes = BSZ;
                        if (aio_read(&bufs[i].aiocb) < 0)  //调用函数后马上返回
                            err_sys("aio read failed");
                        aiolist[i] = &bufs[i].aiocb;
                        numop++;
                    }
                    break;

                case READ_PENDING:
                    if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)  //检查操作状态
                        continue;
                    if (err != 0) {
                        if (err == -1)
                            err_sys("aio_error failed");
                        else
                            err_exit(err, "read failed");
                    }

                    if ((n = aio_return(&bufs[i].aiocb)) < 0) //操作完成，获取结果
                        err_sys("aio_return failed");
                    if (n != BSZ && !bufs[i].last) //不是最后一次读，长度不够
                        err_quit("short read (%d/%d)", n, BSZ);

                    for (j = 0; j < n; ++j)
                        bufs[i].data[j] = translate(bufs[i].data[j]);
                    bufs[i].op = WRITE_PENDING;
                    bufs[i].aiocb.aio_fildes = ofd;
                    bufs[i].aiocb.aio_nbytes = n;
                    if (aio_write(&bufs[i].aiocb) < 0) //读成功之后提交到异步写操作
                        err_sys("aio_write failed");

                    break;

                case WRITE_PENDING:
                    if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)
                        continue;
                    if (err != 0) {
                        if (err == -1)
                            err_sys("aio_error failed");
                        else
                            err_exit(err, "write failed");
                    }

                    if ((n = aio_return(&bufs[i].aiocb)) < 0)
                        err_sys("aio_return failed");
                    if (n != bufs[i].aiocb.aio_nbytes)
                        err_quit("short write (%d/%d)", n, BSZ);
                    aiolist[i] = NULL;  //操作完成，置为空
                    bufs[i].op = UNUSED;
                    numop--;
                    break;
            }
        }
        if (numop == 0) {  //没有在运行的buf
            if (off >= sbuf.st_size)  //处理完了返回
                break;
        } else {
            if (aio_suspend(aiolist, NBUF, NULL) < 0)  //还有未完成的aoi，阻塞等待aiolist
                err_sys("aio_suspend failed");
        }
    }
    bufs[0].aiocb.aio_fildes = ofd;
    if (aio_fsync(O_SYNC, &bufs[0].aiocb) < 0) //同步内容到磁盘
        err_sys("aio_fsync failed");
    exit(0);
}
```

### 14.5 readv和writev

readv和writev函数用于在一次函数调用中读、写多个非连续缓冲区。

readv把读取的数据按顺序写入多个缓冲区，writev把多个缓冲区的数据写出。

相比多次调用write和read，性能要好。应当用尽量少的系统调用次数来完成任务。



### 14. 6 存储映射

存储映射I/O（memory-mapped I/O）能将一个磁盘文件映射到存储空间中的一个缓冲区上。当从缓冲区中取数据时就相当于读文件中的相应字节，处理的是存储空间而不是读、写一个文件。

建立存储映射方法

```c
#include <sys/mman.h>
void *mmap(void *addr, size_t len, int prot, int flag, int fd, off_t off);
```

flag参数

```
MAP_FIXED  返回值必须等于addr
MAP_SHARED 对映射区的存储操作修改映射文件
MAP_PRIVATE  对映射区的存储操作导致创建该映射文件的一个私有副本
如果修改的页是通过MAP_SHARED标志映射到地址空间的, 那么修改并不会立即写回到文件中。而是由内核决定。
```

与映射区相关的信号

```
SIGSEGV  进程试图访问对它不可用的存储区
SIGBUS   映射区的某个部分在访问时已不存在 
```

子进程能通过fork继承存储映射区

如果共享映射中的页已修改，那么可以调用 msync 将该页冲洗到被映射的文件中

当进程终止时会自动解除存储映射区的映射，或者直接调用munmap函数也可以解除映射区

例子

```c
#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR 1024*1024*1024  //控制每次复制最大1G

int main(int argc, char *argv[]) {
    int fdin, fdout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;

    if (argc != 3)
        err_quit("usage: %s infile outfile", argv[0]);
    if ((fdin = open(argv[1], O_RDONLY)) < 0)
        err_sys("cannot open %s", argv[1]);
    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
        err_sys("cannot open %s", argv[2]);

    if (fstat(fdin, &sbuf) < 0)
        err_sys("fstat failed");

    if (ftruncate(fdout, sbuf.st_size) < 0)
        err_sys("ftruncate failed");

    while (fsz < sbuf.st_size) {
        if (sbuf.st_size - fsz > COPYINCR)
            copysz = COPYINCR;
        else
            copysz = sbuf.st_size - fsz;

        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED)
            err_sys("map src failed");
        if ((dst = mmap(0, copysz, PROT_WRITE | PROT_READ, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
            err_sys("map dst failed");

        memcpy(dst, src, copysz);
        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;
    }
    exit(0);
}
```



## 15. 进程间通信

### 15.1 管道

管道的局限性：

- 半双工
- 只能在具有公共祖先的两个进程之间使用
- 管道是通过调用pipe函数创建的

当读一个写端已被关闭的管道时，在所有数据都被读取后read返回0，表示文件结束。

如果写一个读端已被关闭的管道，则产生信号SIGPIPE。

例子1

使用管道传递数据

```c
#include "apue.h"

int main(void) {
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    //传入两个fd, fd[0]作为读，fd[1]作为写端
    if (pipe(fd) < 0)
        err_sys("pipe error");
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0) {
        close(fd[0]);
        write(fd[1], "hello, world\n", 12); //父进程写管道，子进程接收
    } else {
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
    exit(0);
}
```

例子2

使用管道进程父子进程同步

```c
#include "apue.h"

static int  pfd1[2], pfd2[2];

//父进程  写端->读端
//子进程  写端->读端
void TELL_WAIT(void)
{
    if (pipe(pfd1) < 0 || pipe(pfd2) < 0)
        err_sys("pipe error");
}

void TELL_PARENT(pid_t pid)
{
    if (write(pfd2[1], "c", 1) != 1) //向子进程的写端写数据
        err_sys("write error");
}

void WAIT_PARENT(void)
{
    char c;

    if (read(pfd1[0], &c, 1) != 1)  //从父进程的读端读数据
        err_sys("read error");

    if (c != 'p')
        err_quit("WAIT_PARENT: incorrect data");
}

void WAIT_CHILD(void)
{
    char c;

    if (read(pfd2[0], &c, 1) != 1)  //从子进程的读端读数据，读不到阻塞
        err_sys("read error");

    if (c != 'p')
        err_quit("WAIT_PARENT: incorrect data");
}

void TELL_CHILD(pid_t pid)
{
    if (write(pfd1[1], "c", 1) != 1) //向父进程的写端写数据
        err_sys("write error");
}
```

例子3

分页展示数据

```c
#include "apue.h"
#include <sys/wait.h>

#define DEF_PAGER  "/usr/bin/more"

int main(int argc, char *argv[]) {
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;

    if (argc != 2)
        err_quit("usage: pager <pathname>");

    if ((fp = fopen(argv[1], "r")) == NULL)
        err_sys("can't open %s", argv[1]);
    if (pipe(fd) < 0)
        err_sys("pipe error");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        close(fd[0]);

        while (fgets(line, MAXLINE, fp) != NULL) { //父进程不断读取数据
            n = strlen(line);
            if (write(fd[1], line, n) != n)  //写数据到写端，子进程会从读端读到
                err_sys("write error to pipe");
        }
        if (ferror(fp))
            err_sys("fgets error");

        close(fd[1]);  //关闭写端，子进程会关闭读端

        if (waitpid(pid, NULL, 0) < 0)  //获取子进程退出状态
            err_sys("waitpid error");
        exit(0);
    } else {
        close(fd[1]);   //子进程关闭写端
        if (fd[0] != STDIN_FILENO) {  //如果读端不等于标准输入
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)  //使标准输入成为管道的读端
                err_sys("dup2 error to stdin");
            close(fd[0]); //原来的fd不再需要
        }

        if ((pager = getenv("PAGER")) == NULL)
            pager = DEF_PAGER;
        if ((argv0 = strrchr(pager, '/')) != NULL)
            argv0++;
        else
            argv0 = pager;

        //启动分页程序，能从标准输入获取到父进程传来的数据
        if (execl(pager, argv0, (char*)0) < 0)
            err_sys("execl error for %s", pager);
    }
    exit(0);
}
```

### 15.2 popen和pclose

这两个函数实现的操作是：创建一个管道，fork一个子进程，关闭未使用的管道端，执行一个shell运行命令，然后等待命令终止。

```
popen先执行fork，然后调用exec执行cmdstring，并且返回一个标准I/O文件指针。

pclose函数关闭标准I/O流，等待命令终止，然后返回shell的终止状态。
```

例子

分页展示管道内容，使用more命令。父进程从文件读取数据，写到管道，子进程more从管道读取数据，输出到控制台。

```c
#include "apue.h"

#define DEF_PAGER  "${PAGER:-more}"

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc != 2)
        err_quit("usage: pager <pathname>");

    if ((fpin = fopen(argv[1], "r")) == NULL)
        err_sys("popen error");

    if ((fpout = popen(DEF_PAGER, "w")) == NULL) //以写的方式打开管道
        err_sys("popen error");

    while (fgets(line, MAXLINE, fpin) != NULL) { //父进程不断读取数据
        if (fputs(line, fpout) == EOF)
            err_sys("fputs error to pipe");
    }
    if (ferror(fpin))
        err_sys("fgets error");
    if (pclose(fpout) == -1)
        err_sys("pclose error");

    exit(0);
}
```



使用管道在标准输入输出中间添加自定义处理程序。

```c
#include "apue.h"

int main(void) {
    char buf[MAXLINE];
    FILE *fpin;

    if ((fpin = popen("./myuclc", "r")) == NULL) //写读打开管道
        err_sys("popen error");

    for(;;) {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if ((fgets(buf, MAXLINE, fpin)) == NULL) //从管道读取数据
            break;
        if (fputs(buf, stdout) == EOF)
            err_sys("fputs error to pipe");
    }
    if (pclose(fpin) == -1)
        err_sys("pclose error");
    putchar('\n');
    exit(0);
}
```

myuclc执行的工作是从标准输入读取字符转换为小写。数据从标准输入到子进程，转换成小写之后，从子进程输出到管道，父进程从管道读取到buf，输出到标准输出。

### 15.3 协同进程

popen只提供连接到另一个进程的标准输入或标准输出的一个单向管道。

当一个过滤程序既产生某个过滤程序的输入，又读取该过滤程序的输出时，就变成了协同进程（coprocess）。

例子

```c
#include "apue.h"

static void sig_pipe(int);

int main(void) {
    int n, fd1[2], fd2[2];
    pid_t pid;
    char line[MAXLINE];

    if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
        err_sys("signal error");

    if (pipe(fd1) < 0 || pipe(fd2) < 0)  //建立两个管道
        err_sys("pipe error");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0){
        close(fd1[0]);
        close(fd2[1]);

        while (fgets(line, MAXLINE, stdin) != NULL) {  //父进程读数据
            n = strlen(line);
            if (write(fd1[1], line, n) != n) //写管道
                err_sys("write error to pipe");
            if ((n = read(fd2[0], line, n)) < 0) //从管道读
                err_sys("read error");
            if (n == 0) {  //没有读到数据，管道已关闭
                err_msg("child close pipe");
                break;
            }
            line[n] = 0;
            if (fputs(line, stdout) == EOF)  //输出
                err_sys("fputs error");
        }

        if (ferror(stdin))
            err_sys("fgets error on stdin");
        exit(0);
    } else {
        close(fd1[1]);
        close(fd2[0]);

        if (fd1[0] != STDIN_FILENO) {  //保证对应的输入输出是标准输入和标准输出
            if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)   //dup2 重定向标准输入输出到管道
                err_sys("dup2 error");
            close(fd1[0]);
        }

        if (fd2[1] != STDOUT_FILENO) {
            if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
                err_sys("dup2 error");
            close(fd2[1]);
        }

        if (execl("./add2", "add2", (char *)0) < 0)
            err_sys("execl error");
    }
    exit(0);
}

static void sig_pipe(int signo) {
    printf("SIGPIPE caught\n");
    exit(1);
}
```

如果在等待读取时add2进程被杀死，则会产生SIGPIPE信号。

add2用来读取输入的两个整数，返回相加的结果。

```c
#include "apue.h"

int main(void) {
    int n, int1, int2;
    char line[MAXLINE];

    while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) { //这里的读和写都是非缓冲区的，否则无法正常工作。
        line[n] = 0;
        if (sscanf(line, "%d%d", &int1, &int2) == 2) {
            sprintf(line, "%d\n", int1 + int2);
            n = strlen(line);
            if (write(STDOUT_FILENO, line, n) != n)
                err_sys("write error");
        } else {
            if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
                err_sys("write error");
        }
    }
}
```

### 15.4 FIFO

FIFO有时被称为命名管道。通过FIFO，不相关的进程也能交换数据。

