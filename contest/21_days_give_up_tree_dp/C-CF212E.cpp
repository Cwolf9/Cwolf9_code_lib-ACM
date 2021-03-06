/*
链接：
https://vjudge.net/contest/381037#problem/C
题意：
n(3,5000)个点的树，每个点可选择设置2种据点（a，b），但是不能有相
邻的两节点使相同的据点，问最多可设置多少个据点，也就是a+b的最大值
是多少。按大小输出所有pair(a,b)。

思路：
a+b的最大值肯定是3。任意选一个度大于1的点都可以做为分割点。
在分割点不同侧的联通块可以任意全部设置统一据点。
问题转化为求n个数字，不全选求和能组合多少种数字。
因为 n 只有 5000 , dfs 遍历儿子的时候暴力背包 dp 即可。

备注：
范围1e5能做吗？
还有别的做法吗？
DP能优化吗？
DP可以用一种方法出题包装下吗？
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <ctime>
#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 31
#define mk make_pair
#define eb push_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline LL read() {
    LL x = 0;int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(LL x, bool f) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template<class T>T big(const T &a1, const T &a2) { return a1 > a2 ? a1 : a2; }
template<class T>T sml(const T &a1, const T &a2) { return a1 < a2 ? a1 : a2; }
template<typename T, typename ...R>T big(const T &f, const R &...r) { return big(f, big(r...)); }
template<typename T, typename ...R>T sml(const T &f, const R &...r) { return sml(f, sml(r...)); }
void debug_out() { cout << '\n'; }
template<typename T, typename ...R>void debug_out(const T &f, const R &...r) {cout << f << " ";debug_out(r...);}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
// #define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template<typename T>
void print(const T &f) {printf(ptout, f);putchar('\n');}
template<typename T, typename ...R>
void print(const T &f, const R &...r) {printf(ptout, f);putchar(' ');print(r...);}

const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int MOD = 1e9 + 7;//998244353
const int MXN = 5e4 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN];
// int dp[MXN];
vector<int> mp[MXN];
set<int> ans;
void dfs_sz(int u, int ba) {
    ar[u] = 1;
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs_sz(v, u);
        ar[u] += ar[v];
    }
}
void dfs(int u, int ba) {
    vector<int> dp(n, 0);
    dp[0] = dp[n - ar[u]] = 1;
    // debug(u, ar[u], n - ar[u])
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs(v, u);
        for(int i = n - 2; i >= ar[v]; --i) {
            dp[i] |= dp[i - ar[v]];
        }
    }
    for(int i = 1; i < n - 1; ++i) if(dp[i]) {
        ans.insert(i);
        // if(i == 4 || i == 5) debug(u, ar[u])
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    for(int i = 1, a, b; i < n; ++i) {
        a = read(), b = read();
        mp[a].eb(b);
        mp[b].eb(a);
    }
    dfs_sz(1, 0);
    dfs(1, 0);
    print(ans.size());
    for(int x: ans) print(x, n - 1 - x);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}