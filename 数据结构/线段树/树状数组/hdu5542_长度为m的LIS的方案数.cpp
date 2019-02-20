#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD = 1e9 + 7;
const int MXN = 1e3 + 7;
LL dp[MXN][MXN], bit[MXN][MXN];
int ar[MXN], br[MXN];
int n, m;
void b_add(int i, int j, LL x) {
    while(i <= n) {
        bit[i][j] += x;
        if(bit[i][j] >= MOD) bit[i][j] %= MOD;
        i += (i&(-i));
    }
}
LL b_query(int i,int j) {
    LL sum = 0;
    while(i) {
        sum =(sum+bit[i][j])%MOD;
        i -= (i&(-i));
    }
    return sum;
}
int main(){
    int tim, cas = 0; scanf("%d", &tim);
    while(tim--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]), br[i] = ar[i];
        sort(br+1, br+n+1);
        for(int i = 0; i <= n; ++i) for(int j = 0; j <= n; ++j) bit[i][j]=0;
        int k = unique(br+1, br+n+1) - br;
        for(int i = 1; i <= n; ++i) 
            ar[i] = lower_bound(br+1, br+k, ar[i]) - br;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m && j <= i; ++j) {
                if(j == 1) {
                    dp[i][j] = 1; b_add(ar[i], j, 1);
                    continue;
                }
                dp[i][j] = b_query(ar[i]-1, j-1);
                b_add(ar[i], j, dp[i][j]);
            }
        }
        LL ans = 0;
        for(int i = m; i <= n; ++i) ans = (ans + dp[i][m])%MOD;
        printf("Case #%d: %lld\n", ++cas, ans);
    }
    return 0;
}