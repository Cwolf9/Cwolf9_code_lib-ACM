#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#define fir first
#define sec second
using namespace std;

const int maxn = 1<<17;

int n;
int a[maxn];
int dp[maxn][17];

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        int c;
        scanf("%d",&c);
        a[c]++;
    }
    int lit = (1<<16);
    int ans = 0;
    for(int s = 0;s<lit;s++) {
    	dp[s][0] = a[s];
        for(int i=0; i < 16; ++i) {
            if(!(s&(1<<i))) {
            	dp[s][i+1] += dp[s][i]; 
			}else {
				dp[s][i+1] += (dp[s][i]+dp[s^(1<<i)][i]);
				if(s == 7) cout << i << " " << dp[s][i] << " " << dp[s^(1<<i)][i] << endl;
			}
        }
        if(a[s]) ans += dp[s][16];
//        if(dp[s][16]) printf("%d %d\n", s, dp[s][16]);
    }
    printf("%d\n",ans);
    return 0;
}
//4 1 3 7 15
