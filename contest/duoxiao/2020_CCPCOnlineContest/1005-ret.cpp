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
const int MXN = 50 + 5;
const int MXE = 2e6 + 6;
int n, m;
int ar[MXN];
int flag;
typedef long long ll;
inline ll qp(ll x, ll p, ll mod)
{
    ll ans = 1;
    while (p)
    {
        if (p & 1)
            ans = (ll)ans * x % mod;
        x = (ll)x * x % mod;
        p >>= 1;
    }
    return ans;
}

inline bool mr(ll x, ll b)
{
    ll k = x - 1;
    while (k)
    {
        ll cur = qp(b, k, x);
        if (cur != 1 && cur != x - 1)
            return false;
        if ((k & 1) == 1 || cur == x - 1)
            return true;
        k >>= 1;
    }
    return true;
}

inline bool is_prime(ll x)
{
    if (x == 46856248255981ll || x < 2)
        return false;
    if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251)
        return true;
    return mr(x, 2) && mr(x, 61);
}

bool pir(int x) {
    int tx = sqrt(x);
    for(int i = 2; i <= tx; ++i) {
        if(x % i == 0) return false;
    }
    return true;
}
int pnum = 0, cnt = 0;
void read_data() {
    n = read();
    flag = 0;
    pnum = 0, cnt = 0;
    for(int i = 1; i <= n; ++i) {
        ar[i] = read();
        if(ar[i] == 1) continue;
        if((ar[i] & (ar[i] - 1)) == 0) {
            ++ pnum;
        }else if(is_prime(ar[i])) {
            ++ pnum;
        }else {
            ++ cnt;
        }
    }
}
void gao_solve() {
    // debug(cnt, pnum)
    if(cnt + pnum == 0) {
        flag = 0;
    }else if(cnt == 0) {
        if(pnum % 2 == 1) flag = 1;
        else flag = 0;
    }else {
        if(cnt % 2 == 1) flag = 1;
        else {
            if(pnum % 2 == 1) flag = 1;
            else flag = 0;
        }
    }
}
void print_ans() {
    printf("%s\n", flag?"W":"L");
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    // for(int i = 2; i < 100; ++i) {
    //     if(is_prime(i)) debug(i)
    // }
    int tim = read();
    while(tim --) {
        read_data();
        gao_solve();
        print_ans();
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}