/*
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/890/J)
**题意**
$n(5000),m(2000)$
有$n$个木块，可以任意打乱顺序，每个木块宽$w_i$高$h_i$，木块不能旋转。把$n$个木块分成$m$组，求最小材料损耗。
每组木块的高度必须相同，也就是说所有高的木块要切掉一截。
**思路**
思路和BZOJ1010一模一样，[BZOJ1010](https://blog.csdn.net/qq_39599067/article/details/80668515)
按高度从小到大排序然后斜率优化DP。
$dp[i][h] = min_{j=h-1}^{i-1}(dp[j][h-1]+s[i]-s[j]-(sw[i]-sw[j])*h[j+1])$
$k$优于$j(j\lt k)$时，斜率$(j,k)$满足：$\frac{dp[k][h-1]-s[k]+sw[k]*h[k+1]-(dp[j][h-1]-s[j]+sw[j]*h[j+1])}{h[k+1]-h[j+1]}\le sw[i]$
枚举$h$然后DP即可。
斜率优化需要满足$h[i]$是单调递增且$sw[i]$是单调的。
在本题中$sw[i]$需要单调递增。
类似题：[2018宁夏acm网络赛-G-Trouble of Tyrant](https://blog.csdn.net/qq_39599067/article/details/80671353)
**备注**
*/
// #define LH_LOCAL
#define LLDO
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <set>
#include <deque>
#include <list>
#include <bitset>
#include <complex>
#include <cassert>
#include <ctime>
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
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
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
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {putchar('0');if (f) putchar('\n');return;}
    if (x < 0) { putchar('-');x = -x;}
    static char s[23];int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
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

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
constexpr int MXN = 5e3 + 5;
const int MXE = 2e6 + 6;

int n, m;
int64 dp[MXN][MXN/2], ar[MXN], s[MXN], sw[MXN];
class node {
    public:
    int64 w, h;
    bool operator<(const node&B) const {
        return h < B.h;
    }
}cw[MXN];
int Q[MXN], hd, tl;
void read_data() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) cw[i].w = read(), cw[i].h = read();
}
int64 KX(int j, int k, int id) {
    return dp[k][id] - s[k] + sw[k] * cw[k+1].h - (dp[j][id] - s[j] + sw[j] * cw[j+1].h);
}
int64 KY(int j, int k, int id) {
    return cw[k+1].h - cw[j+1].h;
}
void gao_solve() {
    sort(cw + 1, cw + n + 1);
    for(int i = 1; i <= n; ++i) {
        s[i] = s[i - 1] + cw[i].w * cw[i].h;
        sw[i] = sw[i - 1] + cw[i].w;
        dp[i][1] = s[i] - sw[i] * cw[1].h;
    }
    for(int k = 2; k <= m; ++k) {
        hd = tl = 0;
        Q[tl++] = k - 1;
        for(int i = k; i <= n; ++i) {
            while(2 <= tl - hd && KX(Q[hd], Q[hd+1], k - 1) <= (__int128)KY(Q[hd], Q[hd+1], k - 1) * sw[i]) ++ hd;
            assert(hd < tl);
            dp[i][k] = dp[Q[hd]][k-1] + s[i] - s[Q[hd]] - (sw[i] - sw[Q[hd]]) * cw[Q[hd]+1].h;
            while(2 <= tl - hd && (__int128)KX(Q[tl-2], Q[tl-1], k - 1) * KY(Q[tl-1], i, k - 1) >= 
                (__int128)KY(Q[tl-2], Q[tl-1], k - 1) * KX(Q[tl-1], i, k - 1)) -- tl;
            Q[tl++] = i;
        }
    }
}
void print_ans() {
    printf("%lld\n", dp[n][m]);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "sw", stdout);
#endif
    read_data();
    gao_solve();
    print_ans();
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}