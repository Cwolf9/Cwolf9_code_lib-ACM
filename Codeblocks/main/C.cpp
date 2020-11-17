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
int flag, sum;
int64 ar[MXN], res1[MXN], res2[MXN], res3[MXN], res4[MXN];
/**
 * flag表示先手能否永远保证他的先拿资格（全1情况特判）
 * res1[i]表示我是先手我为保证最后我先拿的情况下最大和
 * res2[i]表示我是后手他为保证最后他先拿的情况下最大和
 * res3[i]表示我是先手我不为保证最后我先拿的情况下最大和
 * res4[i]表示我是后手他不为保证最后他先拿的情况下最大和
 * tmp1先手得分
 * tmp2后手得分
 */
void word() {
    n = read();
    sum = n;
    flag = 1;
    int fir = 0, st = 1;
    ar[n + 1] = 0;
    rep(i, 1, n + 1) {
        ar[i] = read();
        if(ar[i] != 1) sum = -1;
        if(fir >= 0) {
            if(ar[i] == 1) ++ fir;
            else fir = - fir - 1;
        }
    }
    fir = - fir - 1;
    // debug(fir)
    flag = (fir % 2 == 0);
    if(flag == 0) st = fir + 1;
    int64 tmp1 = 0, tmp2 = 0;
    rep(i, 1, st) {
        if(i % 2 == 1) ++ tmp1;
        else ++ tmp2;
        res1[i] = tmp1, res2[i] = tmp2;
        res3[i] = tmp1, res4[i] = tmp2;
    }
    rep(i, st, n + 1) {
        if(ar[i + 1] == 1) {//后面有一连串1做好准备
            int k = 1;
            while(i + k <= n && ar[i + k] == 1) ++ k;
            -- k;
            int fg = 0, sub = 0, fg2 = 0;
            if(i + k == n) {//跑完1会自动改变回合情况
                if(k % 2 == 0) {//先手拿奇数才能保证下一轮自己先手
                    fg = 1;
                    if(ar[i] % 2 == 0) sub = 1;
                    if(flag == 0) {
                        fg = 0;
                        if(ar[i] % 2 == 1) sub = 1;
                    }
                }else {//先手拿偶数才能保证下一轮自己先手
                    fg = 0;
                    if(ar[i] % 2 == 1) sub = 1;
                    if(flag == 0) {
                        fg = 1;
                        if(ar[i] % 2 == 0) sub = 1;
                    }
                }
            }else {
                if(k % 2 == 0) {//先手拿偶数才能保证自己先手
                    fg = 0;
                    if(ar[i] % 2 == 1) sub = 1;
                }else {//先手拿奇数才能保证自己先手
                    fg = 1;
                    if(ar[i] % 2 == 0) sub = 1;
                }
            }
            if(flag) {
                res3[i] = (tmp1 + ar[i]) % mod;
                res4[i] = res4[i - 1];
                tmp1 = (tmp1 + ar[i] - sub) % mod;
            }else {
                res3[i] = res3[i - 1];
                res4[i] = (tmp2 + ar[i]) % mod;
                tmp2 = (tmp2 + ar[i] - sub) % mod;
            }
            fg2 = ar[i] % 2;//全拿是否会改变回合
            res1[i] = tmp1, res2[i] = tmp2;
            rep(j, 1, k + 1) {
                if(flag ^ fg) ++ tmp1;
                else ++ tmp2;
                tmp1 %= mod, tmp2 %= mod;
                res1[i + j] = tmp1, res2[i + j] = tmp2;
                fg ^= 1;
                res3[i + j] = res3[i + j - 1];
                res4[i + j] = res4[i + j - 1];
                if(flag ^ fg2) ++ res3[i + j];
                else ++ res4[i + j];
                fg2 ^= 1;
            }
            i += k;
        }else {
            if(flag) {
                res3[i] = (tmp1 + ar[i]) % mod;
                res4[i] = res4[i - 1];
            }else {
                res3[i] = res3[i - 1];
                res4[i] = (tmp2 + ar[i]) % mod;
            }
            int sub = 0;
            if(i == n) {
                if(flag) {//最后一次拿奇数才能保证还能先手资格
                    if(ar[i] % 2 == 0) sub = 1;
                    tmp1 = (tmp1 + ar[i] - sub) % mod;
                }else {//最后一次拿偶数才能保证还能先拿资格
                    if(ar[i] % 2 == 1) sub = 1;
                    tmp2 = (tmp2 + ar[i] - sub) % mod;
                }
            }else {//拿偶数不改变回合
                if(ar[i] % 2 == 1) sub = 1;
                if(flag) {
                    tmp1 = (tmp1 + ar[i] - sub) % mod;
                }else {
                    tmp2 = (tmp2 + ar[i] - sub) % mod;
                }
            }
            res1[i] = tmp1, res2[i] = tmp2;
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
            if(sum == n) {
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
                if(R % n == 0) {
                    ans = (R / n - 1) % mod * res1[n] % mod;
                    ans = (ans + res3[n]) % mod;
                }else {
                    ans = (R / n) % mod * res1[n] % mod;
                    ans = (ans + res3[R % n]) % mod;
                }
            }else {
                if(R % n == 0) {
                    ans = (R / n - 1) % mod * res1[n] % mod;
                    ans = (ans + res4[n]) % mod;
                }else {
                    ans = (R / n) % mod * res1[n] % mod;
                    ans = (ans + res4[R % n]) % mod;
                }
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