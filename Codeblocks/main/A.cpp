#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
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
const int MXN = 4e5 + 5;
const int MXE = 1e6 + 5;
int n, m;
int flag, all_one, pre_one;
int64 ar[MXN], fir[MXN], fir2[MXN];
int suf_one[MXN];
void word() {
    n = read();
    all_one = flag = 1;
    pre_one = ar[n + 1] = suf_one[n + 1] = 0;
    rep(i, 1, n + 1) {
        ar[i] = read();
        if(ar[i] != 1) all_one = -1;
        if(all_one == 1) pre_one = i;
    }
    flag = (pre_one % 2 == 0);
    per(i, n, 1) {
        if(ar[i] == 0) suf_one[i] = suf_one[i + 1] + 1;
        else suf_one[i] = 0;
    }
    int64 tmp1 = 0;
    rep(i, 1, pre_one + 1) {
        if(i % 2 == 1) ++ tmp1;
        fir[i] = tmp1;
        fir2[i] = tmp1;
    }
    rep(i, pre_one + 1, n + 1) {
        if(flag) {
            if(ar[i + 1] == 1) {
                int j = i + suf_one[i + 1], ji = 0, sub = 0;
                if(suf_one[i + 1] % 2 == 1) ji = 1;
                if(j == n && suf_one[i + 1] % 2 == 0) ji = 1;
                if(ar[i] % 2 != ji) sub = 1;
                ji = 1;
                rep(k, i, j + 1) {
                    if(ji == 1) tmp1 = (tmp1 + ar[i] - sub) % mod;
                    if((ar[i] - sub) % 2 == 1) ji ^= 1;
                    sub = 0;
                    fir[k] = tmp1;
                }
            }else {
                int sub = 0;
                if(ar[i] % 2 == 1) sub = 1;
                if(i == n && ar[i] % 2 == 0) sub = 1;
                tmp1 = (tmp1 + ar[i] - sub) % mod;
                fir[i] = tmp1;
            }
        }else {
            if(ar[i + 1] == 1) {
                int j = i + suf_one[i + 1], ji = 0, sub = 0;
                if(suf_one[i + 1] % 2 == 1) ji = 1;
                if(j == n && suf_one[i + 1] % 2 == 0) ji = 1;
                if(ar[i] % 2 != ji) sub = 1;
                ji = 1;
                rep(k, i, j + 1) {
                    if(ji == 0) tmp1 = (tmp1 + ar[i] - sub) % mod;
                    if((ar[i] - sub) % 2 == 1) ji ^= 1;
                    sub = 0;
                    fir[k] = tmp1;
                }
            }
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("/home/cwolf9/CLionProjects/mtxt/in.txt", "r", stdin);
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
#endif
    int tim = read();
    while(tim --) {
        word();
        m = read();
        while(m --) {
            int64 R = read(), ans = 0;
            if(all_one == 1) {
                if(n % 2 == 0) {
                    ans = (R / n) % mod * (n / 2) % mod;
                    if((R / n) % 2 == 1) ans += (R % n) / 2;
                    else ans += (R % n + 1) / 2;
                }else {
                    ans = (R / n) % mod * (n / 2 + 1) % mod;
                    ans += (R % n + 1) / 2;
                }
                ans %= mod;
            }else if(flag || R <= n) {
                
            }else {
                ans = R / n + (R % n != 0);
                if(R % n == 1) -- ans;
            }
            printf("%lld\n", (ans + mod) % mod);
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
/* 


 */