#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MXN = 1e4 + 7;
const int INF = 0x3f3f3f3f;
/*
n(16)行m(1e4)列的矩阵，aij(1e9)，随机行的顺序，求链的相邻两数的最小最大差值
链就是:a11,a21...an1,a12...anm 
*/
int n, m;
int ar[17][MXN];
int d1[17][17], d2[17][17];
int dp[1<<17][17];
/*
枚举起点，预处理最小值最大的哈密顿路径
两点之间的边权就是的d1[i][j]
始终点的边权就是d2[i][j]
最后枚举终点即可
d1[i][j]是第i和j行同一列的最小差值
d2[i][j]是第i和j行相邻列的最小差值 
*/
void hamidun(int s) {
    memset(dp, 0, sizeof(dp));
    dp[1<<s][s] = INF;
    for(int i = 0; i < m - 1; ++i) dp[1<<s][s] = min(dp[1<<s][s], abs(ar[s][i]-ar[s][i+1]));
    for(int i = 0; i < n; ++i) {
        if(i == s) continue;
        dp[(1<<s)|(1<<i)][i] = d1[s][i];
    }
    int sta = 1<<n;
    for(int t = 1; t < sta; ++t) {
        for(int i = 0; i < n; ++i) {
            if(!(t&(1<<i))) continue;
            for(int j = 0, old; j < n; ++j) {
                if(i == j) continue;
                if(!(t&(1<<j))) continue;
                old = t^(1<<i);
                dp[t][i] = max(min(dp[old][j], d1[i][j]), dp[t][i]);
            }
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
#endif 
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) scanf("%d", &ar[i][j]);
    for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) d1[i][j] = d2[i][j] = INF;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < m; ++k) {
                d1[i][j] = min(d1[i][j], abs(ar[i][k] - ar[j][k]));
            }
            for(int k = 1; k < m; ++k) {
                d2[i][j] = min(d2[i][j], abs(ar[i][k-1] - ar[j][k]));
            }
        }
        d1[i][i] = d2[i][i] = INF;
    }
    int ans = -1;
    for(int i = 0; i < n; ++i) {
        hamidun(i);
        for(int j = 0; j < n; ++j) {
            ans = max(ans, min(dp[(1<<n)-1][j], d2[j][i]));
        }
    }
    printf("%d\n", ans);
    return 0;
}