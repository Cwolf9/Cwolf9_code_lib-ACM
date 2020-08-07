/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6831)
**题意**
求114514191911451419191145141919一个最短前缀，添加任意(,),+,*后数值为$n(5000)$.
**思路**
$O(13^3*n^2)$区间dp即可。
**备注**
*/
#define LH_LOCAL
#define LLDO
#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
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
#define rep(i, s, t) for (register int i = s; i < t; ++i)
#define per(i, s, t) for (register int i = s; i >= t; --i)
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
const int mod = 1e9 + 7;  // 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n;
char str[35] = "0114514191911451419191145141919";
bool dp[35][35][5005];
int ans[5005];
#ifdef LH_LOCAL
int stoi(string s) {
    int ans = 0;
    for(char c: s) {
        ans = ans * 10 + c - '0';
    }
    return ans;
}
#endif
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    string s = str;
    clr(ans, 0x3f);
    for (int len = 1; len <= 12; ++len) {
        for (int i = 1, j; i + len - 1 <= 12; ++i) {
            j = i + len - 1;
            if (len <= 4) {
                int x = stoi(s.substr(i, len));
                dp[i][j][x] = 1;
                if(ans[x] == INF && i == 1) ans[x] = len;
            }
            for (int k = i; k < j; ++k) {
                for (int a = 1; a <= 5000; ++a) {
                    if (dp[i][k][a] == 0) continue;
                    for (int b = 1; b <= 5000; ++b) {
                        if (dp[k + 1][j][b] == 0) continue;
                        if (a + b <= 5000) {
                            dp[i][j][a + b] = 1;
                            if(ans[a + b] == INF && i == 1) ans[a + b] = len;
                        }
                        if (a * b <= 5000) {
                            dp[i][j][a * b] = 1;
                            if(ans[a * b] == INF && i == 1) ans[a * b] = len;
                        }
                    }
                }
            }
        }
    }
    ans[3] = ans[7] = -1;
    int tim = read();
    while (tim--) {
        n = read();
        printf("%d\n", ans[n]);
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}