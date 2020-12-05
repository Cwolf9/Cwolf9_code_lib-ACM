
// Problem: D. Number into Sequence
// Contest: Codeforces - Codeforces Round #686 (Div. 3)
// URL: https://codeforces.com/contest/1454/problem/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)
/*
**题意**
给你一个$n$，问最多能分成多少个数字，满足乘积等于$n$，并且$a_i % a_{i-1} == 0$。
**思路**
将$n$质因数分解之后，答案就是质因子次数的最大值。
单组时间复杂度：$O(sqrt(n))$.
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for (register int i = (s), LIM = (t); i < LIM; ++i)
#define per(i, s, t) for (register int i = (s), LIM = (t); i >= LIM; --i)
#define GKD                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
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
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f = true) {
    if (x == 0) {
        putchar('0');
        if (f)
            putchar('\n');
        else
            putchar(' ');
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
    if (f)
        putchar('\n');
    else
        putchar(' ');
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
/*================Header Template==============*/
const int mod = 998244353;  // 998244353
int ksm(int a, int64 b, int kmod = mod) {
    int res = 1;
    for (; b > 0; b >>= 1, a = (int64)a * a % kmod)
        if (b & 1) res = (int64)res * a % kmod;
    return res;
}
const int INF = 0x3f3f3f3f;
const int MXN = 2e5 + 5;

int64 n, m;

void work() {
    n = read();
    int64 tn = sqrt(n), rn = n;
    rep(i, -2, 3) if ((tn + i) * (tn + i) == n) tn = tn + i;
    int Mx = -1, who = 0;
    rep(i, 2, tn + 1) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                ++cnt;
            }
            if (cnt > Mx) {
                Mx = cnt;
                who = i;
            }
        }
        if (n < i) break;
    }
    if (Mx == -1)
        printf("1\n%lld\n", n);
    else {
        printf("%d\n", Mx);
        rep(i, 1, Mx) printf("%d ", who), rn /= who;
        printf("%lld\n", rn);
    }
}
int main() {
#ifdef LH_LOCAL
    freopen("D:/ACM/mtxt/in.txt", "r", stdin);
    // freopen("D:/ACM/mtxt/out.txt", "w", stdout);
#endif
    for (int cas = 1, tim = read(); cas <= tim; ++cas) {
        // printf("Case #%d:\n", cas);
        work();
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
