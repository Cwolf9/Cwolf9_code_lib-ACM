#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MXN = (1<<20) + 5;
const int mod = 1000000007;
int n, m;
int ar[MXN], f[MXN];
LL s[MXN], Ans[MXN], ans;
LL ksm(LL a, LL b) {LL res = 1;for(; b; b >>= 1, a = a * a % mod) if(b & 1) res = res * a % mod;return res;}
LL F[MXN], invF[MXN];
void init() {
    F[0] = invF[0] = 1;
    for(int i = 1; i < MXN; ++i) F[i] = F[i-1] * i % mod;
    invF[MXN - 1] = ksm(F[MXN-1], mod - 2);
    for(int i = MXN-2; i > 0; --i) invF[i] = invF[i+1] * (i + 1) % mod;
}
LL COMB(int n, int m) {
    if(m > n) return 0;
    if(m == n) return 1;
    return F[n] * invF[m] % mod * invF[n - m] % mod;
}
int main() {
    init();
    int tim;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &ar[i]);
            ++ f[ar[i]];
        }
        int sta = (1 << 20) - 1;
        for(int i = 0; i < 20; ++i) {
            for(int j = 0; j <= sta; ++j) {
                if((j >> i) & 1) {
                    f[j] += f[j - (1<<i)];
                }
            }
        }
        for(int i = 0; i <= sta; ++i) {
            s[i] = COMB(f[i], m);
            Ans[i] = s[i];
        }
        for(int i = 0; i < 20; ++i) {
            for(int j = 0; j <= sta; ++j) {
                if((j >> i) & 1) Ans[j] = (Ans[j] - Ans[j - (1<<i)] + mod) % mod;
            }
        }
        for(int i = 0; i <= sta; ++i) ans = (ans + Ans[i] * i % mod) % mod;
        printf("%lld\n", ans);
        for(int i = 0; i <= sta; ++i) f[i] = Ans[i] = s[i] = 0;
        ans = 0;
    }
    return 0;
}