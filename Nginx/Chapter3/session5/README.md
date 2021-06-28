# 信号编程进阶、sigprocmask范例
1. 在真实的项目中，后台服务程序不受终端控制，程序在内存中运行，没有交互的界面，程序在内存中周期性或通过事件唤醒的方式执行任务。
2. 信号是用来通知进程发生了什么事件，无法给进程传递任何数据，进程对信号的处理方法有三种：
* 忽略某个信号，进程对该信号不做任何处理，就像未发生过一样。
a) 
3. 信号处理函数被中断
* 当一个信号到达后，进程会调用信号处理函数，如果这个时候进程接收了其他的信号，那么进程会中断之前的信号处理函数，等新的信号处理函数执行完成后再继续执行之前的信号处理函数。
* 当一个信号到达后，进程会调用信号处理函数，如果这个时候进程接收了与之前相同的信号，那么进程会对信号处理函数中信号做排队阻塞处理。
<details><summary>展开/收起</summary>
<pre><code>

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
</code></pre>
</details>  

a)信号被其他信号打断  
<details><summary>展开/收起</summary>
<pre><code>
执行了一次任务！
执行了一次任务！
收到了信号15，第0
收到了信号15，第1
收到了信号15，第2
收到了信号2，第0
收到了信号2，第1
收到了信号2，第2
收到了信号2，第3
收到了信号2，第4
收到了信号2，第5
收到了信号15，第3
收到了信号15，第4
收到了信号15，第5
执行了一次任务！
</code></pre>
</details>  

b) 同一个信号会排队阻塞  
<details><summary>展开/收起</summary>
<pre><code>
执行了一次任务！
执行了一次任务！
执行了一次任务！
执行了一次任务！
执行了一次任务！
^C收到了信号2，第0
收到了信号2，第1
收到了信号2，第2
收到了信号2，第3
收到了信号2，第4
收到了信号2，第5
执行了一次任务！
^C收到了信号2，第0
收到了信号2，第1
^C收到了信号2，第2
收到了信号2，第3
收到了信号2，第4
^C收到了信号2，第5
收到了信号2，第0
收到了信号2，第1
收到了信号2，第2
收到了信号2，第3
收到了信号2，第4

</code></pre>
</details>  

4. 信号的阻塞
* 如果不希望进程在接到信号时中断当前的信号处理函数，也不希望忽略该信号，而是延时一段时间再处理这个信号，这种情况可以通过阻塞信号来实现。
* 信号的阻塞和忽略是不同的，被阻塞的信号不会影响进程的行为，信号只是暂时被进程阻止传递，
* 信号的忽略是指信号被传递给进程，进程将其丢失，
* 执行信号的处理动作称为信号递达（Delivery），信号从产生到递达之间的状态称为信号未决（Pending）。
a) 执行  
```bash
./nginx3_5_3
```
b)打开另一个终端执行  
```bash
kill -15 347
kill -9  347
```
c)结果如下：
<details><summary>展开/收起</summary>
<pre><code>
ii=1
ii=2
ii=3
ii=4
ii=5
ii=6
ii=7
ii=8
ii=9
ii=10
ii=11
ii=12
ii=13
ii=14
ii=15
ii=16
ii=17
ii=18
ii=19
ii=20
ii=21
sig=15
jj(15)=1
jj(15)=2
jj(15)=3
jj(15)=4
jj(15)=5
sig=15
jj(15)=1
jj(15)=2
jj(15)=3
jj(15)=4
jj(15)=5
sig=15
jj(15)=1
jj(15)=2
jj(15)=3
jj(15)=4
jj(15)=5
sig=15
jj(15)=1
jj(15)=2
jj(15)=3
jj(15)=4
jj(15)=5
sig=15
jj(15)=1
jj(15)=2
jj(15)=3
jj(15)=4
jj(15)=5
sig=15
jj(15)=1
jj(15)=2
jj(15)=3
jj(15)=4
jj(15)=5
ii=22
ii=23
ii=24
Killed
</code></pre>
</details>  



```
signal(SIGINT,SIG_IGN);
signal(SIGTERM,SIG_IGN);
```

* 设置中断的处理函数，收到信号后，由该函数来处理。
a) 
```
void func(int sig)
{
    printf("收到了信号%d\n",sig);
}
signal(SIGINT,func);
signal(SIGTERM,func);

```
* 进程对传递的信号采用系统默认的处理操作，大部分的默认操作是终止进程。  
3. 在实际开发中，信号用于服务程序的退出。



## 信号集
1. 使用信号集来记录当前进程正在响应的信号与阻塞的信号，信号集使用sigset_t的结构类型来表示，
```
typedef struct{
    unsigned long sig[2];
}sigset_t;
```

## 信号相关函数
1. int sigemptyset(sigset_t* set)
* sigemptyset()清空set信号集
2. int sigfillset(sigset_t* set)
* 把所有的信号添加到set
3. int sigaddset(sigset_t* set, int signum)
* 把signum信号加入到set信号集
4. int sigdelset(sigset_t* set, int signum)
* 把signum信号从信号集set中删除
5. int sigismember(const sigset_t* set, int signum)
* 判断signum信号是否在信号集set中
6. sigprocmask(int how, const sigset_t* set, sigset_t* oldset)
* 根据how来判断是否阻塞信号set
7. int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact)
* sigaction结构体定义  
a) struct sigaction {
    void (*sa_handler)(int)
    void (*sa_sigaction)(int, siginfo_t*, void*);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
}  
b) 


## sigprocmask等信号函数的范例演示


