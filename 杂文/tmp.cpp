/*#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define pb push_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;


const int INF = 0x3f3f3f3f;
const LL mod = 998244353;
int n;
const int MAXN = 1e6 + 6;
LL F[MAXN], invF[MAXN];
LL ksm(LL a, int b) {
    LL res = 1;
    for(; b; b>>=1, a=a*a%mod) {
        if(b&1) res = res * a % mod;
    }
    return res;
}
void init() {
  F[0] = 1;
  for (int i = 1; i < MAXN; i++) F[i] = F[i - 1] * i % mod;//阶乘
  invF[MAXN - 1] = ksm(F[MAXN - 1], mod - 2);
  for (int i = MAXN - 2; i >= 0; i--) invF[i] = invF[i + 1] * (i + 1) % mod;//阶乘的逆元
}
LL COMB(int n, int m) {//组合数
  if(n < m) return 0; if(n == m)return 1;
  return F[n] * invF[m] % mod * invF[n-m] % mod;
}
LL two[111];
int main(){
    init();
    scanf("%d", &n);
    two[0] = 1;
    for(int i = 1; i <= n; ++i) two[i] = two[i-1] * 2 % mod;
    LL ans = 0;
    for(int i = 0; i <= n; ++i) {
        ans += COMB(n, i) * two[n-i] % mod;
        ans %= mod;
    }
    printf("%lld\n", ans);
    return 0;
}
*/
