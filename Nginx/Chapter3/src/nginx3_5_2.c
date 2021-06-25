#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void exectask()
{
    printf("执行了一次任务！\n");
}

void func(int sig)
{
    printf("收到了信号%d\n", sig);
}

int main()
{
    signal(SIGINT,func); //键盘中断Ctrl+c
    signal(SIGTERM,func); //采用kill + 进程id通知程序
    for(;;)
    {
        exectask(); //执行任务
        sleep(5);
    }
}