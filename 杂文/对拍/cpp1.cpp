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
  init();
  yuchuli();
  int tim = 1;
  //scanf("%d", &tim);
  while(tim--){
    scanf("%lld%lld", &r, &l);
    LL p = r/blocks, re = r - p * blocks, ans = 0, tmp = min(l, re);
    //printf("%lld %lld\n", p, re);
    if(re==0) --p;
    for(int i = 0; i <= tmp; ++i){
      ans = (ans + bino[re][i]*bpre[p+1][min(l-i, p*500)]%MOD)%MOD;
    }
    printf("%lld\n", ans);
  }
  return 0;
}