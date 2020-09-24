#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define BASE_MAX 62
#define mk make_pair
#define o2(x) (x)*(x)
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define clr(a,b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef long long int64;
typedef pair<int, int> pii;
inline LL read() {
  LL x = 0;int f = 0;char ch = getchar();
  while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
  while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
  return x = f ? -x : x;
}
inline void write(LL x) {
    if(x == 0) { putchar('0'), putchar('\n'); return;}
    if(x < 0) { putchar('-'); x = -x;}
    static char s[23];int l = 0;
    while(x != 0) s[l++] = x % 10 + 48, x /= 10;
    while(l) putchar(s[--l]);
    putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template<class T> T big(const T& a1,const T& a2) { return a1>a2?a1:a2; }
template<typename T, typename ...R> T big (const T& f,const R& ...r) { return big(f, big (r...)); }
template<class T> T sml(const T& a1,const T& a2) { return a1<a2?a1:a2; }
template<typename T, typename ...R> T sml (const T& f,const R& ...r) { return sml(f, sml (r...)); }
void debug_out() { cerr << '\n'; }
template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cerr << f << " "; debug_out (r...); }
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000007, 1000000009};
const LL BASE[] = {1572872831, 1971536491};
const int MXN = 1e5 + 7;
const int mod = 1e9 + 7;
int n, m;
int64 dp[MXN], ilg[MXN];
vector<pii > mp[MXN];
map<int, int64> ump[MXN];//保存受到影响的dp[u][j],最多只有O(mlog(m))个
bool noprime[MXN];
int pp[10004], pcnt, mu[MXN];
void init_prime() {
    noprime[0] = noprime[1] = 1;
    mu[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, mu[i]=-1;
        for(int j = 0; j < pcnt && i*pp[j] < MXN; ++j) {
            noprime[i*pp[j]] = 1;
            mu[i*pp[j]] = -mu[i];
            if(i % pp[j] == 0) {
                mu[i*pp[j]] = 0;
                break;
            }
        }
    }
}
int ksm(int a, int b, int Mod) {
    int res = 1;
    for (; b > 0; b >>= 1, a = (int64)a * a % Mod) {
        if (b & 1) res = (int64)res * a % Mod;
    }
    return res;
}
void upd(int64 &x) {
    if(x >= mod) x %= mod;
    else if(x < 0) x += mod;
}
void dfs(int u, int ba) {
    // debug(u, ba)
    int64 all = 1;//当前节点不考虑边权影响的方案数
    for(auto x: mp[u]) {
        if(x.fi == ba) continue;
        dfs(x.fi, u);
        all = all * dp[x.fi];
        upd(all);
        for(int d = 1, dv = x.se; dv <= m; dv += x.se, ++ d) {
            int64 sum = 0;//\mu(d)\sum_{k=1}^{\frac m{wd}f_{son,kwd}}, dv=wd
            for(int kwd = dv; kwd <= m; kwd += dv) {
                sum += mu[d] * (ump[x.fi].find(kwd) != ump[x.fi].end()?ump[x.fi][kwd]:ump[x.fi][0]) % mod;
                upd(sum);
            }
            for(int tj = dv; tj <= m; tj += dv) {
                ilg[tj / x.se] += sum;
                upd(ilg[tj / x.se]);
            }
        }
        int64 ny = ksm(dp[x.fi], mod - 2, mod);
        for(int j = x.se; j <= m; j += x.se) {
            if(ump[u].find(j) != ump[u].end()) {
                ump[u][j] = ump[u][j] * (dp[x.fi] - ilg[j / x.se]) % mod * ny % mod;//受到若干条边权影响后的合法方案数比例
            }else {
                ump[u][j] = (dp[x.fi] - ilg[j / x.se]) * ny % mod;
            }
        }
        for(int j = m / x.se; j >= 1; --j) ilg[j] = 0;
    }
    dp[u] = all * m % mod;//假设全部不受路径边权影响的方案数
    for(auto &p: ump[u]) {
        p.se = p.se * all % mod;//根据比例算出方案数
        dp[u] = (dp[u] + p.se - all + mod) % mod;//更新总的合法方案数
        upd(dp[u]);
    }
    ump[u][0] = all;//不受影响的单个dp[u][j]的方案数
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D://in.in", "r", stdin);
    freopen("D://out.out", "w", stdout);
#endif
    init_prime();
    n = read(), m = read();
    for(int i = 2, a, b, c; i <= n; ++i) {
        a = read(), b = read(), c = read();
        mp[a].eb(mk(b, c));
        mp[b].eb(mk(a, c));
    }
    dfs(1, -1);
    printf("%lld\n", (dp[1] + mod) % mod);
    return 0;
}
