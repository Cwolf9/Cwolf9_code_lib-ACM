/*
**链接**
传送门: [here](https://www.acwing.com/problem/content/288/)
**题意**
题目链接：[here](https://www.acwing.com/problem/content/288/)
一个森林共有$n(1e3)$个点，求选择$m$个点的权值最大和。
要想选$x$必须先选择$x$的父亲。
**思路**
有依赖的树dp，dfs序上dp。
在DFS序上DP，定义 f[i][j] 表示DFS序 [1,i] 选 j 个点的最优解，这样转移就只有两种：
i 点选，那么转移到 f[i+1][k] 。
i 点不选，那么子树也没有选，转移到 f[out[i]+1][k] 。

**备注**
https://zigzagk.top/2018/07/19/dp-on-dfs-order
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
const int MXN = 2e3 + 5;
const int MXE = 2e6 + 6;
int n, m;
int ar[MXN];
int rid[MXN], lid[MXN], inde;
int dp[MXN][MXN];
vector<int> mp[MXN];
void dfs(int u, int ba) {
    rid[++inde] = u;
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs(v, u);
    }
    lid[u] = inde;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read(), m = read() + 1;
    for(int i = 1, a; i <= n; ++i) {
        a = read();
        mp[a].eb(i);
        //cout << a << " " << i << endl;
        ar[i] = read();
    }
    dfs(0, -1);
    clr(dp, -1);
    dp[1][0] = 0;
    for(int i = 1, x; i <= inde; ++i) {
        x = rid[i];
        for(int j = 0; j <= m; ++j) {
            if(j >= 1 && dp[i][j-1] != -1) dp[i+1][j] = max(dp[i+1][j], dp[i][j-1] + ar[x]);
            if(dp[i][j] != -1) dp[lid[x]+1][j] = max(dp[lid[x]+1][j], dp[i][j]);
        }
    }
    printf("%d\n", dp[inde + 1][m]);
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}
