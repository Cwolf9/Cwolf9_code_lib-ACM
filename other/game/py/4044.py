#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# author:Cwolf9 time :2020/07/29
from cyaron import * # 引入CYaRon的库
def ragv():
    x = randint(0, 1048576 - 1)
    return x
d = {}
for i in range(50, 100): # 即在[L, R)范围内循环
    test_data = IO(file_prefix="", data_id=i) # 生成 heat[1|2|3].in/out 测试数据
    tim = randint(1, 100000)
    k = randint(1, 50000)
    test_data.input_writeln(tim, k)
    while tim > 0:
        tim = tim - 1
        a = randint(1, 10000000)
        test_data.input_write(a, ' ')
    test_data.input_writeln()
    test_data.output_gen("D:\\ACM\\tmpFolder\\std.exe") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out
