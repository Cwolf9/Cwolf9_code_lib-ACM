#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 30
#define mk make_pair
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
inline LL read() {
    LL x = 0;int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(LL x, bool f) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');else putchar(' ');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');else putchar(' ');
}
int lowbit(int x) { return x & (-x); }
template<class T>T big(const T &a1, const T &a2) { return a1 > a2 ? a1 : a2; }
template<typename T, typename ...R>T big(const T &f, const R &...r) { return big(f, big(r...)); }
template<class T>T sml(const T &a1, const T &a2) { return a1 < a2 ? a1 : a2; }
template<typename T, typename ...R>T sml(const T &f, const R &...r) { return sml(f, sml(r...)); }
void debug_out() { cerr << '\n'; }
template<typename T, typename ...R>void debug_out(const T &f, const R &...r) {cerr << f << " ";debug_out(r...);}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);


const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 998244353;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 5e5 + 7;
const int MXE = 1e5 + 7;
int n, m;
int ans[MXN], sz[MXN], son[MXN], inde, fid[MXN], lid[MXN], rid[MXN], dep[MXN], sta[MXN];
vector<pii > mp[MXN];
void dfs_sz(int u, int ba) {
    sz[u] = 1;
    son[u] = 0;
    fid[u] = ++ inde;
    rid[inde] = u;
    for(auto V: mp[u]) {
        if(V.fi == ba) continue;
        sta[V.fi] = (sta[u] ^ (1 << V.se));
        dep[V.fi] = dep[u] + 1;
        dfs_sz(V.fi, u);
        sz[u] += sz[V.fi];
        if(sz[V.fi] > sz[son[u]]) son[u] = V.fi;
    }
    lid[u] = inde;
}
int color[1<<(22)+1], cur;//color[i]是状态为i的链的最深深度
void dfs(int u, int ba, int cl) {
    for(auto V: mp[u]) {
        if(V.fi == ba || V.fi == son[u]) continue;
        dfs(V.fi, u, 1);
        ans[u] = big(ans[u], ans[V.fi]);
    }
    if(son[u]) dfs(son[u], u, 0), ans[u] = big(ans[u], ans[son[u]]);
    for(auto V: mp[u]) {
        if(V.fi == ba || V.fi == son[u]) continue;
        for(int i = fid[V.fi]; i <= lid[V.fi]; ++i) {//用其他儿子子树更新答案
            cur = big(cur, dep[rid[i]] + color[sta[rid[i]]] - 2 * dep[u]);
            for(int j = 0; j < 22; ++j) cur = big(cur, dep[rid[i]] + color[sta[rid[i]]^(1<<j)] - 2 * dep[u]);
        }
        for(int i = fid[V.fi]; i <= lid[V.fi]; ++i) color[sta[rid[i]]] = big(color[sta[rid[i]]], dep[rid[i]]);
    }
    cur = big(cur, color[sta[u]] - dep[u]);
    for(int i = 0; i < 22; ++i) cur = big(cur, color[sta[u]^(1<<i)] - dep[u]);
    ans[u] = big(ans[u], cur);
    color[sta[u]] = big(color[sta[u]], dep[u]);
    if(cl) for(int i = fid[u]; i <= lid[u]; ++i) color[sta[rid[i]]] = - INF, cur = 0;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    int tim = 1;
    while(tim --) {
        n = read();
        for(int i = 1; i <= n; ++i) mp[i].clear();
        char b[2];
        for(int i = 2, a; i <= n; ++i) {
            a = read(); scanf("%s", b);
            mp[a].eb(mk(i, b[0] - 'a'));
        }
        fill(begin(color), end(color), - INF);
        dfs_sz(1, 0);
        dfs(1, 0, 0);
        for(int i = 1; i <= n; ++i) printf("%d ", ans[i]); printf("\n");
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
