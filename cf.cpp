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
  const int MX = 1e7; //1e7占用内存11000kb
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
int n, m1, m2;
struct lp{
  int p,h;
  lp(){}
  lp(int a,int b){p=a,h=b;}
}cw[305],pp[305];
int dp[505][55][2];
//if Third dimension is 1 we use the free chance, vice versa
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  io_begin();
  int tc=0;
  while(read(m1)){
    read(m2);read(n);
    if(m1+m2+n==0)break;
    int n1 = 0,n2 = 0;
    for(int i=1,p,h,s;i<=n;++i){
      read(p);read(h);read(s);
      if(s)pp[n1++] = lp(p,h);
      else cw[n2++] = lp(p,h);
    }
    mme(dp, 0);
    int sum1=0;
    for(int i=0;i<n1;++i){
      sum1+=pp[i].h;
      for(int j=m1;j>=0;--j){
        for(int k=m2;k>=0;--k){
          dp[j][k][1]=max(dp[j][k][0]+pp[i].h,dp[j][k][1]);
          if(j-pp[i].p>=0)dp[j][k][1]=max(
            dp[j-pp[i].p][k][1]+pp[i].h,
            dp[j][k][1]
          );
          if(k-pp[i].p>=0)dp[j][k][1]=max(
            dp[j][k-pp[i].p][1]+pp[i].h,
            dp[j][k][1]
          );
          if(j-pp[i].p>=0)dp[j][k][0]=max(
            dp[j-pp[i].p][k][0]+pp[i].h,
            dp[j][k][0]
          );
          if(k-pp[i].p>=0)dp[j][k][0]=max(
            dp[j][k-pp[i].p][0]+pp[i].h,
            dp[j][k][0]
          );
        }
      }
    }
    int flag=0;
    for(int j=0;j<2;++j){
      if(dp[m1][m2][j]==sum1)flag=1;
    }
    printf("Case %d: ", ++tc);
    if(!flag){
      printf("-1\n\n");
      continue;
    }
    for(int i=0;i<n2;++i){
      for(int j=m1;j>=0;--j){
        for(int k=m2;k>=0;--k){
          if(dp[j][k][0]>=sum1)dp[j][k][1]=max(dp[j][k][0]+cw[i].h,dp[j][k][1]);
          if(j-cw[i].p>=0&&dp[j-cw[i].p][k][1]>=sum1)dp[j][k][1]=max(
            dp[j-cw[i].p][k][1]+cw[i].h,
            dp[j][k][1]
          );
          if(k-cw[i].p>=0&&dp[j][k-cw[i].p][1]>=sum1)dp[j][k][1]=max(
            dp[j][k-cw[i].p][1]+cw[i].h,
            dp[j][k][1]
          );
          if(j-cw[i].p>=0&&dp[j-cw[i].p][k][0]>=sum1)dp[j][k][0]=max(
            dp[j-cw[i].p][k][0]+cw[i].h,
            dp[j][k][0]
          );
          if(k-cw[i].p>=0&&dp[j][k-cw[i].p][0]>=sum1)dp[j][k][0]=max(
            dp[j][k-cw[i].p][0]+cw[i].h,
            dp[j][k][0]
          );
        }
      }
    }
    for(int j=0;j<2;++j){
      sum1=max(sum1,dp[m1][m2][j]);
    }
    printf("%d\n\n", sum1);
  }
  return 0;
}






















/*
我发现很多时候有些题目并不是你能讲出理由来，能讲解给别人听，别人会写了，
就代表你真的懂这题了。acm题目无数，变数无数，没有人敢保证自己一定能
做出某类型的题(那些神仙除外)。

ctrl+shift+d：快速复制光标所在的一整行，并复制到该行之后。

ctrl+shift+up/down：交换两行顺序

ctrl+Alt+up/down：一直按上键或下键，选择内容进行操作。例如，代码整体向前，向后，部分代码(不是列断开，而是行断开，这点很厉害)向前向后移动。


*/