/*
**链接**
传送门: [here](https://nanti.jisuanke.com/t/A1670)
**题意**
$N,K 1e5$
无向图，n个节点，2n-3条边。n-1条边从1->i .(2<=i<=n)。n-2条边从i->i+1.(2<=i<=n-1)
 k次询问，问将每条边长度增加d后，从1到n的最短路径。
**思路**
[2018宁夏acm网络赛-G-Trouble of Tyrant](https://blog.csdn.net/qq_39599067/article/details/80671353)
类似题：[BZOJ1010](https://blog.csdn.net/qq_39599067/article/details/80668515)
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
const int MXN = 2e6 + 5;
const int MXE = 2e6 + 6;

int n, m;
int64 dp[MXN], ar[MXN], sum[MXN], id[MXN], qry[MXN], ans[MXN];
int Q[MXN], hd, tl;
void read_data() {
    n = read(), m = read();
    for(int i = n - 1; i >= 1; --i) ar[i] = read();
    for(int i = n - 1; i >= 2; --i) sum[i] = read();
    for(int i = 2; i < n; ++i) sum[i] += sum[i - 1];
    for(int i = 1; i < n; ++i) ar[i] += sum[i];
    for(int i = 1; i <= m; ++i) {
        id[i] = i;
        qry[i] = read();
    }
}
int64 KX(int j, int k) {
    return ar[k] - ar[j];
}
int64 KY(int j, int k) {
    return k - j;
}
bool cmp1(const int &a, const int &b) {
    return qry[a] < qry[b];
}
bool cmp2(const int &a, const int &b) {
    return qry[a] > qry[b];
}
void gao_solve() {
    sort(id + 1, id + m + 1, cmp1);
    hd = tl = 0;
    for(int i = 1; i < n; ++i) {
        if(tl > hd && ar[i] >= ar[Q[tl - 1]]) continue;
        while(tl - hd >= 2 && KX(Q[tl-2], Q[tl-1]) * KY(Q[tl-1], i) >= KX(Q[tl-1], i) * KY(Q[tl-2], Q[tl-1])) -- tl;
        Q[tl++] = i;
    }
    for(int i = 1; i <= m; ++i) {
        while(tl - hd >= 2 && KX(Q[tl - 2], Q[tl - 1]) >= KY(Q[tl - 2], Q[tl - 1]) * (-qry[id[i]])) -- tl;
        ans[id[i]] = ar[Q[tl - 1]] + Q[tl - 1] * qry[id[i]];
    }
}
void print_ans() {
    for(int i = 1; i <= m; ++i) printf("%lld%c", ans[i], " \n"[i==m]);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        read_data();
        gao_solve();
        print_ans();
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}