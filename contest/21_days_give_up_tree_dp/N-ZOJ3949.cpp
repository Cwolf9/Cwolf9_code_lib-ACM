/*
链接：
https://vjudge.net/contest/381037#problem/N
题意：
n(2e5)个点的树，你选择一个最优的点x，在树中添加一条边(1, x)后，使得
sum(dis(1, v)), v = 1...n为最小值。max(depth) = 3e4

思路：
连接一条边后就成环了，贡献肯定是从圆路径中点处往下开始减少
每个深度的点可以减少的贡献的系数如下：
1: 0
2: 1
3: 2
4: 1 3
5: 2 4
6: 1 3 5
7: 2 4 6
8: 1 3 5 7
对于7来说，可以减少的距离为：6 * sz[u] + 4 * (sz[ba] - sz[u]) + 2 * (sz[ye] - sz[ba])
那么如何对每一个点都求出这个来呢？
在一条固定的路径中，维护dep[u] = depth, one[dep[ba]] = sz[ba] - sz[u],
sum1[x] = 1 * one[2] + 3 * one[3] + 5 * one[4] + 7 * one[5] + 9 * one[6] + 11 * one[7] + ...
sum2[x] = one[2] + one[3] + one[4] + ...
minus = sum1[dep[ba]] - sum1[(dep[ba] + 1) / 2]
    - (dep[ba] - 2) * (sum2[dep[ba]] - sum2[(dep[ba] + 1) / 2])
    + sz[u] * (dep[ba] - 1);
此式子最后一项的意思是补全我要求的这个节点的 size ，因为在 one 数组中减去了
注意，要求出one数组需要知道我现在在u的哪一个儿子的路径上，所以在dfs遍历的时候，
我只能求出u的父亲ba可以减少的贡献的大小，这样才能维护上面的式子，叶子节点特判处理。

备注：


*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
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
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
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
void debug_out(const T &f, const R &... r) {cout << f << " ";debug_out(r...);}
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
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int up;
int sz[MXN], dep[MXN], leaf[MXN];
int64 ans, all;
int64 dp[MXN], one[MXN];
int64 sum1[MXN], sum2[MXN];
vector<int> mp[MXN];

void dfs1(int u, int ba, int ye) {
    sz[u] = 1;
    leaf[u] = 1;
    for (int v : mp[u]) {
        if (v == ba) continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u, ba);
        sz[u] += sz[v];
        leaf[u] = 0;
    }
    one[u] = sz[u];
    dp[u] = one[u] * (dep[u] - 1);
}
void dfs2(int u, int ba, int ye) {
    if (dep[u] >= 3) {
        one[ba] = sz[ba] - sz[u];
        sum1[dep[ba]] = sum1[dep[ye]] + one[ba] * (2 * dep[ba] - 3);
        sum2[dep[ba]] = sum2[dep[ye]] + one[ba];
        // debug(dep[ba], dep[u])
        // debug(ba, one[ba], sum1[dep[ba]], sum2[dep[ba]])
        if (dep[u] <= 4)
            dp[ba] = sz[ba] * (dep[u] - 2);
        else {
            dp[ba] = sum1[dep[ba]] - sum1[(dep[ba] + 1) / 2] -
                     (dep[ba] - 2) * (sum2[dep[ba]] - sum2[(dep[ba] + 1) / 2]) +
                     sz[u] * (dep[ba] - 1);
        }
        if (leaf[u]) {
            sum1[dep[u]] = sum1[dep[ba]] + one[u] * (2 * dep[u] - 3);
            sum2[dep[u]] = sum2[dep[ba]] + one[u];
            // debug(u, dep[u], sum1[dep[u]], sum2[dep[u]])
            dp[u] = sum1[dep[u]] - sum1[(dep[u] + 1) / 2] -
                    (dep[u] - 2) * (sum2[dep[u]] - sum2[(dep[u] + 1) / 2]);
        }
    } else if (dep[u] == 2)
        dp[u] = sz[u];
    for (int v : mp[u]) {
        if (v == ba) continue;
        dfs2(v, u, ba);
        all += sz[v];
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while (tim--) {
        n = read();
        for (int i = 1, a, b; i < n; ++i) {
            a = read(), b = read();
            mp[a].eb(b);
            mp[b].eb(a);
        }
        dfs1(1, 0, n + 1);
        dfs2(1, 0, n + 1);
        for (int i = 1; i <= n; ++i) {
            ans = max(ans, dp[i]);
            // debug(i, dp[i], sz[i], dep[i])
            mp[i].clear();
        }
        // debug(all)
        printf("%lld\n", all - ans);
        all = ans = 0;
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
/*
7
12
4 5
4 7
4 8
1 7
4 6
2 6
1 9
1 10
2 11
3 11
6 12
11
1 2
2 3
3 4
3 5
3 6
4 7
7 8
8 9
9 10
9 11
*/