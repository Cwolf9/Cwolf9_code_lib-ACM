/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#include<bits/stdc++.h>
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

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 5e2 + 5;
const int MXE = 2e6 + 6;
int n, T = 1000;
double dp[10005][505][2];
int d[20] = {1,18,4,13,6,10,15,2,17,3,19,7,16,8,11,14,9,12,5,20};
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    debug(19*2.0/20/20/3)
    // dp[0][0][0] = dp[0][0][1] = 1;
    // rep(i, 1, T + 1) dp[i][0][0] = dp[i][0][1] = 1;
    rep(t, 1, T + 1) {
        for(int i = 1; i <= 501; ++i) {
            for(int j = 0; j < 20; ++j) {
                if(d[j] < i) {
                    dp[t][i][0] += dp[t-1][i - d[j]][0] * (1 - dp[t-1][i - d[j]][1]) / 20;
                }else if(d[j] == i) {
                    dp[t][i][0] += (1 - dp[t-1][i - d[j]][1]) / 20;
                }
            }
            for(int j = 0; j < 20; ++j) {
                double win = 0;
                for(int k = 0; k < 3; ++k) {
                    if(d[(j + k) % 20] < i) {
                        win += (1 - dp[t-1][i - d[(j+k)%20]][0]) / 3;
                    }else if(d[(j + k) % 20] == i){
                        win += 1.0 / 3;
                    }
                }
                dp[t][i][1] = max(dp[t][i][1], win);
            }
            rep(j, 0, 2) dp[t][i][j] *= (1 - dp[t-1][i][j]);
        }
        if(t < 5) debug(t, dp[t][1][0], dp[t][1][1])
    }
    n = read();
    while(n) {
        double ans[2] = {0, 0};
        rep(i, 1, T + 1) rep(j, 0, 2) ans[j] += dp[i][n][j];
        printf("%.10f %.10f\n", ans[0], ans[1]);
        n = read();
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}