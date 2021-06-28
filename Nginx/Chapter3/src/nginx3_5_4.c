#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void hdfunc1(int sig);
void hdfunc2(int sig);

int main()
{
    signal(SIGINT, hdfunc1);  //键盘中断Ctrl+c
    signal(SIGTERM, hdfunc2); //采用kill + 进程id通知程序

    for (int ii = 1; ii < 100; ++ii)
    {
        printf("ii=%d\n", ii);
        sleep(1);
    }
    return 0;
}

void hdfunc1(int sig)
{
    sigset_t set;
    sigemptyset(&set);                  //清空信号集set
    sigaddset(&set, 15);                //把信号15添加到set信号集中，
    sigprocmask(SIG_BLOCK, &set, NULL); //阻塞信号集set，如果进程接收到15的信号则对其进行阻塞（进程接收到了信号15，但对其进行了阻塞，没有到达信号处理函数中去）

    printf("sig=%d\n", sig);
    for (int jj = 1; jj <= 5; ++jj)
    {
        printf("jj(%d)=%d\n", sig, jj);
        sleep(1);
    }
    sigprocmask(SIG_UNBLOCK, &set, NULL); //程序执行到这里，解除信号集set的阻塞
}

void hdfunc2(int sig)
{
    printf("sig=%d\n", sig);
    for (int jj = 1; jj <= 5; ++jj)
    {
        printf("jj(%d)=%d\n", sig, jj);
        sleep(1);
    }
}