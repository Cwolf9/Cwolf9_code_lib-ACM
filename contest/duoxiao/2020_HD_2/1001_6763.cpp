/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6763)
**题意**
$n=1e5,m=2e5$的无向图，每个点权值$b_i$，每次选择一个极大$bi$都大于0的联通块，使所有点权值减一。
问最少次数使得所有点权值为0
**思路**
考了逆向过程，从0开始补充bi值，最先被补充的一定是bi最大的点。
我只需要知道完全构建出u这个点之前先构造的是哪一个，u这个点要补充的次数肯定是两个di差值。
原过程就是你删完了那类点后再顺便删u。
所以先从大到小枚举点，在枚举连出去的边中权值比我大的点v，如果u和v没有合并则将uv合并，并
将v的并查集合并到u下面，把v并查集的根指向u，同时我们知道并查集v的是v联通块中最后一个被更新的点。
在更新完v并查集的根rt后应该更新u，rt联通块产生b[rt]-b[u]的贡献。依次让u成为新并查集的根进行下去。
**备注**
经典套路，逆向考虑，建图维护，并查集维护根
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
using namespace std;
typedef long long int64;
typedef pair<int, int> pii;
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T& f, const R&... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int INF = 0x3f3f3f3f;
const int MXN = 2e5 + 5;
const int MXE = 1e7 + 5;
int n, m, k;

int ar[MXN], br[MXN], inde;
int vis[MXN], fa[MXN], las[MXN];
vector<pii> edge;
pii cw[MXN];
vector<int> mp[MXN];
int64 ans;
int Fi(int x) {
    return fa[x] == x?x:fa[x] = Fi(fa[x]);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while (tim--) {
        n = read(), m = read();
        for(int i = 1; i <= n; ++i) {
            ar[i] = read();
            vis[i] = 0;
            las[i] = 0;
            fa[i] = i;
            mp[i].clear();
        }
        edge.clear();
        inde = 0;
        for(int i = 1, a, b; i <= m; ++i) {
            a = read(), b = read();
            if(a > b) swap(a, b);
            int pa = Fi(a), pb = Fi(b);
            if(ar[pa] == ar[pb]) {
                fa[pa] = pb;
            }else {
                edge.eb(mk(a, b));
            }
        }
        for(int i = 1; i <= n; ++i) {
            if(vis[Fi(i)] == 0) {
                vis[Fi(i)] = ++ inde;
                br[inde] = ar[Fi(i)];
            }
        }
        n = inde;
        for(pii &x: edge) {
            x = mk(vis[Fi(x.fi)], vis[Fi(x.se)]);
        }
        for(int i = 1; i <= n; ++i) {
            ar[i] = br[i];
            fa[i] = i;
            // debug(i, ar[i])
            cw[i] = mk(ar[i], i);
        }
        sort(cw + 1, cw + n + 1);
        reverse(cw + 1, cw + n + 1);
        ans = 0;
        for(pii x: edge) {
            // debug(x.fi, x.se)
            if(ar[x.se] > ar[x.fi]) swap(x.fi, x.se);
            mp[x.fi].eb(x.se);
            if(ar[x.fi] >= ar[x.se]) mp[x.se].eb(x.fi);
        }
        for(int ti = 2; ti <= n; ++ ti) {
            int i = cw[ti].se;
            for(int x: mp[i]) {
                if(ar[x] < ar[i]) continue;
                int pa = Fi(i), pb = Fi(x);
                if(pa == pb) continue;
                fa[pb] = pa;
                las[pb] = pa;
            }
        }
        for(int i = 1; i <= n; ++i) ans += ar[i] - ar[las[i]];
        printf("%lld\n", ans);
    }
    return 0;
}