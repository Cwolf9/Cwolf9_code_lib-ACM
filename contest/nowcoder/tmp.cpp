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
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;

bool noprime[MXN];
int pp[MXN/5], pcnt;
int mu[MXN];
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
}
int64 n, k, ans, MAXY;
unordered_map<int, int> mp;
void dfs(int64 Y, int64 dep, int64 num, int64 limit){
    //因子数 深度 当前的数
    if(dep == MAXY)return;
    //if(Y >= n) return;//n个因数的最小整数
    if(mp.find(num) == mp.end()) mp[num] = 1, ++ ans;
    for(int i = 0; i <= limit; ++i) {
        //因为后面的次数不会超过前面,所以这里添加上限就是一个极大的剪枝
        if(n / pp[dep] < num) break;//保证不超过n
        dfs(Y*(i+1), dep+1, num, limit);
        num*=pp[dep];
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    n = read(), k = sqrt(n) - 10;
    debug(n, k)
    cout.flush();
    for(int i = 0; i < pcnt; ++i) {
        if(pp[i] > k) {
            MAXY = i - 1;
            break;
        }
    }
    dfs(1, 0, 1, 30);
    printf("%d\n", ans);
    // string s;
    // while(getline(cin, s)) {
    //     cout << "\"" << s << "\"," << endl;
    // }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}