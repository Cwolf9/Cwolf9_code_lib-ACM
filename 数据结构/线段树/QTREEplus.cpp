
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <cassert>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
typedef long long LL;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MX = 1e5 + 6;
const int MXE = 4e6 + 6;
int n;
struct lp{
    int v, nxt, w;
}E[MXE];
int head[MX], tot, rt[MX];
std::vector<pair<int,int> > bian;
struct Tree {
    int f[MX], p[MX], sz[MX], son[MX], top[MX], dep[MX], totp;
    ll sum[MX << 2], d[MX];
    void dfs(int u, int fa, int deep, int root) {
        f[u] = fa; dep[u] = deep;
        son[u] = 0; sz[u] = 1;
        rt[u] = root;
        for (int i = head[u]; ~i; i = E[i].nxt) {
            int v = E[i].v;
            if (v == fa) continue;
            dfs(v, u, deep + 1, root);
            sz[u] += sz[v];
            if (sz[son[u]] < sz[v]) son[u] = v;
        }
    }
    void rebuild(int u, int t) {
        top[u] = t; p[u] = totp++;
        if (son[u]) rebuild(son[u], t);
        for (int i = head[u]; ~i; i = E[i].nxt) {
            int v = E[i].v;
            if (v == f[u]) continue;
            if (v == son[u]) {
                d[p[v]] = E[i].w;
                continue;
            }
            rebuild(v, v);
            d[p[v]] = E[i].w;
        }
    }
    void prebuild() {
        totp = 1;
        dfs(1, 0, 1, 1);
        rebuild(1, 1);
        build(1, totp - 1, 1);
    }
    inline void PushUP(int rt) {
        sum[rt] = max(sum[rt << 1] , sum[rt << 1 | 1]);
    }
    void build(int l, int r, int rt) {
        sum[rt] = 0;
        if (l == r) {
            sum[rt] = d[l];
            return;
        }
        int m = (l + r) >> 1;
        build(lson), build(rson);
        PushUP(rt);
    }
    void update(int p, int c, int l, int r, int rt) {
        if (l == r) {
            sum[rt] = c;
            return;
        }
        int m = (l + r) >> 1;
        if (p <= m) update(p, c, lson);
        else update(p, c, rson);
        PushUP(rt);
    }
    ll query(int L, int R, int l, int r, int rt) {
        if (L <= l && R >= r) return sum[rt];
        int m = (l + r) >> 1;
        ll ret = 0;
        if (L <= m) ret = max(ret, query(L, R, lson));
        if (R > m) ret = max(ret, query(L, R, rson));
        return ret;
    }
    ll solve(int u, int v) {
        int f1 = top[u], f2 = top[v];
        ll ans = 0;
        while (f1 != f2) {
            if (dep[f1] < dep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            ans = max(ans, query(p[f1], p[u], 1, totp - 1, 1));
            u = f[f1]; f1 = top[u];
        }
        if (u != v) {
            if (dep[u] > dep[v]) swap(u, v);
            ans = max(ans, query(p[son[u]], p[v], 1, totp - 1, 1));
        }
        return ans;
    }
    inline void Update(int u, int v, int val) {//单边修改
        if(u == f[v]) swap(u, v);
        update(p[u], val, 1, totp - 1, 1);
    }
} t;
void add_edge(int u,int v,int w) {
    E[++tot].v=v;E[tot].w=w;E[tot].nxt=head[u];
    head[u]=tot;
    E[++tot].v=u;E[tot].w=w;E[tot].nxt=head[v];
    head[v]=tot;
}
int main() {
    int tim, fuck = 0;
    scanf("%d", &tim);
    while(tim --) {
        memset(head, -1, sizeof(head));
        tot = -1;
        bian.clear();
        scanf("%d", &n);
        bian.push_back({0, 0});
        for(int i = 1, x, y, z; i <= n - 1; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            add_edge(x, y, z);
            bian.push_back({x, y});
        }
        t.prebuild();
        char s[10];
        if(fuck) printf("\n");
        scanf("%s", s);
        while(s[0] != 'D') {
            int a, b;
            scanf("%d%d", &a, &b);
            if(s[0] == 'Q') {
                printf("%lld\n", t.solve(a, b));
            }else {
                t.Update(bian[a].first, bian[a].second, b);
            }
            scanf("%s", s);
        }
        fuck = 1;
    }
    return 0;
}



#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;
typedef long long LL;

const int MXN = 2e5 + 6;
const int MXE = 5e6 + 6;

struct lp{
    int v, w, nex;
}cw[MXE];
int head[MXN], tot, n;
int up[MXN][20];
LL dis[MXN];
int dep[MXN];
void add_edge(int u,int v,int w) {
    cw[++tot].v=v;cw[tot].w=w;cw[tot].nex=head[u];
    head[u]=tot;
    cw[++tot].v=u;cw[tot].w=w;cw[tot].nex=head[v];
    head[v]=tot;
}
void dfs(int u,int ba,int d) {
    up[u][0] = ba; dep[u] = d;
    for(int i = 1, cf; i < 20; ++i) {
        cf = up[u][i-1];
        up[u][i] = up[cf][i-1];
    }
    for(int i = head[u]; ~i; i = cw[i].nex) {
        int v = cw[i].v;
        if(v == ba) continue;
        dis[v] = dis[u] + cw[i].w;
        up[v][0] = u;
        dfs(v, u, d + 1);
    }
}
int LCA(int x,int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 19; i >= 0; --i) {
        if(dep[up[x][i]] >= dep[y]) {
            x = up[x][i];
        }
    }
    if(x == y) return x;
    for(int i = 19; i >= 0; --i) {
        if(up[x][i] != up[y][i]) {
            x = up[x][i];
            y = up[y][i];
        }
    }
    return up[x][0];
}
int main(){
    int tim, fuck = 0;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            head[i] = -1, dis[i] = 0;
            for(int j = 0; j < 20; ++j) {
                up[i][j] = 0;
            }
        }
        tot = -1;
        for(int i = 1, x, y, z; i <= n - 1; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            add_edge(x, y, z);
        }
        dfs(1, 0, 1);
        char s[10];
        scanf("%s", s);
        if(fuck) printf("\n");
        while(s[0] != 'D' || (s[0]=='D'&&s[1] != 'O')) {
            int x, y, k, cf;
            scanf("%d%d", &x, &y);
            if(s[0] == 'D') {
                cf = LCA(x, y);
                printf("%lld\n", dis[x] + dis[y] - 2 * dis[cf]);
            }else {
                scanf("%d", &k);
                cf = LCA(x, y);
                int tmp = dep[x] - dep[cf] + 1;
                if(k == 1) {
                    printf("%d\n", x);
                }else if(k < tmp) {
                    k --;
                    for(int i = 0; i < 20; ++i) {
                        if(k&(1<<i)) {
                            x = up[x][i];
                        }
                    }
                    printf("%d\n", x);
                }else if(k == tmp) {
                    printf("%d\n", cf);
                }else {
                    k = dep[x]-dep[cf]+dep[y]-dep[cf]+1-k;
                    for(int i = 0; i < 20; ++i) {
                        if(k&(1<<i)) {
                            y = up[y][i];
                        }
                    }
                    printf("%d\n", y);
                }
            }
            scanf("%s", s);
        }
    }
    return 0;
}



#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <cassert>
#include<bits/stdc++.h> 
#define lson rt<<1
#define rson rt<<1|1
#define mme(a,b) memset((a),(b),sizeof((a)))  
#define fuck(x) cout<<"* "<<x<<"\n"
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const int N = 2e5 + 7;
const int MX = 2e5 + 7;
int n, m, q;
struct Tree{
  int l,r,d,Sum;
}sgt[N<<2];
struct lp{
  int v,nex;
}cw[MX*2];
int head[MX],tot;
int inde;
int sz[MX],top[MX],son[MX],dep[MX],faz[MX];
int tid[MX],rnk[MX],rtid[MX];//id->dfsid//dfsid->id//lastid
void init(){
  tot=-1;inde=0;
  mme(head,-1);mme(son,-1);
  mme(sz,0);mme(dep,0);mme(faz,0);mme(top,0);
  mme(tid,0);mme(rtid,0);mme(rnk,0);
}
void push_up(int rt){
  if(sgt[lson].Sum) sgt[rt].Sum=sgt[lson].Sum;
  else sgt[rt].Sum=sgt[rson].Sum;
}
void build(int l,int r,int rt){
  sgt[rt].l=l;sgt[rt].r=r;
  sgt[rt].Sum=0;
  if(l==r) return;
  int mid=(l+r)>>1;
  build(l,mid,lson);build(mid+1,r,rson);
}
void update(int p,int rt){
  int l = sgt[rt].l,r=sgt[rt].r,mid=(l+r)>>1;
  if(l == r){
    if(sgt[rt].Sum == 0)sgt[rt].Sum=l;
    else sgt[rt].Sum=0;
    return;
  }
  if(p<=mid)update(p,lson);
  else update(p,rson);
  push_up(rt);
}
int query(int L,int R,int rt){
  int l = sgt[rt].l,r=sgt[rt].r,mid=(l+r)>>1;
  //if(sgt[rt].l>R||sgt[rt].r<L)return INF;
  if(L<=l&&r<=R){
    return sgt[rt].Sum;
  }
  if(L > mid) {
    return query(L,R,rson);
  }else if(R <= mid) {
    return query(L,R,lson);
  }else {
    int t1 = query(L,mid,lson);
    if(t1) return t1;
    return query(mid+1,R,rson);
  }
}
void dfs1(int u,int fat,int depth){
  dep[u] = depth;faz[u] = fat;sz[u] = 1;
  for(int i=head[u];~i;i=cw[i].nex){
    int v = cw[i].v;
    if(v==fat)continue;
    dfs1(v,u,depth+1);
    sz[u] += sz[v];
    if(son[u]==-1||sz[v]>sz[son[u]]){
      son[u] = v;
    }
  }
}
void dfs2(int u,int t){
  top[u] = t;
  tid[u] = ++inde;
  rnk[inde]=u;
  if(son[u]==-1){
    rtid[u]=inde;
    return;
  }
  dfs2(son[u],t);
  for(int i=head[u];~i;i=cw[i].nex){
    int v = cw[i].v;
    if(v!=son[u]&&v!=faz[u]){
      dfs2(v,v);
    }
  }
  rtid[u]=inde;
}
int path_query(int x,int y){
  int ans=0,tmp=0;
  int fx=top[x],fy=top[y];
  while(fx!=fy){
    if(dep[fx]>=dep[fy]){
      tmp=query(tid[fx],tid[x],1);
      x=faz[fx];
    }else {
      tmp=query(tid[fy],tid[y],1);
      y=faz[fy];
    }
    if(tmp) ans = tmp;
    fx=top[x],fy=top[y];
  }
  if(tid[x]<tid[y]){
    tmp=query(tid[x],tid[y],1);
  }else {
    tmp=query(tid[y],tid[x],1);
  }
  if(tmp) ans = tmp;
  return ans;
}
void add_edge(int u,int v){
  cw[++tot].v=v;cw[tot].nex=head[u];
  head[u]=tot;
  cw[++tot].v=u;cw[tot].nex=head[v];
  head[v]=tot;
}
void pre_build(){
  dfs1(1,1,1);
  dfs2(1,1);
  build(1,n,1);
}
int main(){
  while(~scanf("%d%d",&n,&q)){
    init();
    for(int i=1,u,v;i<n;++i){
      scanf("%d%d",&u,&v);
      add_edge(u,v);
    }
    pre_build();
    int op, u;
    while(q--){
      scanf("%d%d", &op, &u);
      if(op==1){
        int tmp = path_query(1,u);
        if(tmp == 0) printf("-1\n");
        else printf("%d\n", rnk[tmp]);
      }else {
        update(tid[u],1);
      }
    }
  }
  return 0;
}
