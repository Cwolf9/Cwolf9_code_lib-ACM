/*
链接
https://ac.nowcoder.com/acm/contest/5666/H
题意
n=50
m=100
给你一个最小费用流图，边单位流量费用ci，Q(100000)次询问，每次询问
告诉你每条边的流量上限是u/v(保证<=1)，问要从1流一个单位流量到n的
最小费用是多少。

思路
因为每条边的流量上限其实都是一样的，所以我们首先预处理，把每条边的流量扩大
v/u倍，这样所有流量上限都是1，费用流每次增广的时候只会增广1的流量，然后
记录下每次增广的花费，边只有100条，最多只会增广100次
询问就是暴力枚举每一条增广路径看流量和是否满足条件，若某次增广的流量多
了就截断多的部分，只取到刚好我要的流量，并算贡献。
复杂度就是O(m*q) = 1e7刚好可以过

比如你加个前缀和预处理，二分处理询问，这样复杂度就是O(q*log(m))
当然可以更快，你可以O(1)算出答案来，复杂度就是O(q)

我这里算的复杂度没有把求gcd算进去

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
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
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
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 2e2 + 5;
const int MXE = 2e5 + 6;
class MCMF_D {
    public:
static const int MAX_V = 1003;
struct edge {
    int to, cap, cost, rev;
    edge(int _to, int _cap, int _cost, int _rev) : to(_to), cap(_cap), cost(_cost), rev(_rev) {}
};
int V;
vector<edge> G[MAX_V];
int h[MAX_V];
int dis[MAX_V];
int preV[MAX_V], preE[MAX_V];
vector<int> vs;
void init(int _v) {
    vs.clear();
    V = _v + 1;//points low-index 0 - v
    for (int i = 0; i <= V; i++) {G[i].clear();preV[i] = preE[i] = 0;}
}
void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back(edge(to, cap, cost, G[to].size()));
    G[to].push_back(edge(from, 0, -cost, G[from].size() - 1));
}
//if you want to solve max_cost_flow, just reverse cost, change pq, init dis, slack and tepan
int min_cost_flow(int s, int t, int f) {
    int res = 0;
    fill(h, h + V, 0);
    while (f > 0) {
        priority_queue<pii, vector<pii>, greater<pii> > que;//
        fill(dis, dis + V, INF);//
        dis[s] = 0;
        que.push(make_pair(0, s));
        while (!que.empty()) {
            pii p = que.top();
            que.pop();
            int v = p.second;
            if (dis[v] < p.first) {//
                continue;
            }
            for (int i = 0; i < G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 && dis[e.to] > dis[v] + e.cost + h[v] - h[e.to]) {//
                    dis[e.to] = dis[v] + e.cost + h[v] - h[e.to];
                    preV[e.to] = v;
                    preE[e.to] = i;
                    que.push(make_pair(dis[e.to], e.to));
                }
            }
        }
        if (dis[t] == INF) return -1;//
        for (int v = 0; v < V; v++) h[v] += dis[v];
        int d = f;
        for (int v = t; v != s; v = preV[v]) d = min(d, G[preV[v]][preE[v]].cap);
        f -= d;
        res += d * h[t];
        vs.eb(h[t]);
        for (int v = t; v != s; v = preV[v]) {
            edge &e = G[preV[v]][preE[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}
void solve() {
    int q = read();
    int64 u, v;
    // debug(vs.size())
    while(q --) {
        u = read(), v = read();
        int64 costX = 0, costY = 0, flag = 0;
        for(int i = 0; i < vs.size(); ++i) {
            if((i+1) * u >= v) {
                flag = 1;
                if(costX == 0) {
                    costX = vs[i] * (v - u * i);
                    costY = v;
                }else {
                    costX += vs[i] * (v - u * i);
                }
                break;
            }else {
                if(costX == 0) {
                    costX = vs[i] * u;
                    costY = v;
                }else {
                    costX += vs[i] * u;
                }
            }
        }
        if(flag == 0) printf("NaN\n");
        else {
            u = __gcd(costX, costY);
            costX /= u;
            costY /= u;
            printf("%lld/%lld\n", costX, costY);
        }
    }
}
}mcmf;
int n, m;
int ar[MXN];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = 1, cas = 0;
    while(~scanf("%d%d", &n, &m)) {
        mcmf.init(n);
        for(int i = 1, a, b, c; i <= m; ++i) {
            a = read(), b = read(), c = read();
            mcmf.add_edge(a, b, 1, c);
            // mcmf.add_edge(b, a, 1, c);
        }
        mcmf.min_cost_flow(1, n, INF);
        mcmf.solve();
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}