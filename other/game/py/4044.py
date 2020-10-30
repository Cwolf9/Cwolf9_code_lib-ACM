#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# author:Cwolf9 time :2020/07/29
from cyaron import * # 引入CYaRon的库
def ragv():
    x = randint(0, 1048576 - 1)
    return x
d = {}
for i in range(220, 221): # 即在[L, R)范围内循环
    test_data = IO(file_prefix="", data_id=i) # 生成 heat[1|2|3].in/out 测试数据
    tim = 20
    test_data.input_writeln(tim)
    n = 0
    while tim > 0:
        tim = tim - 1
        n = n + 1
        test_data.input_writeln(n)
    test_data.output_gen("D:\\ACM\\tmpFolder\\std.exe") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out
