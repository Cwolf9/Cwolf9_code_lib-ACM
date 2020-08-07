/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6769)
**题意**

**思路**

**备注**
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
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m;
class node {
    public:
    int v, a, b;
    void rd() {
        v = read(), a = read(), b = read();
    }
}A;
vector<node> mp[MXN];
int64 dp[MXN][25], ndp[25];
int sz[MXN];
void dfs(int u, int ba, int64 lim) {
    sz[u] = 1;
    clr(dp[u], 0x3f);
    dp[u][0] = 0;
    for(node &V: mp[u]) {
        if(V.v == ba) continue;
        dfs(V.v, u, lim);
        int up1 = min(sz[u], m + 1), up2 = min(sz[V.v] + 1, m + 1);
        clr(ndp, 0x3f);
        for(int i = 0; i < up1; ++i) {
            for(int j = 0; j < up2; ++j) {
                if(i + j <= m && dp[u][i] + dp[V.v][j] + V.b <= lim) 
                    ndp[i+j] = min(ndp[i+j], max(dp[u][i], dp[V.v][j] + V.b));
                if(i + j + 1 <= m && dp[u][i] + dp[V.v][j] + V.a <= lim) 
                    ndp[i+j+1] = min(ndp[i+j+1], max(dp[u][i], dp[V.v][j] + V.a));
            }
        }
        sz[u] += sz[V.v];
        for(int i = 0; i <= min(m, sz[u] - 1); ++i) {
            dp[u][i] = ndp[i];
            //debug(u, V.v, i, ndp[i])
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read(), m = read();
        for(int i = 1, a; i < n; ++i) {
            a = read();
            A.rd();
            mp[a].eb(A);
            swap(a, A.v);
            mp[a].eb(A);
        }
        int64 L = 1, R = 2e13+1, mid, ans = -1;
        //dfs(1, -1, 6);
        while(L <= R) {
            mid = (L + R) >> 1;
            dfs(1, -1, mid);
            if(dp[1][m] <= mid) ans = mid, R = mid - 1;
            else L = mid + 1;
        }
        printf("%lld\n", ans);
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}
