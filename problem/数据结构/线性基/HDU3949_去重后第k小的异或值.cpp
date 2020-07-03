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
const LL mod = 998244353;
const int MXN = 1e6 + 7;
int n, q;
LL id[MXN];
LL bs[MXN];
std::vector<LL> vs;
int zero;
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
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(insert(id[i], bs)) ++ cnt;
    }
    if(cnt < n) zero = 1;//如果ax没有插进线性基中，那么ax一定属于span{a1,ax-1}
    else zero = 0;
    vs.clear();
    for(int i = 0; i <= BASE_MAX; ++i) if(bs[i]) vs.eb(bs[i]);
}
int main(int argc, char const *argv[]){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
    int tim, cas = 0; scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        printf("Case #%d:\n", ++ cas);
        for(int i = 0; i < n; ++i) scanf("%lld", &id[i]);
        for(int i = 0; i <= BASE_MAX; ++i) bs[i] = 0;
        go();
        int q; scanf("%d", &q);
        while(q --) {
            LL k; scanf("%lld", &k);
            k -= zero;
            LL ans = 0;
            int cnt = 0;
            if(k >= (1LL<<(int)vs.size())) ans = -1;
            else {
                for(int i = 0; i < vs.size(); ++i) {
                    if(k & (1LL<<i)) ans ^= vs[i];
                }
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}