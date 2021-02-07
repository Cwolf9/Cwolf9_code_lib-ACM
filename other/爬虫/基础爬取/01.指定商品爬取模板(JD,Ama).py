import requests
import json
import time
def getHTMLText(url):
    headers = {
        'referer':'https://www.lagou.com/',
        'Accept':'application/json, text/javascript, */*; q=0.01',
        "User-Agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
        'cookie': r'JSESSIONID=ABAAAECABIEACCA54E406DD2305A3AF536D1B0C42D8A77C; WEBTJ-ID=2021025下午4:32:18163218-17771520cc935a-0a67b38f5886e2-33e3567-1327104-17771520cca380; RECOMMEND_TIP=true; PRE_UTM=; PRE_LAND=https://www.lagou.com/; user_trace_token=20210205163219-c61be90c-ccb0-4939-91d3-3dbf650d5820; LGUID=20210205163219-50b20c53-d557-4b9b-a877-c04732098ec1; _ga=GA1.2.896509233.1612513939; _gid=GA1.2.1872852181.1612513939; sajssdk_2015_cross_new_user=1; LGSID=20210205163219-bd67dcef-7ac4-4055-930f-cad0ddcbf335; PRE_HOST=www.baidu.com; PRE_SITE=https://www.baidu.com/link?url=Otnl_jtcMgyg9eSGA5OU2dZpBkbQXVFHgFeysj0OLAW&wd=&eqid=a1cea4d000048b5d00000006601d028e; sensorsdata2015session={}; index_location_city=全国; TG-TRACK-CODE=index_search; __lg_stoken__=2307eddceb331345fd3dddd65f46aca86501b45b756eb9a38626e0694b90c6ab4b6cf9e635f33cbe5286627bece2bc2a41478e9272a9afa4f636e5cdfb3d3d83aec18bba9fd0; Hm_lvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1612513939,1612513999,1612514022; X_HTTP_TOKEN=a6546f01c14d1cce8634152161a91cc83ee3e73d27; sensorsdata2015jssdkcross={"distinct_id":"17771520eaf7a0-0643975ebe99cd-33e3567-1327104-17771520eb0580","first_id":"","props":{"$latest_traffic_source_type":"直接流量","$latest_search_keyword":"未取到值_直接打开","$latest_referrer":"","$os":"Windows","$browser":"Chrome","$browser_version":"88.0.4324.146"},"$device_id":"17771520eaf7a0-0643975ebe99cd-33e3567-1327104-17771520eb0580"}; Hm_lpvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1612514368; LGRID=20210205163928-ee822d2d-4fd5-4c96-8052-6b2223bb7e28; SEARCH_ID=73c04338d3d347139e587a5d2da7c498'
    }
    try:
        r = requests.get(url, timeout=30, headers=headers)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        return r.text[:300]
    except :
        return "产生异常"
def tryPostFunc(url):
    try:
        payload = {'k1': 'v1', 'k2': 'v22222'}
        r = requests.post(url, data=json.dumps(payload), timeout=30)#可以是json，字典，或者字符串
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

def main():
    url2 = [
        "http://www.baidu.com",
        'http://httpbin.org/post',
        "http://lhlovedj.top",
        "https://item.jd.com/60076267212.html",
        "https://www.amazon.cn/dp/B07KZFR8GC",
        "https://www.lagou.com/jobs/list_c?labelWords=&fromSearch=true&suginput=",
            ]
    # print(getHTMLText(url2[0]))
    # print(tryPostFunc(url2[1]))
    # print(getJDProd(url2[3]))
    # print(getAmazonProd(url2[4]))
    # url = "https://search.jd.com/Search?"
    # html = getJDProd(url)
    # with open("D:/iJD手机.html", "w", encoding='utf-8') as f:
    #     f.write(html)
    #     f.close()
    print(getHTMLText(url2[5]))
    print(r"sdhjhj\dfdf\"")
main()
print('--')

