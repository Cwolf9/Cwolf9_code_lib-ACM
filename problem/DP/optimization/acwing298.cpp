/*
**链接**
传送门: [here](https://www.acwing.com/problem/content/300/)
**题意**
题目链接：[here](https://www.acwing.com/problem/content/300/)
有$N$块木板从左到右排成一行，有$M$个工匠对这些木板进行粉刷，每块木板至多被粉刷一次。
第$i$个木匠要么不粉刷，要么粉刷包含木板$Si$的，长度不超过$Li$的连续的一段木
板，每粉刷一块可以得到$Pi$的报酬。
不同工匠的$Si$不同。
请问如何安排能使工匠们获得的总报酬最多。
$1\le N\le 16000$
$1\le M\le 100$
$1\le Pi\le 10000$
**思路**
$g[i]$表示前$i$块木板粉刷的最大收益
$h[j][i]$表示第$j$个工匠从第$S[j]$块木板开始向左至多粉刷$i$块木板的最大收益，当然第$S[j]$块木板是必刷的呀
状态转移：
- 当$i>S[j]\;and\;i - S[j] + 1 <= L[j]:$
 $g[i] = max(g[i], h[j][L[j]-(i-S[j]+1)] + P[j] * (i - S[j]))$

- 当$i == S[j]:$
 维护$h[j][k]$数组：$h[j][k] = max(g[i - x - 1] + (x + 1) * P[j]), 0\le x\le k$
 $g[i] = h[j][L[j]]$
答案是：$g[n]$

**备注**
https://www.acwing.com/solution/content/17766/
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, rng);
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
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e4 + 5;
const int MXE = 2e6 + 6;
// int n, m;
// int L[105], P[105], S[105];
// // int f[MXN];
// int g[MXN], h[105][MXN];
// int main() {
// #ifndef ONLINE_JUDGE
//     freopen("D:in.in", "r", stdin);
//     freopen("D:out.out", "w", stdout);
// #endif
//     n = read(), m = read();
//     for(int i = 1; i <= m; ++i) {
//         L[i] = min((int)read(), n);
//         P[i] = read();
//         S[i] = read();
//     }
//     for(int i = 1; i <= n; ++i) {
//         for(int j = 1; j <= m; ++j) {
//             if(L[j] == 0) continue;
//             if(i > S[j] && i - S[j] + 1 <= L[j])
//                 g[i] = max(g[i], h[j][L[j]-(i-S[j]+1)] + P[j] * (i - S[j]));
//             else if(i == S[j]) {
//                 int tmp = 0, k = 0;
//                 for(; k <= i - 1 && k + 1 <= L[j]; ++ k) {
//                     tmp = max(g[i - k - 1] + (k + 1) * P[j], tmp);
//                     h[j][k] = tmp;
//                 }
//                 for(; k <= L[j]; ++k) h[j][k] = max(h[j][k-1], h[j][k]);
//                 g[i] = max(g[i], tmp);
//             }
//             // else if(i < S[j] && S[j] - i + 1 <= L[j]) 
//                 // f[i] = max(f[i], g[i-1] + P[j]);
//         }
//         // debug(i, f[i])
//         g[i] = max(g[i-1], g[i]);
//     }
//     printf("%d\n", g[n]);
// #ifndef ONLINE_JUDGE
//     // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
//     // system("pause");
// #endif
//     return 0;
// }
int n, m;
int L[105], P[105], S[105], d[MXN];
int dp[105][MXN], Q[MXN], hd, tl;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        L[i] = min((int)read(), n);
        P[i] = read();
        S[i] = read();
        d[i] = i;
    }
    sort(d + 1, d + m + 1, [](const int &x, const int &y){return S[x] < S[y];});
    for(int ti = 1, i, i1; ti <= m; ++ ti) {
        i = d[ti];
        i1 = d[ti-1];
        hd = tl = 1;
        for(int j = max(0, S[i] - L[i]); j < S[i]; ++j) {
            while(hd < tl && dp[i1][Q[tl-1]] - P[i] * Q[tl-1] <= dp[i1][j] - P[i] * j) {
                -- tl;
            }
            Q[tl ++] = j;
        }
        for(int j = 1; j <= n; ++j) {
            dp[i][j] = max(dp[i1][j], dp[i][j-1]);
            if(j >= S[i]) {
                while(hd < tl && Q[hd] < j - L[i]) ++ hd;
                if(hd < tl) dp[i][j] = max(dp[i][j], dp[i1][Q[hd]] + P[i] * (j - Q[hd]));
            }
        }
        // debug(hd, tl)
        // assert(hd == tl);
    }
    for(int i = 1; i <= n; ++i) dp[d[m]][0] = max(dp[d[m]][0], dp[d[m]][i]);
    printf("%d\n", dp[d[m]][0]);
    return 0;
}