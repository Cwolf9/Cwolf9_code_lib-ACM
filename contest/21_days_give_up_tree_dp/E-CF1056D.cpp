/*
链接：
https://vjudge.net/contest/381037#problem/E
题意：
n(100000)个点的树，给每个叶子涂一种颜色，定义开心的点满足其子树中所
有叶子颜色不同，k=1,...,n,问至少需要多少种颜色满足开心点个数不少于k。

思路：
贪心就行了，DP是不可能DP的
之前一直想父子背包DP怎么合并。。
又想了dp[i]获得i个开心点至少需要颜色数或者dp[i]表示i个叶子
最多得到开心点数量。。。。
发现没必要，其实只用统计每个点下面叶子数量，然后按这个数量分类。
对于所有只有一个叶子的点，用一种颜色就可以全部得到，以此类推。

备注：
题目改成定义开心的点满足其子树中所有叶子颜色相同，k=1,...,n,
问最多可以用掉多少种颜色满足开心点个数不少于k。
然后dfs遍历，统计每个点的儿子个数son[i]
在返回的时候，如果你有不少于2个儿子，则为了再获得一个开心点，
需要减少son[i]-1种颜色。
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
const int MXN = 1e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ans[MXN];
int ar[MXN], num[MXN];
vector<int> mp[MXN];
void dfs(int u, int ba) {
    int leaf = 1;
    for(int v: mp[u]) {
        if(v == ba) continue;
        leaf = 0;
        dfs(v, u);
        ar[u] += ar[v];
    }
    ar[u] += leaf;
    ++ num[ar[u]];
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    for(int i = 2, a; i <= n; ++i) {
        a = read();
        mp[a].eb(i);
    }
    dfs(1, 0);
    for(int i = 1, j = 1; i <= n; ++i) {
        for(k = 0; k < num[i]; ++k, ++j) ans[j] = i;
    }
    for(int i = 1; i <= n; ++i) print(ans[i]);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}