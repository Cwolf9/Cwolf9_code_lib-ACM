#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mod = 1e9 + 7;
typedef pair<int,int> P;
const int MAX_N = 1e5+9;
int N,M,T,S;
LL Jc[MAX_N];
LL ni_[MAX_N];
LL tran[309][MAX_N];
LL tr[509][509];
//费马小定理求逆元
LL pow(LL a, LL n, LL p)    //快速幂 a^n % p
{
    LL ans = 1;
    while(n)
    {
        if(n & 1) ans = ans * a % p;
        a = a * a % p;
        n >>= 1;
    }
    return ans;
}

LL niYuan(LL a, LL b)   //费马小定理求逆元
{
    return pow(a, b - 2, b);
}

void calJc()    //求maxn以内的数的阶乘
{
    Jc[0] = Jc[1] = 1;
    for(LL i = 2; i < MAX_N; i++)
        Jc[i] = Jc[i - 1] * i % mod;
}
void calni(){
    for(int i=0;i<MAX_N;i++){
        ni_[i] = niYuan(Jc[i],mod);
    }
}

LL C(LL a, LL b)    //计算C(a, b)
{
    return Jc[a] * ni_[b] % mod
        * ni_[a-b] % mod;
}

void init(){
    for(int i=1;i<MAX_N/500;i++){
        for(int j=0;j<MAX_N;j++){
            tran[i][j] = C(500*i,j);
            if(j>0) tran[i][j] = (tran[i][j] + tran[i][j-1])%mod;
        }
    }

    for(int i=0;i<509;i++){
        for(int j=0;j<509;j++){
            tr[i][j] = C(i,j);
        }
    }
}
int main(){
    calJc();
    calni();
    init();
    T = 1;
    //cin>>T;
    while(T--){
        LL a,b;
        scanf("%lld%lld",&a,&b);
        LL ans = 0;
        if(a < 500){
            for(int i=0;i<=b;i++)
                ans = (ans + tr[a][i])%mod;
        }
        else{
            LL t1 = a / 500;
            LL t2 = a - t1*500;
            for(int i=0;i<=min(b,t2);i++){
                ans = (ans + tr[t2][i]*tran[t1][min(b - i,t1*500)])%mod;
            }
        }
        printf("%lld\n",ans);

    }
    return 0;
}