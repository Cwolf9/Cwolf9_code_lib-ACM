import requests
import json
def getHTMLText(url):
    try:
        r = requests.get(url, timeout=30)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        return r.text
    except :
        return "产生异常"
def tryPostFunc(url):
    try:
        payload = {'k1': 'v1', 'k2': 'v22222'}
        r = requests.post(url, data=json.dumps(payload))#可以是json，字典，或者字符串
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        print(r.cookies)
        return r.text
    except :
        return "产生异常"
# https://www.amazon.cn/dp/B07KZFR8GC
def getAmazonProd(url):
    # url = 'https://www.amazon.cn/gp/product/B01M8L5Z3Y'
    try:
        headers = {"user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
            'cookie': "session-id=457-3971279-1519700; i18n-prefs=CNY; ubid-acbcn=460-8830737-0904218; session-token=aq/cOEtIqWeIpAXvX6KWKJfWKx7/eiFNk5xC0tVHIgedvlhA+GSPotl5BLQRGBYU28vZKDFpcjiF0g0W97cFpOUKM1lvmE0p/b2mnJ/dfn7yv30xiE0v5k+9RSsE0GT/dYg/su2MpLgwIAfIG/NkPqoEPXYA8596+QnpHMR/hOMY5PJDab4Zve7pGYvsAMhI; session-id-time=2082729601l; csm-hit=tb:s-NGFBVAPWKY2K4M8E6EVH|1611753089216&t:1611753090428&adb:adblk_yes"
        }
        r = requests.get(url, timeout=30, headers = headers)
        print(r.status_code, r.encoding, r.apparent_encoding)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        return r.text[1000:]
    except :
        return "产生异常"
# "https://item.jd.com/60076267212.html"
def getJDProd(url):
    try:
        headers = {"User-Agent": "Chrome/88.0.4324.104"}
        dQ = {'keyword': '手机'}
        r = requests.get(url, timeout=30, headers = headers, params = dQ)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        # r.encoding = r.apparent_encoding
        print(r.url, r.request.url)
        return r.text
    except :
        return "产生异常"

if __name__ == "__main__":
    url2 = [
        "http://www.baidu.com",\
        'http://httpbin.org/post',\
        "http://lhlovedj.top",\
        "https://item.jd.com/60076267212.html",\
        "https://www.amazon.cn/dp/B07KZFR8GC",\
            ]
    # print(getHTMLText(url2[0]))
    print(tryPostFunc(url2[1]))
    # print(getJDProd(url2[3]))
    # print(getAmazonProd(url2[4]))
    # url = "https://search.jd.com/Search?"
    # html = getJDProd(url)
    # with open("D:/iJD手机.html", "w", encoding='utf-8') as f:
    #     f.write(html)
    #     f.close()
    print(r"sdhjhj\dfdf\"")
