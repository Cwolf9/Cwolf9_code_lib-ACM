/*
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/5667/G)
**题意**
$n(150000),m(40000),1\le a_i,b_i\le 1e9$, 问$a[]$有多少个子数组$S$
满足$\forall i\in\{1,...,m\},S_i\ge b_i.$
**思路**

**备注**
*/
#define LH_LOCAL
// #define LLDO
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
const int MXN = 4e4 + 5;
const int MXE = 1e5 + 5e4 + 6;
int n, m;
int ar[MXE], d[MXE];
int br[MXN], b[MXN];
bitset<MXE> ans, ret;
vector<int> vs;
int get(int x) {
    return upper_bound(all(vs), x) - vs.begin();
}
bool cmp(int x, int y) {
    return ar[x] > ar[y];
}
bool cmp2(int x, int y) {
    return br[x] > br[y];
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) ar[i] = read(), ans.set(i - 1), d[i] = i;
    for(int i = 1; i <= m; ++i) br[i] = read(), vs.eb(br[i]), b[i] = i;
    my_unique(vs);
    int tx = SZ(vs) - 1;
    sort(d + 1, d + n + 1, cmp);
    sort(b + 1, b + m + 1, cmp2);
    int p = 0, i = 1, j = 1;
    while(i <= n && j <= m) {
        if(ar[d[i]] >= br[b[j]]) {
            ret.set(d[i]);
            ++ i;
        }else {
            ans &= (ret >> b[j]);
            ++ j;
        }
    }
    print(ans.count());
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}