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
int n, m;
struct lp{
  int t,l,v;
}cw[31];
int dp[100005];
bool cmp(lp &a, lp &b){
  return a.l-a.t<b.l-b.t;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  io_begin();
  while(read(n)){
    read(m);
    int tim = 0, tmp = 0;
    for(int i=1;i<=n;++i){
      read(cw[i].t);read(cw[i].v);read(cw[i].l);
      //scanf("%d%d%d", &cw[i].t,&cw[i].v,&cw[i].l);
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






















/*
我发现很多时候有些题目并不是你能讲出理由来，能讲解给别人听，别人会写了，
就代表你真的懂这题了。acm题目无数，变数无数，没有人敢保证自己一定能
做出某类型的题(那些神仙除外)。

ctrl+shift+d：快速复制光标所在的一整行，并复制到该行之后。

ctrl+shift+up/down：交换两行顺序

ctrl+Alt+up/down：一直按上键或下键，选择内容进行操作。例如，代码整体向前，向后，部分代码(不是列断开，而是行断开，这点很厉害)向前向后移动。


*/