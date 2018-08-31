#include<bits/stdc++.h>
#define lowbit(x) (x)&(-(x))
#define all(x) x.begin(),x.end()
#define iis std::ios::sync_with_stdio(false)
#define mme(a,b) memset((a),(b),sizeof((a)))
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int MXN = 1e5+7;
const int N = 1e5+7;
const int INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
int n, m, k;
int flag, t;
int is[N];
int ar[N], ans[N*2], vis[N];
std::vector<int> g[N];
struct lh{
  int v,ip;
}aa,bb;
void dfs(int u){
    for(auto v:g[u]){
        if(vis[v] == 1){
            flag=1;
        }else if(vis[v]==0){
            vis[v] = 1;
            dfs(v);
        }
    }
    ans[t++] = u;
    vis[u] = 2;
}
void init(){
    t = 0;
    mme(is, 0);mme(vis, 0);
}
int main(){
  while(~scanf("%d %d",&n,&k)){
    init();
    for(int i = 0; i <= n; ++i)g[i].clear();
    for(int i = 0; i < k; ++i){
      scanf("%d", &ar[i]);
      is[ar[i]] = 1;
    }
    for(int i = 1, x; i <= n; ++i){
      scanf("%d", &x);
      g[i].resize(x);
      for(int j = 0; j < x; ++j){
        scanf("%d", &g[i][j]);
        //in[g[i][j]]++;
      }
    }
    flag = 0;
    for(int i = 0; i < k; ++i){
        if(vis[ar[i]]==0){
            dfs(ar[i]);
        }
    }
    if(flag){
        printf("-1\n");
        continue;
    }
    printf("%d\n", t);
    for(int i = 0; i < t; ++i)printf("%d ", ans[i]);
    printf("\n");
  }
  return 0;
}
