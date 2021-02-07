url = 'https://www.lagou.com/jobs/positionAjax.json?city=%E5%B9%BF%E5%B7%9E&needAddtionalResult=false'
 
payload={
    'first': 'true',
    'pn': '1',
    'kd': '自然语言处理'   
}
 
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.86 Safari/537.36',
    'Referer': 'https://www.lagou.com/jobs/list_%E8%87%AA%E7%84%B6%E8%AF%AD%E8%A8%80%E5%A4%84%E7%90%86?px=default&city=%E5%B9%BF%E5%B7%9E',
    'Accept': 'application/json, text/javascript, */*; q=0.01'
}
 
urls ='https://www.lagou.com/jobs/list_%E8%87%AA%E7%84%B6%E8%AF%AD%E8%A8%80%E5%A4%84%E7%90%86?city=%E5%B9%BF%E5%B7%9E&cl=false&fromSearch=true&labelWords=&suginput='
s = requests.Session()
# 获取搜索页的cookies
r = s.get(urls, headers=headers, timeout=3)
r.encoding = r.apparent_encoding
print(r.text)
# 为此次获取的cookies
cookie = s.cookies
# 获取此次文本
response = s.post(url, data=payload, headers=headers, cookies=cookie, timeout=5).text
print(response)