#include <bits/stdc++.h>
using namespace std;

int dp[30][30];
int res[30][30];
int ans[30];
int main () {
    dp[0][0] = 1;
    for(int i=2;i<=10;i+=2) ans[i] = 1;
    for(int s = 0;s < 10; s++) {
        memset(res,0,sizeof(res));
        for(int i=1;i<=10;i++) {
            for(int j=0;j<=10;j++) {
                for(int g = 2;g<=j;g+=2) {
                    res[i][j] += dp[i-1][j-g]*ans[g];        
                }
            }
        }
    }
    for(int i=1;i<=10;i++) printf("ans[%d] = %d\n",i,ans[i]);
    return 0;
}