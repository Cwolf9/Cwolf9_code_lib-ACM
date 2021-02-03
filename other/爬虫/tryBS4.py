from bs4.element import ProcessingInstruction
import requests
from bs4 import BeautifulSoup
import re

r = requests.get("http://python123.io/ws/demo.html")
demo = r.text
soup = BeautifulSoup(demo, "html.parser")
print(soup.prettify()[:100])
print(soup.title)
print(soup.a)
print(soup.a.get('href'))

soup2 = BeautifulSoup(open("D://demo.html", encoding = "utf-8"), "html.parser")
# print(soup2.prettify())
print(soup2.p)
print(soup2.p.string)
print(soup2.p.contents)
print(soup2.p.children, soup2.p.descendants)
# for x in soup2.p.children: 
#     print(x)

# for x in soup2.p.parents:
#     print(x)
#     print('\n\n')
print('---')
print(soup2.a.next_sibling.next_sibling)
x = soup2.a.next_sibling.next_sibling
for a in x.previous_siblings: 
    print(a)
print('---')
print(soup2.find_all('p', 'titl'))
headers = {"User-Agent": "Chrome/88.0.4324.104"}
r = requests.get("https://www.jianshu.com/p/dbb6e93fab08", headers = headers)
print(r.encoding, r.apparent_encoding)
r.encoding = r.apparent_encoding

with open("D:/idemo.html", "w", encoding='utf-8') as f:
    f.write(r.text)
    f.close()

soup3 = BeautifulSoup(r.text, "html.parser")
# print(soup3.title, str(soup3.a)[:10])
# print(soup3.a.name, soup3.a.parent.name)
# print(soup3.a.attrs)
# print(type(soup3.a.string))
# print(soup3.p.string)
