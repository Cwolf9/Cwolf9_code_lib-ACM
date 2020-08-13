#define LH_LOCAL
// #define LLDO
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {return a1 > a2 ? a1 : a2;}
template <class T>
T sml(const T &a1, const T &a2) {return a1 < a2 ? a1 : a2;}
template <typename T, typename... R>
T big(const T &f, const R &... r) {return big(f, big(r...));}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {return sml(f, sml(r...));}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
#ifdef LLDO
    const char ptout[] = "%lld";
#else
    const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {printf(ptout, f);putchar('\n');}
template <typename T, typename... R>
void print(const T &f, const R &... r) {printf(ptout, f);putchar(' ');print(r...);}

const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
int n, m, k;
vector<pii> mp[MXN];
int c[10], du[MXN], pre[MXN];
int vis[MXN], cnt ,inde;
void dfs(int u, int ba) {
    pre[u] = ba;
    vis[u] = inde;
    int v = mp[u][c[du[u]] - 1].se;
    // debug(u, v, vis[v], inde)
    if(vis[v] == inde) {
        int x = u;
        ++ cnt;
        while(x != v) {
            ++ cnt;
            x = pre[x];
        }
        return;
    }else if(vis[v] == 0) dfs(v, u);
}
int ans = 0, tim = 0;
int up = 1, t;
unordered_map<int64, int> ump;
void check() {
    int64 x = 0;
    for(int i = 1; i <= k; ++i) {
        x = x * 10 + c[i];
    }
    if(ump.find(x) != ump.end()) {
        -- t;
        return;
    }
    ump[x] = 1;
    cnt = 0;
    memset(vis, 0, sizeof(int) * (n + 1));
    for(int i = 1; i <= n; ++i) if(!vis[i]) {
        inde = i;
        dfs(i, 0);
    }
    if(cnt == n) {
        ++ ans;
        // debug(x, ans)
    }
}
void cdfs(int u) {
    for(int i = 1; i <= u; ++i) {
        c[u] = i;
        if(u == k) {
            check();
        }else cdfs(u + 1);
    }
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    // int xx = 1;
    // for(int i = 2; i <= 10; ++i) {
    //     xx *= i;
    //     debug(i, xx)
    // }
    n = read(), m = read(), k = read();
    for(int i = 2; i <= k; ++i) up *= i;
    up = min(up, 5000);
    for(int i = 1, a, b, c; i <= m; ++i) {
        a = read(), b = read(), c = read();
        mp[a].eb(mk(c, b));
    }
    // debug(n)
    for(int i = 1; i <= n; ++i) {
        sort(all(mp[i]));
        du[i] = SZ(mp[i]);
        // debug(i, du[i])
    }
    if(k <= 6) {
        cdfs(1);
        printf("%d\n", ans);
        return 0;
    }
    for(t = 1; t <= up; ++t) {
        ++ tim;
        if(tim >= 1000000) break;
        for(int i = 1; i <= k; ++i) c[i] = rand()%i+1;
        check();
    }
    printf("%d\n", ans);
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}