#include <iostream>
#include <windows.h>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <assert.h>
#include <vector>
#include <queue>
using namespace std;

volatile int x = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
void *runA(void *ptr) {
    for(int i = 0, y; i < 10; i++) {
        pthread_mutex_lock(&m);
        pthread_cond_wait(&cond2, &m);
        cout << "A"; 
        pthread_mutex_unlock(&m);
        Sleep(100);
        pthread_cond_signal(&cond);
    }
    return 0;
}
void *runB(void *ptr) {
    for(int i = 0, y; i < 10; i++) {
        Sleep(100);
        pthread_cond_signal(&cond2);
        pthread_mutex_lock(&m);
        pthread_cond_wait(&cond, &m);
        cout << "B";
        pthread_mutex_unlock(&m);
    }
    return 0;
}
int main() {
    cout << pthread_self() << endl;
    // pthread_mutex_init(&m, nullptr);
    int ret[3];
    pthread_t id[3];
    ret[0] = pthread_create(&id[0], nullptr, runA, nullptr);
    ret[1] = pthread_create(&id[1], nullptr, runB, nullptr);
    if(ret[0] || ret[1]) {
        cout << "create thread failed " << endl;
        return 0;
    }
    pthread_join(id[0], nullptr);
    pthread_join(id[1], nullptr);
    printf("\n%d\n", x);
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cond);
}
/*
POSIX 引入了一个线程调度竞争范围(thread-scheduling contention scope)的概念
线程的contentionscope属性可是PTHREAD_SCOPE_PROCESS,也可以是PTHREAD_SCOPE_SYSTEM。带有PTHREAD_SCOPE_PROCESS属性的线程与它所在的进程中的其他线程竞争处理器资源。带有PTHREAD_SCOPE_SYSTEM属性的线程很像内核级线程，他们在全系统的范围内竞争处理器资源。POSIX的一种映射方式将PTHREAD_SCOPE_SYSTEM线程和内核实体之间绑定起来。
*/
