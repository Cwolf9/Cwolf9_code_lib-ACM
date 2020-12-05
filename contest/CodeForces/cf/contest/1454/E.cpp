// Problem: E. Number of Simple Paths
// Contest: Codeforces - Codeforces Round #686 (Div. 3)
// URL: https://codeforces.com/contest/1454/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)
/*
**题意**
给你一个$n$个点$n$条边的连通图（一棵树加一条边），问有多少条不同的简单路径。
**思路**
首先找到图的唯一一个环。然后计算环上每一个点下面子树的贡献，再计算环上每一个点的子树下的点和其他点的贡献即可。
单组时间复杂度：$O(n)$.
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for (register int i = (s), LIM = (t); i < LIM; ++i)
#define per(i, s, t) for (register int i = (s), LIM = (t); i >= LIM; --i)
#define GKD                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f = true) {
    if (x == 0) {
        putchar('0');
        if (f)
            putchar('\n');
        else
            putchar(' ');
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
    if (f)
        putchar('\n');
    else
        putchar(' ');
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int mod = 998244353;  // 998244353
int ksm(int a, int64 b, int kmod = mod) {
    int res = 1;
    for (; b > 0; b >>= 1, a = (int64)a * a % kmod)
        if (b & 1) res = (int64)res * a % kmod;
    return res;
}
const int INF = 0x3f3f3f3f;
const int MXN = 2e5 + 5;

int n, m;
vector<int> mp[MXN], ring;
int sz[MXN], vis[MXN], fa[MXN];
void dfs(int u, int ba) {
    vis[u] = 1;
    fa[u] = ba;
    for (int v : mp[u]) {
        if (v == ba) continue;
        if (vis[v]) {
            while (u != v) {
                vis[u] = 2;
                ring.eb(u);
                u = fa[u];
            }
            ring.eb(v);
            vis[v] = 2;
            return;
        } else
            dfs(v, u);
        if (!ring.empty()) return;
    }
}
void dfs2(int u, int ba) {
    sz[u] = 1;
    for (int v : mp[u]) {
        if (vis[v] == 2 || v == ba) continue;
        dfs2(v, u);
        sz[u] += sz[v];
    }
}
void work() {
    n = read();
    rep(i, 0, n + 1) mp[i].clear(), vis[i] = sz[i] = 0;
    ring.clear();
    rep(i, 0, n) {
        int a = read(), b = read();
        mp[a].eb(b), mp[b].eb(a);
    }
    dfs(1, 0);
    int64 ans = (int64)SZ(ring) * (SZ(ring) - 1), sum = 0;
    rep(i, 0, SZ(ring)) {
        dfs2(ring[i], -1);
        sum += sz[ring[i]];
    }
    rep(i, 0, SZ(ring)) {
        if (sz[ring[i]] > 1)
            ans += (sum - sz[ring[i]]) * 2LL * (sz[ring[i]] - 1) +
                   (int64)sz[ring[i]] * (sz[ring[i]] - 1) / 2;
        sum -= sz[ring[i]] - 1;
    }
    printf("%lld\n", ans);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:/ACM/mtxt/in.txt", "r", stdin);
    // freopen("D:/ACM/mtxt/out.txt", "w", stdout);
#endif
    for (int cas = 1, tim = read(); cas <= tim; ++cas) {
        // printf("Case #%d:\n", cas);
        work();
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
