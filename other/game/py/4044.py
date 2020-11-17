#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# author:Cwolf9 time :2020/07/29
from cyaron import * # 引入CYaRon的库
def ragv():
    x = randint(0, 1048576 - 1)
    return x
d = {}
for i in range(20, 31): # 即在[L, R)范围内循环
    test_data = IO(file_prefix="", data_id=i) # 生成 heat[1|2|3].in/out 测试数据
    tim = randint(900, 1000)
    k = randint(95, 100)
    test_data.input_writeln(tim, k)
    while k > 0:
        k = k - 1
        a = randint(1, 100)
        b = randint(1, 100)
        test_data.input_writeln(a, ' ', b)
    test_data.output_gen("D:\\ACM\\tmpFolder\\std.exe") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out
