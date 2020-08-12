#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# author:Cwolf9 time :2020/07/29
from cyaron import * # 引入CYaRon的库
def ragv():
    opt = randint(0, 6)
    if opt == 0:
        x = randint(0, 100) - 100
        return x
    x = randint(0, 10000000)
    return x
for i in range(120, 150): # 即在[L, R)范围内循环
    test_data = IO(file_prefix="", data_id=i) # 生成 heat[1|2|3].in/out 测试数据
    n = randint(1, 12)
    m = randint(250, 400)
    test_data.input_writeln(n, m)
    seq = []
    #stri = ""
    for i in range(n):
        x = ragv()
        seq.append(x)
        #seq.append(str(a))
    #stri = ''.join(seq)
    test_data.input_writeln(seq)
    # chain = Graph.chain(n) # 生成一条n个节点的链，是Graph.tree(n, 1, 0)的别名
    
    flower = Graph.tree(n, weight_limit=(1,25))
    test_data.input_writeln(flower)
    # for edge in chain.iterate_edges():  # 遍历所有边，其中edge内保存的也是Edge对象
    #     test_data.input_writeln(edge.start, edge.end, 0)  # 输出这条边，以u v w的形式
    test_data.output_gen("D:\\std_binary.exe") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out
