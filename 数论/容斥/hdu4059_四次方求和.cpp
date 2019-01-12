#include<bits/stdc++.h>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
const int MXN = 2e6 + 7;
/*
sigme(i^4) = n(n+1)(2n+1)(3n^2+3n-1)/30
*/
LL n, thir;
LL ksm(LL a, LL b) {
    LL res = 1;
    for(;b;b>>=1,a=a*a%mod){
        if(b&1) res = res*a%mod;
    }
    return res;
}
LL exe(LL n) {
    return n*(n+1)%mod*(2*n+1)%mod*((3*n*n%mod+3*n-1)%mod+mod)%mod*thir%mod;
}
int main() {
    int tim;
    scanf("%d", &tim);
    thir = ksm(30, mod-2);
    while(tim --) {
        scanf("%lld", &n);
        LL tn = n;
        std::vector<int> vs;
        for(int i = 2; i * i <= n; ++i) {
            if(tn % i == 0) {
                while(tn % i == 0) tn /= i;
                vs.push_back(i);
            }
        }
        if(tn > 1) vs.push_back(tn);
        int tot = vs.size(), sta = 1 << tot;
        LL ans = exe(n);
        for(int i = 1; i < sta; ++i) {
            LL tmp = 1;
            int cnt = 0;
            for(int j = 0; j < tot; ++j) {
                if(i & (1 << j)) {
                    tmp *= vs[j];
                    ++ cnt;
                }
            }
            LL ret = n/tmp;
            if(cnt & 1) ans -= exe(ret)*tmp%mod*tmp%mod*tmp%mod*tmp%mod;
            else ans += exe(ret)*tmp%mod*tmp%mod*tmp%mod*tmp%mod;
            ans %= mod;
            ans = (ans + mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
