# 信号编程进阶、sigprocmask范例
1. 在真实的项目中，后台服务程序不受终端控制，程序在内存中运行，没有交互的界面，程序在内存中周期性或通过事件唤醒的方式执行任务。
2. 信号是用来通知进程发生了什么事件，无法给进程传递任何数据，进程对信号的处理方法有三种：
* 忽略某个信号，进程对该信号不做任何处理，就像未发生过一样。
a) 
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
## sigprocmask等信号函数的范例演示
