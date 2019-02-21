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
}*/

#include<bits/stdc++.h>
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
const int MXN = 3e5 + 7;

int n, nd;
int arr[MXN];
std::mt19937_64 generator(std::clock());
int main(int argc, char const *argv[]){
    freopen("E://ADpan//in.in", "w", stdout);  
    n = 100000;
    printf("%d\n", n);
    for(int i = 0; i < n; ++i) arr[i] = i + 1;
    std::shuffle(arr, arr + n, generator);
    for(int i = 0; i < n; ++i) printf("%d ", arr[i]); printf("\n");
    std::shuffle(arr, arr + n, generator);
    for(int i = 0; i < n; ++i) printf("%d ", arr[i]); printf("\n");
    return 0;
}