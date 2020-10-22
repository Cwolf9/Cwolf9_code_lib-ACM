#include "bits/stdc++.h"
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define pb push_back
#define mp make_pair
#define FI first
#define SE second
#define maxn 100000
#define mod 1000000007
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef double db;

struct P
{
    ll x,y;
    P():x(0),y(0){}
    P(ll x,ll y):x(x),y(y){}
    P operator -(const P &a) const {return P(x-a.x,y-a.y);}
    P operator *(const ll &a) const {return P(x*a,y*a);}
};

void gcd(P &a,P &b)
{
    while(a.x!=0)
    {
        ll t=b.x/a.x;
        b=b-a*t;
        swap(a,b);
    }
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
int main()
{
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int CAS; scanf("%d",&CAS); rep(cas,1,CAS)
    {
        P a,p;
        int n; scanf("%d",&n);
        ll ans=0;
        while(n--)
        {
            int op;
            ll x,y; scanf("%d%lld%lld",&op,&x,&y);
            if(op==1)
            {
                P b(x,y);
                gcd(b,a);
                if(b.y) p.y=__gcd(p.y,abs(b.y));
                if(p.y) a.y%=p.y;
                debug(a.x, a.y, p.x, p.y)
            }
            if(op==2)
            {
                P q(x,y); int w; scanf("%d",&w);
                if(x)
                {
                    if(a.x==0 || x%a.x!=0) continue;
                    ll t=x/a.x;
                    y-=t*a.y;
                }
                if(y==0) ans+=w;
                else if(p.y && y%p.y==0) ans+=w;
            }
        }
        printf("Case #%d: %lld\n",cas,ans);
    }
    return 0;
}