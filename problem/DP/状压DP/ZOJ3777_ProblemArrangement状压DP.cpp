//ZOJ3777_ProblemArrangement状压DP.cpp
//https://www.cnblogs.com/danceonly/p/4004410.html
/*
//今年省赛的题目，比赛的时候知道是状压却一直没搞出，直到最后。虽然赛后知道做法，也一直没做的，最近想不开就来做了 - -， 顺便用了下快速枚举k-子集。

恩， 做法么就是开dp[i][j] i已经选过了的题目的一个集合，j表示的是获得了j分，然后就可以直接做了。。（但是好像说会T或者卡空间，我的做法是快速枚举k-子集，这个东西可以看下watashi翻译的《挑战编程竞赛》的p157。。 汗
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
//#include <cmath>

using namespace std;

int P[15][15];
int dp[1<<12][505];
int n, m;

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) scanf("%d", &P[i][j]);
        }
        memset(dp, 0, sizeof(dp)); dp[0][0] = 1;

        for (int k = 1; k <= n; k++) {
            int comb = (1 << k) - 1;
            while (comb < (1 << n)) {
                for (int i = 0; i < n; i++) {
                    if (comb >> i & 1) {
                        int add = P[i + 1][k], low = max(0, m-add);
                        for (int j = m; j >= low; j--) dp[comb][m] += dp[comb-(1<<i)][j];
                        for (int j = low - 1; j >= 0; j--) dp[comb][j+add] += dp[comb-(1<<i)][j];
                    }
                }
                if (comb == 0) break;
                int x = comb & -comb, y = comb + x;
                comb = ((comb & ~y) / x >> 1) | y;
            }
        }
        int ret = dp[(1<<n)-1][m];
        if (!ret) puts("No solution");
        else {
            int nex = 1;
            for (int i = 1; i <= n; i++) nex *= i;
            int d = __gcd(ret, nex);
            printf("%d/%d\n", nex/d, ret/d);
        }
    }
    return 0;
}