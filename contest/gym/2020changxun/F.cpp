#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(int64 x, bool f = true) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');else putchar(' ');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');else putchar(' ');
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
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;// 998244353
const int MXN = 1e5 + 5;
const int MXE = 1e6 + 5;
const int maxn = 1e5+7;
int n;
int ans[MXE][19], cnt[MXE];
vector<int> vs;
int val[MXN], sz[MXN], son[MXN];
int inde, fid[MXN], lid[MXN], rid[MXN];
vector<int> mp[MXN];
int64 res;
void dfs_sz(int u, int ba) {
    sz[u] = 1;
    son[u] = 0;
    fid[u] = ++ inde;
    rid[inde] = u;
    for(int v: mp[u]) {
        if(v == ba) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
    lid[u] = inde;
}
void dfs(int u, int ba, int cl) {
    for(int v: mp[u]) {
        if(v == ba || v == son[u]) continue;
        dfs(v, u, 1);
    }
    if(son[u]) dfs(son[u], u, 0);
    for(int v: mp[u]) {
        if(v == ba || v == son[u]) continue;
        for(int i = fid[v]; i <= lid[v]; ++i) {
            int vi = rid[i];
            rep(j, 0, 18) {
                if(vi & (1 << j)) {
                    if((val[u] ^ val[vi]) < MXE) res += (int64)ans[val[u] ^ val[vi]][j] * (1LL << j);
                }else {
                    if((val[u] ^ val[vi]) < MXE) res += (int64)(cnt[val[u] ^ val[vi]] - ans[val[u] ^ val[vi]][j]) * (1LL << j);
                }
            }
        }
        for(int i = fid[v]; i <= lid[v]; ++i) {
            int vi = rid[i];
            if(cnt[val[vi]] == 0) vs.eb(val[vi]);
            ++ cnt[val[vi]];
            rep(j, 0, 18) {
                if(!(vi & (1 << j))) {
                    ++ ans[val[vi]][j];
                }
            }
        }
    }
    if(cnt[val[u]] == 0) vs.eb(val[u]);
    ++ cnt[val[u]];
    rep(j, 0, 18) {
        if(!(u & (1 << j))) {
            ++ ans[val[u]][j];
        }
    }
    if(cl) {
        for(int v: vs) {
            cnt[v] = 0;
            clr(ans[v], 0);
        }
        vs.clear();
    }
}
int main() {
    scanf("%d",&n);
    for(int i = 1; i <= n; ++i) scanf("%d", val + i);
    int a, b;
    for(int i = 1; i < n; ++i) {
        scanf("%d%d", &a, &b);
        mp[a].eb(b), mp[b].eb(a);
    }
    dfs_sz(1, 0);
    dfs(1, 0, 0);
    printf("%lld\n", res);
    return 0;
}
