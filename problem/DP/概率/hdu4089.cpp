#include<bits/stdc++.h>
#define o2(x) (x)*(x)
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
const int MXN = 2e3 + 7;
int n, m, k;
double pb[5], dp[2][MXN];
/*
0. Activation failed
1. Connection failed
2. Activation succeeded
3. Service unavailable


dp[i][j]: server down and the number of people before him is less than k.

迭代算出dp[i][i]!!!
要特判，因为有可能p[3]特别小其实答案应该是0，但是p[0]特别大，导致p[1],p[2],p[3]转换后较为
平均，会算出一个不合理的答案。
*/
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    while(~scanf("%d%d%d", &n, &m, &k)) {
        rep(i, 0, 4) scanf("%lf", pb + i);
        if(pb[3] < 1e-8) {
            printf("0.00000\n");
            continue;
        }
        rep(i, 1, 4) pb[i] = pb[i]/(1 - pb[0]);
        memset(dp, 0, sizeof(dp));
        dp[1][1] = pb[3] / (1 - pb[1]);
        int p = 1;
        rep(i, 2, n + 1) {
            double tmp1 = 0;
            double tmp2 = 1;
            per(j, i, 2) {
                tmp1 += tmp2 * ((j <= k?pb[3]:0) + pb[2] * dp[p][j-1]);
                tmp2 *= pb[1];
            }
            tmp1 += tmp2 * pb[3];
            tmp2 *= pb[1];
            dp[!p][i] = tmp1 / (1 - tmp2);
            rep(j, 1, i) {
                if(j == 1) {
                    dp[!p][j] = pb[3] + pb[1] * dp[!p][i];
                }else if(j <= k) {
                    dp[!p][j] = pb[3] + pb[1] * dp[!p][j-1] + pb[2] * dp[p][j-1];
                }else {
                    dp[!p][j] = pb[1] * dp[!p][j-1] + pb[2] * dp[p][j-1];
                }
            }
            p = !p;
        }
        printf("%.5f\n", dp[p][m]);
    }
    return 0;
}
