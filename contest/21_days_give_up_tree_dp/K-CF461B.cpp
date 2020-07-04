/*
链接：
https://vjudge.net/contest/381037#problem/K
题意：
n个点的树，有k+1个黑点，满足的方案是删掉k条边后，k+1个联通块
每个恰好有一个黑点，问有多少种方案数。

思路：
dp[u][0/1]表示u的子树内有0/1个黑色节点
u是v的父亲
dp[u][1] = u-v边保留情况 + u-v边不保留情况
= (dp[u][0]*dp[v][1]+dp[u][1]*dp[v][0]) + dp[u][1]*dp[v][1]
dp[u][0] = u-v边保留情况 + u-v边不保留情况
= dp[u][0] * dp[v][0] + dp[u][0] * dp[v][1]
重点就在u-v边是否要删除情况，初始化就是 dp[u][color[u]] = 1

备注：
状态难想，之前还想了dp[u][0/1]为u的父节点边是否删除的方案数，显然不行
蔓延


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
#define eb emplace_back
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
#define LLDO
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
const int mod = 998244353;
const int MOD = 1e9 + 7;//998244353
const int MXN = 3e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN], du[MXN];
LL dp[MXN][2];
vector<int > mp[MXN];

void dfs(int u, int ba) {
    if(ar[u]) dp[u][0] = 0, dp[u][1] = 1;//11
    else dp[u][0] = 1, dp[u][1] = 0;//1?
    for(int v: mp[u]) {
        dfs(v, u);
        // debug(v-1, u-1)
        // debug(dp[u][0], dp[u][1], dp[v][0], dp[v][1])
        dp[u][1] = (dp[u][0] * dp[v][1] + dp[u][1] * (dp[v][0] + dp[v][1])) % MOD;
        dp[u][0] = dp[u][0] * (dp[v][0] + dp[v][1]) % MOD;
        // debug(u - 1, dp[u][0], dp[u][1])
    }
    // debug(u - 1, dp[u][0], dp[u][1])
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    for(int i = 2, a, b, c; i <= n; ++i) {
        a = read() + 1;
        mp[a].eb(i);
    }
    for(int i = 1; i <= n; ++i) ar[i] = read();
    dfs(1, 0);
    print(dp[1][1]);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}