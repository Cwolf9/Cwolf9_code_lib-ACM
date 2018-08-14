#include<bits/stdc++.h>
#define lowbit(x) (x&(-(x)))
#define mme(a,b) memset((a),(b),sizeof((a))) 
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
const int N = 1e2 + 7;
const int mod = 998244353;
const int INF = 0x3f3f3f3f;
int n, sum;
int s[N][2], dp[200005];
int a[200005];//a[i]表示i体积的最大收益下你选择了多少个物品
int main(){
  while(~scanf("%d", &n)){
    int m = 0;
    for(int i=1;i<=n;++i){
      scanf("%d%d", &s[i][0],&s[i][1]);
      s[i][0]+=1000;
      m += s[i][0];
    }
    mme(dp, 0x80);mme(a, 0);
    dp[0] = 0;
    for(int i = 1; i <= n; ++i){
      for(int j = m; j >= s[i][0]; --j){
        if(dp[j]-a[j]*1000<dp[j-s[i][0]]+s[i][1]-(a[j-s[i][0]]+1)*1000){
          dp[j] = dp[j-s[i][0]]+s[i][1];
          a[j] = a[j-s[i][0]] + 1;
        }
      }
    }
    int mmax=0;
    for(int i=0;i<=m;++i){
      if(i-a[i]*1000<0||dp[i]<0)continue;
      mmax = max(mmax, dp[i]+i-a[i]*1000);
    }
    printf("%d\n", mmax);
  }
  return 0;
}
