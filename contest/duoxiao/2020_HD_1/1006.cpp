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
const int mod = 1000000007;
const int MXN = 1e5 + 5;
const int MXE = 8e6 + 5;
const int MR = 1000000001;
int n, m, k;
class node {
    public:
    int ls, rs, mex, cnt;
}cw[MXN];
int tot_n, rk[MXN];
void push_up(int rt) {
    if(cw[cw[rt].ls].mex == cw[cw[rt].rs].mex) cw[rt].mex = INF;
    else cw[rt].mex = min(cw[cw[rt].ls].mex, cw[cw[rt].rs].mex);
}
void insert(int p, int v, int l, int r, int &rt) {
    if(rt == 0) {
        rt = ++ tot_n;
        cw[rt].ls = cw[rt].rs = cw[rt].cnt = 0;
        cw[rt].mex = INF;
    }
    if(l == r) {
        if(v == 1) {
            cw[rt].mex = INF;
            ++ cw[rt].cnt;
        }else {
            if(cw[rt].cnt == 1) cw[rt].mex = l;
            -- cw[rt].cnt;
        }
        return ;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) insert(p, v, l, mid, cw[rt].ls);
    else insert(p, v, mid + 1, r, cw[rt].rs);
    push_up(rt);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while (tim--) {
        n = read(), m = read();
        int opt, a, b;
        for(int i = 1; i <= n; ++i) rk[i] = 0;
        while(m --) {
            a = read(), b = read();
            insert(b, 1, 0, MR, rk[a]);
            insert(a, 1, 0, MR, rk[b]);
        }
        k = read();
        while(k --) {
            opt = read();
            a = read();
            if(opt == 1) {
                b = read();
                
            }
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
