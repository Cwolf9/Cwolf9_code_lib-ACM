/*
链接：
https://vjudge.net/contest/381037#problem/L
题意：
给定一棵无根树，假设它有n个节点，节点编号从1到n, 求1-n这n个节
点，到其他n-1个节点的距离之和。

思路：
两次dfs


备注：
蔓延

*/
#include<bits/stdc++.h>
#define fi first
#define se second
#define mk make_pair
#define eb push_back
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
inline LL read() {
    LL x = 0;int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MXN = 1e5 + 5;
int n;
LL m, k;
int ans[MXN];
int ar[MXN], sz[MXN];
LL dp[MXN];
vector<pii > mp[MXN];
void dfs(int u, int ba) {
    sz[u] = ar[u];
    for(pii V: mp[u]) {
        int v = V.fi;
        LL w = V.se;
        if(v == ba) continue;
        dfs(v, u);
        sz[u] += sz[v];
        dp[u] += dp[v] + w * sz[v];
    }
}
void dfs2(int u, int ba, LL w) {
    // debug(u, dp[u])
    if(ba) {
        dp[u] = dp[ba] + w * (m - 2 * sz[u]);
    }
    for(pii V: mp[u]) {
        int v = V.fi;
        if(v == ba) continue;
        dfs2(v, u, V.se);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int A[10] = {6,28,496,8128};
    int tim = read();
    while(tim -- ){
        int a = read(), b = read();
        if(a > b) swap(a, b);
        int num = 0;
        for(int i = 0; i < 4; ++i) {
            if(A[i] >= a && A[i] <= b) ++ num;
        }
        printf("%d\n", num);
    }
    return 0;
    n = read();
    for(int i = 1; i <= n; ++i) {
        ar[i] = read(), m += ar[i];
    }
    for(int i = 2, a, b, c; i <= n; ++i) {
        a = read(), b = read(), c = read();
        mp[a].eb(mk(b, c));
        mp[b].eb(mk(a, c));
    }
    dfs(1, 0);
    dfs2(1, 0, 0);
    LL ans = INFLL;
    for(int i = 1; i <= n; ++i) {
        ans = min(ans, dp[i]);
    }
    printf("%lld\n", ans);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}