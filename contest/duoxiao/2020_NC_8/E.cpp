/*
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/5673/E)
**题意**
$T,l,r\le 1e5$
$\sum_{i=l}^rf(i),1\le l\le r\le 1e5,f(i)=\sum_{l=1}^i$用$(l,l+1,l+2)$划分整数$i$的方案数
**思路**
法一：
$l$小于300完全背包计算
$l$大于300暴力枚举计数，分成枚举$l$和$l+1$及$l+1$和$l+2$两种情况，$2$个$l+1$可以变成$l$和$l+2$.
法二：
发现一个规律，然后二次差分前缀和。
题意要求的就是整数$x$的不同划分方案数。
当左端点为$a$，长度为$len$，最小序列和为$a*len+3$，你会发现左端点为$a$，长度为$len$的序列
对答案的贡献是：区间[a*len+3,(a+2)*len-3]方案数+1，区间[a*len+5,(a+2)*len-2]方案数+1，
依次下取区间左端点+2，右端点+1，对着这些区间都会产生方案数为1的贡献。但是这些差分区间没法
一个个设置。需要对差分数组上再进行一次差分，然后二次差分即可得到答案。
二次差分需要对依次差分的左++，右--，分别用一个差分数组维护，然后再合并。
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
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 1e5 + 5;
const int MXE = 2e6 + 6;
const int block = 300;
const int MXP = 100000;
// int n, m;
// int64 dp[MXN], ret[MXN];
// int main() {
// #ifndef ONLINE_JUDGE
//     freopen("D:in.in", "r", stdin);
//     freopen("D:out.out", "w", stdout);
// #endif
//     for(int i = block; i <= MXP; ++i) {
//         for(int j = 0; j <= MXP; j += i) {
//             for(int k = 3; k * i + k + j <= MXP; ++ k) {
//                 dp[k * i + k + j] += (k - 1) / 2;
//             }
//         }
//         for(int j = i + 2; j <= MXP; j += i + 2) {
//             for(int k = 3; k * i + k + j <= MXP; ++ k) {
//                 dp[k * i + k + j] += (k - 1) / 2;
//             }
//         }
//     }
//     for(int i = 1; i < block; ++i) {
//         ++ ret[i * 3 + 3];
//         for(int j = i, k; j <= i + 2; ++j) {
//             for(k = i + i + i + 3 + j; k <= MXP; ++k) {
//                 ret[k] += ret[k - j];
//             }
//         }
//         for(int j = 1; j <= MXP; ++j) dp[j] += ret[j], ret[j] = 0;
//     }
//     for(int i = 1; i <= MXP; ++i) {
//         // if(i < 12) debug(i, ret[i])
//         dp[i] += dp[i-1];
//     }
//     int tim = read(), cas = 0;
//     while(tim --) {
//         int l = read(), r = read();
//         printf("Case #%d: %lld\n", ++ cas, dp[r] - dp[l-1]);
//     }
// #ifndef ONLINE_JUDGE
//     cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
//     // system("pause");
// #endif
//     return 0;
// }
int64 add[MXN*3], del[MXN*3], sum[MXN];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    for(int a = 1; a <= MXP; ++a) {
        for(int len = 3, val = len * a + 3; val <= MXP; ++len, val += a) {
            ++ add[val];
            -- add[val + len - 3 + len - 3 + 2];
            ++ del[val + len - 3 + 1];
            -- del[val + len - 3 + len - 3 + 2];
        }
    }
    for(int i = 2; i <= MXP; ++i) add[i] += add[i-2], del[i] += del[i-1];
    for(int i = 1; i <= MXP; ++i) 
        add[i] -= del[i], add[i] += add[i-1], sum[i] = sum[i-1] + add[i];
    int tim = read(), cas = 0;
    while(tim --) {
        int l = read(), r = read();
        printf("Case #%d: %lld\n", ++ cas, sum[r] - sum[l-1]);
    }
    return 0;
}