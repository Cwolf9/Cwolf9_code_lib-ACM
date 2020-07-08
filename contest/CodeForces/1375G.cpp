/*
链接：
https://codeforces.com/contest/1375/problem/G
题意：
简化理解一下题目所规定的操作就是在一个长为3的子链中：
将一个端点及其儿子全部衔接到另一个端点上
问最少操作次数，使树变成一个星形，也就是菊花图

思路：
树DP，两次dfs
所以能直接对点 u 造成贡献的点与其距离肯定是2，这样距离为2点的数量，
就是进行操作的次数，合并到u点的次数加上这个数量即可。

而与其数量为2的端点的最少操作是一个和u一样的子问题。

因为距离为2有贡献，所以树DP的时候要传递父亲节点和爷爷节点
第一遍dfs记录将u点子树变成以u为核心星形的最少操作次数。
第二遍换根dfs记录以u点为核心的最后答案，也就是要加上u点的兄弟和爷爷对他的贡献。

toFa[p]表示p所有的儿子对p的父亲的贡献
sonVal[p]表示合并p的子树为以p为核心的星形的最少操作次数
allVal[p]表示合并整棵树为以p为核心的星形的最少操作次数
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
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;//998244353
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int leaf[MXN], fa[MXN], toFa[MXN], sonVal[MXN], allVal[MXN];
vector<int> mp[MXN];
void dfs1(int u, int ba, int ye) {
    fa[u] = ba;
    int isLeaf = 1;
    for(int v: mp[u]) {
        if(v == ba) continue;
        isLeaf = 0;
        dfs1(v, u, ba);
    }
    leaf[u] = isLeaf;
    if(isLeaf) {
        ++ sonVal[ye];
        ++ toFa[ba];
    }else {
        sonVal[ye] += 1 + sonVal[u];
        toFa[ba] += 1 + sonVal[u];
    }
    // sonVal[0] = toFa[0] = 0;
}
void dfs2(int u, int ba, int ye) {
    if(ba) {
        if(ye) {
            allVal[u] = sonVal[ye] - 1 + allVal[ye] - toFa[ba] + 1;
        }else {
            allVal[u] = sonVal[ye] - 1;
            // debug(allVal[ye], toFa[ba])
        }
    }else {
        allVal[u] = sonVal[u];
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
    n = read();
    for(int i = 1, a, b; i < n; ++i) {
        a = read(), b = read();
        mp[a].eb(b);
        mp[b].eb(a);
    }
    dfs1(1, 0, n+1);
    // for(int i = 1; i <= n; ++i) {
    //     debug(i, sonVal[i], toFa[i])
    // }
    allVal[0] = sonVal[0];
    // debug(sonVal[1], toFa[1], sonVal[0], toFa[0])
    dfs2(1, 0, n+1);
    // for(int i = 1; i <= n; ++i) {
    //     debug(i, allVal[i], sonVal[i], toFa[i])
    // }
    int Min = INF;
    for(int i = 1; i <= n; ++i) Min = min(Min, allVal[i]);
    print(Min);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
