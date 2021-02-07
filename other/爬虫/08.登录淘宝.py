import requests
import re
from bs4 import BeautifulSoup
import time
import json
import csv
import hashlib
def getMD5(s) :
    md5 = hashlib.md5()
    md5.update(s.encode('utf-8'))
    return md5.hexdigest()
import codecs
def bytesToStr(bs) :
    # s = "%E7%AC%94%E8%AE%B0%E6%9C%AC" #笔记本
    # s = s.replace('%', '\\x')
    # '\xE7\xAC\x94\xE8\xAE\xB0\xE6\x9C\xAC'
    # ss = codecs.escape_decode(s, 'hex-escape')[0]
    # print(ss.decode('utf-8'))
    bs = bs.replace('%', '\\x')
    bss = codecs.escape_decode(bs, 'hex-escape')[0]
    bss = bss.decode('utf-8')
    return bss
def postLoginTB() :
    """
    须知：
    开始前要自己先打开F12，登录淘宝，获取login_data的一些关键参数，例如：loginId,password2,ua,_csrf_token,umidToken,hsiz。这些参数可能会该改变。
    功能：
    首先发送post请求登录淘宝，登录成功的话，返回的页面内容大致如下：
    {"content":{"data":{"redirect":true,"redirectUrl":"https://i.taobao.com/my_taobao.htm?nekot=xxxxxxxxxx","asyncUrls":["https://passport.alibaba.com/mini_apply_st.js?callback=callback&site=0&token=xxxxxxxx"],"resultCode":100},"status":0,"success":true},"hasError":false}
    然后访问搜索笔记本页面，返回此页面内容。
    留坑：
    能登录成功的关键在于ua，有合法的基于用户身份的ua登录才不用滑块验证。一般输入完账户还没输入密码的时候就会发出一个post请求，带有ua，而且ua是动态的！
    这个ua是在登录页面的console通过命令：window["_n"] or window[UA_Opt.LogVal]获取。
    https://blog.csdn.net/weixin_41624982/article/details/86710995
    https://mp.weixin.qq.com/s?__biz=MzI2OTQ1NzEyMQ==&mid=2247483923&idx=1&sn=b54293568b411695dac564a6433c2016&chksm=eae1419ddd96c88bb653a1cef4b7cdbeb0ff5b983c173b4e3730f01b0dfec28d391a43c45b76&scene=21#wechat_redirect
    """
    login_url = "https://login.taobao.com/newlogin/login.do?appName=taobao&fromSite=0"
    login_headers = {
        'Connection': 'keep-alive',
        'Cache-Control': 'max-age=0',
        'Content-Type': 'application/x-www-form-urlencoded',
        "origin": "https://login.taobao.com",
        "referer": "https://login.taobao.com/member/login.jhtml",
        "user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
    }
    login_data = {
        'loginId':'15172425261',
        'password2':'2cfd4a4a8d8325540bfcb461e0179ffb7a0b3d438f0174c0fa610f6979fb9b2619ff3105e67bc2d2d2dc187c0a3e31d044bed17901d1808749560c8587de42df13e0b80fdc9da53c08de5e41866de04c20e7466fccdf9f38061767b913094ab9d4523815f0a39cc7765dd0e82821119909ddea0162b71d5a79389601b071d861',
        'keepLogin':'false',
        'ua':'140#9a1oE8+vzzP3Azo24i2Fw6Sra4E3njTP+pmb1lkzr6JVUvkOQOZ0w7Lfx9xT+Jg19wdevR2nak2JrZgqlbzx6Jh7wOjnzFr+s2Y0ltQzzPzbVXlqlbrnsv3GwEFw1D8+ji4IlpTzzPzYVXE/lb4hu8c+V8TKBjDI1wba7X5medetO4heA3zb5Paisy6MQ7Cs0YjvbbYPR8OppoxxC7uWGxuxTrIxpo4apn9GpqwEpQm+o1seFcOFUucqqM1UFyYsG+QO9BcpjoYMt6BhMr0RnwE8DNaT+lY8d0BOD04/sdGTadK5Jz2yQTdfxkaOMQK7usp4rgp8poslEjS8alc4eBsoQ87xesqPMiDOho6sE0OOjgWMbFpez+JBy9549wjRVz1qgLW8WDoMBh9WmIX/54/c7Q0Ap3ZVeMu++KdD+Ps40BxlqiIjwdg4IhuIw21BJKK5qtBrKYOXtxXPxghWZWn3tiuBTGt2WYPD7ceqkYug6sc4HM4UfCUufjIj+JoGW87/7P/vhxXRXsR8NAoaeL6Zdr9oABiOqhTqJLz++m399E6AQlwoFjGlc8LgHCVZroosGniw60dtF3c8u+MoN4udgu+IG03wPoCfDH+rOxwEwPcxiPYKzXmvXJtDNvVqtlo0VlEDjqYvx/tVWnD1iDpnNNINVXdPPkYY4TuYCvNQ2UE89eCAD/jmTX0gQu4ksNGgOANxi68aMMJj/4hev27s49sLy1JJWcuFH2tvzfNcWlhdE+6DZj5g06OvW1b0J0MDmur5DKvMGMK9r9SdcrxQ4Oe6koDgkLorFSJO5y6cKgDlMPVCuBSJTxHtM6jA5NxkUJB+orEwqSN/UhFm57DxUF8BQR7aR4gWIhNpBMgV8szMybz=',
        'umidGetStatusVal':' 255',
        'screenPixel':' 1536x864',
        'navlanguage':' zh-CN',
        "navUserAgent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.146 Safari/537.36",
        'navPlatform':' Win32',
        'appName':' taobao',
        'appEntrance':' taobao_pc',
        '_csrf_token':' HqA00WQEu5zsSbuBnvLwi9',
        'umidToken':' 7036346e59ee8664b3d7cf0b6e4df50e6ea4f7f0',
        'hsiz':' 17b54f4e7e5b3a136597c2c5d57e44c0',
        'style':' default',
        'appkey':' 00000000',
        'from':' tb',
        'isMobile':' false',
        'lang':' zh_CN',
        'returnUrl':' http://i.taobao.com/my_taobao.htm',
        'fromSite':' 0',
        'bx-ua': '140#Thfr4H2vzzFOIQo23bsz3pSXt1a tnblYf95pQR9qFAwFt13H7PLi2l/JVfqileUzQVgODz4y6hqzznU6p9LDbszzWb VY/ulFzx2DD3VthqzFZIp MHv0exzPFIV25etFrz2PoDzS5HnbZLMZ2aMX DN7JZuRx2LCcMj1uoA5IS/Seik7VsIUGxqJgclT1EVpslV LWtkXJTQDMkCtMxmEkaa5a3M4h54LK2AfsD3bYquI2A2NYIaaSByVMSgyumQ4Zi3r1a4tA2jlEB6FXIzNAImABRYOw9WCDEayVK3MoSzAR0ac4SWrhwdOz5C5QCK6IW1ZXC3YwEwR8utpuyXOXdDVmCW1eaowM7Ss9mkPkIojHLv/h2RNEaDfN3l0TC0N1fJXm4grjJX/HDKiHqgXHlmB9 hkmNyo EavkCv12bolz3JWFsybY/JSVui/7S/ftrpjQLe2/YHQgK3MqUs/1uKU3za7LqirayVlBJlSQj1vxWPXivIijrVTZ05XaTsazNAUjZ5mKQ8x1OS4PTABkMHeyFLp95dJY8OHrivx6EwpRlId/ALqQV92Rte8yWy8BTypqgL5TxDg/BrCX678NxBveeKfwNVWbPep/gyo75AOPmOV5e2 HCgoFG56 UO7UBsT9mUxrH1QrUsNu3rxar3vxvvpK3SLq7KW HHw57wbkpYiU8VUFy 51Lw4nS0U1r6Y4Mhc1uOAakOH/L8c9oIjzCpL/cFhQF0rjwV6QcLFaPa8rlwvjSqM3Vb1XkGgtY2/mD8g9GJsnefMvlrXMWiCEWn0j4prEhWZJS8ddci7153ME7WQ6wHLKBFyaf/0Melv82XTTnYAES2N/ycNvngjofibuLzah7wWMR5JitJx0Pak8djGMatW6Y4WOUoVqbo/1iHPdUoFoaf2eMC0khCF3wdcQGRQogP4riWP/6d1I1L1DI3EjgxW882kWz hwl7nihdZXW LSjY1UaTHb5yS/ZqeOX1lyEksnYHNMI6/O5cjhcYSlKLMl/fw8BP jFSHT/6 esj5Ojd9i8SwuUSOrYGnbuz9ChWQObjm/UoBrzTIJB5199SddJ/mTvDxRPQE4FPmR8owBwfuNYvua/bEZMRabQychlYll6Dhk5uzJmHjvVw3nfTRO30p4OkWfr4u7Z FZKE4sqEf9GwquKDAuaFasZKm84KzQOMHCB8SeJCI/utR5hRUXHWCgsvn/VhEvNrLxBulJYTT1ltNObNG2Pq3tTAUW/8Z6xfDprJc9mc5hZL8UvO Xr5uxpL8zuQV8XClv6WvvL qZd6lPFwKLRlwTVOdmutpSrx2gZqjsdVBf9 pbPh55gZGo7M6eINNYqdjZeITVYgRMy0sRqnuxl5B5Y9/JUsRGKCoh0DBGTTpb6y1hUZgMnpdJOQrae71Vsx1d qtsrE7JBRKNG7 =',
        'bx-umidtoken': 'T2gAcyQJh8zPYUjSavc81S-lS_NPHm_zonle5MSIEvE8kTBCFg0qDFI6nwwrP2ilU6I='
    }
    try:
        reqS = requests.Session()
        r = reqS.post(login_url, headers=login_headers, data=login_data,timeout=3)
        cookieJar = reqS.cookies
        cookieDict = requests.utils.dict_from_cookiejar(cookieJar)
        print(r.status_code, r.request.url)
        # 输出cookieJar和cookieDict
        print(cookieJar)
        print(cookieDict)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        print(r.text)
        url = "https://s.taobao.com/search?q=笔记本"
        r = reqS.get(url, headers=login_headers, timeout=3)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except :
        print("登录淘宝失败")
        return "登录淘宝失败"
def testSessionCookie() :
    """
    dic是上面登录淘宝后得到的cookieJar转换成的cookieDict
    本函数测试通过上面得到的cookie能否访问淘宝商品页面
    """
    dic = {'lc': 'VySm68lYV6GCfc2gkg%3D%3D', 'lid': '%E9%85%92%E7%96%AF%E7%8B%BClp', '_cc_': 'VFC%2FuZ9ajQ%3D%3D', '_l_g_': 'Ug%3D%3D', '_nk_': '%5Cu9152%5Cu75AF%5Cu72FClp', '_samesite_flag_': 'true', '_tb_token_': '3d7f85533e8be', 'cookie1': 'U7HwN3kxiXT7IEAcQ8eG3KkqRoGDI3P9LO%2BTJyuRgyU%3D', 'cookie17': 'UU6nRCwmzNLA9Q%3D%3D', 'cookie2': '1e0b4a022011f10cc1241c70145104de', 'csg': '50c32918', 'dnk': '%5Cu9152%5Cu75AF%5Cu72FClp', 'existShop': 'MTYxMjY4NDYyMw%3D%3D', 'lgc': '%5Cu9152%5Cu75AF%5Cu72FClp', 'sg': 'p17', 'sgcookie': 'E1004OHee30IDOjhPSWSU%2BeA%2F2mKa0Tgd4aJ2zcTZsJlu4EdsbVtybmLNFwphfRnXDZ2B2Ou27sy%2FwEH%2Bv0w1XERTw%3D%3D', 'skt': 'f3c173a2e907eef2', 't': '872f101011ab7eeb1b6370209ea7c705', 'tracknick': '%5Cu9152%5Cu75AF%5Cu72FClp', 'uc1': 'existShop=false&cookie14=Uoe1gB30%2BPSX2A%3D%3D&cookie21=Vq8l%2BKCLjA%2Bl&pas=0&cookie16=U%2BGCWk%2F74Mx5tgzv3dWpnhjPaQ%3D%3D&cookie15=V32FPkk%2Fw0dUvg%3D%3D', 'uc3': 'lg2=U%2BGCWk%2F75gdr5Q%3D%3D&vt3=F8dCuAc5ZLqEMvLdvi8%3D&nk2=3Rj2a800wpk%3D&id2=UU6nRCwmzNLA9Q%3D%3D', 'uc4': 'id4=0%40U2xqIFo4BlQVQlqi37AO884Z%2B6w5&nk4=0%4035PWOqVA3il14dduk5H5gvvgEA%3D%3D', 'unb': '2665991651', 'XSRF-TOKEN': '8c1a9750-3eda-485a-9efa-6fa32460e3bc'}
    cookieStr = ''
    for key in dic:
        cookieStr = cookieStr + key + '=' + dic[key] + ';'
    print(cookieStr)
    print("")
    headers = {"user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
        "referer": "https://s.taobao.com/",
        'cookie': cookieStr
    }
    url = "https://s.taobao.com/search?q=笔记本"
    r = requests.get(url, headers = headers, timeout=3)
    print(r.status_code, r.encoding, r.apparent_encoding)
    print(r.request.url)
    r.raise_for_status()
    r.encoding = r.apparent_encoding
    print(r.text)
def main() :
    rtext = postLoginTB()
    print(rtext)
main()
# testSessionCookie()