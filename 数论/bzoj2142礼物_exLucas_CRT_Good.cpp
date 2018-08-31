#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
typedef long long ll;
using namespace std;
ll mod,n,m,w[10],ans,x,y,module[10002],piset[10002],r[10002],num;

ll mod_pow(ll x,ll n,ll p){
    ll res=1;
    while(n){
        if(n&1) res=res*x%p;
        x=x*x%p;
        n>>=1;
    }
    return res;
}

ll extgcd(ll a,ll b,ll &x,ll &y){
    ll d=a;
    if(b)  d=extgcd(b,a%b,y,x),y-=a/b*x;
    else x=1,y=0;
    return d;
}

ll inv(ll t,ll mod){ extgcd(t,mod,x,y);return (x+mod)%mod;}

ll multi(ll n,ll pi,ll pk){//求非互质的部分 
    if (!n) return 1;
    ll ans=1;
    for (ll i=2;i<=pk;i++) if(i%pi) ans=ans*i%pk;
    ans=mod_pow(ans,n/pk,pk);
    for (ll i=2;i<=n%pk;i++) if(i%pi) ans=ans*i%pk;
    return ans*multi(n/pi,pi,pk)%pk;
}


ll exlucas(ll n,ll m,ll pi,ll pk){//组合数 c(n,m)mod pk=pi^k 
    if(m>n) return 0;
    ll a=multi(n,pi,pk),b=multi(m,pi,pk),c=multi(n-m,pi,pk);
    ll k=0;
    for(ll i=n;i;i/=pi) k+=i/pi;
    for(ll i=m;i;i/=pi) k-=i/pi;
    for(ll i=n-m;i;i/=pi) k-=i/pi;
    return a*inv(b,pk)%pk*inv(c,pk)%pk*mod_pow(pi,k,pk)%pk;//组合数求解完毕 
}

ll crt(int n,ll *r,ll *m){
    ll M=1,ret=0;
    for(int i=0;i<n;i++) M*=m[i];
    for(int i=0;i<n;i++){
        ll w=M/m[i];
        ret+=w*inv(w,m[i])*r[i];
        ret%=M;
    }
    return (ret+M)%M;
}

ll fz(ll n,ll *m,ll *piset){//分解质因子 
    ll num=0;
    for (ll i=2;i*i<=n;i++){
        if(n%i==0){
            ll pk=1;
            while(n%i==0) pk*=i,n/=i;
            m[num]=pk;
            piset[num]=i;
            num++;
        }
    }
    if(n>1) m[num]=n,piset[num]=n,num++;
    return num;
}

ll excomb(ll n,ll m){
    for(int i=0;i<num;i++){
        r[i]=exlucas(n,m,piset[i],module[i]);
    }
    return crt(num,r,module);
}


int main(){
    scanf("%lld",&mod);
    scanf("%lld%lld",&n,&m);
    ll sum=0;
    for(int i=1;i<=m;i++) scanf("%lld",&w[i]),sum+=w[i];
    if(n<sum){ puts("Impossible");return 0;}
    num=fz(mod,module,piset); 
    ans=1;
    for(int i=1;i<=m;i++){
        n-=w[i-1];
         ll a1=excomb(n,w[i]);
        ans=ans*a1%mod;
    }
    printf("%lld\n",ans);
    return 0;
}

/*
 * https://www.cnblogs.com/elpsycongroo/p/7620197.html
 * n!/(w1!*w2!*...*(n-sum)!)
*/
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
typedef long long ll;
using namespace std;
ll mod,P,n,m,w[10],ans,x,y,module[10002],piset[10002],r[10002],num,jc[10];

ll mod_pow(ll x,ll n,ll p){
    ll res=1;
    while(n){
        if(n&1) res=res*x%p;
        x=x*x%p;
        n>>=1;
    }
    return res;
}

ll extgcd(ll a,ll b,ll &x,ll &y){
    ll d=a;
    if(b)  d=extgcd(b,a%b,y,x),y-=a/b*x;
    else x=1,y=0;
    return d;
}

ll inv(ll t,ll mod){ extgcd(t,mod,x,y);return (x+mod)%mod;}

ll multi(ll n,ll pi,ll pk){//求非互质的部分 
    if (!n) return 1;
    ll ans=1;
    for (ll i=2;i<=pk;i++) if(i%pi) ans=ans*i%pk;
    ans=mod_pow(ans,n/pk,pk);
    for (ll i=2;i<=n%pk;i++) if(i%pi) ans=ans*i%pk;
    return ans*multi(n/pi,pi,pk)%pk;
}


ll exlucas(ll n,ll pi,ll pk){
    ll ans=multi(n,pi,pk); 
    for(int i=0;i<m;i++){
        jc[i]=multi(w[i+1],pi,pk);
        ans=ans*inv(jc[i],pk)%pk;
    }
    ll k=0;
    for(ll i=n;i;i/=pi) k+=i/pi;
    for(int i=1;i<=m;i++) for(ll j=w[i];j;j/=pi) k-=j/pi;
    return ans*mod_pow(pi,k,pk)%pk;
}

ll crt(int n,ll *r,ll *m){
    ll M=1,ret=0;
    for(int i=0;i<n;i++) M*=m[i];
    for(int i=0;i<n;i++){
        ll w=M/m[i];
        ret+=w*inv(w,m[i])*r[i];
        ret%=M;
    }
    return (ret+M)%M;
}

ll fz(ll n,ll *m,ll *piset){//分解质因子 
    ll num=0;
    for (ll i=2;i*i<=n;i++){
        if(n%i==0){
            ll pk=1;
            while(n%i==0) pk*=i,n/=i;
            m[num]=pk;
            piset[num]=i;
            num++;
        }
    }
    if(n>1) m[num]=n,piset[num]=n,num++;
    return num;
}

int main(){
    scanf("%lld",&mod);
    scanf("%lld%lld",&n,&m);
    ll sum=0;
    for(int i=1;i<=m;i++) scanf("%lld",&w[i]),sum+=w[i];
    if(n<sum){ puts("Impossible");return 0;}//puts会自动换行
    if (sum<n) w[++m]=n-sum;  
    num=fz(mod,module,piset); 
    for(int i=0;i<num;i++)    r[i]=exlucas(n,piset[i],module[i]);
    printf("%lld\n",crt(num,r,module));
    return 0;
}

