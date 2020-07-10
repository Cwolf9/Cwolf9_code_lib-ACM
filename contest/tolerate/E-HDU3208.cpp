/*
链接：
https://vjudge.net/contest/381323#problem/E
题意：
定义f(x)为x最多能开几次方，输出 L-R 的 f(i)之和，范围1e18.

思路：
容斥
dp[i] = pow(m, 1.0/i)
按因子倍数容斥，因为能开 2*a 次方的数字，也一定能开 a 次方。

暴力
幂次大于等于3的最大数字不超过1e6，幂次至少等于2的开方后直接取大于1e6的答案
然后暴力枚举1-1e6算其他的即可，倍数数字个数不超过2e6。
注意枚举过程中可以开偶次方项的数可能会和大于1e6的平方项重复计算，加上少去的贡献。

备注：
卡了 sqrt(m) 和 pow(m, 1.0/2) 转 int64 后的精度，这个我是万万没想到

*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <assert.h>
#include <bits/stdc++.h>

#include <algorithm>
#include <cmath>
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
const int mod = 55566677;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
vector<int> ar, br;
int64 lo, hi, ret, ans;
// int nopr[MXN], pp[MXN], pcnt;
int is[MXN];
const double eps = 1e-8;
int64 dp[MXN];
void init_prime() {
    // nopr[1] = 1;
    // for (int i = 2; i < 63; ++i) {
    //     if (!nopr[i]) pp[pcnt++] = i;
    //     for (int j = 0; j < pcnt && pp[j] * i < 63; ++j) {
    //         nopr[pp[j] * i] = 1;
    //         if (i % pp[j] == 0) break;
    //     }
    // }
    for (int i = 2; i < MXN; ++i) is[i] = 1;
    for (int i = 2; i < MXN; ++i) {
        for (int64 j = (int64)i * i; j < MXN; j *= i) {
            is[j] = 0;
        }
    }
}
int64 pow_(int64 x, int n) {
    int64 ans = 1;
    while (n) {
        if (n & 1) {
            double tmp = 1.0 * INFLL / ans;
            if (x > tmp) return -1;
            ans *= x;
        }
        n >>= 1;
        if (x > ((int64)1 << 31) && n) return -1;
        x = x * x;
    }
    return ans;
}
//返回精确的\sqrt[y]{x}
int64 cal(int64 x, int64 n) {
    int64 a = (int64)pow(x, 1.0 / n);
    int64 qt = pow_(a, n);
    int64 ql = pow_(a - 1, n);
    int64 qr = pow_(a + 1, n);
    if (qr != -1 && qr <= x)
        return a + 1;
    else if (qt != -1 && qt <= x)
        return a;
    else if (ql != -1 && ql <= x)
        return a - 1;
}
// unordered_map<int64, int> mp;
int64 get(int64 m) {
    if (m == 1) return 0;
    ans = 0;
    for(int i = 2; i < 63; ++i) {
        dp[i] = max(0LL, cal(m, i) - 1);
    }
    for(int i = 62; i >= 2; --i) {
        for(int j = i + i; j < 63; j += i) {
            dp[i] -= dp[j];
        }
    }
    ret = 0;
    for(int i = 2; i < 63; ++i) ans += dp[i] * i, ret += dp[i];
    return ans + m - 1 - ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    while (~scanf("%lld%lld", &lo, &hi) && lo) {
        print(get(hi) - get(lo - 1));
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
/*
int n, m, k;
vector<int> ar, br;
int64 lo, hi, ret, ans;
int is[MXN];
const double eps = 1e-8;
void init_prime() {
    for (int i = 2; i < MXN; ++i) is[i] = 1;
    for (int i = 2; i < MXN; ++i) {
        for (int64 j = (int64)i * i; j < MXN; j *= i) {
            is[j] = 0;
        }
    }
}
int64 pow_(int64 x, int n) {
    int64 ans = 1;
    while (n) {
        if (n & 1) {
            double tmp = 1.0 * INFLL / ans;
            if (x > tmp) return -1;
            ans *= x;
        }
        n >>= 1;
        if (x > ((int64)1 << 31) && n) return -1;
        x = x * x;
    }
    return ans;
}
//返回精确的\sqrt[y]{x}
int64 cal(int64 x, int64 n) {
    int64 a = (int64)pow(x, 1.0 / n);
    int64 qt = pow_(a, n);
    int64 ql = pow_(a - 1, n);
    int64 qr = pow_(a + 1, n);
    if (qr != -1 && qr <= x)
        return a + 1;
    else if (qt != -1 && qt <= x)
        return a;
    else if (ql != -1 && ql <= x)
        return a - 1;
}
// unordered_map<int64, int> mp;
int64 get(int64 m) {
    if (m == 1) return 0;
    int64 all = m - 1;
    int64 sum = 0;
    int64 sq2 = sqrt(m) + eps;
    int64 sq3 = pow(m, 1.0/3) + eps;
    // assert(sq2 == cal(m, 2) && sq3 == cal(m, 3));
    sq2 = cal(m, 2);
    sq3 = cal(m, 3);
    // assert(sq2 * sq2 <= m && (sq2 + 1) * (sq2 + 1) > m);
    // assert(sq3 * sq3 * sq3 <= m && (sq3 + 1) * (sq3 + 1) * (sq3 + 1) > m);
    if (sq2 > 1000000) {
        all -= sq2 - 1000000;
        sum = (sq2 - 1000000) * 2;
        sq2 = 1000000;
    }
    int al = 0;
    for (int i = 2; i <= sq2; ++i) {
        if (is[i] == 0) continue;
        int cnt = 2;
        for (int64 j = (int64)i * i; j <= m; j *= i) {
            if(cnt % 2 == 0 && j > 1000000000000) sum += cnt - 2;
            else sum += cnt, -- all;
            ++ cnt;
            if (m < (double)i * j) break;
        }
    }
    sum += all;
    return sum;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    debug(INFLL > 1e18 + 500)
    init_prime();
    while (~scanf("%lld%lld", &lo, &hi) && lo) {
        print(get(hi) - get(lo - 1));
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

*/