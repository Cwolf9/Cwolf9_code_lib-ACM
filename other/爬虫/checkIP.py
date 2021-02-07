# https://www.cnblogs.com/zhaoxinhui/p/12383760.html
import requests
import random
import time
def main():
    http_ip = [
        '118.163.13.200:8080',
        '222.223.182.66:8000',
        '51.158.186.242:8811',
        '171.37.79.129:9797',
        '139.255.123.194:4550'
    ]

    for i in range(10):
        try:
            ip_proxy = random.choice(http_ip)
            proxy_ip = {
                'http': ip_proxy,
                'https': ip_proxy,
            }
            print('使用代理的IP:', proxy_ip)
            response = requests.get("http://httpbin.org/ip", proxies=proxy_ip)
            print(response.text)
            print('当前IP有效')
            time.sleep(2)
        except Exception as e:
            print(e.args[0])
            print('当前IP无效')
            continue


def ipTest():
    start = time.time()
    proxy={
        'http':'51.158.186.242:8811',
        'https': '51.158.186.242:8811',
    }
    response=requests.get("http://httpbin.org/ip", proxies=proxy)
    print(response.text)
    run_time = time.time() - start
    print('运行时间为%d分钟%d秒。%f.' % (run_time // 60, run_time % 60, run_time))

