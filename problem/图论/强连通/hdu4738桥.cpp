#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#define fi first
#define se second
#define Fill(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int MXN = 1e4 + 5;
const int MXE = 4e6 + 6;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, m;
struct lp{
    int v, nex, w;
}cw[MXE];
int dfn[MXN], low[MXN], head[MXN], inStack[MXN];
int inde, top, ans, tot;
int stak[MXE];
void dfs_tj(int u,int ba) {
    dfn[u] = low[u] = ++inde;
    inStack[u] = 1;
    stak[++top] = u;
    for(int i = head[u]; ~i; i = cw[i].nex) {
        int v = cw[i].v;
        if((i ^ 1) == ba) continue;
        if(!dfn[v]) {
            dfs_tj(v, i);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]) {
                ans = min(ans, cw[i].w);
            }
        }else if(inStack[v] == 1) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        int v;
        do{
            v = stak[top--];
            inStack[v] = 2;
        }while(v != u);
    }
}

void add_edge(int u, int v, int w) {
    cw[++tot].v = v; cw[tot].nex = head[u];
    head[u] = tot; cw[tot].w = w;
    cw[++tot].v = u; cw[tot].nex = head[v];
    head[v] = tot; cw[tot].w = w;
}

int main(int argc, char const *argv[]) {
    while(~scanf("%d%d", &n, &m)) {
        if(n == 0 && m == 0) break;
        Fill(dfn, 0);Fill(low, 0);Fill(inStack, 0);Fill(head, -1);
        inde = top = 0;tot = -1;ans = INF;
        for(int i = 0, a, b, c; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, c);
        }
        dfs_tj(1, -1);
        int flag = 0;
        for(int i = 1; i <= n; ++i) {
            if(!dfn[i]) flag = 1;
        }
        if(flag) ans = 0;
        else {
            if(ans == INF) ans = -1;
            if(ans == 0) ans = 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
