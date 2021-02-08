import os
import requests
import re
from bs4 import BeautifulSoup
import time
import json
import csv
import hashlib
import codecs
def getMD5(s) :
    md5 = hashlib.md5()
    md5.update(s.encode('utf-8'))
    return md5.hexdigest()
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
reqS = requests.Session()
COOKIES_FILE_PATH = 'D:\\taobao_login_cookies.txt'
class TBLogin:
    """
    须知：
    开始前要自己先打开F12，登录淘宝https://login.taobao.com/member/login.jhtml，获取login_data的一些关键参数，例如：loginId,password2,ua,_csrf_token,umidToken,hsiz。这些参数可能会该改变。
    
    功能：
    参考别人博客的思路是，首先判断是否需要滑块验证，然后验证密码，验证成功的话，返回的页面内容大致如下：
    {"content":{"data":{"redirect":true,"redirectUrl":"https://i.taobao.com/my_taobao.htm?nekot=vsa36MDHbHA=1612689094592","asyncUrls":["https://passport.alibaba.com/mini_apply_st.js?callback=callback&site=0&token=1cV7NfuThwWJTwvOOI4cbTQ"],"resultCode":100},"status":0,"success":true},"hasError":false}
    asyncUrls是申请st码的地址
    然后通过申请st码的地址来获取st码，最后再使用st码登录。
    
    我个人感觉貌似只需要验证密码返回成功，就已经算登录成功了，因为验证完密码，就重定向到自己主页了，至于为什么要获取st码并再登录一次，不太清楚。

    留坑：
    能登录成功的关键在于ua，有合法的基于用户身份的ua登录才不用滑块验证。一般输入完账户还没输入密码的时候就会发出一个post请求，带有ua，而且ua是动态的！
    这个ua是在登录页面的console通过命令：window["_n"] or window[UA_Opt.LogVal]获取。
    @property什么用

    参考：
    [猪哥66](https://blog.csdn.net/u014044812/article/details/99584382)
    从代码层面将模拟登录淘宝分为以下四个步骤：
        输入用户名后，浏览器会向淘宝（taobao.com）发起一个post的请求，判断是否出现滑块验证！
        用户输入密码后，浏览器向淘宝（taobao.com）又发起一个post请求，验证用户名密码是否正确，如果正确则返回一个token。
        浏览器拿着token去阿里巴巴（alibaba.com）交换st码！
        浏览器获取st码之后，拿着st码获取cookies，登录成功
    https://www.cnblogs.com/542684416-qq/p/11427600.html

    https://blog.csdn.net/weixin_41624982/article/details/86710995
    https://mp.weixin.qq.com/s?__biz=MzI2OTQ1NzEyMQ==&mid=2247483923&idx=1&sn=b54293568b411695dac564a6433c2016&chksm=eae1419ddd96c88bb653a1cef4b7cdbeb0ff5b983c173b4e3730f01b0dfec28d391a43c45b76&scene=21#wechat_redirect
    """
    def __init__(self, loginId, password2, ua, _csrf_token, umidToken, hsiz) :
        """
        账号登录对象
        :param loginId: 用户名
        :param password2: 加密后的密码
        :param ua: 淘宝的ua参数
        :param _csrf_token: _csrf_token
        :param umidToken: 新版登录新增参数
        :param hsiz: hsiz
        """
        # 检测是否需要验证码的URL
        self.user_check_url = "https://login.taobao.com/member/request_nick_check.do?_input_charset=utf-8"
        # 'https://login.taobao.com/newlogin/account/check.do?appName=taobao&fromSite=0'
        # 验证淘宝用户名密码URL
        self.verify_password_url = "https://login.taobao.com/newlogin/login.do?appName=taobao&fromSite=0"
        # 申请st码地址
        self.apply_st_url = "https://passport.alibaba.com/mini_apply_st.js?callback=callback&site=0&token=1cV7NfuThwWJTwvOOI4cbTQ"
        # 使用st码登录的URL
        self.vst_url = 'https://login.taobao.com/member/vst.htm?st={}'
        # 淘宝个人主页URL
        self.my_taobao_url = 'http://i.taobao.com/my_taobao.htm'

        self.stma = "17C4JsU5lXRW2cQ60tOoV6A"
        self.loginId = loginId
        self.password2 = password2
        self.ua = ua
        self._csrf_token = _csrf_token
        self.umidToken = umidToken
        self.hsiz = hsiz

    def user_check_vcode(self) :
        """
        检测账号是否需要验证码
        :return:
        """
        print("调用账户是否需要滑动验证码接口(True:需要/False:不需要)")
        user_check_result = True
        user_check_url = self.user_check_url
        data = {
            "username": self.loginId,
            'ua': self.ua
        }
        try:
            user_check_response = reqS.post(user_check_url, data=data)
            user_check_result = user_check_response.json()["needcode"]
            print("返回结果为: %s" % user_check_result)
        except Exception as e:
            print("用户验证接口请求失败，msg:{}".format(e))
            user_check_result = True
            print("需要滑动验证，搞不定！休息10秒再来一次试试")
        return user_check_result

    def get_umidToken(self) :
        """
        获取umidToken参数
        :return:
        """
        response = reqS.get('https://login.taobao.com/member/login.jhtml')# 登录网址
        umidToken_match = re.search(r'"umidToken":"(.*?)"', response.text)
        print("umidToken: ", umidToken_match.group(1))
        return umidToken_match.group(1)

    def verify_password(self) :
        """
        验证账户密码是否正确
        :return:
        """
        verify_ans = False
        login_headers = {
            'Connection': 'keep-alive',
            'Cache-Control': 'max-age=0',
            'Content-Type': 'application/x-www-form-urlencoded',
            "origin": "https://login.taobao.com",
            "referer": "https://login.taobao.com/member/login.jhtml",
            "user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
        }
        login_data = {
            'loginId': self.loginId,
            'password2': self.password2,
            'keepLogin':'false',
            'ua': self.ua,
            'umidGetStatusVal':' 255',
            'screenPixel':' 1536x864',
            'navlanguage':' zh-CN',
            "navUserAgent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.146 Safari/537.36",
            'navPlatform':' Win32',
            'appName':' taobao',
            'appEntrance':' taobao_pc',
            '_csrf_token': self._csrf_token,
            'umidToken': self.umidToken,
            'hsiz': self.hsiz,
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
            r = reqS.post(self.verify_password_url, headers = login_headers, data = login_data, timeout = 3)
            cookieJar = reqS.cookies
            cookieDict = requests.utils.dict_from_cookiejar(cookieJar)
            print(r.status_code, r.request.url)
            # 输出cookieJar和cookieDict
            print(cookieJar)
            print(cookieDict)
            r.raise_for_status()
            r.encoding = r.apparent_encoding
            print("验证密码返回内容：")
            print(r.text)
            self.apply_st_url = r.json()['content']['data']['asyncUrls'][0]
            if self.apply_st_url:
                verify_ans = True
                print("验证密码并获取申请st码地址成功。")
            else:
                print("未获取到申请st码地址。")
        except :
            verify_ans = False
            print("验证密码并获取申请st码地址出现bug。")
        return verify_ans
    def apply_st(self) :
        """
        获取st码
        :return:
        """
        ast_flag = False
        try:
            r = reqS.get(self.apply_st_url)
            r.raise_for_status()
            st_match = re.search(r'"data":{"st":"(.*?)"}', r.text)
            self.stma = st_match.group(1)
            if self.stma:
                ast_flag = True
                print('获取st码成功，st码：{}'.format(st_match.group(1)))
            else :
                raise RuntimeError('获取st码失败')
        except Exception as e:
            print('申请st码请求失败!')
            ast_flag = False
        return ast_flag
    def login_with_stma(self) :
        """
        首先判断是否需要滑块验证，然后验证密码，然后获取st码，再使用st码登录
        :return:
        """
        login_result = False
        ucv_r = self.user_check_vcode()
        if ucv_r :
            return False
        vp_r = self.verify_password()
        if not vp_r :
            return False
        as_r = self.apply_st()
        if not as_r :
            return False
        login_headers = {
            'Connection': 'keep-alive',
            'Cache-Control': 'max-age=0',
            'Content-Type': 'application/x-www-form-urlencoded',
            "origin": "https://login.taobao.com",
            "referer": "https://login.taobao.com/member/login.jhtml",
            "user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
        }
        try:
            url = self.vst_url.format(self.stma)
            print('vst login url:')
            print(url)
            response = reqS.get(self.vst_url.format(self.stma), headers = login_headers, timeout = 3)
            response.raise_for_status()
            print("response.text:")
            print(response.text)
            print('--end--')
            my_taobao_match = re.search(r'top.location.href = "(.*?)"', response.text)
            print('登录淘宝成功，跳转链接：{}'.format(my_taobao_match.group(1)))
            self.my_taobao_url = my_taobao_match.group(1)
            login_result = True
            self.serialization_cookies()
        except Exception as e:
            print('登录淘宝失败，{}.'.format(e))
            login_result = False
        return login_result
    def serialization_cookies(self):
        """
        序列化cookies并保持cookieDict
        :return:
        """
        cookies_dict = requests.utils.dict_from_cookiejar(reqS.cookies)
        print('cookie 如下：')
        print(reqS.cookies)
        print(cookies_dict)
        with open(COOKIES_FILE_PATH, 'w+', encoding='utf-8') as file:
            json.dump(cookies_dict, file)
            print('保存cookies文件成功！')
    def deserialization_cookies(self) :
        """
        反序列化cookies
        :return:
        """
        cookies = ""
        with open(COOKIES_FILE_PATH, 'r+', encoding='utf-8') as file:
            cookies_dict = json.load(file)
            cookies = requests.utils.cookiejar_from_dict(cookies_dict)
        return cookies
    def load_cookies(self):
        """
        从COOKIES_FILE_PATH加载之前保存的cookieDict内容
        :return:
        """
        if not os.path.exists(COOKIES_FILE_PATH) :
            return False
        reqS.cookies = self.deserialization_cookies()
        try:
            self.get_taobao_nick_name()
        except Exception as e:
            os.remove(COOKIES_FILE_PATH)
            print('cookies过期，删除cookies文件！')
            return False
        print('加载淘宝cookies登录成功!!!')
        return True
    def get_taobao_nick_name(self) :
        """
        通过requests.Session()尝试获取淘宝昵称。
        最主要目的是判断Session中是否有合法的cookieJar。
        :return: 淘宝昵称
        """
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'
        }
        try:
            response = reqS.get(self.my_taobao_url, headers=headers)
            response.raise_for_status()
            nick_name_match = re.search(r'<input id="mtb-nickname" type="hidden" value="(.*?)"/>', response.text)
            if nick_name_match:
                print('登录淘宝成功，你的用户名是：{}'.format(nick_name_match.group(1)))
                return nick_name_match.group(1)
            else:
                raise RuntimeError('获取淘宝昵称失败！')
        except Exception as e:
            print('获取淘宝昵称失败！')
            return '获取淘宝昵称失败！'
    def testSessionCookie(self) :
        """
        dic是上面登录淘宝后得到的cookieJar转换成的cookieDict
        本函数测试通过上面得到的cookie能否访问淘宝商品页面
        :return:
        """
        dic = {}
        with open(COOKIES_FILE_PATH, 'r+', encoding='utf-8') as file:
            dic = json.load(file)
        cookieStr = ''
        for key in dic:
            cookieStr = cookieStr + key + '=' + dic[key] + ';'
        print(cookieStr)
        print("")
        headers = {"user-agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36',
            "referer": "https://s.taobao.com/",
            'cookie': cookieStr
        }
        testurl = "https://s.taobao.com/search?q=笔记本"
        try:
            r = requests.get(testurl, headers = headers, timeout = 3)
            print(r.status_code, r.encoding, r.apparent_encoding)
            print(r.request.url, r.url)
            r.raise_for_status()
            r.encoding = r.apparent_encoding
            print(r.text)
        except :
            print("test fail")
    def test(self) :
        """
        测试
        :return:
        """
        # self.user_check_vcode()
        self.login_with_stma()
        nick_name = self.get_taobao_nick_name()
def main() :
    loginId = '15172425261'
    password2 = '2cfd4a4a8d8325540bfcb461e0179ffb7a0b3d438f0174c0fa610f6979fb9b2619ff3105e67bc2d2d2dc187c0a3e31d044bed17901d1808749560c8587de42df13e0b80fdc9da53c08de5e41866de04c20e7466fccdf9f38061767b913094ab9d4523815f0a39cc7765dd0e82821119909ddea0162b71d5a79389601b071d861'
    ua = '140#9a1oE8+vzzP3Azo24i2Fw6Sra4E3njTP+pmb1lkzr6JVUvkOQOZ0w7Lfx9xT+Jg19wdevR2nak2JrZgqlbzx6Jh7wOjnzFr+s2Y0ltQzzPzbVXlqlbrnsv3GwEFw1D8+ji4IlpTzzPzYVXE/lb4hu8c+V8TKBjDI1wba7X5medetO4heA3zb5Paisy6MQ7Cs0YjvbbYPR8OppoxxC7uWGxuxTrIxpo4apn9GpqwEpQm+o1seFcOFUucqqM1UFyYsG+QO9BcpjoYMt6BhMr0RnwE8DNaT+lY8d0BOD04/sdGTadK5Jz2yQTdfxkaOMQK7usp4rgp8poslEjS8alc4eBsoQ87xesqPMiDOho6sE0OOjgWMbFpez+JBy9549wjRVz1qgLW8WDoMBh9WmIX/54/c7Q0Ap3ZVeMu++KdD+Ps40BxlqiIjwdg4IhuIw21BJKK5qtBrKYOXtxXPxghWZWn3tiuBTGt2WYPD7ceqkYug6sc4HM4UfCUufjIj+JoGW87/7P/vhxXRXsR8NAoaeL6Zdr9oABiOqhTqJLz++m399E6AQlwoFjGlc8LgHCVZroosGniw60dtF3c8u+MoN4udgu+IG03wPoCfDH+rOxwEwPcxiPYKzXmvXJtDNvVqtlo0VlEDjqYvx/tVWnD1iDpnNNINVXdPPkYY4TuYCvNQ2UE89eCAD/jmTX0gQu4ksNGgOANxi68aMMJj/4hev27s49sLy1JJWcuFH2tvzfNcWlhdE+6DZj5g06OvW1b0J0MDmur5DKvMGMK9r9SdcrxQ4Oe6koDgkLorFSJO5y6cKgDlMPVCuBSJTxHtM6jA5NxkUJB+orEwqSN/UhFm57DxUF8BQR7aR4gWIhNpBMgV8szMybz='
    _csrf_token = 'HqA00WQEu5zsSbuBnvLwi9'
    umidToken = '7036346e59ee8664b3d7cf0b6e4df50e6ea4f7f0' # '245ac74e4d57971b49813a9b2a19454faf54ac24'
    hsiz = '17b54f4e7e5b3a136597c2c5d57e44c0'
    tbl = TBLogin(loginId, password2, ua, _csrf_token, umidToken, hsiz)
    tbl.test()
    # with open(COOKIES_FILE_PATH, 'r+', encoding='utf-8') as file:
    #     dic = json.load(file)
    #     print("dic:")
    #     print(dic)
main()