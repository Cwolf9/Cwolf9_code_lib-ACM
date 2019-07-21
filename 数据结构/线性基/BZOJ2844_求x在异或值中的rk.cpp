#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define eb emplace_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
#define BASE_MAX 62
 
const int INF = 0x3f3f3f3f;
const int mod = 10086;
const int MXN = 1e6 + 7;
int n;
LL id[MXN], m;
LL bs[MXN];
int cnt;
//贪心求最大的异或值；从高到底枚举线性基。
//如果ax没有插进线性基中，那么ax一定属于span{a1,ax-1};故一定存在异或值为0的方案。
//任意一条 1 到 n 的路径的异或和，都可以由任意一条 1 到 n 路径的异或和与图中的一些环的异或和来组合得到。
//每个数都出现一样的次数，且这个次数为2^{n-|线性基|}。
bool insert(LL x, LL *bs) {
    for(int j = BASE_MAX; j >= 0; --j) {//63
        if(!(x >> j)) continue;
        if(bs[j]) x ^= bs[j];
        else {
            bs[j] = x;
            for(int k = j-1; k >= 0; --k) if(bs[k]&&(bs[j]&(1LL<<k))) bs[j]^=bs[k];
            for(int k = j+1; k <= BASE_MAX; ++k) if(bs[k]&(1LL<<j)) bs[k]^=bs[j];
            return true;
        }
    }
    return false;
}
void go() {
    for(int i = 0; i < n; ++i) if(insert(id[i], bs)) ++ cnt;
}
LL ksm(LL a, int b) {
    LL res = 1;
    for(;b;b>>=1,a=a*a%mod) {
        if(b&1)res=res*a%mod;
    }
    return res;
}
int main(int argc, char const *argv[]){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%lld", &id[i]);
    scanf("%lld", &m);
    go();
    LL rk = 0;
    std::vector<int> vs;
    for(int i = 0; i <= BASE_MAX; ++i) if(bs[i]) vs.push_back(i);
    for(int i = vs.size()-1; i >= 0; --i) {
        if((m&(1LL<<vs[i]))!=0) rk += 1LL<<i;
    }
    LL ans = (rk)*ksm(2, n-cnt)%mod;
    printf("%lld\n", (ans+1)%mod);
    return 0;
}
