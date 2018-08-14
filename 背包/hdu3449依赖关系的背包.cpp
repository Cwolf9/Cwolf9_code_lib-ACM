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
const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
template<typename T>
inline T read(T&x){
  x=0;int f=0;char ch=getchar();
  while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
  while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
  return x=f?-x:x;
}
typedef pair<int,int> pii;
int n, m;
vector<pii> mp[N];
int ar[N],len[N],dp[N][100005];
//dp[i][j]前i个购物车用j元钱能获得的最大价值
int main(){
  int tim, tc = 0;
  while(~scanf("%d%d",&n,&m)){
    for(int i=1;i<=n;++i)mp[i].clear();
    for(int i = 1;i <= n;++i){
      read(ar[i]),read(len[i]);
      for(int j = 0;j < len[i];++j){
        int a, b;read(a), read(b);//a是花费，b是所得
        mp[i].push_back(make_pair(a,b));
        //printf("%d %d\n", a,b);
      }
    }
    mme(dp, 0);
    for(int i=1;i<=n;++i){
      //第i组要买至少一个
      for(int j=0;j<ar[i];++j)dp[i][j] = -1;//有依赖关系，要赋值-1
      for(int j=ar[i];j<=m;++j){
        dp[i][j] = dp[i-1][j-ar[i]];
      }
      for(int j=0;j<len[i];++j){
        for(int t=m;t>=mp[i][j].fi&&t>=ar[i];--t){
          if(dp[i][t-mp[i][j].fi]!=-1){ //注意依赖背包有不可能的情况
            dp[i][t]=max(
              dp[i][t-mp[i][j].fi]+mp[i][j].se,
              dp[i][t]);
          }
        }
      }
      //第i组不买
      for(int j=0;j<=m;++j)dp[i][j]=max(dp[i-1][j],dp[i][j]);
    }
    printf("%d\n", dp[n][m]);
  }
  return 0;
}


///滚动数组
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
const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
int n, m;
int dp[100005], tmp[100005];
int main(){
  while(~scanf("%d%d",&n,&m)){
    mme(dp, 0);
    for(int i=1;i<=n;++i){
      int x,num;scanf("%d%d",&x,&num);
      for(int j=0;j<=m;++j)tmp[j]=dp[j];
      for(int j=0;j<num;++j){
        int w,v;scanf("%d%d",&w,&v);
        for(int t=m;t>=w;--t){
          tmp[t]=max(tmp[t], tmp[t-w]+v);
        }
      }
      for(int j=x;j<=m;++j){
        dp[j] = max(dp[j], tmp[j-x]);
      }
    }
    printf("%d\n", dp[m]);
  }
  return 0;
}
