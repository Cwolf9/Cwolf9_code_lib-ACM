#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <unordered_map>

namespace lh {
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

}
using namespace lh;//我的namespace


const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
const int MXN = 1e6 + 7;

int n;
int ar[MXN], dp[MXN];
//O(nlog(n))求解LIS
int main(int argc, char const *argv[]){
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &ar[i]);
        }
        int p = 1;
        dp[0] = ar[1];
        for(int i = 2; i <= n; ++i) {
            int k = lower_bound(dp, dp+p, ar[i]) - dp;
            if(ar[i] > dp[p-1]) dp[p++] = ar[i];
            else dp[k] = ar[i];
        }
        printf("%d\n", p);
    }
    return 0;
}
/*O(n2)求解LIS
int main(int argc, char const *argv[]) {
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &ar[i]);
            dp[i] = 1;
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j < i; ++i) {
                if(ar[j] < ar[i]) dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
        int ans = 0;
        for(int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
        printf("%d\n", ans);
    }
    return 0;
}
*/
/*
int main(int argc, char const *argv[]){
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &ar[i]);
        }
        int p = 1;
        dp[0] = ar[1];
        printf("1");
        for(int i = 2; i <= n; ++i) {
            int k = lower_bound(dp, dp+p, ar[i]) - dp;
            if(ar[i] > dp[p-1]) dp[p++] = ar[i];
            else dp[k] = ar[i];
            printf(" %d", k+1);
        }
        printf("\n");
    }
    return 0;
}
*/