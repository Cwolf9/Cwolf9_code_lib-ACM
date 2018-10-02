#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")


#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

typedef long long LL;

const int MXN = 3e5 + 6;
const int MXT = 1e5 + 5;
const int mod = 998244353;

LL n, m, k;
LL f[MXN], invF[MXN];
LL niyuan(int t) {
    return t == 1? 1: (mod-mod/t)*niyuan(mod%t)%mod;
}
LL ksm(LL a, int b) {
    LL ans = 1;
    while(b) {
        if(b&1) ans = ans * a %mod;
        b >>= 1;
        a = a * a %mod;
    }
    return ans;
}
void init() {
    f[0] = 1; invF[0] = 1;
    for(int i = 1; i < MXN; ++i) f[i] = f[i-1] * i % mod;
    //invF[MXN-1] = niyuan(f[MXN-1]);
    invF[MXN-1] = ksm(f[MXN-1], mod-2);
    for(int i = MXN-2; i >= 1; --i) invF[i] = invF[i+1]*(i+1)%mod;
}
LL COMB(LL n, LL m) {
    if(n < m) return 0;
    return f[n] * invF[m] % mod * invF[n-m] % mod;
}
int main(int argc, char const *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
#endif
    init();
    int tim;
    scanf("%d", &tim);
    while(tim--) {
        scanf("%lld%lld%lld", &n, &m, &k);
        LL ans = COMB(k+m-1,m-1), tmp;
        for(int i = 1; i <= m; ++i) {
            tmp = COMB(k+m-i*n-1, m-1) * COMB(m, i) % mod;
            if(i & 1) ans = (ans - tmp + mod)%mod;
            else ans = (ans + tmp)%mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

/*
字母xi=[0,n-1],问有多少个长度为m的单词,其和为k
*/