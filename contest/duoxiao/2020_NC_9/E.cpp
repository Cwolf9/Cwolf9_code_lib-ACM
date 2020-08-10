/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
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
// const int MOD = 1e9 + 7;
const int MXN = 4e4 + 5;
const int MXE = 2e6 + 6;
int a, b, c, d, x, y;
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
vector<pii> vs1, vs2;
class node {
    public:
    int p, k1, k2;
};
vector<node> vs;
int ksm(int a, int b) {
    int res = 1;
    for (; b > 0; b >>= 1, a = (int64)a * a % mod) {
        if (b & 1) res = (int64)res * a % mod;
    }
    return res;
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    a = read(), b = read(), c = read(), d = read();
    x = read(), y = read();
    init_prime();
    for(int i = 0; i < pcnt && pp[i] <= x; ++i) {
        if(x % pp[i] == 0) {
            int cnt = 0;
            while(x % pp[i] == 0) x /= pp[i], ++ cnt;
            vs1.eb(mk(pp[i], cnt));
        }
        if(x == 1) break;
    }
    if(x > 2) vs1.eb(mk(x, 1));
    for(int i = 0; i < pcnt && pp[i] <= y; ++i) {
        if(y % pp[i] == 0) {
            int cnt = 0;
            while(y % pp[i] == 0) y /= pp[i], ++ cnt;
            vs2.eb(mk(pp[i], cnt));
        }
        if(y == 1) break;
    }
    if(y > 2) vs2.eb(mk(y, 1));
    int p1 = 0, p2 = 0;
    while(p1 < SZ(vs1) && p2 < SZ(vs2)) {
        if(vs1[p1].fi == vs2[p2].fi) {
            vs.eb(node{vs1[p1].fi, vs1[p1].se, vs2[p2].se});
            ++ p1, ++ p2;
        }else if(vs1[p1].fi < vs2[p2].fi) ++ p1;
        else ++ p2;
    }
    int64 ans = 1;
    vector<int64> Log(vs.size(), 0);
    int PI = -1;
    for(auto x: vs) {
        ++ PI;
        debug(x.p, x.k1, x.k2);
        int f = 0;
        if(x.k1 < x.k2) {
            swap(x.k1, x.k2);
            swap(a, c);
            swap(b, d);
            f = 1;
        }
        int64 tmp;
        for(int i = a; i <= b; ++i) {
            tmp = (int64)i * x.k1 / x.k2 + 1;
            debug(tmp, c, d, a, b)
            if(tmp > d) {
                tmp = ((int64)d+c)*(d-c+1)/2;
                if(tmp >= mod - 1) tmp %= mod - 1;
                tmp *= x.k2;
                // debug(tmp)
                if(tmp >= mod - 1) tmp %= mod - 1;
                Log[PI] += tmp;
                if(Log[PI] >= mod - 1) Log[PI] %= mod - 1;
            }else if(tmp <= c) {
                tmp = (int64)i*(d-c+1);
                if(tmp >= mod - 1) tmp %= mod - 1;
                tmp *= x.k1;
                if(tmp >= mod - 1) tmp %= mod - 1;
                Log[PI] += tmp;
                if(Log[PI] >= mod - 1) Log[PI] %= mod - 1;
            }else {
                int dd = tmp - 1;
                tmp = ((int64)dd+c)*(dd-c+1)/2;
                if(tmp >= mod - 1) tmp %= mod - 1;
                tmp *= x.k2;
                if(tmp >= mod - 1) tmp %= mod - 1;
                Log[PI] += tmp;
                if(Log[PI] >= mod - 1) Log[PI] %= mod - 1;
                // debug(ksm(x.p, tmp))
                int cc = dd + 1;
                tmp = (int64)i*(d-cc+1);
                if(tmp >= mod - 1) tmp %= mod - 1;
                tmp *= x.k1;
                if(tmp >= mod - 1) tmp %= mod - 1;
                Log[PI] += tmp;
                if(Log[PI] >= mod - 1) Log[PI] %= mod - 1;
                // debug(ksm(x.p, tmp))
            }
        }
        if(f) {
            swap(a, c);
            swap(b, d);
        }
    }
    for(int i = 0; i < SZ(vs); ++i) ans = ans * ksm(vs[i].p, Log[i]) % mod;
    printf("%lld\n", (ans + mod) % mod);
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}