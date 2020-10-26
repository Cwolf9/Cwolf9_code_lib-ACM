#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# author:Cwolf9 time :2020/07/29
from cyaron import * # 引入CYaRon的库
def ragv():
    x = randint(0, 1048576 - 1)
    return x
for i in range(1, 100): # 即在[L, R)范围内循环
    test_data = IO(file_prefix="", data_id=i) # 生成 heat[1|2|3].in/out 测试数据
    n = 1000000
    m = randint(1, n)
    test_data.input_writeln(n, m)
    seq = []
    #stri = ""
    for i in range(n):
        x = ragv()
        seq.append(x)
        #seq.append(str(a))
    #stri = ''.join(seq)
    test_data.input_writeln(seq)
    test_data.output_gen("D:\\std_binary.exe") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out
