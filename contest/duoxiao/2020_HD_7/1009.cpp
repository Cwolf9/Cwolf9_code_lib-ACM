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
// const int MOD = 1e9 + 7;
const int MXN = (1 << 21) + 5;
const int MXE = 2e6 + 6;
int n, m;
// int q[MXN];
// int sum[MXN], ans[MXN];
int ksm(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = (int64)a * a % mod) {
        if (b & 1) res = (int64)res * a % mod;
    }
    return res;
}
vector<int> mp[MXN];
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    vector<int> ans;
    while(tim --) {
        ans.clear();
        n = read();
        int x = read(), y = read(), flag = 1;
        if(x + y > n + 1) {
            printf("NO\n");
            continue;
        }
        int l = 1, r = n, flag = 1;
        for(int i = 1; i < x; ++i) {
            if(l > r) {
                flag = 0;
                break;
            }
            mp[i].eb(l ++);
        }
        if(l > r) flag = 0;
        mp[x].eb(r--);
        for(int i = 1; i < y; ++i) {
            if(l > r) {
                flag = 0;
                break;
            }
            mp[x].eb(r--);
        }
        for(int i = x - 2; i >= 1; --i) {
            for(int j = 0; j < y; ++j) {
                mp[i].eb(r --);
            }
        }
        if(flag == 0 || SZ(ans) != n) printf("NO\n");
        else {
            printf("YES\n");
            for(int i = 0; i < n; ++i) {
                if(i == n - 1) printf("%d\n", ans[i]);
                else printf("%d ", ans[i]);
            }
        }
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}