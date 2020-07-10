#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
const int MXN = 2e5 + 7;
const int MXE = 6e5 + 7;
const int mod = 998244353;

int n, m;
struct lp {
    int v, nex, w;
}cw[MXN*2];
int head[MXN], tot_b;
int dep[MXN], up[MXN][20];
struct TRIE {
    int sum[MXE*40], cw[MXE*40][2], rt[MXN], tot;
    void init() {
        sum[0] = 0;cw[0][0] = cw[0][1] = 0;rt[0] = 0;tot = 0;
    }
    void insert(int old, int cur, int len, int V) {//32
        int t = ++ tot; rt[cur] = t;
        cw[t][0] = cw[t][1] = 0;
        old = rt[old];
        for(int i = len-1, x; i >= 0; --i) {
            x = (V>>i)&1;
            sum[t] = sum[old] + 1;
            cw[t][!x] = cw[old][!x];
            if(cw[t][x] == 0) cw[t][x] = ++ tot;
            t = cw[t][x]; old = cw[old][x];
        }
        sum[t] = sum[old] + 1;
    }
    LL query(int l, int r, int len, int V) {
        LL ans = 0;
        l = rt[l], r = rt[r];
        for(int i = len-1, x; i >= 0; --i) {
            x = !((V>>i)&1);
            if(sum[cw[r][x]] - sum[cw[l][x]] > 0) {
                ans += (1LL << i);
                l = cw[l][x]; r = cw[r][x];
            }else {
                l = cw[l][!x]; r = cw[r][!x];
            }
        }
        return ans;
    }
}trie;
void add_edge(int a, int b, int c) {
    cw[++tot_b] = {b, head[a], c}; head[a] = tot_b;
    cw[++tot_b] = {a, head[b], c}; head[b] = tot_b;
}
void build(int u,int ba,int d,int x) {
    trie.insert(ba, u, 32, x);
    dep[u] = d; up[u][0] = ba;
    for(int i = 1; i < 20; ++i) up[u][i]=up[up[u][i-1]][i-1];
    for(int i = head[u]; ~i; i = cw[i].nex) {
        int v = cw[i].v;
        if(v == ba) continue;
        build(v, u, d+1, cw[i].w);
    }
}
int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 19; i >= 0; --i) {
        if(dep[up[x][i]] >= dep[y]) x = up[x][i];
    }
    if(x == y) return x;
    for(int i = 19; i >= 0; --i) {
        if(up[x][i] != up[y][i]) {
            x = up[x][i], y = up[y][i];
        }
    }
    return up[x][0];
}
int main(int argc, char const *argv[]) {
    scanf("%d%d", &n, &m);
    trie.init();
    tot_b = -1; for(int i = 1; i <= n; ++i) head[i] = -1;
    for(int i = 1, a, b, c; i < n; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        add_edge(a, b, c);
    }
    build(1, 0, 1, 0);
    int l, r, x;
    while(m --) {
        scanf("%d%d%d", &l, &r, &x);
        int lca = LCA(l, r);
        printf("%lld\n", max(trie.query(lca, l, 32, x), trie.query(lca, r, 32, x)));
    }
    return 0;
}
/*
给你一棵树，每个点有一个权值
Q次询问，每次询问你在(x,y)这条链上的点与c异或的最大值是多少
*/