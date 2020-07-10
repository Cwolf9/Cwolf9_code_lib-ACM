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
const int MXE = 2e5 + 6;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, m;
struct lp{
    int u, v, nex;
}cw[MXE];
int head[MXN], tot;
int dfn[MXN], low[MXN], inde, iscut[MXN];
int stak[MXE], top;
int ans1, ans2;
int vis1[MXN];
void dfs_tj(int u,int ba) {
    dfn[u] = low[u] = ++inde;
    int child = 0;
    for(int i = head[u]; ~i; i = cw[i].nex) {
        int v = cw[i].v;
        if(!dfn[v]) {
            stak[++top] = i;
            ++ child;
            dfs_tj(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                iscut[u] = 1;
                Fill(vis1, 0);
                int tmp1 = 0, tmp2 = 0;
                while(1) {
                    int id = stak[top--];
                    int a = cw[id].u, b = cw[id].v;
                    if(!vis1[a]) ++tmp1;
                    if(!vis1[b]) ++tmp1;
                    vis1[a] = vis1[b] = 1;
                    ++tmp2;
                    if(cw[id].u == u && cw[id].v == v) {
                        if(tmp1 > tmp2) ans1 += tmp2;
                        if(tmp1 < tmp2) ans2 += tmp2;
                        break;
                    }
                }
            }
        }else if(dfn[v] < dfn[u] && v != ba) {
            stak[++top] = i;
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(ba < 0 && child == 1) iscut[u] = 0;
}
void add_edge(int u,int v) {
    cw[++tot].v = v; cw[tot].nex = head[u];
    head[u] = tot; cw[tot].u = u;
    cw[++tot].v = u; cw[tot].nex = head[v];
    head[v] = tot; cw[tot].u = v;
}
int main(int argc, char const *argv[]) {
    while(~scanf("%d%d", &n, &m) && (n + m)) {
        Fill(dfn, 0);Fill(low, 0);Fill(iscut, 0);
        inde = top = 0;
        Fill(head, -1);
        tot = -1;
        ans1 = ans2 = 0;
        for(int i = 0, a, b; i < m; ++i) {
            scanf("%d%d", &a, &b);
            ++ a, ++ b;
            add_edge(a, b);
        }
        for(int i = 1; i <= n; ++i) {
            if(!dfn[i]) dfs_tj(i, -1);
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}
/*
8 10
0 1
1 2
2 3
3 0
3 4
4 5
5 6
6 7
7 4
5 7
0 0

9 10
1 2
2 3
3 7
7 8
8 9
9 1
3 4
4 5
5 6
6 7

6 6
1 2
2 3
3 4
4 5
5 6
6 1

14 16
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 1
2 11
4 9

*/
