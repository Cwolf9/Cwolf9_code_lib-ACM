/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6820)
**题意**
$n(2e5)$个点的带边权的树，选出一个连通子图，保证至多只有一个点的度数可以大
于$k(0\le k\lt n)$，问这种子图的最大边权和。
**思路**
换根$dp$+优先队列贪心
$dp[u][0]$表示至多选出$u$的$k-1$个子树的最大边权和
$dp[u][1]$表示至多选出$u$的$k$个子树的最大边权和
$dp[u][1] = \sum_{max\;k\;v} (dp[v][0]+w_{uv})$
选出最大的$k$个$dp[v][0]+w_{uv}$转移即可，优先队列贪心维护最大的$k$个。
$k_son_val[u]$表示$u$的第$k$大的子树权值和：$dp[v][0]+w_{uv}$
$max_k1_son[v]$表示$v$是否属于其父亲子树中权值和最大的$k-1$个子树
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long int64;
typedef pair<int, int> pii;
typedef pair<int64, int> pLi;
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
int64 ksm(int64 a, int b, int Mod) {int64 res = 1;for(; b; b>>=1, a=a*a%Mod) {if(b&1) res = res * a % Mod;}return res;}
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 2e5 + 5;
int n, k;
pLi tmp;
vector<pii> mp[MXN];
int64 ans, dp[MXN][2], k_son_val[MXN];
int max_k1_son[MXN], vis[MXN];
void get_u_val(int u, priority_queue<pLi, vector<pLi>, greater<pLi> >&Q) {
    if(SZ(Q) == k) {
        tmp = Q.top(); Q.pop();
        k_son_val[u] = dp[u][1] = tmp.fi;
        vis[tmp.se] = 1;
    }
    while(!Q.empty()) {
        tmp = Q.top(); Q.pop();
        dp[u][1] += tmp.fi, dp[u][0] += tmp.fi;
        max_k1_son[tmp.se] = vis[tmp.se] = 1;
    }
}
void dfs(int u, int ba) {
    dp[u][0] = dp[u][1] = 0;
    max_k1_son[u] = k_son_val[u] = 0;
    priority_queue<pLi, vector<pLi>, greater<pLi> > Q;
    for(pii V: mp[u]) {
        if(V.fi == ba) continue;
        dfs(V.fi, u);
        Q.push(mk(dp[V.fi][0] + V.se, V.fi));
        if(SZ(Q) > k) Q.pop();
    }
    get_u_val(u, Q);
    int64 ret = dp[u][1];
    for(pii V: mp[u]) {
        if(V.fi != ba && vis[V.fi] == 0) ret += V.se + dp[V.fi][0];
        vis[V.fi] = 0;
    }
    ans = max(ans, ret);
    // debug(u, ans)
}
void dfs2(int u, int ba, int d) {
    if(ba != 0) {
        int64 tmp1 = 0;
        if(max_k1_son[u] == 0) tmp1 = dp[ba][0] + d;
        else tmp1 = dp[ba][0] - dp[u][0] - d + k_son_val[ba] + d;
        priority_queue<pLi, vector<pLi>, greater<pLi> > Q;
        Q.push(mk(tmp1, ba));
        for(pii V: mp[u]) {
            if(V.fi == ba) continue;
            max_k1_son[V.fi] = 0;
            Q.push(mk(dp[V.fi][0] + V.se, V.fi));
            if(SZ(Q) > k) Q.pop();
        }
        dp[u][1] = dp[u][0] = 0;
        get_u_val(u, Q);
        int64 ret = dp[u][1];
        for(pii V: mp[u]) {
            if(V.fi != ba && vis[V.fi] == 0) ret += V.se + dp[V.fi][0];
            if(V.fi != ba) vis[V.fi] = 0;
        }
        if(vis[ba] == 0) ret += tmp1;
        vis[ba] = 0;
        // debug(u, ret)
        ans = max(ans, ret);
    }
    for(pii V: mp[u]) {
        if(V.fi == ba) continue;
        dfs2(V.fi, u, V.se);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read(), k = read();
        ans = 0;
        for(int i = 1; i <= n; ++i) mp[i].clear();
        for(int i = 1, a, b, c; i < n; ++i) {
            a = read(), b = read(), c = read();
            mp[a].eb(mk(b, c));
            mp[b].eb(mk(a, c));
        }
        if(k == 0) ans = 0;
        else {
            dfs(1, 0);
            dfs2(1, 0, 0);
        }
        printf("%lld\n", ans);
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}