/*
**链接**
https://ac.nowcoder.com/acm/contest/5671/K
**题意**
$k-bag$是一个由若干个任意$k$的排列组成的序列，问给定的长度为$n(1e5)$的字符串是不是一个$k-bag$序列的子串
**思路**
$dp[i]$表示前$i$个序列是不是合法$k-bag$子串
找到第一个出现两次的数字$x$的出现位置$a$和$b$，初始化$dp[1-(b-1)] = 1$
然后从$b$位置开始跑双指针，双指针大小为$k$的时候，进行依次状态转移, $dp[i] = dp[i-k]$

**备注**
 
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
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
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 5e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN], is[MXN];
unordered_map<int, int> ump;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read(), k = read();
        for(int i = 1; i <= n; ++i) ar[i] = read();
        ump.clear();
        for(int i = 0; i <= n; ++i) is[i] = 0;
        is[0] = 1;
        int f = 0, cnt = 0, L = 1, flag = 1;
        for(int i = 1; i <= n; ++i) {
            if(ar[i] > k || ar[i] < 1) flag = 0;
            if(ump[ar[i]] == 1) {
                if(f == 0) for(int j = 0; j < i; ++j) is[j] = 1;
                // else if(cnt == k) is[i] = is[i - k];
                // if(cnt == k && ar[1] == ar[i]) is[i] = is[i-k];
                while(L < i && ar[L] != ar[i]) {
                    ump[ar[L]] = 0;
                    ++ L;
                    -- cnt;
                }
                ++ L;
                f = 1;
            }else ++ cnt, ump[ar[i]] = 1;
            if(cnt == k) is[i] = is[i-k];
        }
        ump.clear();
        for(int i = n; i >= 1; --i) {
            if(ump[ar[i]] == 1) {
                f = is[i];
                for(int j = i + 1; j <= n; ++j) {
                    f |= is[j];
                    if(ar[j] == ar[i]) break;
                }
                if(f == 0) flag = 0;
                break;
            }
            ump[ar[i]] = 1;
        }
        printf("%s\n", flag?"YES":"NO");
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}