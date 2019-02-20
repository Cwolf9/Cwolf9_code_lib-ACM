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
int ar[MXN];
int fa[MXN], rk[MXN];
std::vector<int> son[MXN];
pii bi[MXN];
int Fi(int x) {
    return fa[x] == x?x:fa[x] = Fi(fa[x]);
}
void un(int x, int y) {
    int pa = Fi(x), pb = Fi(y);
    if(pa == pb) return;
    if(rk[pa] < rk[pb]) swap(pa, pb);
    fa[pb] = pa;
    rk[pa] ++;
}
void dfs(int u, int ba) {
    for(auto v: son[u]) {
        if(v == ba) continue;
        if(ar[u] != ar[v] && ar[u] && ar[v]) ++ nd;
        dfs(v, u);
    }
}
int main(int argc, char const *argv[]){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]), fa[i] = i;
    for(int i = 1, a, b; i < n; ++i) {
        scanf("%d%d", &a, &b);
        if(ar[a] == ar[b]) {
            un(a, b);
        }
        bi[i] = {a, b};
    }
    for(int i = 1; i < n; ++i) {
        Fi(bi[i].fi); Fi(bi[i].se);
        if(fa[bi[i].fi] == fa[bi[i].se]) continue;
        son[fa[bi[i].fi]].push_back(fa[bi[i].se]);
        son[fa[bi[i].se]].push_back(fa[bi[i].fi]);
    }
    dfs(fa[1], -1);
    if(nd >= 2) printf("0\n");
    else if(nd == 1) printf("1\n");
    else printf("%d\n", n-1);
    return 0;
}