/*
**链接**
https://ac.nowcoder.com/acm/contest/5671/H
**题意**
$0\le A\le B\le 10^{100}$，问有多少对$pair(A,B)$满足$S(A)\gt S(B)$, $S(X)$为各位数之和。
**思路**
$A,B$保持限制条件$A\le B$一起往下跑数位$dp$即可
$dp[i][j][a(2)][b(2)][c(2)]$表示当前填补到第$i$位，$S(A)$和$S(B)$差为$j$，限制条件为$a,b,c$的后面按要求填的合法方案数。
如果不把限制条件记录进状态，会得到$TLE$。
**备注**
2019牛客第七场H题类似
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <assert.h>
#include <bits/stdc++.h>

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
const int MXN = 1e2 + 3;
const int MXE = 2e6 + 6;
int n, m, k;
char s[MXN];
int ar[MXN];
int dp[MXN][2002][2][2][2];
int dfs(int pos, int curA, int curB, bool is, bool limita, bool limitb) {
    // debug(pos, curA, curB)
    assert(curA - curB + 1000 < 2002);
    if (pos == -1) {
        return curA > curB;
    }
    if (dp[pos][curA - curB + 1000][limita][limitb][is] != -1)
        return dp[pos][curA - curB + 1000][limita][limitb][is];
    int upa = limita ? ar[pos] : 9;
    int upb = limitb ? ar[pos] : 9;
    // debug(upa, upb)
    int sum = 0;
    for (int i = 0; i <= upa; ++i) {
        for (int j = 0; j <= upb; ++j) {
            if (is && i > j) continue;
            sum = (sum + dfs(pos - 1, curA + i, curB + j, is && i == j, limita && i == upa, limitb && j == upb));
            if(sum >= MOD) sum %= MOD;
        }
    }
    if (1||(!limita && !limitb && !is)) dp[pos][curA - curB + 1000][limita][limitb][is] = sum;
    return sum;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    scanf("%s", s);
    n = strlen(s);
    reverse(s, s + n);
    for (int i = 0; i < n; ++i) {
        ar[i] = s[i] - '0';
    }
    clr(dp, -1);
    printf("%d\n", dfs(n - 1, 0, 0, 1, 1, 1));
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
