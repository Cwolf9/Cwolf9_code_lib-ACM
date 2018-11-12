#include<bits/stdc++.h>
using namespace std;


/*

#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head
 
const int M=2010;
int n,m,x,k;
ll g[M],pw[M];
char s[M];
 
struct Hash_table {
    static const int V=1000003;
    int fst[V],nxt[V];
    int ctm,ptm[V],T;
    int val[V];
    vector<pair<ll,int>> key;
    void init() { T=0; ctm++; key.clear(); }
    void add(ll s) {
        int S=s%V;
        if (ptm[S]!=ctm) ptm[S]=ctm,fst[S]=-1;
        for (int j=fst[S];j!=-1;j=nxt[j]) if (key[j].fi==s) {
            key[j].se++;
            return;
        }
        nxt[T]=fst[S],fst[S]=T; key.pb(mp(s,1));
        T++;
    }
    int operator [](ll s) {
        int S=s%V;
        if (ptm[S]!=ctm) return 0;
        for (int j=fst[S];j!=-1;j=nxt[j]) if (key[j].fi==s)
            return key[j].se;
        return 0;
    }
}cnt;
 
void solve() {
    rep(j,0,m) g[j]=0;
    rep(i,0,n) {
        scanf("%s",s);
        rep(j,0,m) if (s[j]=='1') g[j]|=(1ll<<i);
    }
 
    ll ret=0;
    cnt.init();
    rep(i,0,m) cnt.add(g[i]);
 
    ll c0=cnt[0];
    ll rk1=m-c0; ll rk0=c0;
    ret=(ret+rk1*pw[n-1]+rk0*pw[n])%mod;
 
    ll rk2=m*(m-1)/2; rk0=c0*(c0-1)/2;
    rk1=0;
    for (auto p:cnt.key) if (p.fi!=0) rk1+=p.se*(p.se-1)/2+p.se*c0;
    rk2=rk2-rk1-rk0;
 
    if (n>=2) ret=(ret+6*rk2*pw[n-2])%mod;
    if (n>=1) ret=(ret+6*rk1*pw[n-1])%mod;
    if (n>=0) ret=(ret+6*rk0*pw[n])%mod;
 
//  printf("%d %d %d\n",rk0,rk1,rk2);
 
    ll rk3=m*(m-1)*(m-2)/6;
    rk0=c0*(c0-1)*(c0-2)/6;
    rk1=0; rk2=0;
 
 
    // rk1 p 0 0, p p 0, p p p
    for (auto p:cnt.key) if (p.fi!=0)
        rk1+=p.se*(p.se-1)*(p.se-2)/6+p.se*(p.se-1)/2*c0+p.se*c0*(c0-1)/2;
    // rk2 0 p q p q p^q p p q p q q
    for (auto p:cnt.key) if (p.fi!=0) {
        for (auto q:cnt.key) if (q.fi>p.fi) {
            rk2+=c0*p.se*q.se+(p.se-1)*p.se/2*q.se+(q.se-1)*q.se/2*p.se;
            ll w=p.fi^q.fi;
            if (w<p.fi) rk2+=cnt[w]*p.se*q.se;
        }
    }
    rk3=rk3-rk2-rk1-rk0;
 
//  printf("%d %d %d %d\n",rk0,rk1,rk2,rk3);
 
    if (n>=3) ret=(ret+6*rk3*pw[n-3])%mod;
    if (n>=2) ret=(ret+6*rk2*pw[n-2])%mod;
    if (n>=1) ret=(ret+6*rk1*pw[n-1])%mod;
    if (n>=0) ret=(ret+6*rk0*pw[n])%mod;
 
    if (ret<0) ret+=mod;
    printf("%lld\n",ret);
}
int _,__;
int main() {
    pw[0]=1;
    rep(i,1,51) pw[i]=pw[i-1]*2%mod;
    while (scanf("%d%d",&n,&m)!=EOF) solve();
}
*/
