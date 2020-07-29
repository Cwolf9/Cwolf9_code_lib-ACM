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
const int mod = 1e9 + 7;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 3;
const int MXE = 2e6 + 6;
int64 n, m, k;
int ar[MXN], fa[MXN];
int64 sz1[MXN], sz2[MXN];
int Fi(int x) {
    return fa[x] == x?x:fa[x] = Fi(fa[x]);
}
int64 C2(int64 n) {
    if(n <= 1) return 0;
    return n * (n - 1) / 2;
}
int64 C3(int64 n) {
    if(n <= 2) return 0;
    return n * (n - 1) * (n - 2) / 6;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        k = read();
        n = m = 0;
        for(int i = 1; i <= k; ++i) fa[i] = i;
        for(int i = 1; i <= k; ++i) {
            ar[i] = read();
            if(ar[i] == 1) ++ m, sz1[i] = 1, sz2[i] = 0;
            else ++ n, sz1[i] = 0, sz2[i] = 1;
        }
        int64 ans1 = C2(n) * m, ans2 = C3(n);
        printf("%lld\n", (ans1 + ans2)%mod);
        for(int i = 1, a, b; i < k; ++i) {
            a = read(), b = read();
            int pa = Fi(a), pb = Fi(b);
            if(pa != pb) {
                // debug(a, b, pa, pb)
                // debug(ans1, ans2, sz1[pa], sz2[pa], sz1[pb], sz2[pb])
                ans1 -= (sz2[pa] * (n - sz2[pa] - sz2[pb])) * sz1[pb] 
                + (sz2[pb] * (n - sz2[pb] - sz2[pa])) * sz1[pa] + (sz2[pa] * sz2[pb]) * (m - sz1[pa] - sz1[pb]);
                ans2 -= (sz2[pa] * sz2[pb] * (n - sz2[pa] - sz2[pb]));
                fa[pa] = pb;
                sz1[pb] += sz1[pa];
                sz2[pb] += sz2[pa];
            }
            // debug(ans1, ans2)
            printf("%lld\n", (ans1 + ans2)%mod);
        }
    }
#ifndef ONLINE_JUDGE
    //cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    //system("pause");
#endif
    return 0;
}
