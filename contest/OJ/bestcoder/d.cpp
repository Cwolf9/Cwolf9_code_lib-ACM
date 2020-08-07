/*


*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <assert.h>
#include<unordered_map>
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
// const int mod = 998244353;
const int MOD = 1e9 + 9;  // 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN];
int64 sum[MXN<<2], asn[MXN<<2];
int ksm(int a, int b) {
    int res = 1;
    while(b > 0) {
        if(b & 1) res = (int64)res * a % MOD;
        a = (int64) a * a % MOD;
        b >>= 1;
    }
    return res;
}
void build(int l, int r, int rt) {
    asn[rt] = -1;
    if(l == r) {
        sum[rt] = ar[l] + 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    sum[rt] = sum[rt << 1] * sum[rt << 1 | 1] % MOD;
}
void push_down(int rt, int l, int mid, int r) {
    if(asn[rt] == -1) return;
    asn[rt << 1] = asn[rt << 1 | 1] = asn[rt];
    sum[rt << 1] = ksm(asn[rt], mid - l + 1) % MOD;
    sum[rt << 1 | 1] = ksm(asn[rt], r - mid) % MOD;
    asn[rt] = -1;
}
void update(int L, int R, int v, int l, int r, int rt) {
    if(L <= l && r <= R) {
        asn[rt] = v + 1;
        sum[rt] = ksm(v + 1, r - l + 1);
        return ;
    }
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) update(L, R, v, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) update(L, R, v, l, mid, rt << 1);
    else {
        update(L, mid, v, l, mid, rt << 1);
        update(mid + 1, R, v, mid + 1, r, rt << 1 | 1);
    }
    sum[rt] = sum[rt << 1] * sum[rt << 1 | 1] % MOD;
}
void single(int p, int v, int l, int r, int rt) {
    if(l == r) {
        sum[rt] = v + 1;
        return ;
    }
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(p <= mid) single(p, v, l, mid, rt << 1);
    else single(p, v, mid + 1, r, rt << 1 | 1);
    sum[rt] = sum[rt << 1] * sum[rt << 1 | 1] % MOD;
}
int64 query(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) return sum[rt];
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) return query(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) return query(L, R, l, mid, rt << 1);
    else {
        return (query(L, mid, l, mid, rt << 1) * query(mid + 1, R, mid + 1, r, rt << 1 | 1)) % MOD;
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D://in.in", "r", stdin);
    freopen("D://out.out", "w", stdout);
#endif
    n = read(), m = read();
    assert(n >= 1 && n <= 100000 && m >= 1 && m <= 200000);
    for(int i = 1; i <= n; ++i) ar[i] = read(), assert(ar[i] >= 0 && ar[i] <= 1000000000);
    build(1, n, 1);
    while(m -- ) {
        int opt = read();
        assert(opt <= 3 && opt >= 1);
        if(opt == 1) {
            int l = read(), r = read(), v = read();
            assert(1 <= l && l <= r && r <= n && v >= 0 && v <= 1000000000);
            update(l, r, v, 1, n, 1);
        }else if(opt == 2) {
            int p = read(), v = read();
            assert(1 <= p && p <= n && v >= 0 && v <= 1000000000);
            single(p, v, 1, n, 1);
        }else {
            int l = read(), r = read();
            assert(1 <= l && l <= r && r <= n);
            printf("%lld\n", query(l, r, 1, n, 1));
        }
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}
