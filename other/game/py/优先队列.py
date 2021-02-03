'''
https://www.yangyanxing.com/article/priorityqueue_in_python.html
'''
from queue import PriorityQueue
import time
import random
import threading

# 使用heapq实现优先队列
#定义一个可比较对象
class CompareAble:
    def __init__(self,priority,jobname):
        self.priority = priority
        self.jobname = jobname

    def __cmp__(self, other):
        if self.priority < other.priority:
            return -1
        elif self.priority == other.priority:
            return 0
        else:
            return 1

    def __lt__(self, other):
        if self.priority <= other.priority:
            return False
        else:
            return True

tasks = [(i, "do task %s"%i) for i in range(10,100,5)]
def produce(pq,lock):
    while True:
        lock.acquire()
        task = tasks[random.randint(0,len(tasks)-1)]
        print('put %s %s in pq'%(task[0],task[1]))
        pq.put(CompareAble(task[0],task[1]))
        lock.release()
        time.sleep(1)

def consumer(pq,lock):
    while True:
        lock.acquire()
        try:
            if pq.empty():
                continue
            task = pq.get_nowait()
            if task:
                print(task.priority, task.jobname)
        finally:
            lock.release()
            time.sleep(1)

def mmain():
    task_queue = PriorityQueue()
    task_lock = threading.Lock()
    for i in range(3):
        t = threading.Thread(target=produce,args=(task_queue,task_lock))
        t.setDaemon(False)
        t.start()
    for i in range(2):
        t = threading.Thread(target=consumer,args=(task_queue,task_lock))
        t.setDaemon(False)
        t.start()

# mmain()

from heapq import *
lst = [5, 8, 0, 4, 6, 7]
print(nsmallest(3, lst))
print(nlargest(3, lst))