/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
我博客
https://blog.csdn.net/qq_39599067/article/details/90574496
*/
#define LH_LOCAL
#define LLDO
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
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
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 1e6 + 5;
const int MXE = MXN + MXN;

int n, m, Q;
int ar[MXN], br[MXN];
class node {
    public:
    int l, r;
    unsigned int x;
}cw[2005];
unsigned int ans[2005], tf[64];
class edge {
    public:
    int f[64];
    int l, r;
}tr[MXE], tmpans;
int inde, root;
void push_up(edge &c, edge a, edge &b) {
    for(int i = 0; i < m; ++i) {
        if(a.f[i] == -1) continue;
        for(int j = 0; j < m; ++ j) {
            if(a.f[i] != -1 && b.f[j] != -1) c.f[i^j] = max(a.f[i] + b.f[j], c.f[i^j]);
        }
    }
}
void push_up2(edge &c, const edge &a, const edge &b) {
    for(int i = 0; i < m; ++i) {
        if(a.f[i] == -1) continue;
        for(int j = 0; j < m; ++ j) {
            if(a.f[i] != -1 && b.f[j] != -1) c.f[i^j] = max(a.f[i] + b.f[j], c.f[i^j]);
        }
    }
}
void build(int l, int r, int &rt) {
    if(rt == 0) rt = ++ inde;
    clr(tr[rt].f, -1);
    tr[rt].f[0] = 0;
    if(l == r) {
        tr[rt].f[ar[l]] = br[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, tr[rt].l); build(mid + 1, r, tr[rt].r);
    push_up2(tr[rt], tr[tr[rt].l], tr[tr[rt].r]);
    // debug(l, r)
    // for(int i = 0; i < m; ++i) debug(i, tr[rt].f[i])
}
void query(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) {
        push_up(tmpans, tmpans, tr[rt]);
        return;
    }
    int mid = (l + r) >> 1;
    if(L > mid) query(L, R, mid + 1, r, tr[rt].r);
    else if(R <= mid) query(L, R, l, mid, tr[rt].l);
    else {
        query(L, mid, l, mid, tr[rt].l);
        query(mid + 1, R, mid + 1, r, tr[rt].r);
    }
}
void read_data() {
    n = read();
    m = read();
    Q = read();
    for(int i = 1; i <= n; ++i) {
        ar[i] = read();
        br[i] = read();
    }
    for(int i = 1; i <= Q; ++i) {
        cw[i].l = read() + 1;
        cw[i].r = read() + 1;
        cw[i].x = read();
    }
}

void gao_solve() {
    clr(tr[0].f, -1);
    tr[0].f[0] = 0;
    build(1, n, root);
    for(int i = 1; i <= Q; ++i) {
        ans[i] = 0;
        clr(tmpans.f, -1);
        tmpans.f[0] = 0;
        query(cw[i].l, cw[i].r, 1, n, 1);
        tf[0] = tmpans.f[0];
        // debug(tf[0])
        for(int i = 1; i < m; ++i) {
            if(tmpans.f[i] == 0) tmpans.f[i] = -1;
            tf[i] = tmpans.f[i];
            // if(tf[i] != -1) debug(i, tf[i])
        }
        for(unsigned int j = 0; j < m; ++j) ans[i] += tf[j] * (cw[i].x ^ j);
    }
}
void print_ans() {
    unsigned int res = 0;
    for(unsigned int i = 1; i <= Q; ++i) res += (i^ans[i]);
    printf("%u\n", res);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    read_data();
    gao_solve();
    print_ans();
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
