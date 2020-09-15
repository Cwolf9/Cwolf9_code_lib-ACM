// #define LH_LOCAL
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
// mt19937 rng(time(NULL));
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
const int MXN = 2e5 + 5;
int n, m;
int ar[MXN];
int64 sum[MXN];
const int MAXN = 1e6 + 6;
int64 fac[MAXN], facInv[MAXN], inv[MAXN];
void init(int mod) {
    inv[1] = fac[0] = facInv[0] = 1;
    for(int i = 1; i <  MAXN; ++i) {
        if(i != 1) inv[i] = (mod - mod / i)*inv[mod % i] % mod;
        fac[i] = fac[i-1] * i % mod;
        facInv[i] = facInv[i-1] * inv[i] % mod;
    }
}
int64 COMB(int n, int m) {
    if(m > n) return 0;
    if(m == n) return 1;
    return fac[n] * facInv[m] % mod * facInv[n - m] % mod;
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init(mod);
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) ar[i] = read();
    sort(ar + 1, ar + n + 1);
    for(int i = 1; i <= n; ++i) sum[i] = (sum[i - 1] + ar[i] ) % mod;
    while(m --) {
        int a = read(), b = read();
        int cnt = lower_bound(ar + 1, ar + 1 + n, b) - ar;
        int64 tmp = (sum[n] - sum[cnt - 1] + mod)%mod;
        int64 tmp2 = sum[cnt - 1];
        // debug(cnt)
        cnt = n - cnt + 1;
        if(cnt < a) {
            print(0);
        }else {
            int64 ans = tmp * (cnt - a) % mod * inv[cnt] + tmp2 * (cnt - a + 1) % mod * inv[cnt + 1] % mod;
            print(ans % mod);
        }
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}