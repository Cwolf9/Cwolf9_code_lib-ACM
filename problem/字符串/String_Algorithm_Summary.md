[TOC]



## Suffix Array Summay

参考：罗大佬后缀数组论文

### 单个字符串问题

#### 不可重叠最长重复子串 (poj1743)

二分答案把题目变成判定性问题。判断是否存在两个长度为$k$的子串是相同的。利用$height$数组将排序的后缀分成若干组，其中每组后缀的$height$都小于$k$。记录每组中$sa[i]$的最大值和最小值即可。

#### 可重叠的 $k$次最长重复子串 (poj3261)

出现次数至少$k$次，还是二分答案，常用套路按$height$分组，若存在一组后缀个数不小于$k$即有解。

#### 本质不同的子串个数 (spoj694,spoj705,2019牛客多校4I)

每个子串定是某个后缀的前缀，问题转化为求所有后缀之间不相同的前缀个数。枚举排序后的后缀数组，新加入一个后缀$suffix(sa[k])$后将产生$n-sa[k]+1-height[k]$个新的子串，累加即可答案为$\frac {n*(n+1)}2-\sum height[i]$。

#### 最长回文子串 (ural11297,UVA11475)

将原串反过来用一个特殊字符拼在一起，枚举每一位，分奇数串和偶数串计算以这个字符为中心的最长回文子串。两种情况都可转化为求一个后缀和反过来写的后缀的$lcp$，求出$height$数组即可解决此问题。

#### 连续重复子串 (poj 2406)

连续重复串：如果一个字符串$L$是由某个字符串$S$重复$R$次而得到的，则称$L$是一个连续重复串。$R$是这个字符串的重复次数。

求最小循环节，$kmp：\frac {len}{len-nex[len]}$；枚举答案$k$，若$lcp(suf(1),suf(1+k))==n-k$即可。

#### 重复次数最多的连续重复子串 (spoj687,poj3693)

这题看到网上很多大致思路相同，但是做法是假的的写法，我自己乱改了一下复杂度很稳定了。

先枚举$len$，得到重复次数最多的那些$len$，然后枚举求解字典序最小。记这个子字符串为$S$，那么$S$肯定包括了字符$r[0],r[len],r[len*2],...$中的某相邻的两个。先看字符$r[len*i],r[len*(i+1)]$往后能匹配长度$L$，因为答案的字符串可能不是以$r[L*i]$开头，但我们知道他错位数一定是$cha=len-L\%len$。所以我们把当前枚举的字符向前移$cha$位那个字符开始再求一遍$lcp(suf(x),suf(x+len))$即可，答案是$\frac L{len}+1$。

得到重复次数最多的那些$len$后，枚举排序后的后缀，在枚举$len$看是否合法即可。

---

### 两个字符串问题

#### 最长公共子串 (poj2774, ural11517)

按后缀排序后求排名相邻的不在同一串的两个后缀的$height$值的最大值。

#### 长度不小于$k$的公共子串的个数 (poj3415)

两串用一个不出现字符拼在一起求一遍后缀数组，分别算一次$s$串对$t$串的贡献和$t$串对$s$串的贡献。

令$height[i]=max(height[i]-k+1,0)$这是合法的贡献数量，维护一个单调递增的栈，栈里每个元素记录两个值：$height[],num$（$num$是贡献次数）。压入元素进栈后，弹出的元素的$height$值肯定把你压入元素的$height$要大，你要把弹出元素的$num$累加到新元素里面去。压入和弹出时要动态维护贡献值。每个元素贡献都是$height$乘上$num$。大致代码如下：

```cpp
for(int i = 2; i <= n + m + 1; ++i) {//分别算一次s对t的贡献和t对s的贡献
    vs.eb(SA.height[i]);
    if(SA.sa[i-1] > n) sum += SA.height[i];is.eb(1); else is.eb(0);
    while(vs.size() > 2 && vs.back() <= vs[vs.size()-2]) {
        LL vsa = vs.back(), isa = is.back();
        vs.pop_back(); is.pop_back();
        sum -= is.back()*(vs.back() - vsa);
        is[is.size()-1] += isa, vs[vs.size()-1] = vsa;
    }
    if(SA.sa[i] < n) ans += sum;
}
```

---

### 多个字符串问题

#### 不少于$k$个字符串中的最长重复子串 (poj3294,poj3450,poj3080)

给定$n(100)$个字符串(1000)，求出现在不小于$k$个字符串中的最长子串。[here]((https://blog.csdn.net/qq_39599067/article/details/95810586))

可以拼串+二分+常用套路分组判定解决，判断每组的后缀是否出现在不小于$k$个的原串中。

也可以直接单调栈写，拼串后记录每个字符所属字符串标号。

记录栈里面属于不同编号的后缀的数量。当栈里面$lcp$大小为$0$时，要移动左端点。当数量一旦达到$k$个，就求一下他们的$lcp$，取$max$。然后移动左端点，直到不同编号的后缀数量小于k。

```cpp
int ans = 0, cnt = 1, aim = k/2 + 1, l = 1; ++ vis[id[SA.sa[1]]];
for(int i = 2; i <= len; ++i) {
    if(vis[id[SA.sa[i]]] == 0 && id[SA.sa[i]]) ++ cnt; ++ vis[id[SA.sa[i]]];
    if(cnt >= aim) ans = max(ans, SA.RMQ_query(SA.sa[l+1], SA.sa[i]));
    while(l < i && SA.RMQ_query(SA.sa[l+1], SA.sa[i]) == 0) {
        -- vis[id[SA.sa[l]]];
        if(id[SA.sa[l]] && vis[id[SA.sa[l]]] == 0) -- cnt;
        ++ l; if(cnt >= aim) ans = max(ans, SA.RMQ_query(SA.sa[l+1], SA.sa[i]));
    }
    while(cnt >= aim && l < i) {
        -- vis[id[SA.sa[l]]];
        if(id[SA.sa[l]] && vis[id[SA.sa[l]]] == 0) -- cnt;
        ++ l; if(cnt >= aim) ans = max(ans, SA.RMQ_query(SA.sa[l+1], SA.sa[i]));
    }
}
```



#### 每个字符串至少出现两次且不重叠的最长子串 (spoj220,poj1226)
给定$n$个字符串，求在每个字符串中至少出现两次且不重叠的最长子串。

拼串+二分+常用套路分组判定解决。按$height$分组后记录来自每个字符串的$sa[i]$的最大值和最小值，当差大于二分的$mid$时，$cnt++$。



## AC-Automaton Summary

AC 自动机是 **以 TRIE 的结构为基础** ，结合 **KMP 的思想** 建立的。可进行多模式匹配。

kmp的next 指针求的是最长 Border（即最长的相同前后缀），而 fail 指针指向所有模式串的前缀中匹配当前状态的最长后缀。

### 求长度为n(2e9)不包含给定字符串的合法串个数

给定10个长度不超过10的字符串，对其建立AC自动机，将包含给定字符串的节点标记为坏节点。将非坏节点拎出来建立一个矩阵，两点权值为相互转换的方法数。跑一遍矩阵快速莫，第一行总和即为答案。

若n不是很大，可以dp求，$dp[i][j]=\sum dp[i-1][k]*dis[k][j]$。

### 包含至少一个词根长度不超过n(2e9)的字符串个数

5个长度不超过5的词根。用总方案数减去不合法方案数，不合法方案数和上题一样建立AC自动机，取出矩阵。上题总串长度给定，本题貌似需要求一个前缀和，只需在原矩阵基础在最右边添加一列值全为1即可。跑完矩阵快速幂后对第一行求和即可所有不合法方案数。总方案数也是一个简单矩阵构造。



## Suffix Automaton Summary

参考：[OI-wiki](https://oi-wiki.org/string/sam)

### SAM 的定义

字符串$s$的 SAM 是一个接受$s$的所有后缀的最小 **DFA** （确定性有限自动机或确定性有限状态自动机）。

- SAM 是一张有向无环图。节点被称作状态，边被称作状态间的转移。
- 图存在一个源点$t_0$，称作**初始状态**，其他各节点均可从$t_0$出发到达。
- 每个**转移**都标有一些字母。从一个节点出发的所有转移均不同。
- 存在一个或多个**终止状态**。每个终止状态都是字符串$s$的一个后缀。$s$的每个后缀均可用一条从$t_0$到某个终止状态的路径构成。
- 在所有满足上述条件的自动机中，SAM的节点数是最少的。

### SAM的性质

### 子串的性质

SAM 最简单、也最重要的性质是，它包含关于字符串$s$的所有子串的信息。任意从初始状态$t_0$开始的路径，如果我们将转移路径上的标号写下来，都会形成$s$的一个 **子串** 。反之每个$s$的子串对应从$t_0$开始的某条路径。

到达某个状态的路径可能不止一条，因此我们说一个状态对应一些字符串的集合，这个集合的每个元素对应这些路径。

### 结束位置 endpos

考虑字符串$s$的任意非空子串$t$，我们记$endpos(t)$为在字符串$s$中$t$的所有结束位置（假设对字符串中字符的编号从零开始）。

字符$s$的所有非空子串都可以根据它们的$endpos$集合被分为若干 **等价类** 。

**显然，SAM 中的每个状态对应一个或多个$endpos$相同的子串。**换句话说，SAM 中的状态数等于所有子串的等价类的个数，再加上初始状态。SAM 的状态个数等价于$endpos$相同的一个或多个子串所组成的集合的个数$+1$。

> **引理1：**两个非空子串$u$和$w$（假设$|u|\le|w|$）的$endpos$相同，当且仅当字符串$u$是$w$的后缀。
>
> **引理2：**考虑两个非空子串$u$和$w$（假设$|u|\le|w|$）。那么要么$endpos(u)\cap endpos(w)=\emptyset$，要么$endpos(w)\subseteq endpos(u)$，取决于是否为的一个后缀：

## Palindromic Tree(回文自动机) Summary

参考：[poursoul](https://blog.csdn.net/u013368721/article/details/42100363)

**回文树可以干啥？**

假设我们有一个串$S$，$S$下标从$0$开始，则回文树能做到如下几点：
>1.求串$S$前缀$0 - i$内**本质不同回文串的个数**（两个串长度不同或者长度相同且至少有一个字符不同便是本质不同）
>2.求串$S$内**每一个本质不同回文串出现的次数**
>3.求串$S$内**回文串的个数**（其实就是1和2结合起来）
>4.求以下标$i$结尾的回文串的个数

空间复杂度为$O(N*CharSize)$，时间复杂度为$O(N*log(CharSize))$。

应用：hdu6599,2019牛多校4I

```cpp
/*
pos[]数组记录原字符串端点对应回文树上的端点
len[i]表示编号为i的节点表示的回文串的长度（一个节点表示一个回文串）
next[i][c]表示编号为i的节点表示的回文串在两边添加字符c以后变成的回文串的编号（和字典树类似）。
fail[i]表示节点i失配以后跳转不等于自身的节点i表示的回文串的最长后缀回文串（和AC自动机类似）。
cnt[i]表示节点i表示的本质不同的串的个数(建树时求出的不是完全的，最后count()函数跑一遍以后才对)
num[i]表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数。
last指向新添加一个字母后所形成的最长回文串表示的节点。
S[i]表示第i次添加的字符（一开始设S[0] = -1（可以是任意一个在串S中不会出现的字符））。
p表示添加的节点个数。（p-2为本质不同回文串的个数）
n表示添加的字符个数。
一开始回文树有两个节点，0表示偶数长度串的根和1表示奇数长度串的根，且len[0] = 0，len[1] = -1，last = 0，S[0] = -1，n = 0，p = 2（添加了节点0、1）。
*/
struct Palindromic_Tree {
    static const int MAXN = 600005 ;
    static const int CHAR_N = 26 ;
    int next[MAXN][CHAR_N];//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[MAXN];//fail指针，失配后跳转到fail指针指向的节点
    int cnt[MAXN];
    int num[MAXN];
    int len[MAXN];//len[i]表示节点i表示的回文串的长度
    int S[MAXN];//存放添加的字符
    int last;//指向上一个字符所在的节点，方便下一次add
    int n;//字符数组指针
    int p;//节点指针
    int pos[MAXN];
    int newnode(int l) {//新建节点
        for (int i = 0; i < CHAR_N; ++i) next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }
    void init() {//初始化
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        S[n] = -1;//开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }
    int get_fail(int x) {//和KMP一样，失配后找一个尽量最长的
        while (S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }
    void add(int c, int id) {
        c -= 'a';
        S[++n] = c;
        int cur = get_fail(last);//通过上一个回文串找这个回文串的匹配位置
        if (!next[cur][c]) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);//新建节点
            fail[now] = next[get_fail(fail[cur])][c];//和AC自动机一样建立fail指针，以便失配后跳转
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = next[cur][c];
        cnt[last] ++;
        pos[last] = id;
    }
    void count() {
        for (int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
        for(int i = 0, tmp; i < p; ++i) {
            tmp = pos[i];
            if(len[i] % 2 == 0 && get_hash(tmp - len[i] + 1, tmp - len[i]/2) == get_hash(tmp - len[i]/2 + 1, tmp)) ANS[len[i]] += cnt[i];
            else if((len[i] & 1) && get_hash(tmp - len[i] + 1, tmp - len[i]/2) == get_hash(tmp - len[i]/2, tmp)) ANS[len[i]] += cnt[i];
        }
    }
} pt;
```





## Kmp & ExKmp Summary



## Manacher Summary



## Hash Summary









