print(len('Pfs66WPhKHMEePlral5R5YhYgAZMogg9'))


def submitOJ(url):
    try:
        payload = {
            'id': '1476',
            'language': '1',
            'vcode': r'1134333333333333333335454546555555555556#include<bits/stdc++.h> int main() return 0;{}78',
            'csrf': 'sq5RkqPSzw3gW9d03mwdVZQlXAb410g1'
        }
        headers = {"user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
                'cookie': r"PHPSESSID=qqcf8q02s3qb90ttd1sf9i7324; lastlang=0",
                'Origin': 'http://pipioj.online',
                'Content-Type': 'application/x-www-form-urlencoded',
                'Referer': 'http://pipioj.online/submitpage.php?id=1476'
        }
        r = requests.post(url, headers = headers, data = payload)
        print(r.status_code, r.encoding, r.apparent_encoding)
        print(r.url)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        return r.text
    except :
        print("产生异常")
        return "产生异常"
def main():
    ans = submitOJ('http://pipioj.online/submit.php')
    # print(ans)
    with open("D:/iOJ.html", "w", encoding='utf-8') as f:
        f.write(ans)

import urllib.request   
url="https://www.baidu.com/"  
r=urllib.request.urlopen(url)    #返回文件对象
page=r.read()
print(page.decode('utf-8'))
print(r.url)

'''
检查Referer字段
HTTP头中有一个Referer字段，这个字段用以标明请求来源于哪个地址。在处理敏感数据请求时，通常来说，Referer字段应和请求的地址位于同一域名下。以上文银行操作为例，Referer字段地址通常应该是转账按钮所在的网页地址，应该也位于www.examplebank.com之下。而如果是CSRF攻击传来的请求，Referer字段会是包含恶意网址的地址，不会位于www.examplebank.com之下，这时候服务器就能识别出恶意的访问。
这种办法简单易行，工作量低，仅需要在关键访问处增加一步校验。但这种办法也有其局限性，因其完全依赖浏览器发送正确的Referer字段。虽然http协议对此字段的内容有明确的规定，但并无法保证来访的浏览器的具体实现，亦无法保证浏览器没有安全漏洞影响到此字段。并且也存在攻击者攻击某些浏览器，篡改其Referer字段的可能。
添加校验token
由于CSRF的本质在于攻击者欺骗用户去访问自己设置的地址，所以如果要求在访问敏感数据请求时，要求用户浏览器提供不保存在cookie中，并且攻击者无法伪造
的数据作为校验，那么攻击者就无法再运行CSRF攻击。
这种数据通常是窗体中的一个数据项。服务器将其生成并附加在窗体中，其内容是一个伪随机数。当客户端通过窗体提交请求时，这个伪随机数也一并提交上去以供
校验。正常的访问时，客户端浏览器能够正确得到并传回这个伪随机数，而通过CSRF传来的欺骗性攻击中，攻击者无从事先得知这个伪随机数的值，服务端就会因
'''