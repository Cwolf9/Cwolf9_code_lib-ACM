#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
bool Finish_read;
inline long long read(){long long x = 0;Finish_read=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return x;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;return x;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
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
typedef pair<int, int> pii;
#define fi first
#define se second
/*================Header Template==============*/
constexpr int INF = 0x3f3f3f3f;
const int MXN = 2e4 + 7;
const int MXE = 4e4 + 7;
int n, m;
int tn;
struct lp{
    int v, nex;
    int w;
}cw[MXE];
int tot, head[MXN], dep[MXN], siz[MXN], hvy, hvysiz, vis[MXN];
int stak[MXN];
LL ans;
void add_edge(int a, int b, int c) {
    cw[++ tot].v = b, cw[tot].nex = head[a], cw[tot].w = c;
    head[a] = tot;
    cw[++ tot].v = a, cw[tot].nex = head[b], cw[tot].w = c;
    head[b] = tot;
}
void dfs_pre(int u, int ba) {
    int mm = 0;
    siz[u] = 1;
    for(int i = head[u], v; ~i; i = cw[i].nex) {
        v = cw[i].v;
        if(v == ba || vis[v]) continue;
        dfs_pre(v, u);
        siz[u] += siz[v];
        mm = big(mm, siz[v]);
    }
    mm = big(mm, tn - siz[u]);
    if(hvy == -1 || (mm < hvysiz)) {
        hvy = u;
        hvysiz = mm;
    }
}
void get_dep(int u, int ba) {
    stak[++ stak[0]] = dep[u];
    for(int i = head[u], v; ~i; i = cw[i].nex) {
        v = cw[i].v;
        if(v == ba || vis[v]) continue;
        dep[v] = dep[u] + cw[i].w;
        get_dep(v, u);
    }
}
void get_ans(int u, int w, int flag) {
    stak[0] = 0;
    dep[u] = w;
    get_dep(u, u);
    sort(stak + 1, stak + 1 + stak[0]);
    for(int i = 1, j = stak[0]; i <= stak[0]; ++i) {
        while(j > i && stak[i] + stak[j] > m) -- j;
        ans += flag * big(0, j - i);
    }
//    printf("%d :\n", u);
//    for(int i = 1; i <= stak[0]; ++i) printf("%d ", stak[i]);
//    printf("\n");
}
void dfs_dian(int u, int ba) {
    vis[u] = 1;
    get_ans(u, 0, 1);
//    printf("%d %lld\n", u, ans);
    for(int i = head[u], v; ~i; i = cw[i].nex) {
        v = cw[i].v;
        if(v == ba || vis[v]) continue;
        get_ans(v, cw[i].w, -1);
        tn = siz[v];
        hvy = hvysiz = -1;
        dfs_pre(v, u);
        dfs_dian(hvy ,0);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    while(~scanf("%d%d", &n, &m) && (n + m)) {
        for(int i = 1; i <= n; ++i) head[i] = -1, vis[i] = 0;
        tot = -1;
        for(int i = 1, a, b, c; i < n; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, c);
        }
        ans = 0;
        tn = n;
        hvy = hvysiz = -1;
        dfs_pre(1, 0);
        dfs_dian(hvy, 0);
        printf("%lld\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}