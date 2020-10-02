/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
// #define LH_LOCAL
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
const int MXN = 1e5 + 5;
const int MXE = 2e6 + 6;
int n, m;
int ar[MXN];
int flag;
namespace mr {
long long mul(long long a, long long b, long long mod) {
    long long r = 0;
    while (b > 0) {
        if (b & 1) r = (r + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return r;
}
long long power(long long v, long long p, long long m) {
    long long r = 1;
    while (p > 0) {
        if (p & 1) r = mul(r, v, m);
        v = mul(v, v, m);
        p >>= 1;
    }
    return r;
}
bool witness(long long a, long long p) {
    int k = 0;
    long long q = p - 1;
    while ((q & 1) == 0) ++k, q >>= 1;
    long long v = power(a, q, p);
    if (v == 1 || v == p - 1) return false;  // probably prime number
    while (k-- != 0) {
        v = v * v % p;
        if (v == p - 1) return false;
    }
    return true;  // composite number
}
bool miller_rabin(long long p) {
    if (p == 2) return true;
    if (p % 2 == 0) return false;
    for (int i = 0; i != 50; ++i) {
        long long a = std::rand() % (p - 1) + 1;
        if (witness(a, p)) return false;
    }
    return true;
}
long long factor[100];  //质因数分解结果（刚返回时是无序的）
int tol;  //质因数的个数。数组小标从0开始,记得初始化

long long gcd(long long a, long long b) {
    long long t;
    while (b) {
        t = a;
        a = b;
        b = t % b;
    }
    return a >= 0 ? a : -a;
}
//找出一个因子
long long Pollard_rho(long long x, long long c) {
    long long i = 1, k = 2;
    long long x0 = rand() % (x - 1) + 1;
    long long y = x0;
    while (1) {
        i++;
        x0 = (mul(x0, x0, x) + c) % x;
        long long d = gcd(y - x0, x);
        if (d != 1 && d != x) return d;
        if (y == x0) return x;
        if (i == k) {
            y = x0;
            k += k;
        }
    }
}
//对n进行素因子分解
void findfac(long long n, int k) {
    if (n == 1) return;
    if (miller_rabin(n)) {
        factor[tol++] = n;
        return;
    }
    long long p = n;
    int c = k;
    while (p >= n) p = Pollard_rho(p, c--);
    findfac(p, k);
    findfac(n / p, k);
}
}
bool noprime[MXN];
int pp[MXN/5], pcnt;
int mu[MXN];
void init_prime(int MXn) {
    noprime[0] = noprime[1] = 1;
    mu[1] = 1;
    for(int i = 2; i < MXn; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, mu[i]=-1;
        for(int j = 0; j < pcnt && i*pp[j] < MXn; ++j) {
            noprime[i*pp[j]] = 1;
            mu[i*pp[j]] = -mu[i];
            if(i % pp[j] == 0) {
                mu[i*pp[j]] = 0;
                break;
            }
        }
    }
}
int pir(int x) {
    // mr::tol = 0;tle
    // mr::findfac(x, 107);
    // return mr::tol;
    int tx = sqrt(x), cnt = 0;
    for(int i = 0; i < pcnt && pp[i] <= tx; ++i) {
        if(x % pp[i] == 0) {
            while(x % pp[i] == 0) x /= pp[i], ++ cnt;
        }
        if(x == 1) break;
    }
    if(x > 1) ++ cnt;
    return cnt;
}

void read_data() {
    flag = 0;
    n = read();
    for(int i = 1; i <= n; ++i) {
        ar[i] = read();
    }
}
void gao_solve() {
    for(int i = 1; i <= n; ++i) {
        int pnum = 0, cnt = 0;
        if(ar[i] % 2 == 0) {
            pnum = 1;
            while(ar[i] % 2 == 0) ar[i] /= 2;
        }
        cnt = pir(ar[i]);
        flag ^= (cnt + pnum);
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
    init_prime((int)sqrt(1000000000) + 1);
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
