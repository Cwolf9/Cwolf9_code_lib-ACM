/*
链接：
https://vjudge.net/contest/381323#problem/D
题意：
求小于等于n的，形如m^k(k>1)的数字的个数

思路：
系数最大不超过63，容斥小于63的素质数作为系数即可。
或者
暴力
有三次方项的基数不超过1e6，枚举1到1e6即可，注意不要重复计算。
然后暴力算平方项的解。

备注：


*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <cmath>
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
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
vector<int> ar, br;
int64 lo, hi, ret, ans;
int nopr[MXN], pp[MXN], pcnt;
const double eps = 1e-8;
void init_prime() {
    nopr[1] = 1;
    for(int i = 2; i < 63; ++i) {
        if(!nopr[i]) pp[pcnt ++] = i;
        for(int j = 0; j < pcnt && pp[j] * i < 63; ++j) {
            nopr[pp[j] * i] = 1;
            if(i % pp[j] == 0) break;
        }
    }
}

int check(int i) {
    int cnt = -2;
    lo = hi;
    while(lo > 0) {
        lo /= i;
        ++ cnt;
    }
    return max(cnt, 0);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    while(~scanf("%lld", &hi)) {
        int64 sq2 = sqrt(hi);
        int64 sq3 = pow(hi, 1.0/3);
        ans = 1;
        int64 ret;
        for(int i = 0; i < pcnt; ++i) {
            if(pow(2, pp[i]) > hi) break;
            ret = (int64)(pow(hi, 1.0/pp[i]) - 1 + eps);
            ans += ret;
            // debug(i, pp[i], ret)
            for(int j = i + 1; j < pcnt; ++j) {
                if(pp[i] * pp[j] >= 63 || pow(2, pp[i] * pp[j]) > hi) break;
                ret = (int64)(pow(hi, 1.0/(pp[i] * pp[j])) - 1 + eps);
                // debug(i, j, pp[i], pp[j], ret)
                ans -= ret;
                for(k = j + 1; k < pcnt; ++k) {
                    if(pp[i] * pp[j] * pp[k] >= 63 || pow(2, pp[i] * pp[j] * pp[k]) > hi) break;
                    ret = (int64)(pow(hi, 1.0/(pp[i] * pp[j] * pp[k])) - 1 + eps);
                    ans += ret;
                }
            }
        }
        print(ans);
        ans = 0;
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
int mu[MXN];
void init_prime() {
    for(int i = 2; i < MXN; ++i) mu[i] = 1;
    for(int64 i = 2; i < MXN; ++i) {
        for(int64 j = i * i; j < MXN; j *= i) {
            mu[j] = 0;
        }
    }
}
int check(int i) {
    int cnt = -2;
    lo = hi;
    while(lo > 0) {
        lo /= i;
        ++ cnt;
    }
    return max(cnt, 0);
}
int main() {
    init_prime();
    while(~scanf("%lld", &hi)) {
        int64 sq2 = sqrt(hi);
        int64 sq3 = pow(hi, 1.0/3);
        ans = max(0LL, sq2 - 1000000) + 1;
        for(int i = 2; i <= 1000000; ++i) {
            ans += mu[i] * check(i);
            for(int64 j = (int64)i * i; j <= sq2 && mu[i] == 1; j *= i) {
                if(j > 1000000) {
                    -- ans;
                }
            }
        }
        print(ans);
    }
    return 0;
}
*/

