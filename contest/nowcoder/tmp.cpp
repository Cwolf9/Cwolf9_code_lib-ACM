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
typedef pair<int, int64> piL;
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
const int MXN = 1e5 + 5;
const int MXE = 2e6 + 6;
int n, q;
bool noprime[305];
int pp[305], pcnt, rp[305];
void init_prime() {
    noprime[0] = noprime[1] = 1;
    for(int i = 2; i < 305; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, rp[i] = pcnt - 1;
        for(int j = 0; j < pcnt && i*pp[j] < 305; ++j) {
            noprime[i*pp[j]] = 1;
            if(i % pp[j] == 0) break;
        }
    }
}
class point {
    public:
    int x, y, t;
    void rd() {
        x = read(), y = read(), t = read();
    }
}node[MXN];
int sxy[62][2][MXN];
class ST2 {
    public:
    int id, id2;
    int64 sum[MXN<<2];
    int sz[MXN<<2];
    void build(int l, int r, int rt) {
        if(l == r) {
            sum[rt] = (int64)sxy[id][id2][l] * l;
            sz[rt] = sxy[id][id2][l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
        sz[rt] = sz[rt << 1] + sz[rt << 1 | 1];
    }
    void modify(int p, int f, int v, int l, int r, int rt) {
        if(l == r) {
            sz[rt] += f;
            sum[rt] += f * v;
            return;
        }
        int mid = (l + r) >> 1;
        if(p <= mid) modify(p, f, v, l, mid, rt << 1);
        else modify(p, f, v, mid + 1, r, rt << 1 | 1);
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
        sz[rt] = sz[rt << 1] + sz[rt << 1 | 1];
    }
    piL query(int L, int R, int l, int r, int rt) {
        if(L <= l && r <= R) {
            return mk(sz[rt], sum[rt]);
        }
        int mid = (l + r) >> 1;
        if(L > mid) return query(L, R, mid + 1, r, rt << 1 | 1);
        else if(R <= mid) return query(L, R, l, mid, rt << 1);
        else {
            piL a = query(L, mid, l, mid, rt << 1);
            piL b = query(mid + 1, R, mid + 1, r, rt << 1 | 1);
            return mk(a.fi + b.fi, a.se + b.se);
        }
    }
}tree[62][2];

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    debug(pcnt)
    debug(pcnt * 1e5 * 4 * 2)
    int64 tmp = 1;
    for(int i = 0; ; ++i) {
        tmp *= pp[i];
        if(tmp >= 1000000) {
            debug(i);
            break;
        }
    }
    n = read(), q = read();
    for(int i = 1; i <= n; ++i) {
        node[i].rd();
        node[i].t = rp[node[i].t];
        ++ sxy[node[i].t][0][node[i].x];
        ++ sxy[node[i].t][1][node[i].y];
    }
    for(int i = 0; i < pcnt; ++i) {
        tree[i]->build(1, 100000, 1);
    }
    int opt, x, y, z;
    while(q --) {
        opt = read();
        if(opt == 1) {
            z = read(), x = read(), y = read();
            tree[node[z].t]->modify(node[z].x, -1, node[z].y, 1, 100000, 1);
            tree[node[z].t]->modify(x, 1, y, 1, 100000, 1);
            node[z].x = x, node[z].y = y;
        }else {
            x = read(), y = read(), z = read();
            int64 ans = 0;
            for(int i = 0; i < pcnt && z >= pp[i]; ++i) {
                if(z % pp[i] == 0) {
                    while(z % pp[i] == 0) z /= pp[i];
                    
                }
                if(z == 1) break;
            }
        }
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
