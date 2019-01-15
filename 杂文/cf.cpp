#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
typedef long long LL;

const int MXN = 5e5 + 6;
const int INF = 0x3f3f3f3f;
const LL mod = 1000000009;
const LL p1 = 691504013;
const LL p2 = 308495997;
const LL p3 = 276601605;

int n, m;
LL ar[MXN], pre[MXN], mul1[MXN], mul2[MXN];
LL sum[MXN<<2], lazy1[MXN<<2], lazy2[MXN<<2];
LL ksm(LL a, LL b) {
    LL res = 1;
    for(;b;b>>=1,a=a*a%mod) {
        if(b&1) res = res * a %mod;
    }
    return res;
}
void check(LL &a) {
    if(a >= mod) a /= mod;
}
void push_up(int rt) {
    sum[rt] = sum[lson] + sum[rson]; check(sum[rt]);
}
void push_down(int l,int r,int rt) {
    if(lazy1[rt] == 0 && lazy2[rt] == 0) return;
    LL a = lazy1[rt], b = lazy2[rt];
    int mid = (l + r) >> 1;
    int len1 = mid-l+1, len2 = r - mid;
    lazy1[lson] += a; lazy2[lson] += b;
    sum[lson] = (sum[lson] + a*(mul1[len1+2]-mul1[2]))%mod + mod; check(sum[lson]);
    sum[lson] = (sum[lson] - b*(mul2[len1+2]-mul2[2]))%mod + mod; check(sum[lson]);
    lazy1[rson] += a*mul1[len1]; lazy2[rson] += b*mul2[len1];
    sum[rson] = (sum[rson] + a*mul1[len1]*(mul1[len2+2]-mul1[2]))%mod + mod; check(sum[rson]);
    sum[rson] = (sum[rson] - b*mul2[len1]*(mul2[len2+2]-mul2[2]))%mod + mod; check(sum[rson]);
    lazy1[rt] = lazy2[rt] = 0;
    check(lazy1[lson]);check(lazy1[rson]);check(lazy2[lson]);check(lazy2[rson]);
}
void update(int L,int R,int l,int r,int rt,LL x,LL y) {
    if(L <= l && r <= R) {
        lazy1[rt] += x; lazy2[rt] += y;
        sum[rt] = (sum[rt] + x*(mul1[r-l+3]-mul1[2]))%mod + mod; check(sum[rt]);
        sum[rt] = (sum[rt] - y*(mul2[r-l+3]-mul2[2]))%mod + mod; check(sum[rt]);
        return;
    }
    push_down(l, r, rt);
    int mid = (l + r) >> 1;
    if(L > mid) update(L,R,mid+1,r,rson,1,1);
    else if(R <= mid) update(L,R,l,mid,lson,1,1);
    else {
        update(L,mid,l,mid,lson,1,1);
        update(mid+1,R,mid+1,r,rson,mul1[mid-L+1]*x,mul2[mid-L+1]*y);
    }
    push_up(rt);
}
LL query(int L,int R,int l,int r,int rt) {
    if(L <= l && r <= R) {
        return sum[rt];
    }
    push_down(l,r,rt);
    int mid = (l+r) >> 1;
    if(L > mid) return query(L,R,mid+1,r,rson);
    else if(R <= mid) return query(L,R,l,mid,lson);
    else {
        LL ans = query(L,mid,l,mid,lson);
        ans += query(mid+1,R,mid+1,r,rson);
        return ans;
    }
}
int main() {
    printf("%d\n", ksm(691504013-1,mod-2));
    printf("%d\n", ksm(308495997-1,mod-2));
    //F(n) = √5/5[((1+√5)/2)^n-((1-√5)/2)^n]
    //383008016^2 ≡ 5 (mod 1e9 + 9)
    //383008016 ≡ sqrt(5) (mod 1e9 + 9)
    printf("%lld\n", ksm(383008016,mod-2));//1/sqrt(5)≡276601605(mod)
    printf("%lld\n", 383008017*ksm(2,mod-2)%mod);//(1+sqrt(5))/2≡691504013(mod)
    printf("%lld\n", (mod-383008016+1)*ksm(2,mod-2)%mod);//(1-sqrt(5))/2≡308495997(mod)
    scanf("%d%d", &n, &m);
    mul1[0] = mul2[0] = 1;
    for(int i = 1; i <= n+3; ++i) {
        mul1[i] = mul1[i-1] * p1;
        mul2[i] = mul2[i-1] * p2;
        check(mul1[i]); check(mul2[i]);
    }
    for(int i = 1; i <= n; ++i) scanf("%lld", &ar[i]), pre[i] = (pre[i-1] + ar[i])%mod;
    while(m --) {
        int opt, l, r;
        scanf("%d%d%d", &opt, &l, &r);
        if(opt == 1) {
            update(l, r, 1, n, 1, 1, 1);
        }else {
            printf("%lld\n", (p3*query(l,r,1,n,1)%mod+pre[r]-pre[l-1])%mod);
        }
    }
    return 0;
}
/*
void push_down(int o,int l,int r) {
    LL aa=node[o].a,bb=node[o].b;
    if(!aa&&!bb) return;
    int lc=o << 1, rc=(o<<1)|1,mid=(l+r)>>1;
    int len1=mid-l+1,len2=r-mid;
    node[lc].a=(node[lc].a+aa)%wuyiqi;
    node[lc].b=(node[lc].b+bb)%wuyiqi;




    node[lc].sum=(node[lc].sum+aa*(mul1[len1+2]-mul1[2]))%wuyiqi;
    node[lc].sum=(node[lc].sum-bb*(mul2[len1+2]-mul2[2]))%wuyiqi;




    node[rc].a=(node[rc].a+aa*mul1[len1])%wuyiqi;
    node[rc].b=(node[rc].b+bb*mul2[len1])%wuyiqi;


    node[rc].sum=(node[rc].sum+aa*mul1[len1]%wuyiqi*(mul1[len2+2]-mul1[2])%wuyiqi)%wuyiqi;
    node[rc].sum=(node[rc].sum-bb*mul2[len1]%wuyiqi*(mul2[len2+2]-mul2[2])%wuyiqi)%wuyiqi;
    node[o].a=node[o].b=0;
}
void update(int o,int l,int r,int ql,int qr,LL x,LL y) {
    if (l==ql&&r==qr) {
        node[o].a=(node[o].a+x)%wuyiqi;
        node[o].b=(node[o].b+y)%wuyiqi;
        node[o].sum=(node[o].sum+x*(mul1[r-l+3]-mul1[2]))%wuyiqi;
        node[o].sum=(node[o].sum-y*(mul2[r-l+3]-mul2[2]))%wuyiqi;
        return;
    }
    push_down(o,l,r);
    int mid=(l+r)>>1;
    if (qr<=mid)
        update(o<<1,l,mid,ql,qr,x,y);
    else if (ql>mid) 
        update((o<<1)|1,mid+1,r,ql,qr,x,y);
    else {
        int len = mid - ql + 1;
        update(o<<1,l,mid,ql,mid,x,y);
        update((o<<1)|1,mid+1,r,mid+1,qr,x*mul1[len]%wuyiqi,y*mul2[len]%wuyiqi);
    }
    push_up(o);
}
*/