/*
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

int n, m, k;
int dp[1005][35];//dp[i][j]表示i体积下的第j优解的价值，dp[i][1]表示最大值
int s[1005][2];//0表价值，1表体积
int a[1005], b[1005];//合并前k优解，k个不一样的值
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  int tim;
  scanf("%d", &tim);
  while(tim--){
    scanf("%d%d%d", &n, &m, &k);
    for(int i=1;i<=n;++i){
      scanf("%d", &s[i][0]);
    }
    for(int i=1;i<=n;++i){
      scanf("%d", &s[i][1]);
    }
    mme(dp, 0);
    for(int i=1;i<=n;++i){
      for(int j=m;j>=s[i][1];--j){
        for(int t=1;t<=k;++t){
          a[t] = dp[j][t];
          b[t] = dp[j-s[i][1]][t]+s[i][0];
        }
        a[k+1] = b[k+1] = -1;
        int x=1,y=1,w=1;
        while(w<=k&&(x<=k||y<=k)){
          if(a[x]>=b[y]){
            dp[j][w]=a[x];
            ++x;
          }else{
            dp[j][w]=b[y];
            ++y;
          }
          if(w==1||dp[j][w]!=dp[j][w-1])++w;
        }
      }
    }
    printf("%d\n", max(dp[m][k], 0));
  }
  return 0;
}
*/
