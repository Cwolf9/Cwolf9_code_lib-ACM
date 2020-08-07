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
const int mod = 1e9 + 7;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, k, x;
int dp[MXN], dmk1[MXN], dxk[MXN], last[MXN];
int ksm(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = (int64)a * a % MOD) {if (b & 1) res = (int64)res * a % MOD;}
    return res;
}
bool noprime[MXN];
int pp[MXN/5], pcnt, mu[MXN], fu[MXN];
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
    for(int i = 1; i < MXN; ++i) {
        if(mu[i]) fu[i] = 1;
        else fu[i] = 0;
    }
}
int solve(int n) {
    if(last[n] != -1) return last[n];
    int ans = 0;
    for(int L = 1, R; L <= n; L = R + 1) {
        R = n/(n/L);
        ans = (ans + ((int64)dxk[R]-dxk[L-1])%mod*dp[n/L]%mod)%mod;
    }
    return last[n] = ans;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    int tim = read();
    k = read(), x = read();
    int64 tmp = 0, tj;
    for(int i = 1, j; i < MXN; ++i) {
        j = ksm(i, k);
        tj = ksm(j, x);
        dxk[i] = (tj*mu[i] + dxk[i-1])%mod;
        if(dxk[i] < 0) dxk[i] += mod;
        tmp = (tmp + j);
        if(tmp >= mod) tmp %= mod;
        dp[i] = ksm(tmp, x);
        dmk1[i] = tj * i % mod;
        dmk1[i] = (dmk1[i-1] + dmk1[i] * fu[i]%mod);
        if(dmk1[i] >= mod) dmk1[i] %= mod;
    }
    for(int i = 1; i < MXN; ++i) last[i] = -1;
    while(tim -- ) {
        n = read();
        int64 ans = 0;
        for(int L = 1, R; L <= n; L = R + 1) {
            R = n/(n/L);
            ans = (ans + ((int64)dmk1[R] - dmk1[L-1])%mod*solve(n/L)%mod)%mod;
        }
        if(ans < 0) ans += mod;
        printf("%lld\n", ans);
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}