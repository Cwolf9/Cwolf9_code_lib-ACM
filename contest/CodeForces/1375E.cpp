/*
给你一个n=1000的序列，记所有逆序对为vpairs，你要将vpairs重排一种顺序，
满足做操作swap(a[pair.first], a[pair.second])后序列变成有序
从后往前考虑，每次先恢复最大的数字，恢复的数字位就不用管了。
对于 1 - t 位置的数字，将 1 - (t - 1) 中大于 a[t] 的数字按大小排序，然后按照
原位置依次与 t 做swap操作即可。
因为这样可以保证最后一个数是较大，且不会影响其他位置的逆序对情况。
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <ctime>
#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline LL read() {
    LL x = 0;int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(LL x, bool f) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template<class T>T big(const T &a1, const T &a2) { return a1 > a2 ? a1 : a2; }
template<class T>T sml(const T &a1, const T &a2) { return a1 < a2 ? a1 : a2; }
template<typename T, typename ...R>T big(const T &f, const R &...r) { return big(f, big(r...)); }
template<typename T, typename ...R>T sml(const T &f, const R &...r) { return sml(f, sml(r...)); }
void debug_out() { cout << '\n'; }
template<typename T, typename ...R>void debug_out(const T &f, const R &...r) {cout << f << " ";debug_out(r...);}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
// #define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template<typename T>
void print(const T &f) {printf(ptout, f);putchar('\n');}
template<typename T, typename ...R>
void print(const T &f, const R &...r) {printf(ptout, f);putchar(' ');print(r...);}

const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;//998244353
const int MXN = 2e3 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN], br[MXN];
vector<int> fward[MXN], back[MXN];
map<int, int> mp;
bool cmpsml(const int &a, const int &b) {
    return ar[a] < ar[b];
}
bool cmpbig(const int &a, const int &b) {
    return ar[a] > ar[b];
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = 1;
    while(tim --) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]);
        for(int i = 1; i <= n; ++i) {
            for(int j = i + 1; j <= n; ++j) {
                if(ar[i] > ar[j]) {
                    mp[i * 10000 + j] = 1;
                }
            }
        }
        vector<pii > ans, srt;
        for(int t = n; t >= 2; --t) {
            srt.clear();
            for(int i = 1; i < t; ++i) {
                if(ar[i] > ar[t]) {
                    srt.eb(mk(ar[i], i));
                }
            }
            sort(all(srt));
            for(pii x: srt) {
                ans.eb(mk(x.se, t));
            }
        }
        print((int)ans.size());
        for(pii x: ans) print(x.fi, x.se);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
