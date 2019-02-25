/*#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define pb push_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;


const int INF = 0x3f3f3f3f;
const LL mod = 998244353;
const int MXN = 1e4 + 7;

LL n, m;
int ar[MXN];
LL dp[19][19][3000];
LL dfs(int pos,int mid,int cur,bool limit){
  if(pos==-1) return cur==0;
  if(cur<0) return 0;
  if(!limit&&dp[pos][mid][cur]!=-1)return dp[pos][mid][cur];
  int up = limit? ar[pos]: 9;
  LL sum = 0;
  for(int i = 0; i <= up; ++i){
    int tmp = (pos-mid)*i;
    sum += dfs(pos-1,mid,cur+tmp,limit&&i==ar[pos]);
  }
  if(!limit) dp[pos][mid][cur] = sum;
  return sum;
}
LL solve(LL x){
  if(x<0) return 0;
  else if(x==0) return 1;
  int pos = 0;
  while(x){
    ar[pos++] = x % 10;
    x /= 10;
  }
  LL sum = 0;
  for(int i = pos-1; i >= 0; --i){
    sum += dfs(pos-1, i, 0, 1);
  }
  return sum-(pos-1);
}
int main(int argc, char const *argv[]) {
    memset(dp, -1, sizeof(dp));
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", solve(m)-solve(n-1));
    return 0;
}
*/
#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define eb emplace_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
#define BASE_MAX 62
 
const int INF = 0x3f3f3f3f;
const int mod = 10086;
const int MXN = 1e6 + 7;
int n;

int main(int argc, char const *argv[]) {
#ifndef ONLINE_JUDGE
    //freopen("E://ADpan//in.in", "r", stdin);
    freopen("E://ADpan//in.in", "w", stdout);  
#endif
    for(int i = 0; i < 99999; ++i) printf("c");
    printf("\n");
    printf("#\n");
    return 0;
}