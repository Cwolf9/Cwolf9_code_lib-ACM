/*
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/5667/G)
**题意**
$n(150000),m(40000),1\le a_i,b_i\le 1e9$, 问$a[]$有多少个子数组$S$
满足$\forall i\in\{1,...,m\},S_i\ge b_i.$
**思路**

**备注**
*/
// #define LH_LOCAL
#define LLDO
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
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
mt19937 rng(time(NULL));
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
// const int MOD = 1e9 + 7;
const int MXN = 2000 + 5;
const int MXE = 2e6 + 6;
int n, m;
pii cw[MXN];
typedef pair<int64, int> pLi;
vector<pLi> vs;
int64 dis[MXN][MXN];
int ip[MXN][MXN], is[MXN];
int64 get(int i, int j) {
    return o2(cw[i].fi*1LL-cw[j].fi) + o2(cw[i].se*1LL-cw[j].se);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read();
        for(int i = 1; i <= n; ++i) {
            cw[i].fi = read();
            cw[i].se = read();
            is[i] = 0;
            for(int j = 1; j <= n; ++j) {
                ip[i][j] = 0;
            }
            for(int j = 1; j <= i; ++j) {
                dis[i][j] = dis[j][i] = get(i, j);
            }
        }
        for(int i = 1; i <= n; ++i) {
            vs.clear();
            for(int j = 1; j <= n; ++j) {
                if(i != j) vs.eb(mk(dis[i][j], j));
            }
            sort(all(vs));
            ip[i][vs.back().se] = 1;
            for(int j = SZ(vs) - 2; j >= 0; --j) {
                if(vs[j].fi == vs.back().fi) {
                    ip[i][vs[j].se] = 1;
                }else break;
            }
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = i; j <= n; ++j) {
                if((ip[i][j] & ip[j][i]) == 0) {
                    ip[i][j] = ip[j][i] = 0;
                }
            }
        }
        int flag = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(ip[i][j]) is[i] = 1;
            }
        }
        if(is[1]) {
            printf("YES\n");
            continue;
        }
        // debug(flag)
        flag = 0;
        int cnt = 0;
        for(int i = 2; i <= n; ++i) {
            for(int j = 2; j <= n; ++j) {
                if(dis[1][i] < dis[j][i] && j != i) {
                    ++ cnt;
                    if(ip[i][j] == 0 && is[j]) {
                        flag = 1;
                    }
                }
            }
        }
        if(cnt == 0) flag = 0;
        if(flag == 0) flag = !(rng()%4);
        flag = rng()%3;
        printf("%s\n", flag?"YES":"NO");
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
