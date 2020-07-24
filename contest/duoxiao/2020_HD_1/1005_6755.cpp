/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6755)
**题意**

**思路**

**备注**
https://blog.csdn.net/u014609452/article/details/53039223
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <assert.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
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
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

#define LLDO
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
const int64 mod = 1000000009;
const int64 p1 = 691504013;
const int64 p2 = 308495997;
const int64 p3 = 276601605;
const int MXN = 1e5 + 5;
int64 n, c, k;
int64 F[MXN], invF[MXN], p1r[MXN], p2r[MXN];
int64 ksm(int64 a, int64 b) {
    int64 res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void init() {
    F[0] = 1;
    for (int i = 1; i < MXN; i++) F[i] = F[i - 1] * i % mod;  //阶乘
    invF[MXN - 1] = ksm(F[MXN - 1], mod - 2);
    for (int i = MXN - 2; i >= 0; i--)
        invF[i] = invF[i + 1] * (i + 1) % mod;  //阶乘的逆元
    p1r[0] = p2r[0] = 1;
    for (int i = 1; i < MXN; ++i) {
        p1r[i] = p1r[i - 1] * p1 % mod;
        p2r[i] = p2r[i - 1] * p2 % mod;
    }
}
int64 C(int n, int m) {  //组合数
    if (n < m) return 0;
    if (n == m) return 1;
    return F[n] * invF[m] % mod * invF[n - m] % mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    init();
    // debug(p3 * ((ksm(p1, 2) - ksm(p2, 2)) % mod + mod) % mod) int tim = read();
    while (tim--) {
        n = read(), c = read(), k = read();
        int64 a = ksm(p1, c);
        int64 b = ksm(p2, c);
        for (int i = 1; i <= k; ++i) {
            p1r[i] = p1r[i - 1] * a % mod;
            p2r[i] = p2r[i - 1] * b % mod;
        }
        int64 ans = 0, tmp, t;
        for (int i = 0; i <= k; ++ i) {
            t = p1r[k - i] * p2r[i] % mod;
            tmp = t == 1 ? n % mod : t * (ksm(t, n) - 1 + mod) % mod * ksm(t - 1, mod-2) % mod;
            if (i % 2 == 0)
                ans += C(k, i) * tmp % mod, ans %= mod;
            else
                ans += mod - C(k, i) * tmp % mod, ans %= mod;
        }
        printf("%lld\n", ans * ksm(p3, k) % mod);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
