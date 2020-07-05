#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define eb push_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline LL read() {
    LL x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
int lowbit(int x) { return x & (-x); }
void debug_out() { cerr << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cerr << f << " ";
    debug_out(r...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
const int MXN = 1e5 + 5;
const int MXE = 2e6 + 7;
const int INF = 0x3f3f3f3f;
int n, m, k;
vector<pii> mp[MXN];
vector<int> son[MXN];
vector<pair<pii, int> > edge;
LL dis[2][MXN];
int vis[MXN], is[MXN];
int dfn[MXN], low[MXN], inde, st[MXN], top;
void dfs(int u, int Fa) {
    dfn[u] = low[u] = ++inde;
    vis[u] = 1;
    int v;
    st[++top] = u;
    for (int v : son[u]) {
        if (v == Fa || is[v] == 0) continue;
        if (!vis[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) is[u] = 1;
        } else if (vis[v] == 1) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        do {
            v = st[top--];
            vis[v] = 2;
        } while (v != u);
    }
}

struct lh {
    int u;
    LL w;
    lh() {}
    lh(int a, LL b) { u = a, w = b; }
    bool operator<(const lh &a) const { return w > a.w; }
} A, B;
void dij(int s, int ip) {
    priority_queue<lh> Q;
    for(int i = 1; i <= n; ++i) dis[ip][i] = 1e18;
    A.u = s;
    A.w = 0;
    Q.push(A);
    dis[ip][s] = 0;
    while (!Q.empty()) {
        B = Q.top();
        Q.pop();
        int u = B.u;
        if (vis[u]) continue;
        vis[u] = 1;
        for (pii V : mp[u]) {
            int v = V.fi, w = V.se;
            if (dis[ip][v] > dis[ip][u] + w) {
                dis[ip][v] = dis[ip][u] + w;
                A.u = v;
                A.w = dis[ip][v];
                Q.push(A);
            }
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("E://ADpan//in.in", "r", stdin);
    // freopen("E://ADpan//out.out", "w", stdout);
#endif
    // iis;
    int tim = read();
    while (tim--) {
        n = read(), m = read();
        // TODO: init
        inde = top = 0;
        for(int i = 1; i <= n; ++i) {
            mp[i].clear();
            son[i].clear();
        }
        edge.clear();
        for (int i = 1, a, b, c; i <= m; ++i) {
            a = read(), b = read(), c = read();
            mp[a].eb(mk(b, c));
            mp[b].eb(mk(a, c));
            edge.eb(mk(mk(a, b), c));
        }
        for (int i = 1; i <= n; ++i) vis[i] = 0;
        dij(1, 0);
        for (int i = 1; i <= n; ++i) vis[i] = 0;
        dij(n, 1);
        for (int i = 1; i <= n; ++i) is[i] = vis[i] = 0;
        LL tmin = dis[0][n];
        for (int i = 0, a, b, c; i < m; ++i) {
            a = edge[i].fi.fi, b = edge[i].fi.se, c = edge[i].se;
            if (dis[0][a] + dis[1][b] + c == tmin ||
                dis[0][b] + dis[1][a] + c == tmin) {
                son[a].eb(b);
                son[b].eb(a);
                // debug(a, b)
                is[a] = is[b] = 2;
            }
        }
        is[1] = is[n] = 1;
        for (int i = 1; i <= n; ++i) {
            if (is[i] && vis[i] == 0) {
                dfs(i, -1);
            }
        }
        for(int i = 1; i <= n; ++i) {
            printf("%d%c", is[i], " \n"[i==n]);
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}