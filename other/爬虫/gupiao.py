'''
股票爬虫的新网站及代码
股票代码一览表：https://hq.gucheng.com/gpdmylb.html
股票数据来源：https://hq.gucheng.com
https://www.icourse163.org/learn/BIT-1001870001?tid=1461946455#/learn/forumdetail?pid=1320068406
1、采用国内源，加速下载模块的速度
2、常用pip源：
	-- 豆瓣：https://pypi.douban.com/simple
	-- 阿里：https://mirrors.aliyun.com/pypi/simple
3、加速安装的命令：
	-- >: pip install -i https://pypi.douban.com/simple 模块名
    
'''
import requests
from bs4 import BeautifulSoup
import re
import traceback

def getHTMLText(url):
    try:
        r = requests.get(url, timeout=30)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except:
        return ""

def getStockList(lst, stockURL):
    html = getHTMLText(stockURL)
    soup = BeautifulSoup(html, "html.parser")
    a = soup.find_all('a')
    for i in a:
        try:
            href = i.attrs['href']
            lst.append(re.findall(r"[S][HZ]\d{6}", href)[0])          #该网站为大写
        except:
            continue

def getStockInfo(lst, stockURL, fpath):
    count = 0
    for stock in lst:
        url = stockURL + stock
        html  =getHTMLText(url)
        try:
            if html == "":
                continue
            infoDict = {}
            soup = BeautifulSoup(html, "html.parser")
            stockInfo = soup.find('div', attrs={'class': "s_price"})        #根据网页源码
            infoDict['股票代码'] = stock                                    #
            price = stockInfo.find_all('em')[0].string                 #
            infoDict['股票价格'] = price                                    #

            #print(infoDict)                                                    #不写入文件可以屏幕输出
            with open(fpath, 'a', encoding='utf-8') as f:
                f.write(str(infoDict) + '\n')
                count = count + 1
                print("\r当前进度: {:.2f}%".format(count*100/len(lst)), end="")
        except:
            count = count + 1
            print("\r当前进度: {:.2f}%".format(count * 100 / len(lst)), end="")
            traceback.print_exc()
            continue


def main():
    stock_list_url = "https://hq.gucheng.com/gpdmylb.html"
    stock_info_url = "https://hq.gucheng.com/"
    output_file = "D://Stock.txt"
    slist = []
    getStockList(slist, stock_list_url)
    getStockInfo(slist, stock_info_url, output_file)

main()

