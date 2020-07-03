/*
8 5
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 1
0 5 2
10 5 3
11 5 4
110 8 2
*/
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
std::vector<int> mp[MXN];
struct lp{
    int l, r, sum;
}cw[MXN*40];
int rot[MXN], k;
int ar[MXN], br[MXN];
int sz[MXN], son[MXN], top[MXN], dep[MXN], fa[MXN], CNT;
void init() {
    CNT = 0;
    cw[0].l = cw[0].r = cw[0].sum = 0;
    for(int i = 1; i <= n; ++i) mp[i].clear();
    memset(rot, 0 ,sizeof(rot));
    memset(son, 0, sizeof(son));
    memset(top, 0, sizeof(top));
}
void insert(int &cur,int last,int p,int l,int r) {
    cw[++CNT] = cw[last];
    cur = CNT;
    cw[cur].sum ++;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) insert(cw[cur].l, cw[last].l, p, l, mid);
    else insert(cw[cur].r, cw[last].r, p, mid+1, r);
}
int query(int pl,int pr,int lca,int lca_fa,int p,int l,int r) {
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int tmp = cw[lson(pl)].sum+cw[lson(pr)].sum-cw[lson(lca)].sum-cw[lson(lca_fa)].sum;
    if(p <= tmp) return query(lson(pl),lson(pr),lson(lca),lson(lca_fa),p,l,mid);
    else {
        return query(rson(pl),rson(pr),rson(lca),rson(lca_fa),p-tmp,mid+1,r);
    }
}
void dfs(int u,int ba,int d) {
    sz[u] = 1, dep[u] = d;
    insert(rot[u], rot[ba], ar[u], 1, k);
    int len = mp[u].size();
    for(int i = 0; i < len; ++i) {
        int v = mp[u][i];
        if(v == ba) continue;
        fa[v] = u;
        dfs(v, u, d+1);
        sz[u] += sz[v];
        if(!son[u] || sz[v] > sz[son[u]]) son[u] = v;
    }
}
void dfs(int u,int tu) {
    top[u] = tu;
    if(!son[u]) return;
    dfs(son[u], tu);
    int len = mp[u].size();
    for(int i = 0; i < len; ++i) {
        int v = mp[u][i];
        if(v == son[u] || v == fa[u]) continue;
        dfs(v, v);
    }
}
int LCA(int x,int y) {
    while(top[x] != top[y]) {
        if(dep[top[x]]>=dep[top[y]]) x = fa[top[x]];
        else y = fa[top[y]];
    }
    if(dep[x] >= dep[y]) return y;
    return x;
}
void solve() {
    for(int i = 1; i <= n; br[i] = ar[i], ++i) scanf("%d", &ar[i]);
    sort(br+1, br+1+n);
    k = unique(br+1,br+1+n)-br;
    for(int i = 1; i <= n; ++i) {
        ar[i] = lower_bound(br+1,br+k,ar[i]) - br;
    }
    init();
    for(int i = 1, u , v; i < n; ++ i) {
        scanf("%d%d", &u, &v);
        mp[u].push_back(v);
        mp[v].push_back(u);
    }
    dfs(1, 0, 1);
    dfs(1, 1);
    int lastans = 0;
    while(m --) {
        int u, v, p;
        scanf("%d%d%d", &u, &v, &p);
        u = u ^ lastans;
        int lca = LCA(u, v);
        lastans = br[query(rot[u],rot[v],rot[lca],rot[fa[lca]],p,1,k)];
        printf("%d\n", lastans);
    }
}
int main(int argc, char const *argv[]){
    while(~scanf("%d%d", &n, &m)) solve();
    return 0;
}
