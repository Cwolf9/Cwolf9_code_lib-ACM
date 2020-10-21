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
    for(int v: adj[u]) {
        dfs(v, d + 1);
        ye[u] = max(ye[u], ye[v] + 1);//子树最深叶子深度
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
        ans += d;
        id = u;//上一次军队停留的叶子
        return;
    }
    for(int v: adj[u]) {
        if(id == 0) {//这条路径前没有可产生贡献的军队停留，径直往下走
            dfs2(v, u, h + 1, d + 1);
        }else {
            int w = dep[id] - dep[u];
            if(w < h) {//如果从上次军队停留的叶子出发比从根节点出发更优
                id = 0;//军队就继续出发，所以就没有军队停留了
                dfs2(v, u, h + 1, w + 1);
            }else {
                id = 0;//上个叶子对这条路径产生不了贡献，以后也必不可能产生贡献
                dfs2(v, u, h + 1, h + 1);
            }
        }
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
        //按最深子叶深度从小到大排序，排序是精髓
        for(int i = 1; i <= n; ++i) sort(adj[i].begin(), adj[i].end(), cmp);
        dfs2(1, 0, 0, 0);
        printf("Case #%d: %lld\n", ++kase, ans);
        for(int i = 1; i <= n; ++i) adj[i].clear();
    }
    return 0;
}
/*
8
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
20
1 2 3 4 5 4 7 7 9 2 8 11 11 11 10 9 16 16 12

17
2
6
9
12
8
7
29
*/