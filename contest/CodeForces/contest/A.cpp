/*
 
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <assert.h>
#include <bits/stdc++.h>
 
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
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
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline LL read() {
    LL x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(LL x, bool f) {
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
const LL BASE[] = {1572872831, 1971536491};
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ans = INF;
int val[MXN], dp[MXN][2];
vector<int> mp[MXN];
void dfs(int u, int ba) {
    dp[u][val[u]] = 0;
    dp[u][!val[u]] = 1;
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs(v, u);
        dp[u][val[u]] += dp[v][val[u]];
        dp[u][!val[u]] += dp[v][!val[u]] + (val[u] == val[v]?-1:0);
    }
    if(u == 1) ans = sml(ans, dp[u][0], dp[u][1]);
}
void dfs2(int u, int ba) {
    if(ba) {
        int tmp1 = dp[ba][val[ba]];
        int tmp2 = dp[ba][!val[ba]];
        dp[ba][val[ba]] -= dp[u][val[ba]];
        dp[ba][!val[ba]] -= dp[u][!val[ba]] + (val[u]==val[ba]?-1:0);
        dp[u][val[u]] += dp[ba][val[u]];
        dp[u][!val[u]] += dp[ba][!val[u]] + (val[u] == val[ba]?-1:0);
        // debug(ans, u, dp[u][0], dp[u][1])
        ans = sml(ans, dp[u][0], dp[u][1]);
        dp[ba][val[ba]] = tmp1;
        dp[ba][!val[ba]] = tmp2;
    }
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs2(v, u);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = 1;
    while (tim --) {
        n = read();
        for(int i = 1; i <= n; ++i) val[i] = read();
        for(int i = 1, a, b; i < n; ++i) {
            a = read(), b = read();
            mp[a].eb(b);
            mp[b].eb(a);
        }
        dfs(1, 0);
        dfs2(1, 0);
        printf("%d\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}