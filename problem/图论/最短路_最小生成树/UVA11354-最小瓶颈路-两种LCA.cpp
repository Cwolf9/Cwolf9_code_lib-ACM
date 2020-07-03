#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <ctime>
#include<iostream>
#define lson(x) cw[x].l
#define rson(x) cw[x].r
using namespace std;
typedef long long LL;

const int MXN = 1e5 + 5;
const int MXE = 6e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m;
int fa[MXN], FA[MXN], up[MXN][23], dis[MXN][23], dep[MXN];
int head[MXN], tot;
struct lp{
    int v, w, nex;
}cw[MXE];
struct node{
    int u, v, w;
}edge[MXE];
void init() {
    tot = -1;
    memset(head, -1, sizeof(head));
    memset(dis, 0, sizeof(dis));
}
void dfs(int u,int ba,int d) {
    fa[u] = up[u][0] = ba;
    dep[u] = d;
    for(int i = 1, cf; i < 20; ++i) {
        cf =up[u][i-1];
        up[u][i] = up[cf][i-1];
        dis[u][i] = max(dis[u][i-1],dis[cf][i-1]);
    }
    for(int i = head[u]; ~i; i = cw[i].nex) {
        int v = cw[i].v;
        if(v == ba) continue;
        dis[v][0] = cw[i].w;
        up[v][0] = u;
        dfs(v, u, d+1);
    }
}
/*int LCA(int x,int y) {
    int ans = 0;
    if(dep[x] < dep[y]) swap(x, y);
    int k = dep[x] - dep[y];
    for(int i = 0; i < 20; ++i) {
        if((1<<i)&k){
            ans = max(ans, dis[x][i]);
            x = up[x][i];
        }
    }
    if(x != y){
        for(int i = 19; i >= 0; --i) {
            if(up[x][i] != up[y][i]) {
                ans = max(ans, dis[x][i]);
                ans = max(ans, dis[y][i]);
                x = up[x][i]; y = up[y][i];
            }
        }
        ans = max(ans, max(dis[x][0],dis[y][0]));
    }
    return ans;
}*/
int LCA(int x,int y) {
    int ans = 0;
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 19; i >= 0; --i) {
        if(dep[up[x][i]] >= dep[y]) {
            ans = max(ans, dis[x][i]);
            x = up[x][i];
        }
    }
    if(x != y){
        for(int i = 19; i >= 0; --i) {
            if(up[x][i] != up[y][i]) {
                ans = max(ans, dis[x][i]);
                ans = max(ans, dis[y][i]);
                x = up[x][i]; y = up[y][i];
            }
        }
        ans = max(ans, max(dis[x][0],dis[y][0]));
    }
    return ans;
}
void add_edge(int u,int v,int w) {
    cw[++tot].v = v; cw[tot].w = w; cw[tot].nex = head[u];
    head[u] = tot;
    cw[++tot].v = u; cw[tot].w = w; cw[tot].nex = head[v];
    head[v] = tot;
}
bool cmp(node &a, node &b) {
    return a.w < b.w;
}
int Fi(int x) {
    return FA[x] == x? x: FA[x] = Fi(FA[x]);
}
int fuck = 0;
void solve() {
    if(fuck) printf("\n");
    init();
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", &edge[i].u,&edge[i].v,&edge[i].w);
    }
    sort(edge, edge + m, cmp);
    int CNT = 0;
    for(int i = 1; i <= n; ++i) FA[i] = i;
    for(int i  = 0; i < m; ++i) {
        int pa = Fi(edge[i].u), pb = Fi(edge[i].v);
        if(pa == pb) continue;
        FA[pb] = pa;
        add_edge(edge[i].u,edge[i].v,edge[i].w);
        CNT ++;
        if(CNT == n - 1) break;
    }
    up[1][0] = 1;
    //dis[1][0] = INF;
    dfs(1, 1, 1);
    int q, u, v;scanf("%d", &q);
    while(q--) {
        scanf("%d%d", &u, &v);
        printf("%d\n", LCA(u, v));
    }
    fuck++;
}
int main(int argc, char const *argv[]){
    while(~scanf("%d%d", &n, &m)) solve();
    return 0;
}

