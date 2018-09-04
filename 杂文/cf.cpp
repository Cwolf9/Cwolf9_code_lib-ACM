//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<cstring>
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
#define lson rt<<1
#define rson rt<<1|1
#define all(x) (x).begin(),(x).end()
#define mme(a,b) memset((a),(b),sizeof((a)))
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int MXN = 2e5 + 7;
const int MXE = 1e6 + 7;
const int INF = 0x3f3f3f3f;
int n, m;
int ar[MXN], br[MXN];
struct lp{
  int l, r;
  int nd, sum, lazy;
}cw[MXN<<2];
void push_up(int rt){
  cw[rt].nd = min(cw[lson].nd, cw[rson].nd);
  cw[rt].sum = cw[lson].sum + cw[rson].sum;
}
void build(int l,int r,int rt){
  cw[rt].l = l; cw[rt].r = r;
  cw[rt].sum = cw[rt].lazy = 0;
  if(l == r){
    cw[rt].nd = br[l];
    return;
  }
  int mid = (l + r)>>1;
  build(l,mid,lson);build(mid+1,r,rson);
  push_up(rt);
}
void push_down(int rt){
  if(cw[rt].lazy){
    cw[lson].lazy += cw[rt].lazy;
    cw[rson].lazy += cw[rt].lazy;
    cw[lson].nd -= cw[rt].lazy;
    cw[rson].nd -= cw[rt].lazy;
    cw[rt].lazy = 0;
  }
}
void update(int L,int R,int l,int r,int rt){
  if(L<=l && r<= R){
    if(cw[rt].nd <= 1){
      if(l == r){
        --cw[rt].nd;
        if(cw[rt].nd <= 0){
          cw[rt].nd = br[l];
          cw[rt].sum++;
        }
        return;
      }
    }else{
      --cw[rt].nd;
      ++cw[rt].lazy;
      return;
    }
  }
  if(l == r)return;
  push_down(rt);
  int mid = (l+r)>>1;
  if(L > mid)update(L,R,mid+1,r,rson);
  else if(R <= mid)update(L,R,l,mid,lson);
  else {
    update(L,mid,l,mid,lson);
    update(mid+1,R,mid+1,r,rson);
  }
  push_up(rt);
}
int query(int L, int R,int l,int r,int rt){
  if(L <= l&&r <= R){
    return cw[rt].sum;
  }
  if(l == r)return 0;
  push_down(rt);
  int mid = (l+r)>>1, ans = 0;
  if(L > mid)ans = query(L,R,mid+1,r,rson);
  else if(R <= mid)ans = query(L,R,l,mid,lson);
  else {
    ans = query(L,mid,l,mid,lson);
    ans += query(mid+1,R,mid+1,r,rson);
  }
  return ans;
}
int main(int argc, char const *argv[]){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  while(~scanf("%d%d", &n, &m)){
    for(int i = 1; i <= n; ++i){
      scanf("%d", &br[i]);
    }
    char op[10];
    int a, b;
    build(1,n,1);
    while(m--){
      scanf("%s%d%d", op, &a, &b);
      if(op[0] == 'a'){
        update(a, b, 1, n, 1);
      }else{
        printf("%d\n", query(a, b, 1, n, 1));
      }
    }
  }
  return 0;
}