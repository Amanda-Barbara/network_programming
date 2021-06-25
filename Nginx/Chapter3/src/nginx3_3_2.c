#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int g_mysign = 0;
void muNEfunc(int value)
{
    g_mysign = value;
}
//信号处理函数
void sig_usr(int signo)
{
    //不可重入函数的错误演示
    // int* p;
    // p = (int*)malloc(sizeof(int));
    // free(p);

    //不可重入函数的安全演示
    int myerrno = errno;
    int tmpsign = g_mysign;
    muNEfunc(22);
    if (signo == SIGUSR1)
    {
        printf("收到了SIGUSR1信号！\n");
    }
    else if (signo == SIGUSR2)
    {
        printf("收到了SIGUSR2信号！\n");
    }
    else
    {
        printf("收到了未捕捉的信号%d！\n", signo);
    }

    //不可重入函数的安全演示
    g_mysign = tmpsign;
    errno == myerrno;
    
}

int main(int argc, char* const *argv)
{
    if (signal(SIGUSR1,sig_usr) == SIG_ERR) //系统函数，参数1：是个信号，参数2：是个函数指针
    {
        printf("无法捕捉SIGUSR1信号！\n");
    }
    if (signal(SIGUSR2,sig_usr) == SIG_ERR)
    {
        printf("无法捕捉SIGUSR2信号！\n");
    }
    for(;;)
    {
        // sleep(1);
        // printf("休息1秒\n");
        int* p;
        p = (int*) malloc(sizeof(int));
        free(p);

        // muNEfunc(15);
        //sig_usr恰巧在此刻执行，把g_mysign的值修改了，那么程序是不安全的
        // printf("g_mysign=%d\n",g_mysign);
    }
    printf("再见！\n");
    return 0;
}