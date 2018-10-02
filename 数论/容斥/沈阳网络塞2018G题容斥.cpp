//https://www.cnblogs.com/Cwolf9/p/9617408.html
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = (LL)1e9 + 7;
LL n, m, inv2, inv6;
vector<int> ve;
LL inv(LL t){
  return t == 1LL? 1LL: (MOD-MOD/t)*inv(MOD%t)%MOD;
}
LL get_num1(LL n){
  return n*(n+1)%MOD*inv2%MOD;
}
LL get_num2(LL n){
  return n*(n+1)%MOD*(2*n%MOD+1)%MOD*inv6%MOD;
}
int main(){
  inv2 = inv(2), inv6 = inv(6);
  while(~scanf("%lld%lld", &n, &m)){
    ve.clear();
    int tm = m;
    for(int i = 2; (LL)i * i <= m && i <= n; ++i){
      if(tm % i == 0){
        ve.push_back(i);
        while(tm % i == 0)tm /= i;
      }
      if(tm == 1)break;
    }
    if(tm != 1)ve.push_back(tm);
    int len = ve.size(), state = 1 << len;
    LL ans = (get_num1(n)+get_num2(n))%MOD;
    ans = 0;
    for(int i = 0; i < state; ++i){
      LL tot = 1, cnt;
      int num = 0;
      for(int j = 0; j < len; ++j){
        if(i&(1<<j)){
          ++num;
          tot *= ve[j];
        }
      }
      cnt = n/tot;
      //printf("*%lld %lld %d\n", tot,cnt,num);
      if(num % 2 == 0){
        ans = (ans+ tot*tot%MOD*get_num2(cnt)%MOD+tot*get_num1(cnt)%MOD)%MOD;
      }else{
        ans = (ans- tot*tot%MOD*get_num2(cnt)%MOD-tot*get_num1(cnt)%MOD)%MOD;
        ans = (ans + MOD)%MOD;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}