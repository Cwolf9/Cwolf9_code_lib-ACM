#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
#define all(x) (x).begin(),(x).end()
#define mme(a,b) memset((a),(b),sizeof((a)))
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int MXN = 1e5 + 7;
const int MXE = 1e6 + 7;
const int INF = 0x3f3f3f3f;
const LL MOD = 1e9 + 7;
const LL mod = 1e9 + 7;

int n;
LL l, r;

const int MX = 1e5 + 7;
LL F[MX], invF[MX];
LL ksm(LL a, LL b){
  LL res = 1;
  for(;b;b>>=1,a=a*a%mod){
    if(b&1)res = res * a % mod;
  }
  return res;
}
void init() {
  F[0] = 1;
  for (int i = 1; i < MX; i++) F[i] = F[i - 1] * i % mod;
  invF[MX - 1] = ksm(F[MX - 1], mod - 2);
  for (int i = MX - 2; i >= 0; i--) invF[i] = invF[i + 1] * (i + 1) % mod;
}
LL COMB(int n, int m) {
  if(n == m)return 1;
  if(n < m) return 0;
  return F[n]*invF[m]%mod*invF[n-m]%mod;
}

LL bino[505][505], bpre[505][MXN];
int blocks = 500;
void yuchuli(){
  for(int i = 0; i < blocks; ++i){
    for(int j = 0; j < blocks; ++j){
      bino[i][j] = COMB(i,j);
    }
  }
  for(int i = 1; i < MXN/blocks; ++i){
    for(int j = 0; j < MXN; ++j){
      if(j==0)bpre[i][j] = COMB(blocks*i, j);
      else bpre[i][j] = (bpre[i][j-1] + COMB(blocks*i, j))%MOD;
    }
  }
}

int main(int argc, char const *argv[]){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  init();
  yuchuli();
  int tim = 1;
  scanf("%d", &tim);
  while(tim--){
    scanf("%lld%lld", &r, &l);
    /*if(r<blocks){
      LL ans = 0;
      for(int i = 0; i <= l; ++i)ans = (ans + bino[r][i])%MOD;
      printf("%lld\n", ans);
      continue;
    }*/
    LL p = r/blocks, re = r - p * blocks, ans = 0, tmp = min(l, re);
    //printf("%lld %lld\n", p, re);
    if(p == 0) p = 1;
    for(int i = 0; i <= tmp; ++i){
      ans = (ans + bino[re][i]*bpre[p][min(l-i, 0LL*500)])%MOD;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
//481494772

/*
#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define lowbit(x) (x&(-(x)))
#define mme(a,b) memset((a),(b),sizeof((a)))
#define test printf("**-**\n")
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int MXN = 2e5 + 7;
const int MXE = 1e6 + 7;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;

int n;

const int MX = 1e5 + 5;
LL F[MX], invF[MX];
LL ksm(LL a, LL b){
  LL res = 1;
  for(;b;b>>=1,a=a*a%mod){
    if(b&1)res = res * a % mod;
  }
  return res;
}
void init() {
  F[0] = 1;
  for (int i = 1; i < MX; i++) F[i] = F[i - 1] * i % mod;
  invF[MX - 1] = ksm(F[MX - 1], mod - 2);
  for (int i = MX - 2; i >= 0; --i) invF[i] = invF[i + 1] * (i + 1) % mod;
}
LL COMB(LL n, LL m) {
  if(n == m)return 1;
  if(n < m) return 0;
  return F[n]*invF[m]%mod*invF[n-m]%mod;
}
struct lp{
  int l, r, id;
}cw[MX];
int belong[MX];
LL ans, Ans[MX];
bool cmp(lp &a,lp &b){
  if(belong[a.l]!=belong[b.l])return belong[a.l]<belong[b.l];
  return a.r<b.r;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  init();
  scanf("%d", &n);
  int block = sqrt(MX*1.0);
  for(int i = 1; i < MX; ++i)belong[i] = (i-1)/block;
  for(int i = 1; i <= n; ++i){
    scanf("%d%d", &cw[i].r, &cw[i].l);
    cw[i].id = i;
  }
  sort(cw+1,cw+n+1,cmp);
  int L = 1, R = 0;
  ans = 1LL;
  LL two = ksm(2LL, mod-2);
  for(int i = 1; i <= n; ++i){
    while(R<cw[i].r)ans = ((ans * 2LL - COMB(R++, L))%mod+mod)%mod ;
    while(R>cw[i].r)ans = (ans + COMB(--R, L))*two%mod ;
    while(L<cw[i].l)ans = (ans + COMB(R,++L))%mod ;
    while(L>cw[i].l)ans = (ans - COMB(R,L--) + mod)%mod ;
    Ans[cw[i].id] = ans;
  }
  for(int i = 1; i <= n; ++i){
    printf("%lld\n", Ans[i]);
  }
  return 0;
}
*/

/*
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<cctype>
#include<string>
#include<cmath>
#include<bitset>
#include<cassert>
#include<ctime>
using namespace std;
typedef long long LL;
const LL mod = 1e9 + 7;
typedef pair<int,int> P;
const int MAX_N = 1e4+9;
int N,M,T,S;
LL F[MAX_N];
LL Jc[MAX_N];
LL ni_[MAX_N];
LL tran[309][MAX_N];
LL tr[509][509];
LL pow(LL a, LL n, LL p){
  LL ans = 1;
  while(n){
      if(n & 1) ans = ans * a % p;
      a = a * a % p;
      n >>= 1;
  }
  return ans;
}
LL niYuan(LL a, LL b){
  return pow(a, b - 2, b);
}
void calJc(){
  Jc[0] = Jc[1] = 1;
  for(LL i = 2; i < MAX_N; i++)
    Jc[i] = Jc[i - 1] * i % mod;
}
void calni(){
  for(int i=0;i<MAX_N;i++){
    ni_[i] = niYuan(Jc[i],mod);
  }
}
LL C(LL a, LL b){
  return Jc[a] * ni_[b] % mod* ni_[a-b] % mod;
}
void init(){
  F[0]=1;
  for(int i = 1; i <= 1000; ++i)F[i]=F[i-1]*2%mod;
  for(int i=1;i<MAX_N/500;i++){
    for(int j=0;j<MAX_N;j++){
      tran[i][j] = C(500*i,j);
      if(j>0) tran[i][j] = (tran[i][j] + tran[i][j-1])%mod;
    }
  }
  for(int i=0;i<509;i++){
    for(int j=0;j<509;j++){
      tr[i][j] = C(i,j);
    }
  }
}
int main(){
    calJc();
    calni();
    init();
    cin>>T;
    while(T--){
      LL a,b;
      scanf("%I64d%I64d",&a,&b);//C(a,b)
      b--;
      LL ans = 0;
      if(a < 500){
        for(int i=0;i<=b;i++)
          ans = (ans + tr[a][i])%mod;
      }else{
        LL t1 = a / 500;
        LL t2 = a - t1*500;
        for(int i=0;i<=min(b,t2);i++){
          ans = (ans + tr[t2][i]*tran[t1][min(b - i,t1*500)])%mod;
        }
      }
      LL tmp = F[a];
      ans = (tmp-ans+mod)%mod*pow(tmp,mod-2,mod)%mod;
      printf("%I64d\n",ans);
    }
    return 0;
}
*/