/*
  
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
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 6;
int n;
vector<int> mp[MXN], rmp[MXN];
int du[MXN], is[MXN], sz[MXN];
int aim;
vector<int> leaf, oth, sec;
void dfs(int u, int ba) {
    sz[u] = is[u];
    for(int v: mp[u]) {
        if(v == ba) continue;
        rmp[u].eb(v);
        dfs(v, u);
        sz[u] += sz[v];
    }
}
void dfs2(int u, int ba) {
    for(int v: rmp[u]) {
        dfs2(v, u);
    }
    if(is[u] && aim > 0) {
        du[u] = 1;
        -- aim;
        leaf.eb(u);
    }else if(is[u]) {
        du[u] = 2;
        sec.eb(u);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("D:in.in", "r", stdin);
    // freopen("D:out.out", "w", stdout);
#endif
    n = read();
    for(int i = 1, a, b; i < n; ++i) {
        a = read(), b = read();
        du[a] ++;
        du[b] ++;
        mp[a].eb(b);
        mp[b].eb(a);
    }
    if(n == 1) {
        printf("0\n");
        return 0;
    }
    int rt = 1, cnt = 0;
    for(int i = 1; i <= n; ++i) if(du[i] == 1) {
        rt = i;
        ++ cnt;
        is[i] = 1;
    }
    dfs(rt, -1);
    int mid = -1, mn = INF;
    aim = (cnt + 1) / 2;
    for(int i = 1; i <= n; ++i) if(sz[i] >= (cnt + 1) / 2 && sz[i] < mn) {
        mid = i;
        mn = sz[i];
    }
    for(int i = 1; i <= n; ++i) du[i] = 0;
    dfs2(mid, -1);
    reverse(all(sec));
    for(int x: sec) oth.eb(x);
    for(int i = 1; i <= n; ++i) {
        if(is[i]) {
            if(du[i] == 0) oth.eb(i);
        }
    }
    printf("%d\n", (int)(cnt + 1)/2);
    if(cnt % 2 == 0) {
        mid = cnt / 2;
        for(int i = 0; i < mid; ++ i) {
            printf("%d %d\n", leaf[i], oth[i]);
        }
    }else {
        assert((int)leaf.size() > (int)oth.size());
        mid = cnt / 2;
        for(int i = 0; i < mid; ++ i) {
            printf("%d %d\n", leaf[i], oth[i]);
        }
        printf("%d %d\n", oth[0], leaf.back());
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}