#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
typedef long long LL;

const int MXN = 5e5 + 6;
const int INF = 0x3f3f3f3f;
const int mod = 1000000009;

int n, m;
LL sum[MXN<<2], ar[MXN];
LL ksm(LL a,LL b) {
    LL res = 1;
    for(;b;b>>=1,a=a*a%mod) {
        if(b&1) res = res * a %mod;
    }
    return res;
}
int main() {
    //F(n) = √5/5[((1+√5)/2)^n-((1-√5)/2)^n]
    //383008016^2 ≡ 5 (mod 1e9 + 9)
    //383008016 ≡ sqrt(5) (mod 1e9 + 9)
    printf("%lld\n", ksm(383008016,mod-2));//1/sqrt(5)≡276601605(mod)
    printf("%lld\n", 383008017*ksm(2,mod-2)%mod);//(1+sqrt(5))/2≡691504013(mod)
    printf("%lld\n", (mod-383008016+1)*ksm(2,mod-2)%mod);//(1-sqrt(5))/2≡308495997(mod)
    scanf("%d%d", &n, &m);
    ar[1] = ar[2] = 1;
    for(int i = 3; i <= n; ++i) ar[i] = ar[i-1] + ar[i-2];
    return 0;
}
