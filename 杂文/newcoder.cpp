//https://www.cnblogs.com/George1994/p/7821357.html
#include<bits/stdc++.h> 
#define lowbit(x) (x&(-(x)))
#define lson rt<<1
#define rson rt<<1|1
#define mme(a,b) memset((a),(b),sizeof((a)))  
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
#define fi first
#define se second
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
const int N = 1e5 + 7;
const int MX = 2e5 + 7;
int n, m, q, mod, root;
struct Tree{
  int l,r,d;
  LL Sum,lazy;
}sgt[N<<2];
struct POP{
  int id,u,v,w;
}op[N];
LL ar[N];
struct lp{
  int v,nex;
}cw[MX];
int head[MX],tot;
int inde;
int sz[MX],top[MX],son[MX],dep[MX],faz[MX];
int tid[MX],rnk[MX],rtid[MX];//id->dfsid//dfsid->id//lastid
void init(){
  tot=-1;inde=0;root=1;
  mme(head,-1);mme(son,-1);
  mme(sz,0);mme(dep,0);mme(faz,0);mme(top,0);
  mme(tid,0);mme(rtid,0);mme(rnk,0);
}
void push_up(int rt){
  sgt[rt].Sum=sgt[lson].Sum+sgt[rson].Sum;
}
void push_down(int rt){
  if(sgt[rt].lazy){
    int c = sgt[rt].lazy;
    sgt[lson].lazy+=c;
    sgt[rson].lazy+=c;
    sgt[lson].Sum+=sgt[lson].d*1LL*c;
    sgt[rson].Sum+=sgt[rson].d*1LL*c;
    sgt[rt].lazy=0;
  }
}
void build(int l,int r,int rt){
  sgt[rt].l=l;sgt[rt].r=r;
  sgt[rt].d=r-l+1;
  sgt[rt].lazy=0;
  if(l==r){
    sgt[rt].Sum=ar[rnk[l]];
    return;
  }
  int mid=(l+r)>>1;
  build(l,mid,lson);build(mid+1,r,rson);
  push_up(rt);
}
void update(int L,int R,int c,int rt){
  int l = sgt[rt].l,r=sgt[rt].r,mid=(l+r)>>1;
  if(sgt[rt].l>R||sgt[rt].r<L)return;
  if(L<=l&&r<=R){
    sgt[rt].lazy+=c;
    sgt[rt].Sum+=sgt[rt].d*1LL*c;
    return;
  }
  if(sgt[rt].l==sgt[rt].r)return;
  push_down(rt);
  if(L<=mid)update(L,R,c,lson);
  if(R>mid)update(L,R,c,rson);
  push_up(rt);
}
LL query(int L,int R,int rt){
  int l = sgt[rt].l,r=sgt[rt].r,mid=(l+r)>>1;
  if(L<=l&&r<=R){
    return sgt[rt].Sum;
  }
  if(sgt[rt].l>R||sgt[rt].r<L)return 0;
  if(sgt[rt].l==sgt[rt].r)return 0;
  push_down(rt);
  LL _sum = 0;
  if(L<=mid)_sum = query(L,R,lson);
  if(R>mid)_sum=_sum+query(L,R,rson);
  return _sum;
}
int LCA(int x,int y){
  int f1=top[x],f2=top[y];
  while(f1!=f2){
    if(dep[f1]<dep[f2])swap(f1,f2),swap(x,y);
    x=faz[f1],f1=top[x];
  }
  if(dep[x]<dep[y])swap(x,y);
  return y;
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
LL path_query(int x,int y){
  LL ans=0;
  int fx=top[x],fy=top[y];
  while(fx!=fy){//当两个点不在同一条链上 
    if(dep[fx]>=dep[fy]){//x的深度更深
      ans+=query(tid[fx],tid[x],1);//ans加上x点到x所在链顶端 这一段区间的点权和
      x=faz[fx];//把x跳到x所在链顶端的那个点的上面一个点
    }else {
      ans+=query(tid[fy],tid[y],1);
      y=faz[fy];
    }
    fx=top[x],fy=top[y];
  }//直到两个点处于一条链上
  if(tid[x]<tid[y]){//x点深度更低
    ans+=query(tid[x],tid[y],1);//加上此时两个点的区间和即可
  }else {
    ans+=query(tid[y],tid[x],1);
  }
  return ans;
}
void path_update(int x,int y,int c){
  int fx=top[x],fy=top[y];
  while(fx!=fy){
    if(dep[fx]>dep[fy]){
      update(tid[fx],tid[x],c,1);
      x=faz[fx];
    }else {
      update(tid[fy],tid[y],c,1);
      y=faz[fy];
    }
    fx=top[x],fy=top[y];
  }
  if(tid[x]<tid[y]){
    update(tid[x],tid[y],c,1);
  }else {
    update(tid[y],tid[x],c,1);
  }
}
void add_edge(int u,int v){
  cw[++tot].v=v;cw[tot].nex=head[u];
  head[u]=tot;
  cw[++tot].v=u;cw[tot].nex=head[v];
  head[v]=tot;
}
void pre_build(){
  dfs1(root,root,1);
  dfs2(root,root);
  build(1,n,1);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  scanf("%d%d",&n,&q);
  init();
  for(int i=1,u,v;i<n;++i){
    scanf("%d%d",&u,&v);
    add_edge(u,v);
  }
  pre_build();
  for(int t=1;t<=q;++t){
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    path_update(a, b, 1);
    if(path_query(c, d)) printf("Y\n");
    else printf("N\n");
    path_update(a, b, -1);
  }
  return 0;
}
