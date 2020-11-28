
// Problem: F. Array Partition
// Contest: Codeforces - Codeforces Round #686 (Div. 3)
// URL: https://codeforces.com/contest/1454/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)
/*
**题意**
给你一个长度为$n$的数组，问能够将数组切两刀分成三部分，满足第一部分的最大值等于第二部分的最小值等于第三部分的最大值。
**思路**
单调栈，求出每个点左边第一个小于它的位置，和右边第一个小于它的位置。
例如第$i$个数$a_i$，左边第一个小于它的数的位置$ls[i]$和右边第一个小于它的数的位置$rs[i]$。
只需要判断前$ls[i]$个数或者前$ls[i]+1$个数的最大值是否等于$a_i$和
后$rs[i]$个数或者后$rs[i]+1$个数的最大值是否也等于$a_i$即可。
注意要保证三段区间长度至少为`1`。
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
int ar[MXN], ls[MXN], rs[MXN], pre[MXN], suf[MXN];
void work() {
    n = read();
    vector<int> vs;
    rep(i, 0, n) {
        ar[i] = read();
        if (i == 0)
            pre[i] = ar[i];
        else
            pre[i] = max(pre[i - 1], ar[i]);
        while (!vs.empty() && ar[vs.back()] >= ar[i]) vs.pop_back();
        if (vs.empty())
            ls[i] = -1;
        else
            ls[i] = vs.back();
        vs.push_back(i);
    }
    vs.clear();
    per(i, n - 1, 0) {
        if (i == n - 1)
            suf[i] = ar[i];
        else
            suf[i] = max(suf[i + 1], ar[i]);
        while (!vs.empty() && ar[vs.back()] >= ar[i]) vs.pop_back();
        if (vs.empty())
            rs[i] = n;
        else
            rs[i] = vs.back();
        vs.push_back(i);
    }
    rep(i, 1, n - 1) {
        int fir = -1, sec = -1;
        if ((ls[i] == -1 || pre[ls[i]] < ar[i]) && ls[i] + 1 != i &&
            ar[ls[i] + 1] == ar[i]) {
            fir = ls[i] + 1;
        } else if (ls[i] != -1 && pre[ls[i]] == ar[i])
            fir = ls[i];
        if ((rs[i] == n || suf[rs[i]] < ar[i]) && rs[i] - 1 != i &&
            ar[rs[i] - 1] == ar[i]) {
            sec = rs[i] - 1;
        } else if (rs[i] != n && suf[rs[i]] == ar[i])
            sec = rs[i];
        if (fir != -1 && sec != -1) {
            printf("YES\n");
            int a = fir + 1, c = n - sec, b = n - a - c;
            printf("%d %d %d\n", a, b, c);
            return;
        }
    }
    printf("NO\n");
}
int main() {
#ifdef LH_LOCAL
    // freopen("D:/ACM/mtxt/in.txt", "r", stdin);
    // freopen("D:/ACM/mtxt/out.txt", "w", stdout);
#endif
    for (int cas = 1, tim = read(); cas <= tim; ++cas) {
        // printf("Case #%d:\n", cas);
        work();
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
