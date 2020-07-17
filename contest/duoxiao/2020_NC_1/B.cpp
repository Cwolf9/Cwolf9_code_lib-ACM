/*
链接
https://ac.nowcoder.com/acm/contest/5666/B
题意
mindiv(x) be the minimum divisor greater than 1 of n.
f(u, v) be the number of edges between vertices u and v 
m = 100000, w[i] <= 10000
求min(\sum_{i=1}^m w[i]*f(u, i!)), u你自己任选，求最小值

思路
建出虚树然后 dp 即可
虚树中1,2!,3!,...,n间不会有两个点lca高度相同
x! = p1^k1*p2^k2...pm^km
从1到x!的路径长度为 \sum_{i=1}^m ki
从1到x!路径上相邻两点的倍数关系一定是km个pm, ..., 直到k1个p1
x!的深度比(x-1)!的深度多 x 的素因子次数和
x!和(x-1)!的分界点一定是次数不相同的最大的素数

备注

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
const int MXN = 1e5 + 5;
const int MXNN = MXN + MXN;
const int MXE = 1e6 + 6;
int n, m, k;
int val[MXNN], mindiv[MXNN], lcadep[MXNN], dep[MXNN];
int64 ans;
namespace VT {
    struct lp {
        int v, nex;
        int64 w;
    } cw[MXE];
    int tot, head[MXNN], stak[MXNN], top, vtx;
    void add_edge(int a, int b, int64 c) {
        cw[++tot].v = b, cw[tot].nex = head[a], cw[tot].w = c;
        head[a] = tot;
        cw[++tot].v = a, cw[tot].nex = head[b], cw[tot].w = c;
        head[b] = tot;
    }
    //注意dep不要被污染了
    void build(int n) {//依次构建1-n的虚树，虚树中1,2!,3!,...,n间不会有两个点lca高度相同
        vtx = MXN;
        tot = head[1] = -1;
        stak[top = 1] = 1;
        for(int i = 1; i <= n; ++i) {
            if(i == 1) continue;
            int lcaD = lcadep[i];//i!和(i-1)!的lca的高度
            if(lcaD != dep[stak[top]]) {//栈顶不是lca
                while(lcaD < dep[stak[top-1]]) {//把另一条链弹出去并连边
                    add_edge(stak[top], stak[top-1], dep[stak[top]]-dep[stak[top-1]]);
                    -- top;
                }
                if(lcaD == dep[stak[top-1]]) {//lca在栈顶下面一个
                    add_edge(stak[top], stak[top-1], dep[stak[top]]-dep[stak[top-1]]);
                    -- top;
                }else {//把栈顶和lca的边补上，并替换栈顶
                    ++ vtx;//动态开点维护lca
                    dep[vtx] = lcaD;
                    head[vtx] = -1;
                    add_edge(vtx, stak[top], dep[stak[top]] - lcaD);
                    stak[top] = vtx;
                }
            }
            stak[++top] = i;
            head[stak[top]] = -1;
        }
        for(int i = 2; i <= top; ++i) 
            add_edge(stak[i], stak[i-1], dep[stak[i]] - dep[stak[i-1]]);
    }
    int64 dp[MXNN], sz[MXNN];
    void dfs(int u, int ba) {
        dp[u] = 0;
        sz[u] = val[u];
        val[u] = 0;
        for(int i = head[u], v; ~i; i = cw[i].nex) {
            v = cw[i].v;
            if(v == ba) continue;
            // debug(u, v, cw[i].w)
            dfs(v, u);
            sz[u] += sz[v];
            dp[u] += cw[i].w * sz[v] + dp[v];
        }
        // debug(u, sz[u], dp[u])
    }
    void rdfs(int u, int ba, int64 w) {
        if(ba) {
            int64 tmp = dp[ba] - dp[u] - w * sz[u];
            dp[u] += tmp + w * (sz[1] - sz[u]);
        }
        // debug(u, dp[u])
        ans = sml(ans, dp[u]);
        for(int i = head[u], v; ~i; i = cw[i].nex) {
            v = cw[i].v;
            if(v == ba) continue;
            rdfs(v, u, cw[i].w);
        }
    }
}
int bit[MXN];
void add_bit(int x, int v) {
    while(x < MXN) {
        bit[x] += v;
        x += lowbit(x);
    }
}
int query_bit(int x) {
    int ans = 0;
    while(x > 0) {
        ans += bit[x];
        x -= lowbit(x);
    }
    return ans;
}
bool nop[MXN];
int pp[50005], pcnt;
void init() {
    for(int i = 2; i < MXN; ++i) {
        if(!nop[i]) pp[pcnt++] = i, mindiv[i] = i;
        for(int j = 0; j < pcnt && pp[j] * i < MXN; ++j) {
            nop[pp[j]*i] = 1;
            mindiv[pp[j]*i] = pp[j];
            if(i % pp[j] == 0) break;
        }
    }
    for(int i = 2, j; i < MXN; ++i) {
        dep[i] = dep[i-1] + 1;
        j = i;
        //dep[i]在dep[i-1]的基础上多的高度即为i的素因子次数和
        for(; j != mindiv[j]; j /= mindiv[j]) ++ dep[i];
        //现在j为i的最大素因子
        //较大的素因子出现次数即为lcaDep
        lcadep[i] = query_bit(MXN - 1) - query_bit(j - 1);
        //维护i!里面素因子各个次数
        for(j = i; j != 1; j /= mindiv[j]) add_bit(mindiv[j], 1);
        // if(i <= 5) printf("%d %d %d\n", i, dep[i], lcadep[i]);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init();
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; ++ i) val[i] = read();
        ans = 1e18;
        VT::build(n);
        VT::dfs(1, 0);
        VT::rdfs(1, 0, 0);
        printf("%lld\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
