#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MXN = 1e6 + 7;
const int INF = 0x3f3f3f3f;
/*
n(40)加油站m(250000)趟列车,列车有起始加油站，油箱容量为V,每公里耗油ci,可加ri次
油,每次加满。求最小V是的所有列车可达到终点. 
*/
int n, m, V;
int ar[MXN];
struct lp {
    int s, t, c, r;
}cw[MXN];
int dp[405][405];
vector<int> belong[405];
/*
dp[i][j][k]表示把第i到j这个线段分成k+1段中段的的最小最大长度
dp[i][j][k] <= dp[i][j+1][k]
opt[i][j][k]表示取dp[i][j][k]这个值的最后一段线段的起始位置
opt[i][j][k] <= opt[i][j+1][k]
dp[i][j][k] = min(x:max(dp[i][x][k-1],ar[j]-ar[x]))
最优的x就是opt[i][j][k]
当i和k不变时，x随j单挑不递减
故以i,k,j顺序枚举,n^3预处理出dp[i][j][k]
其中第一位起始不需要保存，因为它对后面的情况无影响
*/
int main() {
#ifndef ONLINE_JUDGE
    //freopen("1.in", "r", stdin);
#endif 
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d%d", &cw[i].s, &cw[i].t, &cw[i].c, &cw[i].r);  
        belong[cw[i].s].push_back(i);
    }
    LL ans = -1;
    for(int i = 1; i <= n; ++i) {
        for(int j = i; j <= n; ++j) dp[j][0] = ar[j] - ar[i];
        for(int k = 1, last_add; k <= n; ++k) {
            last_add = i;
            for(int j = i; j <= n; ++j) {
                while(last_add<j&&max(dp[last_add][k-1], ar[j] - ar[last_add])>=max(dp[last_add+1][k-1], ar[j] - ar[last_add+1])) ++last_add;
                dp[j][k] = max(dp[last_add][k-1], ar[j] - ar[last_add]);
            }
        }
        for(int id: belong[i]) {
            ans = max(ans, dp[cw[id].t][cw[id].r]*1LL*cw[id].c);
        } 
    }
    printf("%lld\n", ans);
    return 0;
}