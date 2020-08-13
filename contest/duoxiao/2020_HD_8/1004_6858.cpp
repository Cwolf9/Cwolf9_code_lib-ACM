/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6858)
**题意**
$n,m,q(3e5)$，$q$次询问区间$[L,R]$的边能否构成一个简单环。
**思路**
$LCT$
**备注**

*/
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
const int MXN = 3e5 + 5;
const int PN = 40;
int n, m, q;
bool vis[MXN];
int id[MXN], TIM[MXN], alltim, vist[MXN];
// int mx[MXN];
vector<pii> mp[MXN], vs;
int mmin[MXN][22];
void RMQ(int n){
    for(int i = 1; i <= n; ++i) mmin[i][0] = vs[i-1].se;
    for(int j=1;j<20;++j){
        for(int i=1;i<=n;++i){
            if(i+(1<<j)-1<=n){
                mmin[i][j]=min(mmin[i][j-1],mmin[i+(1<<(j-1))][j-1]);
            }
        }
    }
}
int zhi(int a,int b){
  int k=(int)(log(b-a+1.0)/log(2.0));
  return min(mmin[a][k],mmin[b-(1<<k)+1][k]);
}
int stm;
void dfs(int u, int ba) {
    ++ TIM[u];
    if(TIM[u] == stm && alltim <= PN && vist[u] == 0) {
        vist[u] = 1;
        ++ alltim;
    }
    if(vist[u] == 0 && TIM[u] >= stm) return;
    vis[u] = true;
    for(pii e: mp[u]) {
        if(e.se == id[ba]) continue;
        if(vis[e.fi] == 0 && e.se > id[ba]) {
            id[u] = e.se;
            dfs(e.fi, u);
            vis[e.fi] = 0;
        }else if(vis[e.fi] && id[e.fi] < e.se) {
            vs.eb(mk(id[e.fi], e.se));
        }
    }
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        alltim = 0;
        n = read(), m = read(), q = read();
        stm = sqrt(3e5);
        for(int i = 1; i <= n; ++i) {
            TIM[i] = id[i] = vis[i] = 0;
            vist[i] = 0;
            mp[i].clear();
        }
        for(int i = 1, a, b; i <= m; ++i) {
            a = read(), b = read();
            mp[a].eb(mk(b, i));
            mp[b].eb(mk(a, i));
        }
        vs.clear();
        for(int i = 1; i <= n; ++i) {
            if(!vis[i]) {
                dfs(i, 0);
            }
        }
        sort(all(vs));
        // int ti = 1;
        // for(pii x: vs) {
        //     debug(x.fi, x.se)
        //     // mx[ti] = max(mx[ti-1], x.se);
        //     // ++ ti;
        // }
        RMQ(SZ(vs));
        int las = 0;
        for(int qq = 1, l, r; qq <= q; ++qq) {
            l = read(), r = read();
            if(SZ(vs) == 0) {
                printf("No\n");
                continue;
            }
            l = (l^las)%m+1;
            r = (r^las)%m+1;
            if(l > r) swap(l, r);
            pii x = mk(l, 0);
            int p = lower_bound(all(vs), x) - vs.begin();
            x = mk(r, INF);
            int q = lower_bound(all(vs), x) - vs.begin() - 1;
            if(p + 1 > q) {
                printf("No\n");
                las = 0;
            }else {
                int ans = zhi(p + 1, q);
                // debug(p + 1, q, ans, r)
                if(ans <= r) {
                    printf("Yes\n");
                    las = 1;
                }else {
                    printf("No\n");
                    las = 0;
                }
            }
        }
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}