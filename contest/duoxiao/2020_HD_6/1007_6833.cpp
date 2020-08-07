/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6833)
**题意**
$T\le1e4,n\le2e5,k,x\le1e9$
求：
$$
\sum_{a_1=1}^n...\sum_{a_x=1}^n(\prod_{j=1}^xa_j^k)\times f(gcd(a_1,...,a_x))\times gcd(a_1,...,a_x)
$$
**思路**
$$
\sum_{a_1=1}^n...\sum_{a_x=1}^n(\prod_{j=1}^xa_j^k)=(\sum_{i=1}^ni^k)^x
$$
容易推导出：
$$\Downarrow$$
$$
\sum_{d=1}^nf(d)d^{xk}\sum_{p=1}^{\frac nd}\mu(p)\times p^{xk}\times S(\frac n{pd})
$$
比赛时的测评机全部预处理$O(n\times \sqrt n+T\sqrt n)$即可通过，比赛后的测评机记忆化处理也能过。
还可以进一步优化。
$$\Downarrow$$
$$
T=pd,\sum_{T=1}^nS(\frac nT)\times T^{xk}\sum_{p|T}\mu(p)f(\frac Tp)
$$
由于出题人不卡时限，所以$O(n\times log(n)+T\sqrt n)$或者$O(n+T\sqrt n)$均可以通过。
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <set>
#include <deque>
#include <list>
#include <bitset>
#include <complex>
#include <cassert>
#include <ctime>
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
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
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
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {putchar('0');if (f) putchar('\n');return;}
    if (x < 0) { putchar('-');x = -x;}
    static char s[23];int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {return a1 > a2 ? a1 : a2;}
template <class T>
T sml(const T &a1, const T &a2) {return a1 < a2 ? a1 : a2;}
template <typename T, typename... R>
T big(const T &f, const R &... r) {return big(f, big(r...));}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {return sml(f, sml(r...));}
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
void print(const T &f) {printf(ptout, f);putchar('\n');}
template <typename T, typename... R>
void print(const T &f, const R &... r) {printf(ptout, f);putchar(' ');print(r...);}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, k, x;
int dp[MXN], S[MXN], last[MXN];
int ksm(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = (int64)a * a % MOD) {if (b & 1) res = (int64)res * a % MOD;}
    return res;
}
bool noprime[MXN];
int pp[MXN/5], pcnt, mu[MXN], fu[MXN];
void init_prime() {
    noprime[0] = noprime[1] = 1;
    mu[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, mu[i]=-1;
        for(int j = 0; j < pcnt && i*pp[j] < MXN; ++j) {
            noprime[i*pp[j]] = 1;
            mu[i*pp[j]] = -mu[i];
            if(i % pp[j] == 0) {
                mu[i*pp[j]] = 0;
                break;
            }
        }
    }
    for(int i = 1; i < MXN; ++i) fu[i] = abs(mu[i]);
    for(int i = 1; i < MXN; ++i) {
        for(int j = i; j < MXN; j += i) {
            last[j] += mu[i]*fu[j/i];
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    int tim = read();
    k = read(), x = read();
    int tmp = 0;
    for(int i = 1; i < MXN; ++i) {
        tmp = (tmp + ksm(i, k));
        if(tmp >= mod) tmp %= mod;
        S[i] = ksm(tmp, x);
        dp[i] = ((int64)last[i]*ksm(i, (int64)k*x%(mod-1))%mod + dp[i-1])%mod;
    }
    while(tim -- ) {
        n = read();
        int ans = 0;
        for(int L = 1, R; L <= n; L = R + 1) {
            R = n/(n/L);
            ans = (ans + (int64)S[n/L]*(dp[R] - dp[L-1])%mod)%mod;
        }
        if(ans < 0) ans += mod;
        printf("%d\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}