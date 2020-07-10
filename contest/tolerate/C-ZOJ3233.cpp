/*
链接：
https://vjudge.net/contest/381323#problem/C
题意：
n=15, m=500, L<=R=1e18, 问有多少个数字至少有一个因子在n个数字里面，且没有任何一个因子
在m个数字里面

思路：
A=至少有一个因子在n个数字里面的数字的个数
B=是m个数的lcm的倍数且至少有一个因子在n个数字里面的数字的个数
答案 A - B

备注：
如果把条件 m个数字全都不能有 改成 至少有一个没有呢？

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
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
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
void debug_out(const T &f, const R &... r) {cout << f << " ";debug_out(r...);}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#define LLDO
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
const int mod = 55566677;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e2 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
vector<int> ar, br;
int64 dp[MXN], f[MXN];
int64 lo, hi, ret;
int64 ans, ans2;
int64 lcm(int64 a, int64 b) {
    b = b / __gcd(a, b);
    if(hi / b + 1 < a) return hi + 1;
    return a * b;
}
void dfs(int cur, int64 cnt, int num) {
    if(cur == n) {
        // debug(num, cnt, hi/cnt - (lo - 1) / cnt)
        if(num % 2 == 0 && num) {
            ans -= hi / cnt - (lo - 1) / cnt;
            cnt = lcm(cnt, ret);
            ans2 += hi / cnt - (lo - 1) / cnt;
        }else if(num) {
            ans += hi / cnt - (lo - 1) / cnt;
            cnt = lcm(cnt, ret);
            ans2 -= hi / cnt - (lo - 1) / cnt;
        }
        return ;
    }
    dfs(cur + 1, cnt, num);
    dfs(cur + 1, lcm(cnt, (int64)ar[cur]), num + 1);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    while(~scanf("%d%d%lld%lld", &n, &m, &lo, &hi) && n) {
        ar.clear(), br.clear();
        for(int i = 0, x; i < n; ++i) x = read(), ar.eb(x);
        my_unique(ar);
        for(int i = 0, x; i < m; ++i) x = read(), br.eb(x);
        my_unique(br);
        n = ar.size();
        m = br.size();
        ret = 1;
        for(int i = 0; i < m; ++i) ret = lcm(ret, (int64)br[i]);
        dfs(0, 1, 0);
        print(ans + ans2);
        ans = ans2 = 0;
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}

/*

*/
