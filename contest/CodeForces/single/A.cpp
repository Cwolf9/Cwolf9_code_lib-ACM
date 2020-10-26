#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << "\n";
#define debug2(x, y) cout << #x << ": " << x << ", " << #y << ": " << y << "\n";

const int maxn = 1e6 + 7;
const double eps = 1e-8;

typedef long long ll;
int n;
int dep[maxn], ye[maxn];
vector<int> adj[maxn];
void dfs(int u, int d) {
    dep[u] = d;
    ye[u] = 0;
    if(adj[u].size()) ye[u] = 1e9;
    for(int v: adj[u]) {
        dfs(v, d + 1);
        ye[u] = min(ye[u], ye[v] + 1);
    }
}
ll ans;
int id;
bool cmp(const int &a, const int &b) {
    if(ye[a] != ye[b]) return ye[a] < ye[b];
    return a < b;
}
void dfs2(int u, int ba, int h, int d) {
    //cout << u << " " << d << endl;
    if(adj[u].size() == 0) {
        debug(u)
        ans += d;
        id = u;
        return;
    }
    int tid;
    for(int v: adj[u]) {
        if(id == 0) {
            dfs2(v, u, h + 1, d + 1);
        }else {
            int w = dep[id] - dep[u];
            if(w < h) {
                id = 0;
                dfs2(v, u, h + 1, w + 1);
            }else {
                tid = id;
                id = 0;
                dfs2(v, u, h + 1, h + 1);
                id = (dep[id] < dep[tid]?id:tid);
            }
        }
        if(u == 4) debug(id)
    }
}
int main() {
    //freopen("in.txt", "r", stdin);
    int T;scanf("%d",&T);
    int kase = 0;
    while(T--) {
        id = 0;
        ans = 0;
        scanf("%d", &n);
        for(int i = 2; i <= n; ++i) {
            int f; scanf("%d", &f);
            adj[f].push_back(i);
        }
        dfs(1, 0);
        for(int i = 1; i <= n; ++i) sort(adj[i].begin(), adj[i].end(), cmp);
        dfs2(1, 0, 0, 0);
        printf("Case #%d: %lld\n", ++kase, ans);
        for(int i = 1; i <= n; ++i) adj[i].clear();
    }
    return 0;
}
/*
7
14
1 2 3 3 5 3 7 8 2 10 11 12 13
3
1 1
6
1 2 3 4 4
9
1 2 2 4 5 1 7 8
12
1 2 3 1 5 6 4 4 12 9 11
7
1 2 3 3 2 5
6
1 2 3 3 2

17
2
6
9
12
8
7

1
21
1 2 3 4 5 4 7 7 9 2 8 11 11 11 10 9 16 16 12 20
*/