#!/usr/bin/env python
# -*- coding: UTF-8 -*-
# author:Cwolf9 time :2020/07/29
from cyaron import * # 引入CYaRon的库
for i in range(11, 12): # 即在[L, R)范围内循环
    test_data = IO(file_prefix="", data_id=i) # 生成 heat[1|2|3].in/out 测试数据
    n = 10
    m = 10
    t = min(1000, randint(1, 50) * (n + m - 2))
    h = randint(0, 6)
    if h == 0:
        t = randint(1, 1000)
    if h < 3 and h >= 1:
        t = min(1000, randint(0, 255) * 4 + (n + m - 2))
    test_data.input_writeln(n, m, t)
    for i in range(n) :
        for j in range(m) :
            x = randint(t + 1, t + 10)
            x = min(x, 1000)
            test_data.input_write(x)
        test_data.input_writeln()
    test_data.output_gen("D:\\ACM\\tmpFolder\\std.exe") # 标程编译后的可执行文件，不需要freopen等，CYaRon自动给该程序输入并获得输出作为.out
