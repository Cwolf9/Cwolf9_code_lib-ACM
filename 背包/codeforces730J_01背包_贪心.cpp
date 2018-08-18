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
const int N = 1e3 + 7;
const int ME = 1e6 + 7;
const int mod = 998244353;
const int INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3f;
typedef pair<int,int> pii;
namespace IO {
  const int MX = 1e7;//1e7占用内存11000kb
  char buf[MX]; int c, sz;
  void io_begin() {
    c = 0;
    sz = fread(buf, 1, MX, stdin);
  }
  inline bool read(int &t) {
    while(c < sz && buf[c] != '-' && (buf[c] < '0' || buf[c] > '9')) c++;
    if(c >= sz) return false;
    bool flag = 0; if(buf[c] == '-') flag = 1, c++;
    for(t = 0; c < sz && '0' <= buf[c] && buf[c] <= '9'; c++) t = t * 10 + buf[c] - '0';
    if(flag) t = -t;
    return true;
  }
}
using namespace IO;
void _read(int &sum){
    sum=0;char ch=getchar();
    while(!(ch>='0'&&ch<='9'))ch=getchar();
    while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=getchar();
}
int n, m;
struct lp{
  int c,v;
}cw[N];
//类01背包
int dp[105][10005];
bool cmp(lp &a,lp &b){
  return a.v>b.v;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  io_begin();
  while(read(n)){
    int sum=0,sum1=0;
    for(int i=0;i<n;++i){
      read(cw[i].c);
      sum+=cw[i].c;
    }
    for(int i=0;i<n;++i){
      read(cw[i].v);
      sum1+=cw[i].v;
    }
    sort(cw,cw+n,cmp);
    int k=0,tm=0;
    for(int i=0;i<n&&tm<sum;++i,++k){
      tm+=cw[i].v;
    }
    //printf("%d\n", k);
    mme(dp, -1);
    dp[0][0]=0;
    tm = 0;
    for(int i=0;i<n;++i){
      tm+=cw[i].v;
      for(int j=k;j>=1;--j){//类01背包
        for(int h=tm;h>=0;--h){
          if(h>=cw[i].v&&dp[j-1][h-cw[i].v]>=0){
            dp[j][h]=max(dp[j-1][h-cw[i].v]+cw[i].c, dp[j][h]);
          }
        }
      }
    }
    int ans=0;
    for(int i=sum;i<=sum1;++i){
      ans=max(ans,dp[k][i]);
    }
    printf("%d %d\n", k, sum-ans);
  }
  return 0;
}
