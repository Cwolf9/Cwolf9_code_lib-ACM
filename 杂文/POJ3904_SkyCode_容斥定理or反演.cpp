#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

typedef long long LL;

const int MXN = 1e6 + 6;
const int MXT = 1e5 + 5;
const LL INF = 0x3f3f3f3f3f3f3f3f;

int n;
int pri[MXN/2], noprime[MXN], pcnt;
int ar[MXN], cnt[MXN], num[MXN];
std::vector<int> ve;
LL f[MXN];
void init() {
    for(int i = 2; i < MXT; ++i) {
        if(!noprime[i]) pri[pcnt++] = i;
        for(int j = 0 ; j < pcnt && pri[j] * i < MXT; ++j) {
            noprime[pri[j]*i] = 1;
            if(i % pri[j] == 0) break;
        }
    }
}
LL comb(int n, int m) {
    if(n < m) return 0;
    if(n == m) return 1;
    if(f[n]) return f[n];
    LL x = 1, y = 1;
    for(int i = 1, j = n; i <= m; ++i, --j) {
        x *= i; y *= j;
        if(y % x == 0) y /= x, x = 1;
    }
    f[n] = y;
    return y;
}
void gao(int n) {
    ve.clear();
    int tn = n;
    for(int i = 0; i < pcnt; ++i) {
        if(tn % pri[i] == 0) {
            ve.push_back(pri[i]);
            while(tn % pri[i] == 0) tn /= pri[i];
        }
        if(tn == 1) break;
    }
    if(tn != 1) {
        ve.push_back(tn);
    }
    int len = ve.size(), State = 1<<len;
    for(int i = 1; i < State; ++i) {
        int CNT = 0;
        LL val = 1;
        for(int j = 0; j < len; ++j) {
            if(i & (1<<j)) {
                ++ CNT;
                val *= ve[j];
            }
        }
        ++ cnt[val];
        num[val] = CNT;
    }
}

int main(int argc, char const *argv[]) {

#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
#endif
    init();
    while(~scanf("%d", &n)) {
        int tmax = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d", &ar[i]);
            gao(ar[i]);
            tmax = tmax > ar[i]? tmax: ar[i];
        }
        LL ans = 0;
        for(int i = 2; i <= tmax; ++i) {
            if(num[i] % 2 == 1) {
                ans += comb(cnt[i], 4);
            }else if(num[i]) {
                ans -= comb(cnt[i], 4);
            }
        }
        printf("%lld\n", comb(n, 4) - ans);
        for(int i = 1; i <= tmax; ++i) cnt[i] = num[i] = 0;
    }
    return 0;
}

/*
f(2) + f(3) - f(2*3)
*/