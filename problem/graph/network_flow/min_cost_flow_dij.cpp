//hdu 6611 6-1009
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
class MCMF_D {
    public:
static const int MAX_V = 4003;
struct edge {
    int to, cap, cost, rev;
    edge(int _to, int _cap, int _cost, int _rev) : to(_to), cap(_cap), cost(_cost), rev(_rev) {}
};
int V;
vector<edge> G[MAX_V];
int h[MAX_V];
int dis[MAX_V];
int preV[MAX_V], preE[MAX_V];
void init(int _v) {
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
        for (int v = t; v != s; v = preV[v]) {
            edge &e = G[preV[v]][preE[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}
}mcmf;
int n, tim, k;
int ar[4005];
int main() {
    scanf("%d", &tim);
    while (tim--) {
        scanf("%d%d", &n, &k);
        int vs1 = 0, vs2 = n + n + 1, vt = n + n + 2;
        mcmf.init(vt);
        mcmf.add_edge(vs1, vs2, k, 0);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &ar[i]);
            mcmf.add_edge(vs2, i, 1, 0);
            mcmf.add_edge(i + n, vt, 1, 0);
        }
        for (int i = 1; i <= n; ++i) {
            mcmf.add_edge(i, i + n, 1, -ar[i]);
            for (int j = 1 + i; j <= n; ++j) {
                if (ar[j] >= ar[i]) mcmf.add_edge(i + n, j, 1, 0);
            }
        }
        printf("%d\n", -mcmf.min_cost_flow(vs1, vt, k));
    }
    return 0;
}
