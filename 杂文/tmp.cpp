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
const int MX = 2e5 + 7;
int n, m, q;
struct lp{
    int l, r, sum;
}cw[MX*20];
std::vector<int> mp[MX];
int inde, tid[MX], rtid[MX], rnk[MX];
int root[MX], vis[MX], tot_node;
void dfs(int u,int ba) {
    int len = mp[u].size();
    tid[u] = ++inde;
    rnk[inde] = u;
    for(int i = 0; i < len; ++i) {
        int v = mp[u][i];
        if(v == ba) continue;
        dfs(v, u);
    }
    rtid[u] = inde;
}
void update(int l,int r,int last,int &cur,int f,int p) {
    cw[++tot_node] = cw[last];
    cw[tot_node].sum = cw[last].sum + f;
    cur = tot_node;
    if(l == r) return;
    int mid = (l+r)>>1;
    if(p <= mid) update(l,mid,cw[last].l,cw[cur].l,f,p);
    else update(mid+1,r,cw[last].r,cw[cur].r,f,p);
}
int query(int l,int r,int cur) {
    if(l == r) return l;
    int mid = (l+r)>>1;
    int sum = cw[cw[cur].l].sum;
    if(sum) return query(l,mid,cw[cur].l);
    else if(cw[cw[cur].r].sum)return query(mid+1,r,cw[cur].r);
    else return 0;
}
int main(int argc, char const *argv[]) {
    while(~scanf("%d%d", &n, &q)) {
        
    }
    return 0;
}

