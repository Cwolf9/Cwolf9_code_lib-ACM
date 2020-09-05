/*
**链接**
传送门: [here](https://codeforces.com/contest/383/problem/E)
**题意**
$n(1e4)$
每个字符串包含3个字母，合法字符串包含至少一个元音。
每个字母都有可能是元音，共有$2^{24}$种可能，求出每种元音集合下合法字符串个数的平方的异或和。
**思路**
SOSdp
$A[x]$表示元音集合为$x$时，合法字符串二进制形式为$x$的个数。
因为合法字符串只需要包含一个元音即可，又一个字符串最多包含三个不同字母，所以
一个字符串能产生的贡献只有 001，010，011，100，101，110，111。
容斥去除重复的贡献，加上奇数个1的状态，减去偶数个1的状态，然后SOSdp即可。
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
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
constexpr int lowbit(int x) { return x & (-x); }
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
const int mod = 1e9 + 7;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = (1<<24) + 5;
const int MXE = 2e6 + 6;
int n, m;
int ans, LN;
int ar[MXN], F[MXN];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    char s[4];
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s);
        int tmp = 0;
        for(int j = 0; j < 3; ++j) {
            tmp |= (1<<(s[j] - 'a'));
        }
        for(int t = tmp; t; t = (t - 1) & tmp) {
            if(__builtin_popcount(t) % 2 == 1) {
                ++ F[t];
            }else {
                -- F[t];
            }
        }
    }
    LN = 1 << 24;
    for(int i = 0; i < 24; ++i) {
        for(int x = 0; x < LN; ++x) {
            if(x & (1 << i)) {
                F[x] += F[x^(1<<i)];
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < LN; ++i) {
        ans ^= F[i] * F[i];
    }
    printf("%d\n", ans);
    // n = read(), m = read();
    // while(m --) {
    //     for(int i = 1; i <= n; ++i) {
    //         ar[i] = read();
    //     }
    // }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    system("pause");
#endif
    return 0;
}
