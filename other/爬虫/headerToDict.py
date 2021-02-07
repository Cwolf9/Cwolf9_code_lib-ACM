import re
# 转换请求头
def headerToDict(s):
    #https://blog.csdn.net/qq_43088815/article/details/90214217
    #https://zhuanlan.zhihu.com/p/35656001
    t = re.sub(r'(?P<key>.*?): (?P<value>.*?),', "'\g<key>':'\g<value>',\n", s)
    return t
s = '''loginId: 15172425261,
password2: 2cfd4a4a8d8325540bfcb461e0179ffb7a0b3d438f0174c0fa610f6979fb9b2619ff3105e67bc2d2d2dc187c0a3e31d044bed17901d1808749560c8587de42df13e0b80fdc9da53c08de5e41866de04c20e7466fccdf9f38061767b913094ab9d4523815f0a39cc7765dd0e82821119909ddea0162b71d5a79389601b071d861,
keepLogin: false,
ua: 140#j4+opH2tzzPB/zo23bsz3pSXt1a+tnblYf95pQR9qFAwFt13H7PLi2l/JVfqileUzQVgOos2c6hqzznU6p9LDbszzZIXIHoulFzx2DD3VthqzFLIp+MHv9TrzIrbL8/qlbrzFbVFHjmijDapV4jYRkrHSoXaH7WSpu4PybrTbRAapvBRfA4DrO/PLHtenEQYsN75tRKsVYUj/IZk1Qs0B3DpttL16lNcx4xgvoZzjioRQRGhWVRDCaESEDIysjeO47ZleJJFPRStB42HY7QE/72wRNbHX6kQCv8OfhcTzICDbl0ucfoETyGXG6zI6t+/wBjgeYt5RnNJoWKH4UzmDlnm/ttq978Q+tHMUF8CGJcRlkpup5HQakFM3Tf7wUmP2zxvpjH/TReQXwc+FKqzZL3fCJrn8HmmJDHq3lB2xAqbVvgHKVBFyfMXZbdo2ZH1nQjaHgH1szbsjPQpF4oKWLvnUQQz1lez6t2qfKi3KfMbT7oanK3RZdZKMF7lrO1BXYqJMuF+E643Cu7+ENKjK74dOeaeF5+gLlhs1yqZldMpou8PwS6iQTt/qLoXrRCtSEUn3Uo45qOjXd+HIY04YDyzsovVPfiN5THq9QQreQm2Zfl8H9vyILEpwoS8wOAyYoHAFTctJKMXZNt9q/jtayhsuTJ+UI5IENJFTCbgfEhTg1hyg3QASPYZMzSXYPVUG/VxK3/W/IaPBuyGqnJe2AGBgCjsTtByW46ZNip2hHBfkZNGU5tvmEhkQzJKvw/OBlASXsboZCislIhqHZ+H6d7F9rwUkQz12iVkx8NcgtcGUg5raCtTAM+UJKXqQLT7PgmqXW0fDOwzGnblKvQJ1s8S35T+HofRytc6GX9pm2WrcjebNK2RL7F3O4mJSxNd1fplZzzUiva8hpz8U52rBx1rmL/tObC/Pjr54RZugj/2K7gnUjSzI/H+bTCdyFcApwjiIKvuonf7BljjMxIHHNmof91mnM/Dvf0AFXlOGz+=,
umidGetStatusVal: 255,
screenPixel: 1536x864,
navlanguage: zh-CN,
navPlatform: Win32,
appName: taobao,
appEntrance: taobao_pc,
_csrf_token: HqA00WQEu5zsSbuBnvLwi9,
umidToken: 7036346e59ee8664b3d7cf0b6e4df50e6ea4f7f0,
hsiz: 17b54f4e7e5b3a136597c2c5d57e44c0,
style: default,
appkey: 00000000,
from: tb,
isMobile: false,
lang: zh_CN,
returnUrl: http://i.taobao.com/my_taobao.htm,
fromSite: 0,'''
t = headerToDict(s)
print(t)
dic = {'a':'1', 'b':2}
print(dic)