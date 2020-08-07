/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6827)
**题意**
$n(2e5)$的序列，求每个区间平均值的期望。
**思路**
算每个数字的期望加起来即可。
**备注**
*/
#define LH_LOCAL
#define LLDO
#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for (register int i = s; i < t; ++i)
#define per(i, s, t) for (register int i = s; i >= t; --i)
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {
        putchar('0');
        if (f) putchar('\n');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[23];
    int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {
    return a1 > a2 ? a1 : a2;
}
template <class T>
T sml(const T &a1, const T &a2) {
    return a1 < a2 ? a1 : a2;
}
template <typename T, typename... R>
T big(const T &f, const R &... r) {
    return big(f, big(r...));
}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {
    return sml(f, sml(r...));
}
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
void print(const T &f) {
    printf(ptout, f);
    putchar('\n');
}
template <typename T, typename... R>
void print(const T &f, const R &... r) {
    printf(ptout, f);
    putchar(' ');
    print(r...);
}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;  // 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n;
int ar[MXN], f[MXN], inv[MXN], pre[MXN];
int ksm(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = (int64)a * a % MOD) 
        if (b & 1) res = (int64)res * a % MOD;
    return res;
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    inv[1] = pre[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        inv[i] = (int64)(mod - mod / i)*inv[mod % i] % mod;
        pre[i] = (pre[i-1] + inv[i]) % mod;
    }
    int tim = read();
    while (tim--) {
        n = read();
        for(int i = 1; i <= n; ++i) {
            f[i] = (f[i-1] + (int64)inv[n-i+1] * i % mod) % mod;
        }
        int64 ans = 0;
        for(int i = 1, x; i <= n; ++i) {
            x = read();
            int a = min(i, n - i + 1);
            if(n % 2 == 1 && a + a == n + 1) {
                ans = (ans + (int64)x * (a + f[a-1]) % mod)%mod;
            }else {
                ans = (ans + (int64)x * (a + f[a] + (int64)a*(pre[n-a]-pre[a])%mod)%mod)%mod;
            }
            if(ans < 0) ans += mod;
        }
        ans = ans * ksm(((int64)n*(n+1)/2)%mod, mod-2)%mod;
        printf("%lld\n", (ans+mod)%mod);
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}