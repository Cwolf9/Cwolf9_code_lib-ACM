import requests
def getHTMLText(url, kv):
    try:
        r = requests.get(url, timeout=30, params=kv)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        print(r.url, r.request.url)
        return r.text[1000:2000]
    except :
        return "产生异常"
if __name__ == "__main__":
    url = 'http://www.baidu.com/s'
    kv = {'wd': 'ip'}
    print(getHTMLText(url, kv))

'''
http://www.baidu.com/s?wd=keyword
http://www.so.com/s?q=keyword
'''