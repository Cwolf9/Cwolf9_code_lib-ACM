#include<bits/stdc++.h>
#define fi first
#define se second
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
typedef long long LL;
typedef pair<LL,int> pii;
const int mod = 1e9+7;
const int MXN = 1e6 + 7;
const int MXE = 1e7 + 5e6 + 7;
const LL INF = 0x3f3f3f3f3f3f3f3f;
//与n不互质的和
LL n;
std::vector<int> ve;
LL niyuan(int t) {
    return t == 1? 1: (mod - mod/t) * niyuan(mod % t) % mod;
}
void rongchi() {
    LL tn = n;
    ve.clear();
    for(int i = 2; i * i <= n; ++i) {
        if(tn % i == 0) {
            ve.push_back(i);
            while(tn % i == 0) tn /= i;
        }
    }
    if(tn > 1) ve.push_back(tn);
    int len = ve.size(), State = 1 << len;
    LL ans = 0, sum = niyuan(2);
    //printf("sum = %lld\n", sum);
    --n;
    for(int i = 1; i < State; ++i) {
        LL val = 1;
        int cnt = 0;
        for(int j = 0; j < len; ++j) {
            if(i & (1 << j)) {
                ++cnt;
                val *= ve[j];
            }
        }
        LL tot = n / val;
        if(cnt & 1) {
            ans = (ans + tot*(tot+1)/2%mod*val%mod)%mod;
        }else {
            ans = (ans - tot*(tot+1)/2%mod*val%mod + mod)%mod;
        }
    }
    printf("%lld\n", ans);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    // freopen("E://ADpan//out.out", "w", stdout);  
#endif
    while(~scanf("%lld", &n)&&n){
        rongchi();
    }
    return 0;
}