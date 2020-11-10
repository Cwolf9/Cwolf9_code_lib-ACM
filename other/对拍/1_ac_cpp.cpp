#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 2e5 + 7;
const int INF = 0x3f3f3f3f;
vector<int>G[maxn];
struct Tree {
    int l,r;
    int lazy;
    int mi,val;
    int val2;
}t[maxn << 2];

void pushdown(int i) {
    if(t[i].lazy) {
        t[i * 2].lazy = t[i].lazy;
        t[i * 2 + 1].lazy = t[i].lazy;
        
        t[i * 2].val = t[i].lazy;
        t[i * 2 + 1].val = t[i].lazy;
        
        t[i * 2].mi = t[i].lazy - t[i * 2].r + 1;
        t[i * 2 + 1].mi = t[i].lazy - t[i * 2 + 1].r + 1;
        
        t[i].lazy = 0;
    }
}
void pushup(int i) {
    t[i].mi = min(t[i * 2].mi,t[i * 2 + 1].mi);
    t[i].val = min(t[i * 2].val,t[i * 2 + 1].val);
}
void build(int i,int l,int r) {
    t[i].l = l;t[i].r = r;
    if(l == r) {
        t[i].mi = 1e9;
//        t[i].val = 1e9;
        return;
    }
    int m = (l + r) >> 1;
    build(i * 2,l,m);
    build(i * 2 + 1,m + 1,r);
    pushup(i);
}
void update(int i,int x,int y,int v) {
    if(x > y) return;
    if(x <= t[i].l && t[i].r <= y) {
        t[i].mi = v - t[i].r + 1;
        t[i].val = v;
        t[i].lazy = v;
        return;
    }
    pushdown(i);
    int m = (t[i].l + t[i].r) >> 1;
    if(x <= m) update(i * 2,x,y,v);
    if(y > m) update(i * 2 + 1,x,y,v);
    pushup(i);
}
int query(int i,int x,int y,int v) {
    if(t[i].l == t[i].r) return t[i].l;
    pushdown(i);
    int m = (t[i].l + t[i].r) >> 1;
    int res = -1;
    if(y > m && t[i * 2 + 1].val < v) res = query(i * 2 + 1,x,y,v);
    if(res == -1 && x <= m && t[i * 2].val < v) res = query(i * 2,x,y,v);
    return res;
}
int main() {
    int n,m;scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i++) {
        G[i].push_back(0);
    }
    for(int i = 1;i <= n;i++) {
        int x;scanf("%d",&x);
        G[x].push_back(i);
    }
    build(1,1,n);
    for(int i = 1;i <= m;i++) {
        for(int j = 1;j < G[i].size();j++) {
            int l = G[i][j - 1] + 1,r = G[i][j];
            int pos = query(1,l,r,r);
//            printf("%d: [pos]%d [l]%d [r]%d\n",i,pos,l,r);
            if(pos == -1) continue;
            update(1,l,pos,r);
        }
        update(1,G[i].back() + 1,n,INF);
        
        printf("%d%c",t[1].mi, " \n"[i == m]);
    }
    return 0;
}
