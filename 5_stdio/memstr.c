//
// Created by lifan on 2021/5/10.
//

#include "apue.h"

#define BSZ 48

//mac os上运行和linux上结果不同
int main(void)
{
    FILE *fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ-2);  //buf使用a初始化
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';   //修改最后两位
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) //会在开始处添加null
        err_sys("fmemopen failed");
    printf("initial buffer contents: %s\n", buf); //打印""
    fprintf(fp, "hello, world");
    printf("before flush: %s\n", buf); //写入hello world\0
    fflush(fp);
    printf("after fflush: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf)); //12

    memset(buf, 'b', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp, "hello, world"); //从12开始继续写，24写\0
    fseek(fp, 0, SEEK_SET); //定位到开头
    printf("after  fseek: %s\n", buf); //输出前24
    printf("len of string in buf = %ld\n", (long)strlen(buf)); //24

    memset(buf, 'c', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp, "hello, world");  //从开头继续写
    fclose(fp);
    printf("after fclose: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf)); //12

    return(0);
}
