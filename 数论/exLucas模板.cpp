//http://codeforces.com/gym/100633/problem/J
#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
#define fi first
#define se second
#define lowbit(x) (x&(-(x)))
#define mme(a,b) memset((a),(b),sizeof((a))) 
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
const int N = 5e1 + 7;
const int ME = 1e6 + 7;
const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;

LL n, m, Mod;

LL ksm(LL a, LL b, LL mod){
  LL res = 1;
  for(;b;b>>=1,a=a*a%mod){
    if(b&1)res = res * a % mod;
  }
  return res;
}
void exgcd(LL a,LL b,LL &x,LL &y){
    if (!b) x=1LL,y=0LL;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
LL Inv(LL A,LL mod){
    if (!A) return 0LL;
    LL a=A,b=mod,x=0LL,y=0LL;
    exgcd(a,b,x,y);
    x=((x%b)+b)%b;
    if (!x) x+=b;
    return x;
}
LL Mul(LL n,LL pi,LL pk){
    if (!n) return 1LL;
    LL ans=1LL;
    if (n/pk){
      for (LL i=2;i<=pk;++i)
        if (i%pi) ans=ans*i%pk;
      ans=ksm(ans,n/pk,pk);
    }
    LL r = n%pk;
    for (LL i=2;i<=r;++i)//不足的部分
      if (i%pi) ans=ans*i%pk;
    return ans*Mul(n/pi,pi,pk)%pk;//再递归一层算(n/pi)!
}
LL COMB(LL n,LL m,LL mod,LL pi,LL pk){
    if (n<m) return 0;
    LL a=Mul(n,pi,pk),b=Mul(m,pi,pk),c=Mul(n-m,pi,pk);
    LL k=0LL,ans;
    for (LL i=n;i;i/=pi) k+=i/pi;
    for (LL i=m;i;i/=pi) k-=i/pi;
    for (LL i=n-m;i;i/=pi) k-=i/pi;
    ans=a*Inv(b,pk)%pk*Inv(c,pk)%pk*ksm(pi,k,pk)%pk;
    return ans*(mod/pk)%mod*Inv(mod/pk,pk)%mod;//CRT合并
}
LL exLucas(LL n, LL m, LL mod){
  LL ans = 0;
  for (LL x=Mod,i=2;i<=Mod;++i){
    if (x%i==0){
      LL pk = 1LL;
      while (x%i==0) pk*=i,x/=i;
      ans=(ans+COMB(n,m,Mod,i,pk))%Mod;
    }
  }
  return ans;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  while(~scanf("%I64d%I64d%I64d",&n,&m,&Mod)){
    printf("%I64d\n",exLucas(n, m, Mod));
  }
}

https://www.cnblogs.com/keshuqi/p/6251525.html
https://www.xuebuyuan.com/3184511.html
https://blog.csdn.net/Mys_C_K/article/details/80861651
https://www.cnblogs.com/hsd-/p/7273574.html
https://blog.csdn.net/lxy767087094/article/details/78215600