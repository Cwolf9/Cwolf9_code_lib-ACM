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
    static const int BZ_SZ = 20;
    static const int INF = 0x3f3f3f3f;
    int up[MXN][BZ_SZ], dep[MXN], fa[MXN];
    int dis[MXN][BZ_SZ];
    int head[MXN], tot;
    struct lp{
        int v, nex;
    }cw[MXE];
    void dfs(int u,int ba, int d) {
        fa[u] = ba;
        dep[u] = d;
        for(int i = 1, cf; i < BZ_SZ; ++i) {
            cf = up[u][i-1];
            up[u][i] = up[fa[cf]][i-1];
            dis[u][i] = (long long)dis[u][i-1] * dis[fa[cf]][i-1] % mod;
        }
        for(int i = head[u]; ~i; i = cw[i].nex) {
            int v = cw[i].v;
            if(v == ba) continue;
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
        // debug(x, y)
        int ans = 1;
        if(dep[x] < dep[y]) swap(x, y);
        for(int i = BZ_SZ - 1; i >= 0; --i) {
            if(dep[fa[up[x][i]]] >= dep[y]) {
                // debug(x, i, up[x][i], dis[x][i])
                ans = (long long)ans * dis[x][i] % mod;
                x = fa[up[x][i]];
            }
        }
        if(x != y) {
            for(int i = BZ_SZ - 1; i >= 0; --i) {
                if(up[x][i] != up[y][i]) {
                    ans = (long long)ans * dis[x][i] % mod;
                    ans = (long long)ans * dis[y][i] % mod;
                    x = fa[up[x][i]]; y = fa[up[y][i]];
                }
            }
        }
        ans = (long long)ans * dis[x][0] % mod;
        return ans;
    }
    vector<int> solve(int n, int m, vector<int>& a, vector<int>& u, vector<int>& v, vector<int>& x, vector<int>& y) {
        // write code here
        tot = -1;
        vector<int> ans;
        memset(head, -1, sizeof(int)*(n+1));
        for(int i = 0; i < n - 1; ++i) {
            add_edge(u[i], v[i]);
        }
        for(int i = 1; i <= n; ++i) {
            dis[i][0] = a[i - 1];
            assert(a[i-1] <= 10000);
            up[i][0] = i;
        }
        for(int i = 0; i < BZ_SZ; ++i) up[0][i] = 0, dis[0][i] = 1;
        dfs(1, 0, 1);
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j < 4; ++j) {
                // debug(i, j, dis[i][j], up[i][j])
            }
        }
        for(int i = 0; i < m; ++i) {
            // debug(x[i], y[i])
            ans.emplace_back(LCA(x[i], y[i]));
        }
        return ans;
    }
};
