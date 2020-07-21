/*
链接
https://ac.nowcoder.com/acm/contest/5667/J
题意
最开始ar[i] = i, 要你求一个n的排列p[], 满足做 m (大质数) 次 new_ar[i]=p[ar[i]]后的
new_ar[] 数组为输入给定的arr[]数组。
思路
首先你把 i->ar[i] 都首尾相连列出来，表示i变换m次后变成ar[i]。它肯定会形成若干个环，环的大小
假设是x，那么也就是x个数字相互转换，一定会成大小为 x 的环
因为 m 是大于 x 的大质数, 那么一定有 {k*m%x|0<= k <x} = {k|0<= k <x}
我们模拟走x次m步，把环之间相互直接的变换模拟出来，然后还原p数组即可
复杂度O(n)
备注

*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
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
const int MXN = 1e5 + 5;
const int MXE = 1e6 + 6;
int n, m, k;
int ar[MXN], fa[MXN], cnt[MXN], br[MXN], p[MXN];
int Fi(int x) {
    return fa[x] == x? x: fa[x] = Fi(fa[x]);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    while(~scanf("%d", &n)) {
        scanf("%d", &m);
        for(int i = 1; i <= n; ++i) fa[i] = i, cnt[i] = 0, ar[i] = read();
        for(int i = 1; i <= n; ++i) {
            if(Fi(i) != Fi(ar[i])) {
                fa[Fi(i)] = fa[Fi(ar[i])];
            }
        }
        for(int i = 1; i <= n; ++i) ++ cnt[Fi(i)];
        for(int i = 1, h; i <= n; ++i) {
            k = cnt[i];
            if(k == 0) continue;
            h = ar[i];
            for(int j = 0; j < k; ++j) {
                br[(int64)j*m%k] = h;
                h = ar[h];
            }
            br[k] = br[0];
            for(int j = 1; j <= k; ++j) {
                p[br[j-1]] = br[j];
            }
        }
        for(int i = 1; i <= n; ++i) printf("%d%c", p[i], " \n"[i == n]);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
