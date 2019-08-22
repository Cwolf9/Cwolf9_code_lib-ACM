#include<bits/stdc++.h>
#define mme(a,b) memset((a),(b),sizeof((a))) 
using namespace std;
typedef long long LL;
const int N = 1e3 + 7;
const int INF = 0x3f3f3f3f;
typedef pair<int,int> pii;
int n, m;
struct lp{
  int t,l,v;
}cw[31];
int dp[100005];
bool cmp(lp &a, lp &b){
  return a.l-a.t<b.l-b.t;
}
int main(){
  while(~scanf("%d%d", &n,&m)){
    int tim = 0, tmp = 0;
    for(int i=1;i<=n;++i){
      scanf("%d%d%d", &cw[i].t,&cw[i].v,&cw[i].l);
      tim += cw[i].t; tmp = max(tmp, cw[i].l);
    }
    tim = max(tim,tmp);
    sort(cw+1,cw+1+n,cmp);
    mme(dp, 0);
    for(int i=1;i<=n;++i){
      for(int j=tim;j>=cw[i].t;--j){
        if(j>=cw[i].l){
          dp[j]=max(dp[j],dp[j-cw[i].t]+cw[i].v);
        }
      }
    }
    int ans=INF;
    for(int j=1;j<=tim;++j){
      if(dp[j]>=m){
        ans=j;break;
      }
    }
    if(ans!=INF)printf("%d\n", ans);
    else puts("zhx is naive!");
  }
  return 0;
}
