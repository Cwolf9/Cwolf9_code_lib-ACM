#include<bits/stdc++.h> 
using namespace std;
typedef long long LL;
#define lson rt<<1
#define rson rt<<1|1
typedef unsigned long long uLL;
const int MXN = 4e5 + 6;
const int INF = 0x3f3f3f3f;
const LL base = 1572872831;
const LL mod = 2078526727;
/*
给你一个长度为n的数字串，有两种操作：
1 L R C： 把s[L, R] 全部变为C；
2 L R d： 询问s[L, R] 是否有长度为d的循环节。
*/
int n, m, q;
char ar[MXN];
LL pw[MXN], dif[10][MXN];
LL num[MXN<<2];
int lazy[MXN<<2];
struct lp{
    LL val;
    int len;
    lp() {}
    lp(LL a, int b) {val = a, len = b;}
};
void init() {
    pw[0] = 1;
    for(int i = 1; i <= n; ++i) pw[i] = pw[i-1] * base % mod;
    for(int i = 1; i <= 9; ++i) {
        dif[i][1] = i;
        for(int j = 2; j <= n; ++j) {
            dif[i][j] = dif[i][j-1] * base + i;
            dif[i][j] %= mod;
        }
    }
}
void push_up(int rt, int len) {
    num[rt] = num[lson] * pw[(len)/2] + num[rson];
    num[rt] %= mod;
    if(lazy[lson] == lazy[rson]) lazy[rt] = lazy[lson];
    else lazy[rt] = -1;
}
void push_down(int rt, int l, int mid, int r) {
    if(lazy[rt] != -1) {
        lazy[lson] = lazy[rson] = lazy[rt];
        num[lson] = dif[lazy[rt]][mid-l+1];
        num[rson] = dif[lazy[rt]][r-mid];
    }
}
void build(int l,int r,int rt) {
    lazy[rt] = -1;
    num[rt] = 0;
    if(l == r) {
        num[rt] = ar[l] - '0';
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lson); build(mid+1, r, rson);
    push_up(rt, r-l+1);
}
void update(int L,int R,int l,int r,int rt,int v) {
    if(L <= l && r <= R) {
        lazy[rt] = v;
        num[rt] = dif[v][r-l+1];
        return;
    }
    int mid = (l+r) >> 1;
    push_down(rt,l,mid,r);
    if(L > mid) update(L,R,mid+1,r,rson,v);
    else if(R <= mid) update(L,R,l,mid,lson,v);
    else {
        update(L,mid,l,mid,lson,v); update(mid+1,R,mid+1,r,rson,v);
    }
    push_up(rt, r-l+1);
}
lp query(int L,int R,int l,int r,int rt) {
    if(L <= l && r <= R) {
        return lp(num[rt], r-l+1);
    }
    int mid = (l+r) >> 1;
    push_down(rt,l,mid,r);
    if(L > mid) return query(L,R,mid+1,r,rson);
    else if(R <= mid) return query(L,R,l,mid,lson);
    else {
        lp p1 = lp{0,-1}, p2 = lp(0,-1);
        p1 = query(L,mid,l,mid,lson);
        p2 = query(mid+1,R,mid+1,r,rson);
        if(p2.len == -1) return p1;
        if(p1.len == -1) return p2;
        p1.val = p1.val * pw[p2.len] + p2.val;
        p1.val %= mod;
        p1.len += p2.len;
        return p1;
    }
}
int main() {
    scanf("%d%d%d", &n, &m, &q);
    init();
    q += m;
    scanf("%s", ar+1);
    build(1, n, 1);
    while(q --) {
        int op,x,y,z;
        scanf("%d%d%d%d", &op, &x, &y, &z);
        if(op == 1) {
            update(x,y,1,n,1,z);
        }else {
            if(y-x+1 < z) printf("NO\n");
            else if(y-x+1 == z) printf("YES\n");
            else {
                lp ans1 = query(x,y-z,1,n,1);
                lp ans2 = query(x+z,y,1,n,1);
                //printf("%llu %llu %d %d\n", ans1.val, ans2.val, ans1.len, ans2.len);
                if(ans1.val == ans2.val) printf("YES\n");
                else printf("NO\n");
            }
        }
    }
    return 0;
}
