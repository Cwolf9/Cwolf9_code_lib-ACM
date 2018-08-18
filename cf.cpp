#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define mme(a,b) memset((a),(b),sizeof((a))) 
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 1e5 + 7;
const int M = 1e5 + 7;
const LL MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const double pi = acos(-1.0);
int n;
LL ar[N],br[N];
LL ksm(LL a, LL b){
  LL res=1;
  while(b){
    if(b&1)res=res*a%MOD;
    a=a*a%MOD;
    b>>=1;
  }
  return res;
}
LL get(LL l,LL r){
  if(l>r)return 0;
  return (l+r)*(r-l+1)/2;
}
LL gao(LL cnt,LL tmp){
  LL ans1=1;
  for(int i=1;i<=n;++i){
    LL L=ar[i],R=min(br[i],cnt);
    ans1=ans1*get(tmp+1-R,tmp+1-L)%MOD;
  }
  return ans1;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  int tim;
  scanf("%d", &tim);
  while(tim--){
    scanf("%d", &n);
    LL mmin=0,mmax=0,sum=1;
    for(int i=1;i<=n;++i){
      scanf("%I64d%I64d",&ar[i],&br[i]);
      mmin=max(mmin,ar[i]);
      mmax=max(mmax,br[i ]);
      sum=sum*(br[i]-ar[i]+1)%MOD;
    }
    LL ans = 0;
    for(LL m = mmin; m <= mmax;++m){       
      LL cnt = m, tmp = m;
      LL ans1=1,ans2=1;
      for(int i=1;i<=n;++i){
        LL L=ar[i],R=min(br[i],cnt);
        ans1=ans1*get(tmp+1-R,tmp+1-L)%MOD;
      }
      cnt=m-1;
      for(int i=1;i<=n;++i){
        LL L=ar[i],R=min(br[i],cnt);
        ans2=ans2*get(tmp+1-R,tmp+1-L)%MOD;
      }
      ans = (ans+ans1-ans2+MOD)%MOD;
    }
    printf("%I64d\n", ans*ksm(sum,MOD-2)%MOD);
  }
  return 0;
}

/*int n,a,b;
int mmax[N][30];
struct lp{
  int bea,mon;
}ar[N],br[N],aa;
bool cmp(lp &a,lp &b){
  return a.bea>b.bea;
}
bool cmp1(const lp &a,const lp &b){
  if(a.mon!=b.mon)return a.mon<b.mon;
  return a.bea>b.bea;
}
void RMQ(int n){
  for(int j=1;j<20;++j){
  for(int i=1;i<=n;++i){
      if(i+(1<<j)-1<=n){
        mmax[i][j]=max(mmax[i][j-1],mmax[i+(1<<(j-1))][j-1]);
      }
    }
  }
}
int get(int a,int b){
  int k=(int)(log(b-a+1.0)/log(2.0));
  return max(mmax[a][k],mmax[b-(1<<k)+1][k]);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  while(~scanf("%d%d%d", &n,&a,&b)){
    char s[2];
    int len1=0,len2=0;
    for(int i=0;i<n;++i){
      int x,y;
      scanf("%d%d%s",&x,&y,s);
      if(s[0]=='C'){
        ar[len1].bea=x;
        ar[len1].mon=y;
        ++len1;
      }else{
        br[len2].bea=x;
        br[len2].mon=y;
        ++len2;
      }
    }
    sort(ar,ar+len1,cmp);
    sort(br,br+len2,cmp);
    int f1=1,f2=1;
    int ans1=0,ans2=0,ans3=0;//交叉购买，C买，D买
    for(int i=0;i<len1;++i){
      if(ar[i].mon<=a){
        f1=0;
        ans1+=ar[i].bea;break;
      }
    }
    for(int i=0;i<len2;++i){
      if(br[i].mon<=b){
        f2=0;
        ans1+=br[i].bea;break;
      }
    }
    if(f1||f2)ans1=0;
    sort(ar,ar+len1,cmp1);
    sort(br,br+len2,cmp1);
    memset(mmax,0,sizeof(mmax));
    for(int i=1;i<=len1;++i){
      mmax[i][0]=ar[i-1].bea;
    }
    RMQ(len1);
    for(int i=1;i<=len1;++i){
      if(len1<2)continue;
      aa.mon=a-ar[i-1].mon;
      if(aa.mon<=0)continue;
      int p=lower_bound(ar,ar+len1,aa,cmp1)-ar;
      if(ar[0].mon>aa.mon)continue;
      if(p==len1)p--;
      while(p>=0&&ar[p].mon>aa.mon)p--;
      if(p<0)continue;
      if(p+1==i)p--;
      if(p<0)continue;
      ans2=max(ans2,aa.mon+get(1,p+1));
    }
    memset(mmax,0,sizeof(mmax));
    for(int i=1;i<=len2;++i){
      mmax[i][0]=br[i-1].bea;
    }
    RMQ(len2);
    for(int i=1;i<=len2;++i){
      if(len2<2)continue;
      aa.mon=b-br[i-1].mon;
      if(aa.mon<=0)continue;
      int p=lower_bound(br,br+len2,aa,cmp1)-br;
      if(br[0].mon>aa.mon)continue;
      if(p==len2)p--;
      while(p>=0&&ar[p].mon>aa.mon)p--;
      if(p<0)continue;
      if(p+1==i)p--;
      if(p<0)continue;
      ans3=max(ans3,aa.mon+get(1,p+1));
    }
    //printf("%d %d %d\n", ans1,ans2,ans3);
    printf("%d\n", max(max(ans1,ans2),ans3));
  }
  return 0;
}
*/
