
// Problem: C. Sequence Transformation
// Contest: Codeforces - Codeforces Round #686 (Div. 3)
// URL: https://codeforces.com/contest/1454/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

/*
**题意**
给你$n$个整数，$f(x)$表示最少有多少段区间不包含整数$x$，输出最小的$f(x)$的值。
**思路**
把相同的$x$用一个桶装起来，然后计算有多少不连续的即可。
单组时间复杂度：$O(n)$.
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
int n, m;
vector<int> mp[MXN];
void work() {
    n = read();
    rep(i, 0, n) { mp[i].assign(1, 0); }
    rep(i, 0, n) {
        int x = read() - 1;
        mp[x].eb(i + 1);
    }
    rep(i, 0, n) mp[i].eb(n + 1);
    int ans = n;
    rep(i, 0, n) {
        if (SZ(mp[i]) == n + 2) ans = 1;
        if (SZ(mp[i]) == 2) continue;
        int cnt = 0;
        for (int j = 1; j < SZ(mp[i]); ++j) {
            if (mp[i][j] - mp[i][j - 1] > 1) ++cnt;
        }
        ans = min(ans, cnt);
    }
    printf("%d\n", ans);
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
