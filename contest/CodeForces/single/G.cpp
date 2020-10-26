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
const int mod = 1e6 + 3;// 998244353
const int MXN = 5e5 + 5;
const int MXE = 1e6 + 5;
int n, m;
struct my_FFT {
    const double pi = acos (-1.0);
    static const int MX = (1<<17) + 5;
    static const int MM = MX * 4;
    int len, res[MM], mx; //开大4倍
    struct cpx {
        double r, i;
        cpx (double r = 0, double i = 0) : r (r), i (i) {};
        cpx operator+ (const cpx &b) {return cpx (r + b.r, i + b.i);}
        cpx operator- (const cpx &b) {return cpx (r - b.r, i - b.i);}
        cpx operator* (const cpx &b) {return cpx (r*b.r - i*b.i,i*b.r + r * b.i);}
    } va[MM], vb[MM];
    void rader (cpx F[], int len) { //len = 2^M,reverse F[i] with  F[j] j为i二进制反转
        int j = len >> 1;
        for (int i = 1; i < len - 1; ++i) {
            if (i < j) swap (F[i], F[j]); // reverse
            int k = len >> 1;
            while (j >= k) j -= k, k >>= 1;
            if (j < k) j += k;
        }
    }
    void FFT (cpx F[], int len, int t) {
        rader (F, len);
        for (int h = 2; h <= len; h <<= 1) {
            cpx wn (cos (-t * 2 * pi / h), sin (-t * 2 * pi / h) );
            for (int j = 0; j < len; j += h) {
                cpx E (1, 0); //旋转因子
                for (int k = j; k < j + h / 2; ++k) {
                    cpx u = F[k];
                    cpx v = E * F[k + h / 2];
                    F[k] = u + v;
                    F[k + h / 2] = u - v;
                    E = E * wn;
                }
            }
        }
        if (t == -1) for (int i = 0; i < len; ++i) F[i].r /= len;//IDFT
    }
    void Conv (cpx a[], cpx b[], int len) { //求卷积
        FFT (a, len, 1); FFT (b, len, 1);
        for (int i = 0; i < len; ++i) a[i] = a[i] * b[i];
        FFT (a, len, -1);
    }
    void gao (int64 a[], int64 b[], int n, int m, int64 ans[]) {
        len = 1; mx = n + m;
        while (len <= mx) len <<= 1; //mx为卷积后最大下标
        for (int i = 0; i < len; i++) va[i].r =va[i].i = vb[i].r = vb[i].i = 0;
        for (int i = 0; i < n; i++) va[i].r = a[i];//根据题目要求改写
        for (int i = 0; i < m; i++) vb[i].r = b[i];//根据题目要求改写
        Conv (va, vb, len);
        for (int i = 0; i < len; ++i) ans[i] += (int64)(va[i].r + 0.5);
    }
}fft;
int ar[MXN], b, c, d;
int fac[MXN], inv[MXN], invF[MXN];
int g[MXN], f[MXN], h[MXN];
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    b = read();
    c = read();
    d = read();
    fac[0] = invF[0] = inv[1] = 1;
    for(int i = 1; i <= n; ++i) {
        ar[i] = read();
        fac[i] = (int64)fac[i - 1] * i % mod;
        if(i != 1) inv[i] = (mod - mod / i)*(int64)inv[mod % i] % mod;
        invF[i] = (int64)invF[i-1] * inv[i] % mod;
    }
    int tmp = 1;
    for(int i = 0; i < n; ++i) {
        g[i] = invF[n - 1 - i];
        f[i] = (int64)ar[i] * tmp % mod * fac[i] % mod;
        tmp = (int64)tmp * d % mod;
    }

#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}