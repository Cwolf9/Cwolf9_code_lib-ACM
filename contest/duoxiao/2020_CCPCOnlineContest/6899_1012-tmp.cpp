#include "bits/stdc++.h"
using namespace std;
typedef long long LL;
LL A, B, C, K;
inline int getpos(LL x, int pos) {
    return ((x >> pos) & 1);
}
LL dp2[50][3][3][3];
LL tsum;
LL dfs2(int pos, LL sum, bool limita, bool limitb) {
    if (sum == 2) return 0;
    if (pos == -1) { 
        if (sum == 0 && abs(tsum) <= K) return 1;
        else return 0;
    }
    if (dp2[pos][sum][limita][limitb] != -1)return dp2[pos][sum][limita][limitb];
    LL upa = limita ? getpos(A, pos) : 1, cnt = 0, upb = limitb ? getpos(B, pos) : 1;
    for (int i = 0; i <= upa; i++) {
        for (int j = 0; j <= upb; j++) {
            if (sum == 0) {
                tsum += (i << pos) - (j << pos);
                cnt += dfs2(pos - 1, sum, limita && i == getpos(A, pos), limitb && j == getpos(B, pos));
                tsum -= (i << pos) - (j << pos);
            }else {
                if ((i ^ j) == getpos(C, pos)) {
                    tsum += (i << pos) - (j << pos);
                    cnt += dfs2(pos - 1, 1, limita && i == getpos(A, pos), limitb && j == getpos(B, pos));
                    tsum -= (i << pos) - (j << pos);
                } else if ((i ^ j) < getpos(C, pos)) {
                    tsum += (i << pos) - (j << pos);
                    cnt += dfs2(pos - 1, 0, limita && i == getpos(A, pos), limitb && j == getpos(B, pos));
                    tsum -= (i << pos) - (j << pos);
                }
            }
        }
    }
    dp2[pos][sum][limita][limitb] = cnt;
    return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(dp2, -1, sizeof(dp2));
        scanf("%lld%lld%lld%lld", &A, &B, &K, &C);
        ++ C;
        LL ans2 = dfs2(29, 1, 1, 1);
        printf("%lld\n", ans2);
    }
    return 0;
}