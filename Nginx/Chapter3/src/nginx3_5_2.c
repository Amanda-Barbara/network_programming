#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void exectask()
{
    printf("执行了一次任务！\n");
}

void func(int sig)
{
    for (int i = 0; i < 6; i++)
    {
        printf("收到了信号%d，第%d\n", sig, i);
        sleep(1);
    }
    
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