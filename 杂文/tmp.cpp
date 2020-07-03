
// bean标签的scope属性：
// 作用：指定bean标签的作用范围
// 取值：singleton: 单例（默认值）
//     prototype: 多例
//     request: 作用于web应用的请求范围
//     session: 作用于web应用的会话范围
//     global-session: 作用于集群环境的会话范围（全局会话范围），当不是集群环境时，它就是session

// bean对象的生命周期：
// 单例对象：立即
// 出生：当容器创建时对象出生
// 活着：容器还在，对象一直活着
// 死亡：容器销毁，对象消亡
// 总结：单例对象的生命周期和容器相同
// 多例对象：延迟
// 出生：当使用对象时，spring框架为我们创建
// 活着：对象只要在使用过程中就一直活着
// 死亡：当对象长时间不用且没有别的对象引用时，由Java的垃圾回收器回收


// 选项A：时间片轮转调度算法：
// 早期的时间片轮转调度法将所有进入系统的就绪进程按照先来先服务原则排队；每次调度时均由队首进程获取CPU并执行一个时间片；时间片用完后，计时器发出中断请求，调度程序中止当前进程将其放入队尾等待再次调度。

// 选项B：短进程优先调度算法：
// 从就绪队列中选择一个估计运行时间最短的进程获取处理机，使之立即执行直至任务完成或因为某事件被阻塞。相对于FCFS，SJ(P)F的平均周转时间和平均带权周转时间都显著缩短，即降低了作业的平均等待时间，提高了系统乔吐量。但是，进入系统的长作业可能被长期忽视，未考虑作业的紧迫程度(优先权)。

// 选项C：先来先服务调度算法：
// 指定最早进入就绪队列的进程可以获得处理机，使之运行，直到进程完成调度或发生某事件而阻塞后才放弃处理机。FCFS利于长作业和CPU繁忙型作业的调度，不利于短作业和I/O繁忙型作业调度。

// 选项D：高响应比优先调度算法：
// 为SJ(P)F中的所有进程引入动态优先权，并使作业的优先数随着等待时间的增加而提高，长作业在等待一定时间后一定有机会获得处理机。




// 1，字符串复制
// 2，TCP和UDP区别
// 3，三次握手
// 4，time_wait状态
// 5，多态，虚函数
// 6，100本书一次拿1~5本，先手赢还是后手赢
// 7，流量控制
// 8，linux下如何抓包
// 9，select 和epoll原理，epoll为什么快

// 对了那个面试官还说滑动窗口的数值每个包都会有吗？
// vector迭代器
// linux 进程 内存
// const
// 虚函数在子类中可以返回类型不同吗
// brk mmap 伙伴系统
// 死锁
// https://baike.baidu.com/item/%E9%A1%B5%E9%9D%A2%E7%BD%AE%E6%8D%A2%E7%AE%97%E6%B3%95
// https://blog.csdn.net/sinat_35261315/article/details/79243834
// https://my.oschina.net/manmao/blog/603253
// https://blog.csdn.net/buster2014/article/details/50084993
// https://www.cnblogs.com/weiyinfu/p/8822876.html
// https://www.cnblogs.com/hongdada/p/10406902.html
// https://blog.csdn.net/a3192048/article/details/82291222
// https://www.jianshu.com/p/74a4efacb0a7
// #include <bits/stdc++.h>
// using namespace std;
// const int MXN = 1e5 + 7;
// int n;
// char s[MXN], t[MXN];
// void get() {
//     int J = 1, no = 0;
//     for(int i = 1; i <= n; ++i) {
//         int fcnt = 0;
//         while(J <= n) {
//             if(s[J] == t[i]) ++ fcnt;
//             ++ J;
//             if(fcnt == 1) break;
//         }
//         if(fcnt == 1) ++ no;
//     }
//     printf("%d\n", J - no - 1);
// }
// int main() {
//     scanf("%d", &n);
//     scanf("%s%s", s + 1, t + 1);
//     get();
//     return 0;
// }
#include <iostream>
#include <semaphore.h>
#include <string.h>
#include <stdio.h>
#include <typeinfo>
using namespace std;
//信号量
sem_t sem;
void *run(void *ptr) {
    char *buf = (char *)ptr;
    while(strcmp("exit\n", buf) != 0) {
        //新号量-1
        sem_wait(&sem);
        cout << "thread output> " << buf << endl << flush;
    }
    return 0;
}

int main() {
    char buf[100] = {0};
    int ret = 0;
    pthread_t id;
    //初始化信号量数量为2。默认类型，非0位进程间共享
    ret = sem_init(&sem, 0, 2);
    if(ret) {
        cout << "sem_init failed" << endl;
    }
    pthread_create(&id, NULL, run, buf);
    //循环从标准输入读（fgets会将\n也读入）
    while(fgets(buf, sizeof(buf), stdin)) {
        if(strcmp("exit\n", buf) == 0) {
            break;
        }
        //信号量+1
        sem_post(&sem);
    }
    //清理信号量
    sem_destroy(&sem);
    return 0;
}