#include <bits/stdc++.h>
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
using namespace std;
const int mod = 998244353;
const int MXN = 2e5 + 5;
int n;
int64_t ar[MXN];
int64_t ksm(int64_t a, int64_t b, int kmod = mod) {
    int64_t res = 1;
    for(;b > 0; b >>= 1, a = (int64_t)a * a % kmod) 
        if(b & 1) res = (int64_t)res * a % kmod;
    return res;
}
void work() {
    cin >> n;
    int64_t ans = 0, all = ksm(2, n);
    ar[1] = 1, ar[2] = 1, ar[3] = 2;
    for(int i = 4; i <= n; ++i) ar[i] = (ar[i - 1] + ar[i - 2]) % mod;
    printf("%lld\n", ar[n] * ksm(all, mod - 2) % mod);
}
int main() {
    ios::sync_with_stdio(false);cin.tie(0);
    int tim = 1;
    // cin >> tim;
    for(int cas = 1; cas <= tim; ++ cas) work();
    return 0;
}
