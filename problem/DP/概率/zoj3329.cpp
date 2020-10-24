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
int up[3], aim[3];
long double cnt[MXN], num[MXN];
/*
dp[i]=∑(pk*dp[i+k]) + dp[0]*p0 + 1
dp[i] = cnt[i] + num[i] * dp[0]
迭代求出答案
dp[0] = cnt[0] + num[0] * dp[0]
ans = dp[0]
*/
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        rep(i, 0, 3) scanf("%d", &up[i]);
        rep(i, 0, 3) scanf("%d", &aim[i]);
        rep(i, 0, 1000) cnt[i] = num[i] = 0;
        per(i, n, 0) {
            cnt[i] = 1;
            rep(a, 1, up[0] + 1) {
                rep(b, 1,up[1] + 1) {
                    rep(c, 1, up[2] + 1) {
                        if(a == aim[0] && b == aim[1] && c == aim[2]) 
                            num[i] += 1.0 / (up[0] * up[1] * up[2]);
                        else {
                            cnt[i] += cnt[i + a + b + c] / (up[0] * up[1] * up[2]);
                            num[i] += num[i + a + b + c] / (up[0] * up[1] * up[2]);
                        }
                    }
                }
            }
        }
        //dp[0] = cnt[0] + num[0] * dp[0]
        printf("%.15Lf\n", cnt[0] / (1 - num[0]));
    }
    return 0;
}
