import requests
import re
from bs4 import BeautifulSoup
import time
import json
import csv
def getTBHTMLText(url, dSearch):
    headers = {"user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
        "referer": "https://s.taobao.com/",
        'cookie': r"cookie2=17b54f4e7e5b3a136597c2c5d57e44c0; t=5b9661cda0b5e825c49d562bbebfb7f1; _tb_token_=57b73e781399b; _samesite_flag_=true; enc=4IcYQAEf6n8oYeYZDLKpWuyuMMQld6/11EcD6gmhQrw/ybZmwqhhOo45tTuOpZMXQNYfj/hoIHrzvTvg+5UuTA==; thw=cn; hng=GLOBAL|zh-CN|USD|999; alitrackid=www.taobao.com; xlly_s=1; lastalitrackid=www.taobao.com; mt=ci=0_0; cna=ghItGJbpnRQCAd73JQuwqdcQ; _m_h5_tk=258f615938a9fffd610ad420c8b6c038_1612187188554; _m_h5_tk_enc=adf4cac53165bdf2f886f6d44e09196f; JSESSIONID=CE1405197D4F86041BF290FE23160A41; l=eBaGSPBgOnge41TyBOfZhurza77TGIRfguPzaNbMiOCPOa1p5LY5W6MkobT9CnGVH62MR38KdX68B4TWsydVtSQ5uM80AC1Z3dC..; isg=BHR0od8YqLBu6QNHDIAcZcY9RTLmTZg3W5DG-A7Vc_-LeRXDNlkixwc7-bGhgdCP; tfstk=cKDPBufYZLpyLFyB68wFPQULnSPRZqa35traZXUZ4qH2xlPlik7Lmn_L0kz9n7f..; sgcookie=E1005JQj9/1cnplokvGtldOlk/RurBNfOYmf7En3q+qG0/3ENfVuDTUmdPd6ErRlZLt677g5UqtOmRtO/K7M1YbXjw==; unb=2665991651; uc1=cookie21=W5iHLLyFe3xm&cookie14=Uoe1gBpbBvXwQw==&pas=0&cookie16=W5iHLLyFPlMGbLDwA+dvAGZqLg==&existShop=false&cookie15=W5iHLLyFOGW7aA==; uc3=lg2=V32FPkk/w0dUvg==&nk2=3Rj2a800wpk=&vt3=F8dCuAbxCWMMXsmH758=&id2=UU6nRCwmzNLA9Q==; csg=339090b8; lgc=\u9152\u75AF\u72FClp; cookie17=UU6nRCwmzNLA9Q==; dnk=\u9152\u75AF\u72FClp; skt=3937ef62536f1fb6; existShop=MTYxMjE3ODU2OQ==; uc4=nk4=0@35PWOqVA3il14dduk5b6A0kRbw==&id4=0@U2xqIFo4BlQVQlqi37AO9HfxSNjE; tracknick=\u9152\u75AF\u72FClp; _cc_=VFC/uZ9ajQ==; _l_g_=Ug==; sg=p17; _nk_=\u9152\u75AF\u72FClp; cookie1=U7HwN3kxiXT7IEAcQ8eG3KkqRoGDI3P9LO+TJyuRgyU="
    }
    cookie_dict = {'cookie': r'cookie2=17b54f4e7e5b3a136597c2c5d57e44c0; t=5b9661cda0b5e825c49d562bbebfb7f1; _tb_token_=57b73e781399b; _samesite_flag_=true; enc=4IcYQAEf6n8oYeYZDLKpWuyuMMQld6/11EcD6gmhQrw/ybZmwqhhOo45tTuOpZMXQNYfj/hoIHrzvTvg+5UuTA==; thw=cn; hng=GLOBAL|zh-CN|USD|999; alitrackid=www.taobao.com; xlly_s=1; lastalitrackid=www.taobao.com; mt=ci=0_0; cna=ghItGJbpnRQCAd73JQuwqdcQ; _m_h5_tk=258f615938a9fffd610ad420c8b6c038_1612187188554; _m_h5_tk_enc=adf4cac53165bdf2f886f6d44e09196f; JSESSIONID=CE1405197D4F86041BF290FE23160A41; l=eBaGSPBgOnge41TyBOfZhurza77TGIRfguPzaNbMiOCPOa1p5LY5W6MkobT9CnGVH62MR38KdX68B4TWsydVtSQ5uM80AC1Z3dC..; isg=BHR0od8YqLBu6QNHDIAcZcY9RTLmTZg3W5DG-A7Vc_-LeRXDNlkixwc7-bGhgdCP; tfstk=cKDPBufYZLpyLFyB68wFPQULnSPRZqa35traZXUZ4qH2xlPlik7Lmn_L0kz9n7f..; sgcookie=E1005JQj9/1cnplokvGtldOlk/RurBNfOYmf7En3q+qG0/3ENfVuDTUmdPd6ErRlZLt677g5UqtOmRtO/K7M1YbXjw==; unb=2665991651; uc1=cookie21=W5iHLLyFe3xm&cookie14=Uoe1gBpbBvXwQw==&pas=0&cookie16=W5iHLLyFPlMGbLDwA+dvAGZqLg==&existShop=false&cookie15=W5iHLLyFOGW7aA==; uc3=lg2=V32FPkk/w0dUvg==&nk2=3Rj2a800wpk=&vt3=F8dCuAbxCWMMXsmH758=&id2=UU6nRCwmzNLA9Q==; csg=339090b8; lgc=\u9152\u75AF\u72FClp; cookie17=UU6nRCwmzNLA9Q==; dnk=\u9152\u75AF\u72FClp; skt=3937ef62536f1fb6; existShop=MTYxMjE3ODU2OQ==; uc4=nk4=0@35PWOqVA3il14dduk5b6A0kRbw==&id4=0@U2xqIFo4BlQVQlqi37AO9HfxSNjE; tracknick=\u9152\u75AF\u72FClp; _cc_=VFC/uZ9ajQ==; _l_g_=Ug==; sg=p17; _nk_=\u9152\u75AF\u72FClp; cookie1=U7HwN3kxiXT7IEAcQ8eG3KkqRoGDI3P9LO+TJyuRgyU='}
    try:
        reqS = requests.Session()
        # reqS.cookies.update(cookie_dict)

        cookies = requests.utils.cookiejar_from_dict(cookie_dict, cookiejar=None, overwrite=True)
        reqS.cookies = cookies
        print(cookies)
        '''
        <RequestsCookieJar[<Cookie cookie=cookie2=17b54f4e7e5b3a136597c2c5d57e44c0; t=5b9661cda0b5e825c49d562bbebfb7f1; _tb_token_=57b73e781399b; _samesite_flag_=true; enc=4IcYQAEf6n8oYeYZDLKpWuyuMMQld6/11EcD6gmhQrw/ybZmwqhhOo45tTuOpZMXQNYfj/hoIHrzvTvg+5UuTA==; thw=cn; hng=GLOBAL|zh-CN|USD|999; alitrackid=www.taobao.com; xlly_s=1; lastalitrackid=www.taobao.com; mt=ci=0_0; cna=ghItGJbpnRQCAd73JQuwqdcQ; _m_h5_tk=258f615938a9fffd610ad420c8b6c038_1612187188554; _m_h5_tk_enc=adf4cac53165bdf2f886f6d44e09196f; JSESSIONID=CE1405197D4F86041BF290FE23160A41; l=eBaGSPBgOnge41TyBOfZhurza77TGIRfguPzaNbMiOCPOa1p5LY5W6MkobT9CnGVH62MR38KdX68B4TWsydVtSQ5uM80AC1Z3dC..; isg=BHR0od8YqLBu6QNHDIAcZcY9RTLmTZg3W5DG-A7Vc_-LeRXDNlkixwc7-bGhgdCP; tfstk=cKDPBufYZLpyLFyB68wFPQULnSPRZqa35traZXUZ4qH2xlPlik7Lmn_L0kz9n7f..; sgcookie=E1005JQj9/1cnplokvGtldOlk/RurBNfOYmf7En3q+qG0/3ENfVuDTUmdPd6ErRlZLt677g5UqtOmRtO/K7M1YbXjw==; unb=2665991651; uc1=cookie21=W5iHLLyFe3xm&cookie14=Uoe1gBpbBvXwQw==&pas=0&cookie16=W5iHLLyFPlMGbLDwA+dvAGZqLg==&existShop=false&cookie15=W5iHLLyFOGW7aA==; uc3=lg2=V32FPkk/w0dUvg==&nk2=3Rj2a800wpk=&vt3=F8dCuAbxCWMMXsmH758=&id2=UU6nRCwmzNLA9Q==; csg=339090b8; lgc=\u9152\u75AF\u72FClp; cookie17=UU6nRCwmzNLA9Q==; dnk=\u9152\u75AF\u72FClp; skt=3937ef62536f1fb6; existShop=MTYxMjE3ODU2OQ==; uc4=nk4=0@35PWOqVA3il14dduk5b6A0kRbw==&id4=0@U2xqIFo4BlQVQlqi37AO9HfxSNjE; tracknick=\u9152\u75AF\u72FClp; _cc_=VFC/uZ9ajQ==; _l_g_=Ug==; sg=p17; _nk_=\u9152\u75AF\u72FClp; cookie1=U7HwN3kxiXT7IEAcQ8eG3KkqRoGDI3P9LO+TJyuRgyU= for />]>
        '''
        r = reqS.get(url, timeout=3, headers = headers, params = dSearch)
        print(r.status_code, r.encoding, r.apparent_encoding)
        print(r.request.url)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        # print(r.request.headers)
        # print(r.request.headers['cookie'])
        print(r.text)
        return r.text
    except :
        print("获取淘宝URL页面失败")
        return "获取淘宝URL页面失败"
def parsePage(ilt, html) :
    try:
        plt=re.findall(r'\"view_price\"\:\"[\d\.]*\"',html)
        tlt=re.findall(r'\"raw_title\"\:\".*?\"',html)
        urllt=re.findall(r'\"detail_url\"\:\".*?\"',html)
        for i in range(len(plt)):
            price = eval(plt[i].split(":")[1])
            title = eval(tlt[i].split(":")[1])
            urllt[i] = re.sub(r'https:', "", urllt[i])
            urlLink = eval(urllt[i].split(":")[1])
            urlLink = urlLink.encode('utf-8').decode('utf-8')
            if len(urlLink) > 120 or urlLink[2] != 'd' :
                continue
            ilt.append([price, urlLink, title])
    except:
        print("解析淘宝HTML内容失败")
def printComments(ilist):
    cnt = 0
    for x in ilist:
        print(cnt, x[0], x[1], x[2], x[3])
        cnt += 1
    print("")
# https://rate.tmall.com/list_detail_rate.htm?itemId=629748003807&spuId=1846540591&sellerId=268451883&order=3&currentPage=1&append=0&content=1&tagId=&posi=&picture=&groupId=&ua=098%23E1hvl9vnvPOvUpCkvvvvvjiWPLqZ1jEHRLFhAjthPmPhsjYbPLF9ljn2n2SOQjiRROvCvCLwjUYJDrMwznAa9lS5FMsJzVD448QCvvyvmCQmFgGvbvTVvpvhvvpvv29Cvvpvvvvv29hvCvvvMMGvvpvVvvpvvhCvKvhv8vvvvvCvpvvtvvmm7ZCvmR%2BvvvWvphvW9pvv9DDvpvACvvmm7ZCv2UVUvpvVmvvC9j3vuvhvmvvv9b%2B1eAw0mvhvLvCrpQvjn%2BkQ0f06WeCpqU0HsfUpwyjIAXcBKFyK2ixrQj7JVVQHYnFhAEI7nDeDyO2vSdtIjbmYSW94P5CXqU5EDfmlJ1kHsX7veEkevpvhvvmv9uQCvvyvmH9mKdIv8EQgvpvhvvvvvv%3D%3D&needFold=0&_ksTS=1612519758221_703&callback=jsonp704
def reqProdComments(url, csv_writer, num = 10): 
    if num > 20: num = 20
    if num <= 0: num = 10
    result = []
    head = {
        "referer": "https://detail.tmall.com/item.htm",
        'user-agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36',
        'cookie': r"cookie2=17b54f4e7e5b3a136597c2c5d57e44c0; t=5b9661cda0b5e825c49d562bbebfb7f1; _tb_token_=57b73e781399b; _samesite_flag_=true; enc=4IcYQAEf6n8oYeYZDLKpWuyuMMQld6/11EcD6gmhQrw/ybZmwqhhOo45tTuOpZMXQNYfj/hoIHrzvTvg+5UuTA==; thw=cn; hng=GLOBAL|zh-CN|USD|999; alitrackid=www.taobao.com; xlly_s=1; lastalitrackid=www.taobao.com; mt=ci=0_0; cna=ghItGJbpnRQCAd73JQuwqdcQ; _m_h5_tk=258f615938a9fffd610ad420c8b6c038_1612187188554; _m_h5_tk_enc=adf4cac53165bdf2f886f6d44e09196f; JSESSIONID=CE1405197D4F86041BF290FE23160A41; l=eBaGSPBgOnge41TyBOfZhurza77TGIRfguPzaNbMiOCPOa1p5LY5W6MkobT9CnGVH62MR38KdX68B4TWsydVtSQ5uM80AC1Z3dC..; isg=BHR0od8YqLBu6QNHDIAcZcY9RTLmTZg3W5DG-A7Vc_-LeRXDNlkixwc7-bGhgdCP; tfstk=cKDPBufYZLpyLFyB68wFPQULnSPRZqa35traZXUZ4qH2xlPlik7Lmn_L0kz9n7f..; sgcookie=E1005JQj9/1cnplokvGtldOlk/RurBNfOYmf7En3q+qG0/3ENfVuDTUmdPd6ErRlZLt677g5UqtOmRtO/K7M1YbXjw==; unb=2665991651; uc1=cookie21=W5iHLLyFe3xm&cookie14=Uoe1gBpbBvXwQw==&pas=0&cookie16=W5iHLLyFPlMGbLDwA+dvAGZqLg==&existShop=false&cookie15=W5iHLLyFOGW7aA==; uc3=lg2=V32FPkk/w0dUvg==&nk2=3Rj2a800wpk=&vt3=F8dCuAbxCWMMXsmH758=&id2=UU6nRCwmzNLA9Q==; csg=339090b8; lgc=\u9152\u75AF\u72FClp; cookie17=UU6nRCwmzNLA9Q==; dnk=\u9152\u75AF\u72FClp; skt=3937ef62536f1fb6; existShop=MTYxMjE3ODU2OQ==; uc4=nk4=0@35PWOqVA3il14dduk5b6A0kRbw==&id4=0@U2xqIFo4BlQVQlqi37AO9HfxSNjE; tracknick=\u9152\u75AF\u72FClp; _cc_=VFC/uZ9ajQ==; _l_g_=Ug==; sg=p17; _nk_=\u9152\u75AF\u72FClp; cookie1=U7HwN3kxiXT7IEAcQ8eG3KkqRoGDI3P9LO+TJyuRgyU="
    }
    itemId = re.search(r'id\=(\d+)', url).group(1)
    print("itemId:", itemId)
    sellerId = "268451883"
    try:
        url = "https:" + url
        r = requests.get(url, timeout=30, headers=head)
        r.raise_for_status()
        sellerId = re.search(r'sellerId\:\"(\d+)\"', r.text).group(1)
        print("sellerId: ", sellerId)
    except:
        print("获取淘宝评论出现bug1")
        return result
    dSearch = {
        "itemId":itemId,
        "sellerId": "196993935",
        "currentPage":"1",
        "callback": "jsonp704"
    }
    url = 'https://rate.tmall.com/list_detail_rate.htm'
    attris = ["displayUserNick", "auctionSku", "rateDate", "rateContent"]
    try:
        while len(result) < num :
            r = requests.get(url, timeout=30, headers=head, params = dSearch)
            r.raise_for_status()
            if r.text == "" :
                break
            rtext = r.text[11:-1]
            # print(rtext)
            rtjs = json.loads(rtext)
            comments = rtjs["rateDetail"]["rateList"]
            for comment in comments:
                tmp = []
                for attri in attris:
                    if(attri == 'rateContent') :
                        # comment[attri] = html.unescape(comment[attri]).replace(r'\n', ' ')
                        comment[attri] = comment[attri].replace('\n', ' ')
                    tmp.append(comment[attri])
                result.append(tmp)
                csv_writer.writerow(tmp)
                if len(result) == num:
                    break
            dSearch['currentPage'] = str(int(dSearch['currentPage']) + 1)
    except:
        print("获取淘宝评论出现bug2")
    return result

def getTBProdComments(url) :
    time.sleep(1)
    ilist = []
    with open('tbData.csv', 'a+', newline='', encoding='gb18030') as f:
        writer = csv.writer(f)
        writer.writerow(("用户昵称", "商品型号", "评论时间", "评论内容"))
        ilist = reqProdComments(url, writer)
    printComments(ilist)
def printGoodsList(ilt, num = 20):
    tplt = "{:4}\t{:8}\t{:16}\t{:16}"
    print(tplt.format("序号","价格","链接","商品名称"))
    count=0
    for g in ilt:
        count=count+1
        print(tplt.format(count,g[0],g[1],g[2]))
        if count == num:
            break
    print("")
def getTaobaoProd(qName = '手机', depth = 1):
    url = "https://s.taobao.com/search"
    # qName = input("请输入搜索商品名称：")
    dSearch = {'q': qName, 's': '0',
    'imgfile':'',
    'commend':'all','ssid':'s5-e','search_type':'item','sourceId':'tb.index','spm':'a21bo.2017.201856-taobao-item.1','ie':'utf8','initiative_id':'tbindexz_20170306'}
    infoList = []
    for i in range(depth):
        dSearch['s'] = str(44 * i)
        try:
            with open("D:/iTaobaoSJ.html", "r", encoding='utf-8') as f:
                # html = f.read()
                html = getTBHTMLText(url, dSearch)
                # parsePage(infoList, html)
                # if i == 0:
                #     with open("D:/iTaobaoSJ.html", "w", encoding='utf-8') as f:
                #         f.write(html)
        except:
            print("获取淘宝商品产生异常")
    return infoList

time.sleep(1)
def main():
    infoList = getTaobaoProd()
    printGoodsList(infoList)
main()
# getTBProdComments("//detail.tmall.com/item.htm?id=616313932022&ns=1&abbucket=10=")
s = "//detail.tmall.com/item.htm?id\u003d616313932022\u0026ns\u003d1\u0026abbucket\u003d10="
print(s)
print(s.encode("unicode_escape"))
print(s.encode("unicode_escape").decode("unicode_escape"))
matchObj  = re.search(r'id\=(\d+)', s)
print(matchObj.group(1))
print("end")

'''
https://login.taobao.com/newlogin/account/check.do?appName=taobao&fromSite=0&_bx-v=2.0.17
loginId: 15172425261
ua: 140#EDbovC1jzzPjgzo2Kx+Tw6Sr7z+OVoYxWDF0nBiNlW6/tn5KaRwFeavt644L87cghcys1I6ywwZj2F9olp1zz/BUUahe6zzxY2aDapluzzrb22U3lp1xzZ29V2EqlaOz2PD+V0LazF2VuOSJo00SONdOHaU+P6ZtqGaP1E/QnRyajxN+OvC5+6agSQKXt2lHKhmm2rYOr7x38bE6GHanptOI7BEntkSrU3Pm3rxar3vxvvpK3SLq7KW+HHw57wbkpn/wk6xL0ZesTb7aJo3ksiR0Yz9VlhxqqTUd68V6EpSf9U/flxc5wrpnaQ731S4dlE1/iCoXDJ3NPJmcXbZQVcKCB2hcTx+1IAHVvXvU+qOO2Pp7B94zybwnCZ5+2LzriglxJ4rc/vptugSmrpxeO7N25xv2PRr+tE68U4XTPT0+WP21atolY/LKpk71z45sU5i52nhCXWRugso7iHYx/+ztNZjXyGMSBUzxDvm4w0aNMaP467v2UTx+7Cx86JhPrlbS6IidpQsQTZ/Eq8lJ20dS5NC8IaSBfg6sA6Kp205JUB5MtpxVqzBI5cDqbbP5B9ErH0AvqrCRgQ+h3GoWb6scM5MbARQADyHnbv2SM7nIGURHu7LEhKhCIlPHS1EehXFDFaGvPj5GxzI/BxBPEGRmFmJpTv062JUf5V/ZWFt9pa8AOyDGaoff/3Pw+59JFT6NMug9hLjy29IDs9k378kp+Plwm5smTVZKUAx03ra5gzWS/GqQohh9w/VozHsGhumZTHR4IHtMLosOx8uqgZAAzz0fctHyYnR+XANLPB/W6swmqppqB7pm9yOZNiaIVlpbB8ZxF1/kMxE2JahrddiDDDZY2cI9Esv21DMOZHSpON9u7MjHoWN/p0pK73vrBsPKR0tEUEVjoAquWt/xVeKQR/BNVdVNuhoGaBnYOSudTJJaioxCzlXj+qee1jR8gWPuF7MHzuyVMauegVft9yw4INzn
umidGetStatusVal: 255
screenPixel: 1536x864
navlanguage: zh-CN
navUserAgent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.146 Safari/537.36
navPlatform: Win32
appName: taobao
appEntrance: taobao_pc
_csrf_token: HqA00WQEu5zsSbuBnvLwi9
umidToken: 7036646e5dee8644b3dacf0b4e4dfb0e6e94f7fe
hsiz: 17b54f4e7e5b3a136597c2c5d57e44c0
bizParams: 
style: default
appkey: 00000000
from: tb
isMobile: false
lang: zh_CN
returnUrl: http://i.taobao.com/my_taobao.htm?nekot=vsa36MDHbHA%3D1612600291168
fromSite: 0
bx-ua: undefined
bx-umidtoken: T2gAcyQJh8zPYUjSavc81S-lS_NPHm_zonle5MSIEvE8kTBCFg0qDFI6nwwrP2ilU6I=

 {"rgv587_flag": "sm", "url": "/newlogin/account/check.do/_____tmd_____/punish?x5secdata=5e0c8e1365474455070961b803bd560607b52cabf5960afff39b64ce58073f781623b2d284642db9fe9b0acd67b3def9a276aaeee5767421bdc9d7c5af795ea4896945aa9e4478a7b9211d36e18d582df7a9960ea00c81f59290bf2683bc6c366819ecc52786a052112497e395b08f56eb2bc16b1dbc91ea592f0222d32ec23f1976b91a091e5174a4153ee53f360b269783bbae415916f4e376d892cf8ccf5d22086f21483648721a731fa880c8c6a0b68b488542a1b34f8301d445f0c069a358fac186dad93c29d54f67986a9ac4af7c41cc3987ad876ba7af13bfee40af82364412e9e8f77a46a04d96ca084547f1165dd37aa6138b58f4ee6dfa387d87301434d87caf04a59720e4c6cea7300d81f2f18e6756705a2756b39ff629e9fab094c8bf63f830a5bbf7e4461239287b50f7e7f155431bef46ca9c9a283277265c904b3e1355e5216d6599b13922214c6771c6e0f093df3c328526c18aa9197c6a953234eddb1e4091bb0186fb01013a8dd2f5a1eba96d45f346c9f7581dd65da027407abee562d442224cbc2fe34113b52c49f9626f34a0134abaae08468cc240fdacd1557afa52558b4a864912846eb66b91e7222c1725e25fdf74b8a74af688f1c67c997c75e6bb235da4c45208f2665d9a678964b11679bf2531504047e854&x5step=2"}


https://login.taobao.com/newlogin/login.do?appName=taobao&fromSite=0&_bx-v=1.1.20
loginId: 15172425261
password2: 2cfd4a4a8d8325540bfcb461e0179ffb7a0b3d438f0174c0fa610f6979fb9b2619ff3105e67bc2d2d2dc187c0a3e31d044bed17901d1808749560c8587de42df13e0b80fdc9da53c08de5e41866de04c20e7466fccdf9f38061767b913094ab9d4523815f0a39cc7765dd0e82821119909ddea0162b71d5a79389601b071d861
keepLogin: false
ua: 140#j4+opH2tzzPB/zo23bsz3pSXt1a+tnblYf95pQR9qFAwFt13H7PLi2l/JVfqileUzQVgOos2c6hqzznU6p9LDbszzZIXIHoulFzx2DD3VthqzFLIp+MHv9TrzIrbL8/qlbrzFbVFHjmijDapV4jYRkrHSoXaH7WSpu4PybrTbRAapvBRfA4DrO/PLHtenEQYsN75tRKsVYUj/IZk1Qs0B3DpttL16lNcx4xgvoZzjioRQRGhWVRDCaESEDIysjeO47ZleJJFPRStB42HY7QE/72wRNbHX6kQCv8OfhcTzICDbl0ucfoETyGXG6zI6t+/wBjgeYt5RnNJoWKH4UzmDlnm/ttq978Q+tHMUF8CGJcRlkpup5HQakFM3Tf7wUmP2zxvpjH/TReQXwc+FKqzZL3fCJrn8HmmJDHq3lB2xAqbVvgHKVBFyfMXZbdo2ZH1nQjaHgH1szbsjPQpF4oKWLvnUQQz1lez6t2qfKi3KfMbT7oanK3RZdZKMF7lrO1BXYqJMuF+E643Cu7+ENKjK74dOeaeF5+gLlhs1yqZldMpou8PwS6iQTt/qLoXrRCtSEUn3Uo45qOjXd+HIY04YDyzsovVPfiN5THq9QQreQm2Zfl8H9vyILEpwoS8wOAyYoHAFTctJKMXZNt9q/jtayhsuTJ+UI5IENJFTCbgfEhTg1hyg3QASPYZMzSXYPVUG/VxK3/W/IaPBuyGqnJe2AGBgCjsTtByW46ZNip2hHBfkZNGU5tvmEhkQzJKvw/OBlASXsboZCislIhqHZ+H6d7F9rwUkQz12iVkx8NcgtcGUg5raCtTAM+UJKXqQLT7PgmqXW0fDOwzGnblKvQJ1s8S35T+HofRytc6GX9pm2WrcjebNK2RL7F3O4mJSxNd1fplZzzUiva8hpz8U52rBx1rmL/tObC/Pjr54RZugj/2K7gnUjSzI/H+bTCdyFcApwjiIKvuonf7BljjMxIHHNmof91mnM/Dvf0AFXlOGz+=
umidGetStatusVal: 255
screenPixel: 1536x864
navlanguage: zh-CN
navUserAgent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.146 Safari/537.36
navPlatform: Win32
appName: taobao
appEntrance: taobao_pc
_csrf_token: HqA00WQEu5zsSbuBnvLwi9
umidToken: 7036346e59ee8664b3d7cf0b6e4df50e6ea4f7f0
hsiz: 17b54f4e7e5b3a136597c2c5d57e44c0
bizParams: 
style: default
appkey: 00000000
from: tb
isMobile: false
lang: zh_CN
returnUrl: http://i.taobao.com/my_taobao.htm?nekot=vsa36MDHbHA%3D1612600291168
fromSite: 0
bx-ua: 140#Thfr4H2vzzFOIQo23bsz3pSXt1a tnblYf95pQR9qFAwFt13H7PLi2l/JVfqileUzQVgODz4y6hqzznU6p9LDbszzWb VY/ulFzx2DD3VthqzFZIp MHv0exzPFIV25etFrz2PoDzS5HnbZLMZ2aMX DN7JZuRx2LCcMj1uoA5IS/Seik7VsIUGxqJgclT1EVpslV LWtkXJTQDMkCtMxmEkaa5a3M4h54LK2AfsD3bYquI2A2NYIaaSByVMSgyumQ4Zi3r1a4tA2jlEB6FXIzNAImABRYOw9WCDEayVK3MoSzAR0ac4SWrhwdOz5C5QCK6IW1ZXC3YwEwR8utpuyXOXdDVmCW1eaowM7Ss9mkPkIojHLv/h2RNEaDfN3l0TC0N1fJXm4grjJX/HDKiHqgXHlmB9 hkmNyo EavkCv12bolz3JWFsybY/JSVui/7S/ftrpjQLe2/YHQgK3MqUs/1uKU3za7LqirayVlBJlSQj1vxWPXivIijrVTZ05XaTsazNAUjZ5mKQ8x1OS4PTABkMHeyFLp95dJY8OHrivx6EwpRlId/ALqQV92Rte8yWy8BTypqgL5TxDg/BrCX678NxBveeKfwNVWbPep/gyo75AOPmOV5e2 HCgoFG56 UO7UBsT9mUxrH1QrUsNu3rxar3vxvvpK3SLq7KW HHw57wbkpYiU8VUFy 51Lw4nS0U1r6Y4Mhc1uOAakOH/L8c9oIjzCpL/cFhQF0rjwV6QcLFaPa8rlwvjSqM3Vb1XkGgtY2/mD8g9GJsnefMvlrXMWiCEWn0j4prEhWZJS8ddci7153ME7WQ6wHLKBFyaf/0Melv82XTTnYAES2N/ycNvngjofibuLzah7wWMR5JitJx0Pak8djGMatW6Y4WOUoVqbo/1iHPdUoFoaf2eMC0khCF3wdcQGRQogP4riWP/6d1I1L1DI3EjgxW882kWz hwl7nihdZXW LSjY1UaTHb5yS/ZqeOX1lyEksnYHNMI6/O5cjhcYSlKLMl/fw8BP jFSHT/6 esj5Ojd9i8SwuUSOrYGnbuz9ChWQObjm/UoBrzTIJB5199SddJ/mTvDxRPQE4FPmR8owBwfuNYvua/bEZMRabQychlYll6Dhk5uzJmHjvVw3nfTRO30p4OkWfr4u7Z FZKE4sqEf9GwquKDAuaFasZKm84KzQOMHCB8SeJCI/utR5hRUXHWCgsvn/VhEvNrLxBulJYTT1ltNObNG2Pq3tTAUW/8Z6xfDprJc9mc5hZL8UvO Xr5uxpL8zuQV8XClv6WvvL qZd6lPFwKLRlwTVOdmutpSrx2gZqjsdVBf9 pbPh55gZGo7M6eINNYqdjZeITVYgRMy0sRqnuxl5B5Y9/JUsRGKCoh0DBGTTpb6y1hUZgMnpdJOQrae71Vsx1d qtsrE7JBRKNG7 =
bx-umidtoken: T2gAcyQJh8zPYUjSavc81S-lS_NPHm_zonle5MSIEvE8kTBCFg0qDFI6nwwrP2ilU6I=

{"rgv587_flag": "sm", "url": "/newlogin/login.do/_____tmd_____/punish?x5secdata=5e0c8e1365474455070961b803bd560607b52cabf5960afff39b64ce58073f781623b2d284642db9fe9b0acd67b3def9a276aaeee5767421bdc9d7c5af795ea4896945aa9e4478a7b9211d36e18d582df7a9960ea00c81f59290bf2683bc6c366819ecc52786a052112497e395b08f56eb2bc16b1dbc91ea592f0222d32ec23f1976b91a091e5174a4153ee53f360b269783bbae415916f4e376d892cf8ccf5d42d83c8982098d747174b3d076d737e9f6ffb3e37287f0dfabb381f37ad7700f93f33a57c1bd8a84c68bbe1052121ab17c41cc3987ad876ba7af13bfee40af82364412e9e8f77a46a04d96ca084547f1165dd37aa6138b58f4ee6dfa387d87301434d87caf04a59720e4c6cea7300d81f2f18e6756705a2756b39ff629e9fab094c8bf63f830a5bbf7e4461239287b50f7e7f155431bef46ca9c9a283277265c904b3e1355e5216d6599b13922214c67a921f00bf741d9d4e67937efa00c2dae61c2e60efc5820ae4a1630ff5ada667cc5990ce00f5ffa5f3cc929a54d61b05079e056de89a12da9512170201d32b4a9b24749603dfa93a95d2702cbc2acfc322bb2a4eb39065f21c2c77345b4a71f057089e2267391bc86127a719ce707fb8f8cf060cbce22ff836348da1ad4aa04b0&x5step=2"}


https://i.taobao.com/my_taobao.htm?nekot=vsa36MDHbHA%3D1612600291168

\u003d =
\u0026 &
jsonp704({rateDetail: {rateCount: {total: 20, shop: 0, picNum: 7, used: 1},…}})
rateDetail: {rateCount: {total: 20, shop: 0, picNum: 7, used: 1},…}
from: "search"
paginator: {lastPage: 1, page: 1, items: 20}
rateCount: {total: 20, shop: 0, picNum: 7, used: 1}
rateDanceInfo: {storeType: 4, currentMilles: 1612519758509, showChooseTopic: false, intervalMilles: 63551843180}
rateList: [,…]
0: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
aliMallSeller: false
anony: false
appendComment: null
attributes: ""
attributesMap: null
aucNumId: 0
auctionPicUrl: ""
auctionSku: "机身颜色:光合绿;套餐类型:官方标配;存储容量:8+128GB;版本类型:中国大陆"
buyCount: 0
carServiceLocation: ""
cmsSource: "天猫"
displayRatePic: ""
displayRateSum: 0
displayUserLink: ""
displayUserNick: "张***毫"
displayUserNumId: 0
displayUserRateLink: ""
dsr: 0
fromMall: true
fromMemory: 0
gmtCreateTime: {date: 30, hours: 12, seconds: 38, month: 0, timezoneOffset: -480, year: 121, minutes: 44,…}
goldUser: false
headExtraPic: ""
id: 1120797749329
memberIcon: ""
pics: []
picsSmall: []
position: ""
rateContent: "张钧甯+迪丽热巴全五分"
rateDate: "2021-01-30 12:44:38"
reply: "星光彩霞不及您的五分好评，山明水秀不及您的五分好评，什么都不及您给客服小**五分好评，三际数码期待您的再次光临！"
sellerId: 268451883
serviceRateContent: ""
structuredRateList: []
tamllSweetLevel: 3
tmallSweetPic: "tmall-grade-t3-18.png"
tradeEndTime: {date: 30, hours: 12, seconds: 55, month: 0, timezoneOffset: -480, year: 121, minutes: 41,…}
useful: true
userIdEncryption: ""
userInfo: ""
userVipLevel: 0
userVipPic: ""
videoList: []
1: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
2: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0,…}
3: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
4: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
5: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
6: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
7: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
8: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
9: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
10: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
11: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
12: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
13: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
14: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
15: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
16: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
17: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
18: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
19: {auctionPicUrl: "", userInfo: "", displayRatePic: "", dsr: 0, displayRateSum: 0, appendComment: null,…}
searchinfo: ""
tags: []
'''
