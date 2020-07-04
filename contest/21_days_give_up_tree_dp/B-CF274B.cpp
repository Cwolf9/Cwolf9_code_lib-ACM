/*
链接：
https://vjudge.net/contest/381037#problem/B
题意：
n = 100000，树上点权1e9
操作：任选包含1号点的联通块，然后所有点权+1 or -1
问最少操作数量使所有点权为0
思路：
以1为根做树DP
dp[u][0]表示u的子树需要+1的操作次数
dp[u][1]表示u的子树需要-1的操作次数

记录u的各个子节点中dp[v][0]和dp[v][1]的最大值，并赋值给dp[u][0/1]。
使u所有子节点变为0后，u权值为ar[u]+max(dp[v][0])-max(dp[v][1])
根据u点权值的正负，添加到相应的dp[u][0/1]
答案为dp[1][0]+dp[1][1]

为什么要这样树DP？
首先因为在u点不同子节点的子树内，某些子孙节点的操作可以合并一起
操作，因为他们本来就是一个联通块，然后这些子孙节点的某些
父节点（同时也是子孙节点）的操作也可以合并，但是子孙节点和
他的父节点的操作不能合并。
所以需要记录一下两种操作的最大操作次数，这样就不会重复计数。

备注：
写题过程中理解错了几次题意。
如果是1有根树，操作改成不选择联通块，而是某个子树，贪心dfs即可吧。
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
const int mod = 1e9 + 7;
const int MOD = 1e9 + 7;//998244353
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
LL ar[MXN];
LL dp[MXN][2];
LL ans, Min, Max;
vector<int> mp[MXN];
void dfs(int u, int ba) {
    LL tmpSum1 = 0, tmpSum2 = 0, tmpSon1 = 0, tmpSon2 = 0;
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs(v, u);
        tmpSon1 = max(tmpSon1, dp[v][0]);
        tmpSon2 = max(tmpSon2, dp[v][1]);
        tmpSum1 = max(tmpSum1, dp[v][0]);
        tmpSum2 = max(tmpSum2, dp[v][1]);
    }
    ar[u] += tmpSon1 - tmpSon2;
    if(ar[u] > 0) {
        dp[u][0] = tmpSum1;
        dp[u][1] = tmpSum2 + ar[u];
    }else if(ar[u] < 0) {
        dp[u][0] = tmpSum1 - ar[u];
        dp[u][1] = tmpSum2;
    }
    // debug(u, dp[u][0], dp[u][1], ar[u])
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
    for(int i = 1; i <= n; ++i) ar[i] = read();
    dfs(1, 0);
    print(dp[1][0] + dp[1][1]);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}