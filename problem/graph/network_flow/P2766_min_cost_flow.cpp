/*
dp[i]表示以i结尾的最长不下降子序列长度
dep[i]表示满足dp[x] = i的点x
dep[i-1] 向 dep[i]连边，并保证:
下标小的向下标大的连边
没有权值大的向权值小的连边
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MXE = 1e6 + 7;
struct DINIC {
    static const int MXN = 1e4 + 7;
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
        memset(d, -1, sizeof(int) * (1 + vt));
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
    int dfs(int x, int f) {
        if (x == vt || f == 0) return f;
        int use = 0, w;
        for (int i = head[x]; i != -1; i = cw[i].nex) {
            int to = cw[i].v;
            if (d[to] == d[x] - 1 && cw[i].w) {
                w = dfs(to, min(cw[i].w, f - use));
                cw[i].w -= w, cw[i ^ 1].w += w;
                use += w;
                if (use == f) return f;
            }
        }
        // if(!use)d[x]=-1;
        return use;
    }
    void init(int st, int ed) {
        tot = -1;
        vs = st, vt = ed;
        memset(head, -1, sizeof(int) * (1 + vt));
    }
    int max_flow() {
        static int ans;
        while (bfs()) ans += dfs(vs, INF);
        return ans;
    }
} dinic;

// class MCMF_D {
//     public:
// static const int MAX_V = 4003;
// struct edge {
//     int to, cap, cost, rev;
//     edge(int _to, int _cap, int _cost, int _rev) : to(_to), cap(_cap),
//     cost(_cost), rev(_rev) {}
// };
// int V;
// vector<edge> G[MAX_V];
// int h[MAX_V];
// int dis[MAX_V];
// int preV[MAX_V], preE[MAX_V];
// void init(int _v) {
//     V = _v + 1;//points low-index 0 - v
//     for (int i = 0; i <= V; i++) {G[i].clear();preV[i] = preE[i] = 0;}
// }
// void add_edge(int from, int to, int cap, int cost) {
//     G[from].push_back(edge(to, cap, cost, G[to].size()));
//     G[to].push_back(edge(from, 0, -cost, G[from].size() - 1));
// }
// //if you want to solve max_cost_flow, just reverse cost, change pq, init dis, slack and tepan
// int min_cost_flow(int s, int t, int f) {
//     int res = 0;
//     fill(h, h + V, 0);
//     while (f > 0) {
//         priority_queue<pii, vector<pii>, greater<pii> > que;//
//         fill(dis, dis + V, INF);//
//         dis[s] = 0;
//         que.push(make_pair(0, s));
//         while (!que.empty()) {
//             pii p = que.top();
//             que.pop();
//             int v = p.second;
//             if (dis[v] < p.first) {//
//                 continue;
//             }
//             for (int i = 0; i < G[v].size(); i++) {
//                 edge &e = G[v][i];
//                 if (e.cap > 0 && dis[e.to] > dis[v] + e.cost + h[v] -
//                 h[e.to]) {//
//                     dis[e.to] = dis[v] + e.cost + h[v] - h[e.to];
//                     preV[e.to] = v;
//                     preE[e.to] = i;
//                     que.push(make_pair(dis[e.to], e.to));
//                 }
//             }
//         }
//         if (dis[t] == INF) return res;//
//         for (int v = 0; v < V; v++) h[v] += dis[v];
//         int d = f;
//         for (int v = t; v != s; v = preV[v]) d = min(d,
//         G[preV[v]][preE[v]].cap); f -= d; res += d; for (int v = t; v != s; v
//         = preV[v]) {
//             edge &e = G[preV[v]][preE[v]];
//             e.cap -= d;
//             G[v][e.rev].cap += d;
//         }
//     }
//     return res;
// }
// }mcmf;
const int MXNE = 505;
int n, tim, k;
int ar[MXNE], dp[MXNE], tp[MXNE];
vector<int> dep[MXNE];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    tim = 1;
    while (tim--) {
        scanf("%d", &n);
        int vs = 0, vt = n + n + 1;
        memset(tp, 0x3f, sizeof(int) * (n + 2));
        int mxd = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &ar[i]);
            k = upper_bound(tp + 1, tp + 1 + n, ar[i]) - tp;
            dp[i] = k;
            tp[k] = ar[i];
            // cout << i << " " << k << endl;
            dep[k].emplace_back(i);
            mxd = max(mxd, k);
        }
        if(mxd == 1) {
            printf("1\n%d\n%d\n", n, n);
            break;
        }
        printf("%d\n", mxd);
        dinic.init(vs, vt);
        for (int i = 1; i <= mxd; ++i) {
            for (int x : dep[i]) {
                if (i == 1) dinic.add_edge(vs, x + x - 1, 1);
                if (i == mxd) dinic.add_edge(x + x, vt, 1);
                dinic.add_edge(x + x - 1, x + x, 1);
                for (int j = i + 1; j <= mxd; j = mxd + 1) {
                    for (int y : dep[j]) {
                        if(ar[x] <= ar[y] && x < y) dinic.add_edge(x + x, y + y - 1, 1);
                    }
                }
            }
        }
        printf("%d\n", dinic.max_flow());
        dinic.add_edge(1, 2, INF);
        dinic.add_edge(n + n - 1, n + n, INF);
        if(dp[1] == 1) dinic.add_edge(vs, 1, INF);
        if(dp[n] == 1) dinic.add_edge(vs, n + n - 1, INF);
        if(dp[n] == mxd) dinic.add_edge(n + n, vt, INF);
        printf("%d\n", dinic.max_flow());
    }
    return 0;
}