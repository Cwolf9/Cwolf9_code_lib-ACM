class A(object):
    def __enter__(self):
        print('__enter__() called')
        return self
    
    def print_hello(self):
        print("hello world!")

    def __exit__(self, e_t, e_v, t_b):
        print('__exit__() called')

# 首先会执行__enter__方法
with A() as a:    # a为__enter__的返回对象
    a.print_hello()
    print('got instance')
# 结束会执行__exit__方法

import re
 
line = "Cats are smarter than dogs"
 
matchObj = re.match(r'(.*) are (.*?) .*', line, re.M|re.I)
 
if matchObj:
   print ("matchObj.group() : ", matchObj.group())
   print ("matchObj.group(1) : ", matchObj.group(1))
   print ("matchObj.group(2) : ", matchObj.group(2))
   print(matchObj.groups())
else:
   print ("No match!!")

line = "Cats are smarter than dogs";
 
matchObj = re.search( r'dogs', line, re.M|re.I)
if matchObj:
   print("search --> searchObj.group() : ", matchObj.group())

pattern = re.compile(r'([a-z]+) ([a-z]+)', re.I)
m = pattern.match('Hello World Wide Web')
print(m.group())

it = re.finditer(r"\d+","12a32bc43jf3") 
for match in it: 
    print (match.group() )
print(it)
print(type(it))

def helli(str1) :
    return 'hello' + str1
list1 = [4, 5, 6, 8]
li = iter(list1)
print('---')

print(type(li))
for i in li:
    print(i)
    li.__next__()

student = [['Tom', 'A', 20], ['Jack', 'C', 18], ['Andy', 'B', 11]]
student.sort(key=lambda student: student[2])
print(student)

L = ['cat', 'binary', 'big', 'dog']
print(sorted(L, key=lambda x: (x[0], x[1])))
from pathlib import Path
log_dir = Path("D:\\a-university-study\\note\\anote")
log_file = log_dir / "电影.txt"
