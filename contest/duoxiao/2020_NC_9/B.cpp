/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
//#define LH_LOCAL
#define LLDO
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
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
int n;
vector<pii > mp[MXN];
int ar[MXN], leaf[MXN];
int64 dep[MXN], sum, sum2, dp[MXN], wt[MXN];
class node {
    public:
    int cost;
    int64 income;
    int64 wt;
    bool operator<(const node&B) const{
        return income - cost - wt > B.income - B.cost - B.wt;
    }
};
vector<node> son[MXN];
void dfs(int u, int ba) {
    leaf[u] = 1;
    wt[u] = 0;
    dp[u] = ar[u];
    son[u].clear();
    for(pii V: mp[u]) {
        if(V.fi == ba) continue;
        leaf[u] = 0;
        dep[V.fi] = dep[u] + V.se;
        dfs(V.fi, u);
        son[u].eb(node{V.se, dp[V.fi], wt[V.fi]});
    }
    sort(all(son[u]));
    // debug(1, u, dp[u], wt[u])
    for(node &x: son[u]) {
        // debug(0, x.income, x.cost)
        wt[u] += max(0LL, x.cost - dp[u]) + max(0LL, 
        x.wt + x.cost - x.income- max(0LL, dp[u] - x.cost) );
        dp[u] = max(0LL, dp[u] - x.cost);
        dp[u] += x.income - x.cost - x.wt;
        dp[u] = max(dp[u], 0LL);
        // debug(u, dp[u], wt[u])
    }
    dp[u] = max(dp[u], 0LL);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read();
        sum = sum2 = 0;
        for(int i = 1; i <= n; ++i) {
            ar[i] = read();
            sum += ar[i];
            mp[i].clear();
        }
        for(int i = 1, a, b, c; i < n; ++i) {
            a = read(), b = read(), c = read();
            mp[a].eb(mk(b, c));
            mp[b].eb(mk(a, c));
            sum2 += c + c;
        }
        dep[1] = 0;
        dfs(1, 0);
        print(max(0LL, wt[1]));
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}