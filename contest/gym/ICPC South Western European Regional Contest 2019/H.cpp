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
const int MXN = 1e3 + 5;
const int MXE = 2e6 + 7;
const int INF = 0x3f3f3f3f;
int n, m, k;
int B, T;
vector<pii> mp[MXN];
int dis[MXN][MXN], dp[MXN][MXN];
int vis[MXN][MXN], C[MXN];
pii pos[MXN];
struct lh {
    int u;
    int v;
    int w;
    lh() {}
    lh(int a, int b, int c) { u = a, v = b, w = c; }
    bool operator<(const lh &a) const { return w > a.w; }
} A;
void dij() {
    priority_queue<lh> Q;
    for(int i = 0; i <= n + 1; ++i) {
        for(int j = 0; j <= B; ++j) dp[i][j] = INF;
    }
    A.u = 0;
    A.v = 0;
    A.w = 0;
    Q.push(A);
    dp[0][0] = 0;
    while (!Q.empty()) {
        lh BB = Q.top();
        Q.pop();
        int u = BB.u;
        int ulen = BB.v;
        // debug(u, BB.v)
        // if (vis[u][ulen]) continue;
        // vis[u][ulen] = 1;
        for (pii V: mp[u]) {
            int v = V.fi, w = C[V.se];
            int vlen = ulen + dis[u][v];
            // debug(u, v, dis[u][v])
            if (vlen <= B && dp[v][vlen] > dp[u][ulen] + w * dis[u][v]) {
                dp[v][vlen] = dp[u][ulen] + w * dis[u][v];
                A.u = v;
                A.v = vlen;
                A.w = dp[v][vlen];
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
    pos[0].fi = read();
    pos[0].se = read();
    pos[1].fi = read();
    pos[1].se = read();
    B = read();
    C[0] = read();
    T = read();
    for(int i = 1; i <= T; ++i) C[i] = read();
    n = read();
    pos[n+1] = pos[1];
    for (int i = 1, a, b, c; i <= n; ++i) {
        a = read(), b = read(), c = read();
        pos[i].fi = a;
        pos[i].se = b;
        while(c --) {
            int x = read() + 1, y = read();
            mp[i].eb(mk(x, y));
            mp[x].eb(mk(i, y));
        }
        mp[0].eb(mk(i, 0));
        mp[i].eb(mk(n+1, 0));
    }
    mp[0].eb(mk(n+1, 0));
    for (int i = 0; i <= n + 1; ++i) {
        for(int j = 0; j <= n + 1; ++j) {
            dis[i][j] = (int)ceil(sqrt((pos[i].fi-pos[j].fi)*(pos[i].fi-pos[j].fi)+(pos[i].se-pos[j].se)*(pos[i].se-pos[j].se)));
        }
    }
    dij();
    int ans = INF;
    for(int i = 0; i <= B; ++i) ans = min(ans, dp[n+1][i]);
    if(ans == INF) ans = -1;
    printf("%d\n", ans);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}