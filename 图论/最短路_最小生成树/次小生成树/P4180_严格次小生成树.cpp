
/*
5 6
1 2 1 
1 3 2 
2 4 3 
3 5 4 
3 4 3 
4 5 6 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <ctime>
#include<iostream>
using namespace std;
typedef long long LL;

const int MXN = 1e5 + 5;
const int MXE = 6e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m;
LL dis[MXN], dis1[MXN][23], dis2[MXN][23];
int dep[MXN], up[MXN][23];
int FA[MXN], rk[MXN];
int head[MXN], tot;
struct lp{
    int v, w, nex;
}cw[MXE];
struct EDGE{
    int u, v, w, is;
}edge[MXE];
bool cmp(const EDGE& a, const EDGE& b) {
    return a.w < b.w;
}
void add(int u,int v,int w) {
    cw[++tot].v = v; cw[tot].nex = head[u]; cw[tot].w = w;
    head[u] = tot;
    cw[++tot].v = u; cw[tot].nex = head[v]; cw[tot].w = w;
    head[v] = tot;
}
void dfs(int u, int ba, int d) {
    dep[u] = d; up[u][0] = ba;
    for(int i = 1; i < 20; ++i) {
        int cf = up[u][i-1];
        up[u][i] = up[cf][i-1];
        dis1[u][i] = max(dis1[u][i-1], dis1[cf][i-1]);
        if(dis1[u][i-1] == dis1[cf][i-1]) dis2[u][i] = max(dis2[u][i-1], dis2[cf][i-1]);
        else {
            dis2[u][i] = min(dis1[u][i-1], dis1[cf][i-1]);
            dis2[u][i] = max(dis2[u][i], max(dis2[u][i-1], dis2[cf][i-1]));
        }
    }
    for(int i = head[u]; ~i; i = cw[i].nex) {
        int v = cw[i].v;
        if(v == ba) continue;
        dis[v] = dis[u] + cw[i].w;
        dis1[v][0] = cw[i].w;
        up[v][0] = u;
        dfs(v, u, d + 1);
    }
}
int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    int k = dep[x] - dep[y];
    for(int i = 0; i < 20; ++i) {
        if((1<<i)&k) {
            x = up[x][i];
        }
    }
    if(x == y) return x;
    for(int i = 19; i >= 0; --i) {
        if(up[x][i] != up[y][i]) {
            x = up[x][i]; y = up[y][i];
        }
    }
    return up[x][0];
}
int Fi(int x) {
    return FA[x] == x? x: FA[x] = Fi(FA[x]);
}
LL calc(int u, int v,int w) {
    if(dep[u] < dep[v]) swap(u, v);
    int k = dep[u] - dep[v];
    LL mx1 = 0, mx2 = 0;
    for(int i = 0; i < 20; ++i) {
        if((1<<i)&k) {
            if(dis1[u][i] > mx1) {
                mx2 = mx1;
                mx1 = dis1[u][i];
            }
            mx2 = max(mx2, dis2[u][i]);
            u = up[u][i];
        }
    }
    if(mx1 != w) return w - mx1;
    return w - mx2;
}
void init() {
    tot = -1;
    memset(up, 0, sizeof(up));
    memset(head, -1, sizeof(head));
    memset(dis, 0, sizeof(dis));
    memset(dis1, 0, sizeof(dis1));
    memset(dis2, 0, sizeof(dis2));
    memset(dep, 0, sizeof(dep));
}
void solve() {
    scanf("%d%d", &n, &m);
    init();
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
        edge[i].is = 0;
    }
    for(int i = 1; i <= n; ++i) FA[i] = i, rk[i] = 1;
    sort(edge, edge + m, cmp);
    int cnt = 0;
    LL MAX = 0;
    for(int i = 0; i < m; ++i) {
        int pa = Fi(edge[i].u), pb = Fi(edge[i].v);
        if(pa == pb) continue;
        if(rk[pa] > rk[pb]) swap(pa,pb);
        FA[pa] = pb;
        rk[pb] += rk[pa];
        add(edge[i].u, edge[i].v,edge[i].w);
        MAX += edge[i].w;
        cnt ++;
        edge[i].is = 1;
        if(cnt == n-1) break;
    }
    up[1][0] = 1;
    dis1[1][0] = 0;
    dfs(1, 1, 1);
    LL tmp = 1e18;
    for(int i = 0; i < m; ++i) {
        if(edge[i].is) continue;
        int cf = LCA(edge[i].u,edge[i].v);
        tmp = min(tmp, calc(edge[i].u,cf,edge[i].w));
        tmp = min(tmp, calc(edge[i].v,cf,edge[i].w));
    }
    printf("%lld\n", MAX + tmp);
}
int main(int argc, char const *argv[]){
    solve();
    return 0;
}
