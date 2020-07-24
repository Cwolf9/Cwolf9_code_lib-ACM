/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6755)
**题意**
$1\le n,c\le1e18, 1\le k\le 1e5$
$Fib1=1,Fib1=1,Fib_n=Fib_{n-1}+Fib_{n-2}$
求$Fib_0^k+Fib_{c}^k+Fib_{2c}^k+...+Fib_{nc}^k,\;mod=1e9+9$

**前请提要**
[有关取模、同余、逆元的一些东西：](https://blog.csdn.net/qq_39599067/article/details/86498387)
$fib[n] = \frac{\sqrt5}{5}\times [(\frac{1+\sqrt5}{2})^n-(\frac{1-\sqrt5}{2})^n]$
$p = 1e9 + 9$
二次剩余：
$383008016^2 ≡ 5 (mod\;p)$
$383008016 ≡ \sqrt5 (mod\;p)$
$\frac{1}{\sqrt5}≡276601605(mod\;p)$
$383008016的逆元 = 276601605$
$(1+\sqrt5)/2≡691504013(mod\;p)$
$383008017\times 2的逆元 = 691504013$
$(1-\sqrt5)/2≡308495997(mod\;p)$
$(p-383008016+1)\times 2的逆元 = 308495997$

$fib[n] = 276601605\times [(691504013)^n-(308495997)^n] (mod\;\;p)$
$fib$前$n$项和等比数列求和：$sum = \frac{a}{a-1} \times (a^n - 1) (mod\;\;p) = a^2(a^n-1)(mod\;\;p)=a^{n+2}-a^2(mod\;\;p)$
当$p=1e9+9, a = 691504013或308495997时成立$。
**思路**
通过上面我们知道，在模$p=1e9+9$意义下有: 
$fib[n] = 276601605\times [(691504013)^n-(308495997)^n] (mod\;\;p)=d\times(a^n-b^n)$
$fib_{nc}=d\times(a^{cn}-b^{cn})=d\times(A^n-B^n)=FibC_n，\;A=a^c,B=b^c$
$(\frac1dfib_{nc})^k$二项式展开有：
$$C_k^0(A^n)^k+(-1)^1C_k^1(A^n)^{k-1}(B^n)+(-1)^2C_k^2(A^n)^{k-2}(B^n)^2+...+(-1)^rC_k^r(A^n)^{k-r}(B^n)^r+...+(-1)^{k-1}C_k^{k-1}(A^n)(B^n)^{k-1}+(-1)^kC_k^k(B^n)^k$$
$$C_k^0(A^k)^n+(-1)^1C_k^1(A^{k-1})^n(B)^n+(-1)^2C_k^2(A^{k-2})^n(B^2)^n+...+(-1)^rC_k^r(A^{k-r})^n(B^r)^n+...+(-1)^{k-1}C_k^{k-1}(A)^n(B^{k-1})^n+(-1)^kC_k^k(B^k)^n$$
现在我们要求$FibC$的前$n$项和，我们$O(k)$枚举$C_k^r$，逐项求出前$n$项和再累加即可。
对于$(-1)^rC_k^r$而言，令$a=A^{k-r}B^r$，前$n$项和为$(-1)^rC_k^r\times\frac {a\times(a^n-1)}{a-1}$
可以加的几个优化：
- 欧拉降幂，$n,c\le1e18,p=1e9+9$，$a^n(mod \;p)=a^{n\%\phi(p)}(mod\;p)$  \^_^
- $a=A^{k-r}B^r$没有必要预处理，我们可以在线求，令$a=A^k$，然后$a=a*b*inv(a)$即可
- 同理$a^n$也可以在线求，然后就过了。

**备注**
参考：[ACDreamers](https://blog.csdn.net/acdreamers/article/details/23039571)
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <assert.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {
        putchar('0');
        if (f) putchar('\n');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[23];
    int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {
    return a1 > a2 ? a1 : a2;
}
template <class T>
T sml(const T &a1, const T &a2) {
    return a1 < a2 ? a1 : a2;
}
template <typename T, typename... R>
T big(const T &f, const R &... r) {
    return big(f, big(r...));
}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {
    return sml(f, sml(r...));
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

#define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {
    printf(ptout, f);
    putchar('\n');
}
template <typename T, typename... R>
void print(const T &f, const R &... r) {
    printf(ptout, f);
    putchar(' ');
    print(r...);
}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 1000000009;
const int p1 = 691504013;
const int p2 = 308495997;
const int p3 = 276601605;
const int MXN = 1e5 + 5;
int64 n, c;
int k;
int F[MXN], invF[MXN];
int ksm(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = (int64)res * a % mod;
        a = (int64)a * a % mod;
        b >>= 1;
    }
    return res;
}
void init() {
    F[0] = 1;
    for (int i = 1; i < MXN; i++) F[i] = (int64)F[i - 1] * i % mod;  //阶乘
    invF[MXN - 1] = ksm(F[MXN - 1], mod - 2);
    for (int i = MXN - 2; i >= 0; i--)
        invF[i] = (int64)invF[i + 1] * (i + 1) % mod;  //阶乘的逆元
}
int C(int n, int m) {
    if (n < m) return 0;
    if (n == m) return 1;
    return (int64)F[n] * invF[m] % mod * invF[n - m] % mod;
}
void ck(int64 &a) {
    if(a >= mod) a %= mod;
}
void sb(int64 &b) {
    if(b < 0) b += mod;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    init();
    while (tim--) {
        n = read(), c = read(), k = read();
        int mn = n % mod, ol = c % (mod-1);
        int a = ksm(p1, ol), b = ksm(p2, ol);
        int inva = ksm(a, mod-2), t = ksm(a, k);
        ol = n % (mod-1);
        int bia = ksm((int64)b*inva%mod, ol), tn = ksm(t, ol);
        int64 ans = 0, tmp;
        for (int i = 0; i <= k; ++ i) {
            if(t != 1) {
                tmp = tn - 1;
                sb(tmp);
                tmp *= t;
                ck(tmp);
                tmp *= ksm(t - 1, mod - 2);
                ck(tmp);
            }else tmp = mn;
            if (i % 2 == 0){
                ans += C(k, i) * tmp % mod;
                ck(ans);
            }else {
                tmp = mod - tmp;
                ans += C(k, i) * tmp % mod;
                ck(ans);
            }
            tn = (int64)tn * bia % mod;
            t = (int64)t * b % mod * inva % mod;
        }
        printf("%lld\n", ans * ksm(p3, k) % mod);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}
