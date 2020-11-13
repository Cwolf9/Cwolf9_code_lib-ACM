#pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 5;
int n, m;
int ar[MXN];
char s[MXN];
int64 ksm(int64 a, int64 b) {
    int64 res = 1;
    while(b > 0) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
const int MAXN = 3000 + 6;
LL fac[MAXN], facInv[MAXN], inv[MAXN];
LL COMB(int n, int m) {
    if(n < m) return 0; if(n == m)return 1;
    return fac[n] * facInv[m] % mod * facInv[n-m] % mod;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    inv[1] = 1;
    fac[0] = facInv[0] = 1;
    for(int i = 1; i < MAXN; ++i) {
        if(i != 1) inv[i] = (mod - mod / i)*inv[mod % i] % mod;
        fac[i] = fac[i-1] * i % mod;
        facInv[i] = facInv[i-1] * inv[i] % mod;
    }
    scanf("%s", s);
    n = strlen(s);
    m = read();
    if(m == 0) {
        printf("1\n");
        return 0;
    }
    int one = 0;
    int64 ans = 0;
    rep(i, 0, n) {
        if(s[i] == '1') {
            // debug(n - i - 1)
            rep(j, 0, n - i) {
                int64 x = COMB(n - i - 1, j);
                if(j + one) ans += ksm(m, j + one) * x % mod;
                // debug(j + one)
                ans %= mod;
            }
            ++ one;
        }
    }
    if(one) ans += ksm(m, one);
    ++ ans;
    printf("%lld\n", (ans + mod) % mod);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
