#include<bits/stdc++.h>
#define lowbit(x) (x&(-(x)))
#define mme(a,b) memset((a),(b),sizeof((a))) 
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
const int N = 1e6 + 7;
const int mod = 998244353;
const int INF = 0x3f3f3f3f;
typedef pair<int,int> pii;

int noprime[N],pm[N],pcnt=0;
void init(){
  noprime[0]=noprime[1]=1;
  for(int i=2;i<N;++i){
    if(!noprime[i])pm[pcnt++]=i;
    for(int j=0;j<pcnt&&i*pm[j]<N;++j){
      noprime[i*pm[j]]=1;
      if(i%pm[j]==0)break;
    }
  }
}
int ar[N],br[N],sum[N],pre[N];
int day[N],num[N];
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  init();
  int n;
  while(~scanf("%d", &n)){
    for(int i=1;i<=n;++i){
      scanf("%d",&ar[i]);
    }
    sum[0]=0;
    for(int i=1;i<=n;++i){
      scanf("%d",&br[i]);
      sum[i]=sum[i-1]+br[i];
    }
    priority_queue<int>Q;
    LL ans = 0;
    for(int i=1;i<=n;++i){
      ans=0;
      Q.push(ar[i]+sum[i-1]);
      if(!Q.empty()&&Q.top()<=sum[i]){
        ans+=Q.top()-sum[i-1];
        Q.pop();
      }
      ans+=br[i]*Q.size();
      printf("%lld\n", ans);
    }
  }  
  return 0;
}
