/*
链接：
https://vjudge.net/contest/381037#problem/M
题意：
n5000树中有m个关键点，有多少种选择关键点的方案数满足任意两点之间距离小于等于k

思路：
树DP
dp[i][j]表示在i子树内选择的key node离i点最远距离为j的方案数

状态转移求 dp[u][i]
udp[i]是sum(dp[u][1...i])
vdp[i]是sum(dp[v][1...i])
x = min(i, k - i)
1、当 i > k, dp[u][i] += dp[v][i-1]
2、当 i <= k 且 i!=0 且 i < k - i, 若 u 前几个子树取到最远距离为i的方
案数,则 v 子树不能取到 k-i , 因为如果这个加到 dp[u][i]中去，就和状态定义相
矛盾了，所以 v 子树也只能去最远距离到 i
dp[u][i] = dp[u][i] * (1 + vdp[x-1]) + dp[v][x-1] * (1 + udp[i-1]);
3、当 i <= k 且 i!=0 且 i >= k - i, 若 u 前几个子树取到最远距离为i的方
案数, v 子树可以取到 k-i , uv反过来同理
dp[u][i] = dp[u][i] * (1 + vdp[x-1]) + dp[v][i-1] * (1 + udp[k-i]);

答案就是sum(dp[1][1...i])
当然你也可以再换根dfs一次，求出最后的dp[i][j]表示树中选择的最远keynode距离i点为j的方案数，不过没必要。

备注：
dp状态设计有点难想，因为感觉太难去重了

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
#include <map>
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
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
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
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;//998244353
const int MXN = 5e3 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN];
int64 dp[MXN][MXN], ans, dep[MXN], udp[MXN], vdp[MXN], sdp[MXN];
vector<int> mp[MXN];
void dfs1(int u, int ba, int ye) {
    dp[u][0] = ar[u];
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs1(v, u, ba);
        dep[u] = max(dep[u], dep[v] + 1);
        for(int i = 0; i <= n; ++i) {
            if(i == 0) udp[i] = dp[u][i], vdp[i] = dp[v][i];
            else {
                udp[i] = (udp[i-1] + dp[u][i]) % MOD;
                vdp[i] = (vdp[i-1] + dp[v][i]) % MOD;
            }
            sdp[i] = 0;
        }
        for(int i = 0; i <= k; ++i) {
            int x = min(k - i, i);
            if(i != 0 && i < k - i) dp[u][i] = (dp[u][i]*(1 + vdp[x-1]) % MOD + dp[v][x-1]*(1 + udp[i-1]) % MOD) % MOD;
            else if(i != 0 && i >= k - i) dp[u][i] = (dp[u][i]*(1 + vdp[x-1]) % MOD + dp[v][i-1]*(1 + udp[k-i]) % MOD) % MOD;
        }
        for(int i = k + 1; i <= dep[u]; ++i) {
            dp[u][i] = (dp[u][i] + dp[v][i-1]) % MOD;
        }
        // debug(u, v, dp[u][1])
    }
    // debug(u, dep[u])
    // for(int i = 0; i <= dep[u]; ++i) debug(i, dp[u][i])
}
void dfs2(int u, int ba, int ye) {
    if(ba) {
        
    }
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs2(v, u, ba);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read(), m = read(), k = read();
    k = min(k, n - 1);
    for(int i = 1, a, b; i < n; ++i) {
        a = read(), b = read();
        mp[a].eb(b);
        mp[b].eb(a);
    }
    for(int i = 1, x; i <= m; ++i) {
        x = read(), ar[x] = 1;
    }
    dfs1(1, 0, n+1);
    for(int i = 0; i <= n; ++i) {
        ans = (ans + dp[1][i]) % MOD;
    }
    printf("%lld\n", (ans+MOD)%MOD);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
