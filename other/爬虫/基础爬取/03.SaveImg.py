import requests
import os
import re
# 爬取图片
def main():
    url = "https://c-ssl.duitang.com/uploads/blog/202011/24/20201124103323_4bf51.jpg"
    root =  "C:/Users/Cwolf9/Documents/Scrshot/"  # 保存路径
    path = root + url.split('/')[-1]  # 新建文件名为root路径之后加上地址最后以“/”分割的部分
    try:
        if not os.path.exists(root):  # 判断括号里的文件是否存在的意思，括号内的可以是文件路径
            os.mkdir(root)  # 不存在则创建目录
        if not os.path.exists(path):  # 文件不存在则开始爬取保存
            r = requests.get(url)
            with open(path, 'wb') as f:
                f.write(r.content)#保存为二进制格式
                f.close()
                print("文件保存成功")
        else:
            print("文件已经存在")
    except:
        print("爬取失败")
'''
https://www.icourse163.org/learn/BIT-1001870001?tid=1461946455#/learn/forumdetail?pid=1319863872
https://github.com/xuehang00126/zh_mooc_reptile/blob/master/8.%E5%8D%95%E5%85%83%E5%85%AD.%E4%B8%AD%E5%9B%BD%E5%A4%A7%E5%AD%A6%E6%8E%92%E5%90%8D%E7%88%AC%E8%99%AB/UnivList.py
https://www.shanghairanking.cn/rankings/bcur/2020
https://www.vmgirls.com/13344.html
'''