/*
链接：
https://vjudge.net/problem/ZOJ-3349
题意：
n=100000, d = 1000000000 , 求最长的子序列长度满足相邻数字差不超过d。

思路：


备注：


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
const int mod = 55566677;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 3e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN], sum[MXN << 2];
vector<int> vs;
int get_p(int x) {
    return lower_bound(all(vs), x) - vs.begin() + 1;
}
void build(int l, int r, int rt) {
    sum[rt] = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
}
void modify(int p, int v, int l, int r, int rt) {
    if(l == r) {
        sum[rt] = v;
        return ;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) modify(p, v, l, mid, rt << 1);
    else modify(p, v, mid + 1, r, rt << 1 | 1);
    sum[rt] = max(sum[rt << 1], sum[rt << 1 | 1]);
}
int query(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) return sum[rt];
    int mid = (l + r) >> 1;
    if(L > mid) return query(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) return query(L, R, l, mid, rt << 1);
    else return max(query(L, mid, l, mid, rt << 1), query(mid + 1, R, mid + 1, r, rt << 1 | 1));
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    while (~scanf("%d%d", &n, &m)) {
        vs.clear();
        for(int i = 1; i <= n; ++i) {
            ar[i] = read();
            vs.eb(ar[i]);
            vs.eb(ar[i] + m);
            vs.eb(max(ar[i] - m, 0));
        }
        my_unique(vs);
        k = vs.size();
        build(1, k, 1);
        for(int i = 1, x, y; i <= n; ++i) {
            x = get_p(max(ar[i]-m, 0));
            y = get_p(ar[i] + m);
            ar[i] = get_p(ar[i]);
            modify(ar[i], query(x, y, 1, k, 1) + 1, 1, k, 1);
        }
        print(sum[1]);
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
