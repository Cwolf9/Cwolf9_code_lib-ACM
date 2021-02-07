import requests
# from requests.api import head
url = "http://m.ip138.com/iplookup.asp"
try:
    headers = {"User-Agent": "Chrome/88.0.4324.104"}
    kv = {'ip': '183.226.23.150'}
    r = requests.get(url, params=kv, headers = headers)
    print(r.request.url)
    r.raise_for_status()
    r.encoding = r.apparent_encoding
    print(r.text[1850:2600])
except:
    print("爬取失败")