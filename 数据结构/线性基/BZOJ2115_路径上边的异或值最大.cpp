#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define eb emplace_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
#define BASE_MAX 62
 
const int INF = 0x3f3f3f3f;
const LL mod = 998244353;
const int MXN = 1e6 + 7;
int n, m, num;
LL flag;
struct lp {
    int v, nex;
    LL w;
}edge[MXN*2];
int head[MXN], cnt;
int vis[MXN];
LL id[MXN], dis[MXN];
LL bs[MXN];
void add_edge(int u, int v, LL w) {
    edge[++cnt].v = v; edge[cnt].nex = head[u]; edge[cnt].w = w;
    head[u] = cnt;
    edge[++cnt].v = u; edge[cnt].nex = head[v]; edge[cnt].w = w;
    head[v] = cnt;
}
bool insert(LL x, LL *bs) {
    for(int j = BASE_MAX; j >= 0; --j) {//63
        if(!(x >> j)) continue;
        if(bs[j]) x ^= bs[j];
        else {
            bs[j] = x;
            for(int k = j-1; k >= 0; --k) if(bs[k]&&(bs[j]&(1LL<<k))) bs[j]^=bs[k];
            for(int k = j+1; k <= BASE_MAX; ++k) if(bs[k]&(1LL<<j)) bs[k]^=bs[j];
            return true;
        }
    }
    return false;
}
void go(int n) {
    for(int i = 0; i < n; ++i) insert(id[i], bs);
}
void dfs(int u, int ba, int bid, LL val) {
    if(u == n) {
        flag = max(flag, val);
    }
    dis[u] = val;
    for(int i = head[u]; ~i; i = edge[i].nex) {
        int v = edge[i].v;
        if(bid == (i^1)) continue;
        if(vis[v]) {
            id[num++] = val ^ edge[i].w ^ dis[v];
            continue;
        }
        vis[v] = 1;
        dfs(v, u, i, val^edge[i].w);
    }
}
//任意一条 1 到 n 的路径的异或和，都可以由任意一条 1 到 n 路径的异或和与图中的一些环的异或和来组合得到。
int main(int argc, char const *argv[]){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
    scanf("%d%d", &n, &m);
    cnt = -1;
    for(int i = 0; i <= n; ++i) head[i] = -1;
    for(int i = 0; i < m; ++i) {
        int a, b; LL c; scanf("%d%d%lld", &a, &b, &c);
        add_edge(a, b, c);
    }
    vis[1] = 1;
    dfs(1, -1, -10, 0);
    go(num);
    LL ans = flag;
    for(int i = BASE_MAX; i >= 0; --i) if((ans^bs[i]) > ans) ans = ans ^ bs[i];
    printf("%lld\n", ans);
    return 0;
}