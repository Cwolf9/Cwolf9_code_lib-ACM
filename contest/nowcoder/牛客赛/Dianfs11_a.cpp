#include <bits/stdc++.h>
#define SZ(x) ((int)x.size())
using namespace std;
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

struct Point {
    int x;
    int y;
};
class Solution {
public:
    /**
     * 路径积
     * @param n int整型 
     * @param m int整型 
     * @param a int整型vector 
     * @param u int整型vector 
     * @param v int整型vector 
     * @param x int整型vector 
     * @param y int整型vector 
     * @return int整型vector
     */
    static const int mod = 1e9 + 7;
    static const int MXN = 1e5 + 5;
    static const int MXE = 2e5 + 5;
    static const int INF = 0x3f3f3f3f;
    static const int BZ_SZ = 20;
    int up[MXN][BZ_SZ], dep[MXN];
    long long dis[MXN][BZ_SZ];
    int head[MXN], tot;
    struct lp{
        int v, nex;
    }cw[MXE];
    void dfs(int u,int ba, int d) {
        up[u][0] = ba;
        dep[u] = d;
        for(int i = 1, cf; i < BZ_SZ; ++i) {
            cf = up[u][i-1];
            up[u][i] = up[cf][i-1];
            dis[u][i] = dis[u][i-1] * dis[cf][i-1] % mod;
        }
        for(int i = head[u]; ~i; i = cw[i].nex) {
            int v = cw[i].v;
            if(v == ba) continue;
            up[v][0] = u;
            dfs(v, u, d + 1);
        }
    }
    void add_edge(int u,int v) {
        cw[++tot].v = v; cw[tot].nex = head[u];
        head[u] = tot;
        cw[++tot].v = u; cw[tot].nex = head[v];
        head[v] = tot;
    }
    int LCA(int x,int y) {
        long long ans = 1;
        if(dep[x] < dep[y]) swap(x, y);
        // debug(dep[x], dep[y])
        for(int i = BZ_SZ - 1; i >= 0; --i) {
            if(dep[up[x][i]] >= dep[y]) {
                ans = ans * dis[x][i] % mod;
                x = up[x][i];
            }
        }
        // debug(x, y, ans)
        if(x != y) {
            for(int i = BZ_SZ - 1; i >= 0; --i) {
                if(up[x][i] != up[y][i]) {
                    ans = ans * dis[x][i] % mod;
                    ans = ans * dis[y][i] % mod;
                    x = up[x][i]; y = up[y][i];
                    // debug(i)
                }
            }
            assert(x != y);
            ans = ans * dis[up[x][0]][0] % mod;
            ans = ans * dis[x][0] % mod * dis[y][0] % mod;
        }else ans = ans * dis[x][0] % mod;
        return (int)ans;
    }
    vector<int> solve(int n, int m, vector<int>& a, vector<int>& u, vector<int>& v, vector<int>& x, vector<int>& y) {
        // write code here
        tot = -1;
        vector<int> ans;
        memset(head, -1, sizeof(int)*(n+1));
        for(int i = 0; i < n - 1; ++i) {
            add_edge(u[i], v[i]);
        }
        for(int i = 0; i < BZ_SZ; ++i) dis[0][i] = 1;
        for(int i = 1; i <= n; ++i) dis[i][0] = a[i - 1];
        dfs(1, 0, 1);
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j < 4; ++j) {
                // debug(i, j, dis[i][j])
            }
        }
        for(int i = 0; i < m; ++i) {
            // debug(x[i], y[i])
            ans.emplace_back(LCA(x[i], y[i]));
        }
        return ans;
    }
};
Solution ss;
int main() {
#ifndef ONLINE_JUDGE
    // freopen("D:in.in", "r", stdin);
    // freopen("D:out.out", "w", stdout);
#endif
    // imnt();
    cout << 1 << endl;
    vector<int> ar = vector<int>{1,2,3,4,5,6};
    vector<int> ar2 = vector<int>{1,2,2,4,4};
    vector<int> ar3 = vector<int>{2,3,4,5,6};
    vector<int> ar4 = vector<int>{3,6,2,2,2};
    vector<int> ar5 = vector<int>{5,5,2,4,5};
    vector<vector<int> > br = vector<vector<int> >{{1,2,3},{1,2,3}};
    vector<Point> par = vector<Point>{{1, 2},{2, 3}};
    vector<int> ans = ss.solve(SZ(ar), SZ(ar4), ar, ar2, ar3, ar4, ar5);
    for(int x: ans) {
        debug(x)
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}
