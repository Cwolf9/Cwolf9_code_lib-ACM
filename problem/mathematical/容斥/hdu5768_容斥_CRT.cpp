#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<time.h>

using namespace std;
typedef long long LL;
const int MXN = 1e6 + 6;
const int INF = 1e9;
/*分析：
先取出前两项
(r1 ≡ r1(mod a1))-->
N ≡ r1(mod a1)
N ≡ r2(mod a2)
N = r1+a1*x = r2+a2*y
--> a1*x - a2*y = r2-r1 --> exgcd()
考虑: a1*X - a2*Y = gcd(a1,a2)
a1*x/gcd - a2*y/gcd = R/gcd
(a1/gcd*x)%(a2/gcd)≡(R/gcd)%(a2/gcd)
令mod = a2/gcd
-->x = (X*(r2-r1)/gcd + mod)%mod
r1 = a1*x + r1
a1 = a1*a2/gcd
*/
int n;
LL ar[MXN], r[MXN];
LL gcd(LL a,LL b){
    while(b^=a^=b^=a%=b);
    return a;
}
inline void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
    if(b==0){
        x=1;y=0;
        d=a;
        return;
    }
    exgcd(b,a%b,d,y,x);
    y -= a/b*x;
    return;
}
LL ksc(LL a, LL b, LL mod) {
    LL res = 0;
    while(b) {
        if(b & 1) res = (res + a)%mod;
        b >>= 1;
        a = (a + a) % mod;
    }
    return res;
}
LL mul(LL a,LL b,LL mo){
    LL tmp=(a*b-(LL)((long double)a/mo*b+1e-8)*mo);
    return tmp<0?tmp+mo:(tmp>=mo?tmp-mo:tmp);
}
LL rongchi(LL MAX) {
    int sta = 1 << n;
    LL ans = 0;
    for(int i = 1; i < sta; ++i) {
        int cnt = 0;
        LL a = 7, r1 = 0, R, d, x, y, dm, M = 7, rj, arj;
        for(int j = 0; j < n; ++j)
            if(i & (1 << j)) M = M * ar[j];
        for(int j = 0; j < n; ++j) {
            if(i & (1 << j)) {
                ++ cnt; rj = r[j], arj = ar[j];
                if(r[j] < r1) {
                    LL tmp = rj; rj = r1; r1 = tmp;
                    tmp = arj; arj = a; a = tmp; 
                }
                exgcd(a, arj, d, x, y);
                R = rj - r1;
                dm = arj / d;
                //x=((x* R/d)%dm+dm)%dm;
                x = (ksc(x, R, dm)+dm)%dm;
                r1 += a * x;
                a *= dm;
            }
        }
        if(r1>a)printf("**\n");
        a = MAX / M;
        if(MAX % M >= r1) ++ a;
        if(cnt & 1) {
            ans += a;
        }else {
            ans -= a;
        }
    }
    return ans;
}
int main(){
    int tim, cas = 0;
    scanf("%d",&tim);
    while(tim--){
        LL x, y;
        scanf("%d%lld%lld",&n, &x, &y);
        for(int i = 0; i < n; ++i){
            scanf("%lld%lld", &ar[i], &r[i]);
        }
        LL ans = y / 7 - (x-1) / 7 - rongchi(y) + rongchi(x - 1);
        printf("Case #%d: %lld\n", ++cas, ans);
    }
    return 0;
}
