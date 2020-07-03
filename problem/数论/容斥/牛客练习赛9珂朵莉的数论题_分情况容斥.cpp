#include<bits/stdc++.h>
#define fi first
#define se second
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
typedef long long LL;
typedef pair<LL,int> pii;
const int mod = 1e9+7;
const int MXN = 1e5 + 7;
const int MXE = 1e7 + 5e6 + 7;
const LL INF = 0x3f3f3f3f3f3f3f3f;

int x, y;
bool is[MXE];
std::vector<int> ve;
void baoli() {
    int tmp = (int)1e9/y;
    if(tmp < x) {
        printf("0\n");
        return;
    }
    for(int i = 1; i <= tmp; ++i) is[i] = 0;
    for(int i = 2; i < y; ++i) {
        if(is[i] == 1) continue;
        for(int j = i; j <= tmp; j += i) {
            is[j] = 1;
        }
    }
    int cnt = 0;
    for(int i = 1; i <= tmp; ++i) {
        if(is[i] == 0) {
            ++cnt;
            if(cnt == x) {
                if(i*1LL*y <= 1000000000){
                    printf("%d\n", i*y);
                    return;
                }
                break;
            }
        }
    }
    printf("0\n");
}
LL rongchi(LL m) {
    int len = ve.size(), State = 1 << len;
    LL ans = 0;
    for(int i = 1; i < State; ++i) {
        int cnt = 0, flag = 0;
        LL val = 1;
        for(int j = 0; j < len; ++j) {
            if(i & (1 << j)) {
                ++cnt;
                val *= ve[j];
            }
        }
        if(cnt & 1) {
            ans += m/val;
        }else {
            ans -= m/val;
        }
    }
    //printf("m = %lld ans = %lld\n", m, ans);
    return m - ans;
}
void gao() {
    for(int i = 2; i < y; ++i) {
        int flag = 0;
        for(int j = 2; j * j <= i; ++j) {
            if(i % j == 0) {
                flag = 1;
                break;
            }
        }
        if(!flag) ve.push_back(i);
    }
    LL l = 2, r = 1e9, mid, ans = 0;
    while(r >= l) {
        mid = (l + r) >> 1;
        if(rongchi(mid) >= x) {
            ans = mid;
            r = mid - 1;
        }else l = mid + 1;
    }
    if(ans * y > (int)1e9) ans = 0;
    printf("%lld\n", ans*y);
    ve.clear();
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    // freopen("E://ADpan//out.out", "w", stdout);  
#endif
    while(~scanf("%d%d", &x, &y)){
        if(y > 70) baoli();
        else gao();
    }
    return 0;
}
