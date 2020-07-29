/*

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
int64 L, R;
int ar[MXN];
int64 dp[10][20][20][20];
int64 dfs(int pos, int curA, vector<int> vs, bool is, bool limit) {
    int ma = 0;
    for(int x: vs) ma = max(ma, x);
    // if(curA > ma) debug(pos,ma,curA,is,limit,dp[m][pos][ma][curA][limit][is])
    if (pos == -1) {
        return curA > ma;
    }
    if (!limit && !is && dp[m][pos][ma][curA] != -1)
        return dp[m][pos][ma][curA];
    int up = limit ? ar[pos] : 9;
    // debug(pos, up, curA, ma, limit, is, up)
    int64 sum = 0;
    for (int i = 0, tmp; i <= up; ++i) {
        if(is && i == 0) ;
        else if(i != m) ++ vs[i];
        if(i == 0) {
            if(is == false) tmp = curA + (i == m);
            else tmp = curA;
        }else tmp = curA + (i == m);
        sum = sum + dfs(pos - 1, tmp, vs, is && i == 0, limit && i == up);
        if(is && i == 0) ;
        else if(i != m) -- vs[i];
    }
    // debug(m, pos, curA, limit, is, sum)
    if(!limit && !is)dp[m][pos][ma][curA] = sum;
    return sum;
}
int64 solve(int64 x) {
    if(x < 10) {
        return x == m && x != 0;
    }
    n = 0;
    while(x > 0) {
        ar[n ++] = x % 10;
        x /= 10;
    }
    // for(int i = 0; i < n; ++i) debug(i, ar[i])
    vector<int> vs(10, 0);
    return dfs(n - 1, 0, vs, 1, 1);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    clr(dp, -1);
    while(tim --) {
        scanf("%lld%lld%d", &L, &R, &m);
        printf("%lld\n", solve(R) - solve(L - 1));
    }
    return 0;
}