import requests
from bs4 import BeautifulSoup
from bs4 import element
def getHTMLText(url):
    try:
        r = requests.get(url, timeout=30)
        r.raise_for_status()  #如果状态不是200 引发http error异常
        r.encoding = r.apparent_encoding
        return r.text
    except :
        return "产生异常"
def fillUnivList(ulist, html):
    soup = BeautifulSoup(html, "html.parser")
    table = soup('table', 'rk-table')[0]
    theadTr = table.thead.tr.children
    for tr in table.tbody.children:
        if isinstance(tr, element.Tag):
            tds = tr('td')
            ulist.append([tds[0].contents[0].strip(), tds[1].a.string.strip(), tds[4].contents[0].strip()])

def printUnivList(ulist, num = -1):
    if num == -1:
        num = len(ulist)
    tplt =  "{0:^4}\t{1:{3}^12}\t{2:^8}" 
    print(tplt.format("排名","学校名称","总分", chr(12288)))
    for i in range(num):
        for j in range(3):
            ulist[i][j] = ulist[i][j].strip()
        print(tplt.format(ulist[i][0], ulist[i][1], ulist[i][2], chr(12288)))
    
def main():
    url = "https://www.shanghairanking.cn/rankings/bcur/2020"
    uinfo = []
    html = getHTMLText(url)
    fillUnivList(uinfo, html)
    printUnivList(uinfo, 20)

main()