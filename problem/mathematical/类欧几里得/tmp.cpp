#include <bits/stdc++.h>
using namespace std;
#include <cstdio>
typedef long long LL;
const int mod = 998244353;
int ksm(int a, int b, int Mod) {
    int res = 1;
    for (; b > 0; b >>= 1, a = (LL)a * a % Mod) {
        if (b & 1) res = (LL)res * a % Mod;
    }
    return res;
}
//abcn>=0,c!=0
LL f(LL a, LL b, LL c, LL n) {
    LL m = (a*n+b)/c;
    if(n == 0 || m == 0) return (b/c)%mod;
    if(n == 1) return (b / c + (a + b) / c)%mod;
    m %= mod;
    if(a >= c || b >= c) return (f(a % c, b % c, c, n) +
    (n*(n+1)/2)%mod*(a/c)%mod + (b/c)*(n+1)%mod)%mod;
    return ((m * n%mod - f(c, c - b - 1, a, m - 1))%mod+mod)%mod;
}
LL two = ksm(2, mod - 2, mod);
LL six = ksm(6, mod - 2, mod);
LL h(LL a, LL b, LL c, LL n);
#define o2(x) (x)*(x)
LL g(LL a, LL b, LL c, LL n) {
    LL m = (a*n+b)/c;
    if(n == 0 || m == 0) return 0;
    if(n == 1) return ((a + b) / c)%mod;
    m %= mod;
    if(a >= c || b >= c) return ((n*(n+1)%mod*(2*n+1)%mod*six)%mod*(a/c)%mod
    + ((n+1)*n/2)%mod*(b/c)%mod + g(a % c, b % c, c, n))%mod; return ((m *
    n%mod * (n + 1)%mod - f(c, c - b - 1, a, m - 1)- h(c, c - b - 1, a, m -
    1))*two%mod+mod)%mod;
}

LL h(LL a, LL b, LL c, LL n) {
    LL m = (a*n+b)/c;
    if(n == 0 || m == 0) return o2(b / c)%mod;
    if(n == 1) return (o2(b / c) + o2((a + b) / c))%mod;
    m %= mod;
    if(a >= c || b >= c) return
    (o2(a/c)%mod*n%mod*(n+1)%mod*(2*n+1)%mod*six%mod + o2(b/c)%mod*(n+1)%mod
    + (a/c)*(b/c)%mod*n%mod*(n+1)%mod +h(a % c, b % c, c, n) +
    2*(a/c)%mod*g(a % c, b % c, c, n)+2*(b/c)%mod*f(a % c, b % c, c, n))%mod;
    return (((m+1) * m%mod * n%mod - 2*g(c, c - b - 1, a, m - 1)%mod - 2*f(c,
    c - b - 1, a, m - 1)%mod - f(a,b,c,n))%mod+mod)%mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:/in.in", "r", stdin);
#endif
    int tim;
    int n, a, b, c;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%d%d%d%d", &n, &a, &b, &c);
        printf("%lld %lld %lld\n", f(a, b, c, n), h(a, b, c, n), g(a, b, c,
        n));
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
