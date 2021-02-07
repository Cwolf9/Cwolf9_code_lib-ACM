# https://blog.csdn.net/CUFEECR/article/details/105467109
# https://blog.csdn.net/aelous_dp/article/details/107461249
import requests
import re
from bs4 import BeautifulSoup
import time
import html
import csv
import json
def getHTMLText(url, code='utf-8'):
    head = {
        'referer': 'https://search.jd.com/',  # 每个页面的后半部分数据，是通过下拉然后再次请求，会做来源检查。
        'user-agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36',
        'Cookie': 'dasgfagda'
    }
    try:
        r = requests.get(url, timeout=30, headers=head)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except:
        print("获取京东URL页面失败")
        return "获取京东URL页面失败"

def parsePage(ilt, html):
    try:
        soup = BeautifulSoup(html, 'html.parser')
        nameInfo = soup.find_all('div', attrs={'class': 'p-name'})
        priceInfo = soup.find_all('div', attrs={'class': 'p-price'})
        # print(nameInfo)
        # print(priceInfo)
        for i in range(len(nameInfo)):
            glink = nameInfo[i].find('a')['href'][2:]
            titlelst = nameInfo[i].find('em').text.split()
            name = ""
            for j in range(len(titlelst)):  # 此处要注意循环变量不能混淆，与JS不同
                # 注意！！！此处之前是选择了截取长度，但是截取长度导致了后几个页面有些数据丢失，不知道为什么 :TODO
                name = name + titlelst[j]
                if len(name) >= 68:
                    break
                if j != len(titlelst) - 1:
                    name += " "
            price = priceInfo[i].find('strong').text
            if (price == '￥'):  # 特殊情况，特殊处理
                price = '￥' + priceInfo[i].find('strong')['data-price']
            ilt.append([price.strip(), glink.strip(), name.strip()])
    except:
        print("解析京东HTML内容失败")
def printGoodsList(ilt, num = 20):
    tplt = "{:4}\t{:8}\t{:20}\t{:20}"
    print(tplt.format("序号","价格","链接","商品名称"))
    count=0
    for g in ilt:
        count=count+1
        print(tplt.format(count,g[0],g[1],g[2]))
        if count == num:
            break
    print("")
def getJDProd(qName = '手机', depth = 1):
    timeID = '%.5f' % time.time()  # 时间戳保留后五位
    infoList = []
    for i in range(depth):
        try:
            with open("D:/iJDSJ.html", "r", encoding='utf-8') as f:
                html = f.read()
                url = 'https://search.jd.com/Search?keyword=' + qName + '&enc=utf-8&qrst=1&rt=1&stop=1&vt=2&wq=' + qName + '&cid2=653&cid3=655&page=' + str(
                    (i + 1) * 2 - 1) + '&click=0'  # 此处注意 应该给i加1，注意细节
                # html = getHTMLText(url)
                # if i == 0:
                #     with open("D:/iJDSJ.html", "w", encoding='utf-8') as f:
                #         f.write(html)
                parsePage(infoList, html)
                time.sleep(1)
        except:
            print("获取京东商品产生异常")
    return infoList
def reqProdComments(url, csv_writer, num = 10):
    if num > 20: num = 20
    if num <= 0: num = 10
    result = []
    pid = url.split('/')[-1].split('.')[0]
    head = {
        'referer': 'https://search.jd.com/',
        'user-agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36',
        'cookie':r'__jdv=76161171|direct|-|none|-|1611731017688; __jdu=16117310176871406427129; user-key=1a59fcf3-fdc0-4a17-9805-d1f856004223; areaId=4; shshshfpa=dee6d79e-ffb8-a320-e9a3-f4480a9d7fce-1611731020; shshshfpb=w8shDykhS2FrhhTT zWdgyA==; ipLoc-djd=4-50951-50965-0; TrackID=1_8mEDXIB1Q7ZUwfJVONM6zD2oq5ZVlZ1md2Kpd2eN2Ko9xYCmZFa7CR2GHjio_G0IPB9qjV0B_rbaPlmM-8Oh7hUcrxroe_D5MApgjx_-5AEfmFy_lMjJMxvx2PP5fOH; pinId=vFWcniFLl1Uf8axLOC0-K7V9-x-f3wj7; pin=jd_71e2e437693da; unick=Cwolf9; ceshi3.com=203; _tp=2DWUiz01VPtXkyXPx03anqCtVg+BiOtslrofe6wlPM0=; _pst=jd_71e2e437693da; __jdc=122270672; shshshfp=0f36980f1d4ef4d9a64edbe653fc0d4a; 3AB9D23F7A4B3C9B=H4JKAUHLDON5RAUTUQQCCKVZAIOC3QYU6GNCZI65J2ZMPNAMZMU6WUW53EIVIOS573UYQMRSJ7HFGZMSFTGBYLV5DU; cn=0; __jda=122270672.16117310176871406427129.1611731018.1612157993.1612322117.13; jwotest_product=99; JSESSIONID=F14A11AAF17621F4A34CA1EA86BD6245.s1; shshshsID=bc1d2b6be48b619180a26b0977c1db88_3_1612323809691; __jdb=122270672.3.16117310176871406427129|13.1612322117'
    }
    reCommentLi = re.compile(r'"guid":".*?"content":"(.*?)".*?"creationTime":"(.*?)",".*?"replyCount":(\d+),"score":(\d+).*?usefulVoteCount":(\d+).*?imageCount":(\d+).*?images":')
    # https://club.jd.com/comment/productCommentSummaries.action?referenceIds=100000499657
    dSearch = {
        "callback": "fetchJSON_comment98",
        "productId": pid,
        "score":"0","sortType":"5",
        "page":"0","pageSize":'10',
        "isShadowSku":"0","fold":"1",
    }
    url = 'https://club.jd.com/comment/productPageComments.action'
    attris = ["creationTime", "score", "replyCount", "usefulVoteCount", "imageCount", "content"]
    try:
        while len(result) < num :
            r = requests.get(url, timeout=30, headers=head, params = dSearch)
            r.raise_for_status()
            r.encoding = r.apparent_encoding
            comment_list = reCommentLi.findall(r.text)
            if r.text == "" or len(comment_list) == 0:
                break
            # print(r.text[20:-2])
            rtjs = json.loads(r.text[20:-2])
            comments = rtjs['comments']
            for comment in comments:
                tmp = []
                for attri in attris:
                    if(attri == 'content') :
                        # comment[attri] = html.unescape(comment[attri]).replace(r'\n', ' ')
                        comment[attri] = comment[attri].replace('\n', ' ')
                    tmp.append(comment[attri])
                result.append(tmp)
                csv_writer.writerow(tmp)
                if len(result) == num:
                    break
            # for comt in comment_list:
            #     if len(comt) != 6 :
            #         continue
            #     content = html.unescape(comt[0]).replace(r'\n', ' ')#将HTML转义字符如&;等转化成普通字符串
            #     creationTime = comt[1]
            #     replyCount = comt[2]
            #     score = comt[3]
            #     usefulVoteCount = comt[4]
            #     imageCount = comt[5]
            #     csv_writer.writerow((creationTime, score, replyCount, usefulVoteCount, imageCount, content))
            #     nli = [content]
            #     for i in range(1, 6):
            #         nli.append(comt[i].strip())
            #     result.append(nli)
            #     if len(result) == num:
            #         break
            dSearch['page'] = str(int(dSearch['page']) + 1)
    except:
        print("获取京东评论出现bug")
    return result
def printComments(ilist):
    cnt = 0
    for x in ilist:
        print(cnt, x[0], x[1], x[2], x[3], x[4], x[5])
        cnt += 1
    print("")
def getJDProdComments():
    time.sleep(1)
    ilist = []
    with open('jdData.csv', 'a+', newline='', encoding='gb18030') as f:
        writer = csv.writer(f)
        writer.writerow(('留言时间', '评分', '回复数', '点赞数', '图片数', '评论内容'))
        ilist = reqProdComments('https://item.jd.com/30191153091.html', writer)
    printComments(ilist)
def main():
    time.sleep(1)
    infoList = getJDProd()
    printGoodsList(infoList)
# main()
getJDProdComments()
print('hello')
"""
序号      价格          链接                      商品名称                
   1    ￥4198.00    item.jd.com/100009989503.html   vivo iQOO 7 12GB+256GB 传奇版 骁龙888 120W超快闪充 KPL官方赛事电竞手机 双模5G全网通vivoiqoo7
   2    ￥1099.00    item.jd.com/100016784100.html   Redmi Note 9 4G 6000mAh大电池 骁龙662处理器 18W快充 烟波蓝 6GB+128GB 游戏智能手机 小米 红米
   3    ￥599.00     item.jd.com/100014348492.html   Redmi 9A 5000mAh大电量 大屏幕大字体大音量 1300万AI相机 八核处理器 人脸解锁 4GB+64GB 砂石黑 游戏智能手机
   4    ￥599.00     item.jd.com/100014348478.html   Redmi 9A 5000mAh大电量 大屏幕大字体大音量 1300万AI相机 八核处理器 人脸解锁 4GB+64GB 晴空蓝 游戏智能手机
   5    ￥1099.00    item.jd.com/100016784108.html   Redmi Note 9 4G 6000mAh大电池 骁龙662处理器 18W快充 羽墨黑 6GB+128GB 游戏智能手机 小米 红米
   6    ￥2999.00    item.jd.com/100009630521.html   OPPO Reno5 5G 6400万水光人像四摄 65W超级闪充 12+256GB 星河入梦 全网通手机
   7    ￥16999.00   item.jd.com/100015137240.html   三星Galaxy Z Fold2 5G(SM-F9160)折叠屏 双模5G手机 骁龙865+ 内外双屏 120Hz自适应屏幕 12GB+512GB松烟墨
   8    ￥3799.00    item.jd.com/100009700283.html   OPPO Reno5 Pro 5G 6400万人像四摄 65W超级闪充 12+256GB 星河入梦 全网通手机
   9    ￥1599.00    item.jd.com/100009586257.html   Redmi Note 9 Pro 5G 一亿像素 骁龙750G 33W快充 120Hz刷新率 静默星空 6GB+128GB 游戏智能手机
  10    ￥1299.00    item.jd.com/100016773624.html   Redmi Note 9 5G 天玑800U 18W快充 4800万超清三摄 云墨灰 6GB+128GB 游戏智能手机 小米 红米
  11    ￥599.00     item.jd.com/100014348458.html   Redmi 9A 5000mAh大电量 大屏幕大字体大音量 1300万AI相机 八核处理器 人脸解锁 4GB+64GB 湖光绿 游戏智能手机
  12    ￥1799.00    item.jd.com/100009586259.html   Redmi Note 9 Pro 5G 一亿像素 骁龙750G 33W快充 120Hz刷新率 碧海星辰 8GB+128GB 游戏智能手机
  13    ￥4549.00    item.jd.com/100015911310.html   三星 Galaxy S20 FE 5G(SM-G7810)双模5G 骁龙865 120Hz屏幕刷新率 多彩雾面质感 游戏手机 8GB+128GB
  14    ￥4869.00    item.jd.com/100008348542.html   Apple iPhone 11 (A2223) 128GB 黑色 移动联通电信4G手机 双卡双待
  15    ￥1499.00    item.jd.com/100016324404.html   OPPO K7x 双模5G 4800万四摄 5000mAh长续航 90Hz电竞屏 蓝影6GB+128GB 30W闪充全网通手机
  16    ￥1999.00    item.jd.com/100016799352.html   Redmi Note 9 Pro 5G 一亿像素 骁龙750G 33W快充 120Hz刷新率 湖光秋色 8GB+256GB 游戏智能手机
  17    ￥1399.00    item.jd.com/100010338210.html   Redmi K30 王一博同款 120Hz流速屏 前置挖孔双摄 索尼6400万后置四摄 4500mAh超长续航 27W快充 8GB+128GB
  18    ￥1299.00    item.jd.com/100016813958.html   Redmi Note 9 5G 天玑800U 18W快充 4800万超清三摄 青山外 6GB+128GB 游戏智能手机 小米 红米
  19    ￥3599.00    item.jd.com/100010088735.html   荣耀V40 5G 超级快充 5000万超感光影像 8GB+128GB钛空银 移动联通电信5G 双卡双待
  20    ￥699.00     item.jd.com/100009082466.html   Redmi 8A 5000mAh大电量 大字体大音量大内存 骁龙八核处理器 AI人脸解锁 莱茵护眼全面屏 4GB+64GB 耀夜黑 游戏智能老人手机


https://club.jd.com/comment/productCommentSummaries.action?referenceIds=100000499657&callback=jQuery8754822&_=1612322147855
jQuery8754822({"CommentsCount":[{"SkuId":100000499657,"ProductId":100000499657,"ShowCount":120911,"ShowCountStr":"10万+","CommentCountStr":"400万+","CommentCount":4971879,"AverageScore":5,"DefaultGoodCountStr":"400万+","DefaultGoodCount":4018800,"GoodCountStr":"100万+","GoodCount":1149865,"AfterCount":12360,"OneYear":0,"AfterCountStr":"1万+","VideoCount":7102,"VideoCountStr":"7000+","GoodRate":0.98,"GoodRateShow":98,"GoodRateStyle":147,"GeneralCountStr":"8000+","GeneralCount":8354,"GeneralRate":0.014,"GeneralRateShow":1,"GeneralRateStyle":2,"PoorCountStr":"7000+","PoorCount":7294,"SensitiveBook":0,"PoorRate":0.006,"PoorRateShow":1,"PoorRateStyle":1}]});

https://club.jd.com/comment/productPageComments.action?callback=fetchJSON_comment98&productId=100000499657&score=0&sortType=5&page=0&pageSize=10&isShadowSku=0&fold=1

"""
