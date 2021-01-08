#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
int dp[1005][11][11][4];
int mp[11][11];
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &mp[i][j]);
        }
    }
    for(int i = 0; i <= k; ++i) for(int x = 0; x <= n; ++ x) for(int y = 0; y <= m; ++y) for(int h = 0; h < 4; ++h) dp[i][x][y][h] = -INF;
    for (int i = 0; i <= 3; ++i) dp[0][1][1][i] = 0;
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int l = 1; l <= m; ++l) {
                for (int i1 = 0; i1 < 4; ++i1) {
                    for (int k1 = 0; k1 < 4; ++k1) {
                        int x = j + dx[k1], y = l + dy[k1];
                        if (k1 != i1 && k1 % 2 == i1 % 2)continue;
                        if (x >= 1 && x <= n && y >= 1 & y <= m) {
                            int res = 0;
                            if (mp[x][y] && i % mp[x][y] == 0) res = 1;
                            dp[i][x][y][k1] = max(dp[i][x][y][k1], dp[i - 1][j][l][i1] + res);
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 4; ++i) ans = max(dp[k][n][m][i], ans);
    printf("%d\n", ans);
    return 0;
}