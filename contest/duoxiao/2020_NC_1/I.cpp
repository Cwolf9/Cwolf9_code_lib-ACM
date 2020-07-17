/*
链接
https://ac.nowcoder.com/acm/contest/5666/I
题意
n=50
m=100
小明要求每个点的度数为 du[i] = 1 or 2, 问你是否存在这样一个边的子集
满足上述条件。
不存在自环，可能有重边
度数和一定要保证为偶数
 
思路
把一条边拆成两个点，把每个点u拆成du[u]个点
edge ->e1 e2
x -> x1
y -> y1 y2
(e1, e2), (x1, e1), (e2, y1), (e2, y2)
再跑一般图最大匹配
看是否是完备匹配
如果存在完美匹配的话，一定可以是每条边拆成两个点分别和两个端点拆成
的du[i]个点中的一个相匹配。
如果完备匹配的话，证明说有条件都满足。
 
备注
如果du[i]等于任意0或者整数, 也是可以这样写的
如果du[i]等于0的话，相当于i相邻的边拆成的两个点自己和自己相匹配
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
class Dhs {
   public:
    static const int D_MXN = 5020;
    static const int D_MXE = 100005;
    static const int D_MXQL = 20005;
    int n;
    int eCnt, head[D_MXN], nex[D_MXE], to[D_MXE];
    int dui[D_MXQL], hed, tail;
    int fa[D_MXN], id[D_MXN], pre[D_MXN], match[D_MXN], vis[D_MXN], Tim;
    inline void add_edge(int u, int v) {
        nex[++ eCnt] = head[u];
        to[eCnt] = v;
        head[u] = eCnt;
        nex[++ eCnt] = head[v];
        to[eCnt] = u;
        head[v] = eCnt;
    }
    inline int Fi(int x) {
        if (fa[x] != x) fa[x] = Fi(fa[x]);
        return fa[x];
    }
    inline int lca(int x, int y) {
        ++ Tim;
        while (vis[x] != Tim) {
            if (x) {
                x = Fi(x);
                if (vis[x] == Tim) return x;
                vis[x] = Tim;
                if (match[x] != 0)
                    x = Fi(pre[match[x]]);
                else
                    x = 0;
            }
            swap(x, y);
        }
        return x;
    }
    inline void change(int x, int y, int k) { 
        //把奇环上的点缩成一个点，并且把原来是奇点的点变成偶点，加入队列
        while (Fi(x) != k) {
            pre[x] = y;
            int z = match[x];
            if (id[z] == 1) {
                id[z] = 0;
                dui[++tail] = z;
            }
            if (Fi(z) == z) fa[z] = k;
            if (Fi(x) == x) fa[x] = k;
            y = z;
            x = pre[y];
        }
    }
 
    inline bool bfs(int ini) {
        for (int i = 1; i <= n; i++) id[i] = -1, fa[i] = i;
        hed = tail = 0;
        dui[++tail] = ini;
        id[ini] = 0;
        int u;
        while (hed < tail) {
            u = dui[++hed];
            for (int i = head[u]; i; i = nex[i]) {
                int v = to[i];
                if (id[v] == -1) {
                    pre[v] = u;
                    id[v] = 1;
                    if (!match[v]) {
                        int last, t, now = v;
                        while (now != 0) {
                            t = pre[now];
                            last = match[t];
                            match[t] = now;
                            match[now] = t;
                            now = last;
                        }
                        return true;
                    }
                    id[match[v]] = 0;
                    dui[++tail] = match[v];
                } else if (id[v] == 0 && Fi(u) != Fi(v)) { 
                    //出现奇环且不是在同一个环中
                    int g = lca(u, v);
                    change(u, v, g);
                    change(v, u, g);
                }
            }
        }
        return false;
    }
    void init(int _n) {
        n = _n;
        eCnt = Tim = 0;
        for (int i = 1; i <= n; ++i) {
            head[i] = match[i] = vis[i] = pre[i] = 0;
        }
    }
    int max_match() {
        int ans = 0;
        for (int i = 1; i <= n; i++) if (!match[i] && bfs(i)) ++ans;
        // printf("%d\n", ans);
        // for (int i = 1; i <= n; i++) printf("%d ", match[i]);
        // puts("");
        return ans;
    }
} dhs;
int n, m, sum_du, inde;
int id[MXN][MXN], contest[MXN][2], du[MXN];
int ein[MXN][2];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = 1, cas = 0;
    while(~scanf("%d%d", &n, &m)) {
        // n = read(), m = read();
        sum_du = inde = 0;
        for(int i = 1; i <= n; ++i) du[i] = 0;
        for(int i = 1; i <= n; ++i) {
            id[i][0] = read();
        }
        for(int i = 1; i <= m; ++i) {
            ein[i][0] = read();
            ein[i][1] = read();
            ++ du[ein[i][0]];
            ++ du[ein[i][1]];
            contest[i][0] = ++ inde;
            contest[i][1] = ++ inde;
        }
        int flag = 0;
        for(int i = 1; i <= n; ++i) {
            if(id[i][0] > du[i]) flag = 1;
            if(flag) continue;
            sum_du += id[i][0];
            for(int j = 1; j <= id[i][0]; ++j) {
                id[i][j] = ++ inde;
            }
        }
        // printf("Case %d: ", ++ cas);
        if(flag || sum_du % 2 == 1) {
            printf("No\n");
            continue;
        }
        dhs.init(inde);
        for(int i = 1, a, b; i <= m; ++i) {
            a = ein[i][0], b = ein[i][1];
            dhs.add_edge(contest[i][0], contest[i][1]);
            for(int j = 1; j <= id[a][0]; ++j) {
                dhs.add_edge(id[a][j], contest[i][0]);
            }
            for(int j = 1; j <= id[b][0]; ++j) {
                dhs.add_edge(id[b][j], contest[i][1]);
            }
        }
        printf("%s\n", dhs.max_match() == inde / 2?"Yes":"No");
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}