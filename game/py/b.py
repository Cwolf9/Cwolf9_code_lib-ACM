#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# author:Cwolf9 time :2020/07/29
from cyaron import * # 引入CYaRon的库
def ragv():
    opt = randint(0, 8)
    if opt == 0:
        x = randint(0, 10000)
        return x
    x = randint(0, 1000000000)
    return x
for i in range(200, 220): # 即在[L, R)范围内循环
    test_data = IO(file_prefix="", data_id=i) # 生成 heat[1|2|3].in/out 测试数据
    n = 100
    test_data.input_writeln(n)
    seq = []
    #stri = ""
    for i in range(n):
        x = ragv()
        seq.append(x)
        #seq.append(str(a))
    #stri = ''.join(seq)
    # test_data.input_writeln(seq)
    for i in range(n):
        x = randint(100000, 1000000000)
        test_data.input_writeln(x)
    test_data.output_gen("D:\\std_binary.exe") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out
