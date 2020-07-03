#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define pb push_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int INF = 0x3f3f3f3f;
const LL mod = 1000000007;
const int MXN = 4e5 + 7;
int n, q;
int noprime[MXN], pp[MXN], pcnt;
int phi[MXN], mu[MXN];
void init_prime() {
    noprime[0] = noprime[1] = 1;
    mu[1] = 1; phi[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, phi[i] = i-1, mu[i] = -1;
        for(int j = 0; j < pcnt && pp[j] * i < MXN; ++j) {
            noprime[pp[j]*i] = 1;
            phi[pp[j]*i] = (pp[j]-1)*phi[i];
            mu[pp[j]*i] = -mu[i];
            if(i % pp[j] == 0) {
                phi[pp[j]*i] = pp[j]*phi[i];
                mu[pp[j]*i] = 0;
                break;
            }
        }
    }
}
LL sum[MXN<<2], bit[MXN<<2];
LL flag1[MXN<<2], flag2[MXN<<2];
int ar[MXN];
LL bin[MXN], ni[MXN];
LL ksm(LL a, LL b) {
    assert(b >= 0);
    LL res = 1;
    for(; b; b>>=1, a=a*a%mod) {
        if(b&1) res = res * a % mod;
    }
    return res;
}
void build(int l,int r,int rt) {
    flag1[rt] = 1;
    if(l == r) {
        sum[rt] = ar[l];
        bit[rt] = bin[l];
        return ;
    }
    int mid = (l+r) >> 1;
    build(l, mid, rt<<1); build(mid+1, r, rt<<1|1);
    sum[rt] = sum[rt<<1] * sum[rt<<1|1] % mod;
    bit[rt] = bit[rt<<1] | bit[rt<<1|1];
}
void push_down(int l,int mid,int r,int rt) {
    if(flag1[rt] != 1) {
        flag1[rt<<1] = flag1[rt<<1]*flag1[rt]%mod;
        flag1[rt<<1|1] = flag1[rt<<1|1]*flag1[rt]%mod;
        sum[rt<<1] = sum[rt<<1] * ksm(flag1[rt],mid-l+1)%mod;
        sum[rt<<1|1] = sum[rt<<1|1] * ksm(flag1[rt],r-mid)%mod;
        flag1[rt] = 1;
    }
    if(flag2[rt]) {
        flag2[rt<<1] |= flag2[rt];
        flag2[rt<<1|1] |= flag2[rt];
        bit[rt<<1] |= flag2[rt];
        bit[rt<<1|1] |= flag2[rt];
        flag2[rt] = 0;
    }
}
void update(int L, int R, int l, int r, int rt, LL val, LL msk) {
    if(L <= l && r <= R) {
        sum[rt] = sum[rt] * ksm(val, r-l+1) % mod;
        bit[rt] |= msk;
        flag1[rt] = flag1[rt] * val % mod;
        flag2[rt] |= msk;
        return ;
    }
    int mid = (l + r) >> 1;
    push_down(l,mid,r,rt);
    if(L > mid) update(L,R,mid+1,r,rt<<1|1,val,msk);
    else if(R <= mid) update(L,R,l,mid,rt<<1,val,msk);
    else {
        update(L,mid,l,mid,rt<<1,val,msk);
        update(mid+1,R,mid+1,r,rt<<1|1,val,msk);
    }
    sum[rt] = sum[rt<<1] * sum[rt<<1|1] % mod;
    bit[rt] = bit[rt<<1] | bit[rt<<1|1];
}
pll query(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) {
        return {sum[rt], bit[rt]};
    }
    int mid = (l + r) >> 1;
    push_down(l,mid,r,rt);
    if(L > mid) return query(L,R,mid+1,r,rt<<1|1);
    else if(R <= mid) return query(L,R,l,mid,rt<<1);
    else {
        pll a = query(L,mid,l,mid,rt<<1);
        pll b = query(mid+1,R,mid+1,r,rt<<1|1);
        return {a.fi*b.fi%mod,a.se|b.se};
    }
}
int main() {
    init_prime();
    for(int i = 0; i < 62; ++i) {
        ni[i] = ksm(pp[i], mod-2);
    }
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) {
        LL msk = 0;
        scanf("%d", &ar[i]);
        for(int j = 0; pp[j] <= ar[i]; ++j) {
            if(ar[i] % pp[j] == 0) {
                msk |= (1LL<<j);
            }
        }
        bin[i] = msk;
    }
    build(1, n, 1);
    char s[10];
    int l, r, x;
    while(q --) {
        scanf("%s%d%d", s, &l, &r);
        if(s[0] == 'M') {
            scanf("%d", &x);
            LL msk = 0;
            for(int j = 0; pp[j] <= x; ++j) {
                if(x % pp[j] == 0) {
                    msk |= (1LL<<j);
                }
            }
            update(l, r, 1, n, 1, x, msk);
        }else {
            pll a = query(l, r, 1, n, 1);
            LL ans = a.fi;
            for(int i = 0; i < 62; ++i) {
                if(a.se & (1LL<<i)) {
                    ans = ans * (pp[i]-1LL) % mod * ni[i] % mod;
                }
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}