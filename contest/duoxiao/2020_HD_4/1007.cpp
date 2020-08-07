/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
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
#define rep(i, s, t) for (register int i = s; i < t; ++i)
#define per(i, s, t) for (register int i = s; i >= t; --i)
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
const int mod = 998244353;  // 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m;
map<pii, int> mp0;  //去重
map<pii, pii> mp2;  //左右两个id
struct DINIC {
    int tot, vt, vs;
    int d[MXN], head[MXN];
    struct lp {
        int v, w, nex;
    } cw[MXE];
    void add_edge(int a, int b, int c) {
        cw[++tot].v = b;
        cw[tot].nex = head[a], cw[tot].w = c;
        head[a] = tot;
        cw[++tot].v = a;
        cw[tot].nex = head[b], cw[tot].w = 0;
        head[b] = tot;
    }
    bool bfs() {
        for (int i = 0; i <= vt; ++i) d[i] = -1;
        queue<int> Q;
        Q.push(vt);
        d[vt] = 0;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = head[u]; i != -1; i = cw[i].nex) {
                int v = cw[i].v;
                if (cw[i ^ 1].w && d[v] == -1) {
                    d[v] = d[u] + 1;
                    Q.push(v);
                }
            }
        }
        return d[vs] != -1;
    }
    int dfs(int x, int low) {
        if (x == vt || low == 0) return low;
        int flow = 0, used = 0;
        for (int i = head[x]; i != -1; i = cw[i].nex) {
            int v = cw[i].v;
            if (cw[i].w && d[v] + 1 == d[x] &&
                (used = dfs(v, min(low, cw[i].w))) > 0) {
                // used=dfs(v,min(low,cw[i].w));
                if (!used) continue;
                flow += used, low -= used;
                cw[i].w -= used;
                cw[i ^ 1].w += used;
                if (!low) break;
            }
        }
        if (!flow) d[x] = -1;
        return flow;
    }
    // int dfs(int x, int f) {
    //     if (x == vt || f == 0) return f;
    //     int use = 0, w;
    //     for (int i = head[x]; i != -1; i = cw[i].nex) {
    //         int to = cw[i].v;
    //         if (d[to] == d[x] - 1 && cw[i].w) {
    //             w = dfs(to, min(cw[i].w, f - use));
    //             cw[i].w -= w, cw[i ^ 1].w += w;
    //             use += w;
    //             if (use == f) return f;
    //         }
    //     }
    //     // if(!use)d[x]=-1;
    //     return use;
    // }
    void init(int st, int ed) {
        tot = -1;
        for (int i = 0; i <= ed; ++i) head[i] = -1;
        vs = st;
        vt = ed;
    }
    int max_flow() {
        int ans = 0;
        while (bfs()) ans += dfs(vs, INF);
        return ans;
    }
} dinic;
int vs, vt, inde;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while (tim--) {
        n = read();
        mp0.clear();
        mp2.clear();
        inde = 0;
        vs = 0, vt = n + n + 1;
        dinic.init(vs, vt);
        for (int i = 1; i <= n; ++i) {
            int a = read(), b = read();
            if (mp0.find(mk(a, b)) != mp0.end()) continue;
            int s = b - a, t = b + a;
            if (mp2.find(mk(s, 1)) == mp2.end()) {
                mp2[mk(s, 1)].fi = ++inde;
                dinic.add_edge(vs, mp2[mk(s, 1)].fi, 1);
            }
            if (mp2.find(mk(t, -1)) == mp2.end()) {
                mp2[mk(t, -1)].fi = ++inde;
                dinic.add_edge(mp2[mk(t, -1)].fi, vt, 1);
            }
            dinic.add_edge(mp2[mk(s, 1)].fi, mp2[mk(t, -1)].fi, 1);
        }
        printf("%d\n", dinic.max_flow());
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}