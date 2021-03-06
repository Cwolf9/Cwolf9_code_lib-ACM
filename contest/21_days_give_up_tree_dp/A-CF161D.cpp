/*
链接：
https://vjudge.net/contest/381037#problem/A
题意：
n = 50000, k = 500
求书上距离为k的点对数量
思路：
树DP
dp[u][d]表示树中与点u距离d的点的数量

树分治裸题
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
    if (x == 0) {putchar('0'); if(f)putchar('\n');else putchar(' ');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');else putchar(' ');
}
int lowbit(int x) { return x & (-x); }
template<class T>T big(const T &a1, const T &a2) { return a1 > a2 ? a1 : a2; }
template<class T>T sml(const T &a1, const T &a2) { return a1 < a2 ? a1 : a2; }
template<typename T, typename ...R>T big(const T &f, const R &...r) { return big(f, big(r...)); }
template<typename T, typename ...R>T sml(const T &f, const R &...r) { return sml(f, sml(r...)); }
void debug_out() { cerr << '\n'; }
template<typename T, typename ...R>void debug_out(const T &f, const R &...r) {cerr << f << " ";debug_out(r...);}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);


const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 1e9 + 7;
const int MOD = 1e9 + 7;//998244353
const int INF = 0x3f3f3f3f;
const int MXN = 1e5 + 5;
int n, m, k;
int dp[MXN][505];
vector<int> mp[MXN];
void dfs1(int u, int ba) {
    dp[u][0] = 1;
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs1(v, u);
        for(int i = 0; i < 500; ++i) dp[u][i+1] += dp[v][i];
    }
}
void dfs2(int u, int ba) {
    if(ba) {
        for(int i = 500; i >= 1; --i) {
            dp[u][i] += dp[ba][i-1] - dp[u][i-2];
        }
    }
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs2(v, u);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("D:in.in", "r", stdin);
    // freopen("D:out.out", "w", stdout);
#endif
    n = read(), m = read();
    for(int i = 1, a, b; i < n; ++i) {
        a = read(), b = read();
        mp[a].eb(b);
        mp[b].eb(a);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    LL ans = 0;
    for(int i = 1; i <= n; ++i) {
        ans += dp[i][m];
        // debug(i, dp[i][m])
    }
    printf("%lld\n", ans / 2);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}