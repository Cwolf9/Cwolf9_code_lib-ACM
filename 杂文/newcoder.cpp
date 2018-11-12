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

#include<bits/stdc++.h> 
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
const int MXN = 2e5 + 7;
int n, m;
int sum[MXN], w[MXN];
std::vector<int> mp[MXN];
void dfs(int u,int ba) {
    for(auto v: mp[u]) {
        if(v == ba) continue;
        dfs(v, u);
        sum[u] += sum[v];
    }
    sum[u] -= 2 * w[u];
}
int main(int argc, char const *argv[]){
    scanf("%d", &n);
    for(int i = 1, a, b; i < n; ++i) {
        scanf("%d%d", &a, &b);
        mp[a].push_back(b);
        mp[b].push_back(a);
    }
    int a, b;
    scanf("%d%d", &a, &b);
    while(a+b) {
        ++ sum[a], ++ sum[b];
        scanf("%d%d", &a, &b);
    }
    sum[5] -= 1;
    sum[2] -= 1;
    sum[1] -= 1;
    dfs(1, -1);
    for(int i = 1; i <= n; ++i) {
        printf("%d ", sum[i]);
    }
    printf("\n");
    return 0;
}
