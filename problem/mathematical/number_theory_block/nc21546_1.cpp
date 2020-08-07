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
#include <cmath>
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
// #define LLDO
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
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 6;
int64 n, m, k;
int64 L, R;
int val[MXN], dp[MXN];
map<int, int> mp;
int noprime[MXN], pp[MXN], pcnt;
int is[MXN], mu[MXN];
int64 ksm(int64 a, int64 b) {
    int64 res = 1;
    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1) res = res * a % MOD;
    }
    return res;
}
int pre_mu[MXN];
unordered_map<int, int> mp1;
void init_prime() {
    noprime[0] = noprime[1] = 1;
    mu[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, mu[i]=-1;
        for(int j = 0; j < pcnt && i*pp[j] < MXN; ++j) {
            noprime[i*pp[j]] = 1;
            mu[i*pp[j]] = -mu[i];
            if(i % pp[j] == 0) {
                mu[i*pp[j]] = 0;
                break;
            }
        }
    }
    for(int i = 1; i < MXN; ++i) pre_mu[i] = pre_mu[i-1]+mu[i];
}

int solve_mu(int n) {
    if(n < MXN) return pre_mu[n];
    if(mp1[n]) return mp1[n];
    int ans = 1;
    for(int L = 2, R; L <= n; L = R + 1) {
        R = n/(n/L);
        ans -= (R-L+1)*solve_mu(n/L);
    }
    mp1[n] = ans;
    return ans;
}

int solve(int n) {
    if(n <= 0) return 0;
    if(n < MXN) return pre_mu[n];
    if(mp1[n]) return mp1[n];
    int64 ans1 = 1;
    for(int L = 2, R; L <= n; L = R + 1) {
        R = n/(n/L);
        ans1 -= (R-L+1)*solve_mu(n/L);
    }
    mp1[n] = ans1;
    return ans1;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    n = read(), k = read(), L = read(), R = read();
    L = (L - 1) / k + 1;
    R = R / k;
    m = R - L + 1;
    for (int i = 0; i < m; ++i) val[i] = i + L;
    int64 ans = mu[1] * ksm((R - (L - 1)), n) % MOD;
    int tn = R, tm = L - 1;
    for(int l = 2, r; l <= tn; l = r + 1) {
        if(tm/l <= 0) {
            r = tn/(tn/l);
            ans = (ans + (solve(r) - solve(l-1)) * ksm((tn / r ), n) % MOD) % MOD;
        }else {
            r = min(tn/(tn/l), tm/(tm/l));
            ans = (ans + (solve(r) - solve(l-1)) * ksm((tn / r - tm / r), n) % MOD) % MOD;
        }
    }
    print((ans + MOD) % MOD);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
