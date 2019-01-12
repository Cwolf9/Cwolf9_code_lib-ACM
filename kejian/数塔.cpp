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
const int MXN = 1e3 + 7;

int n;
int ar[MXN][MXN],dp[MXN][MXN];

int main(int argc, char const *argv[]) {
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= i; ++j) {
                scanf("%d", &ar[i][j]);
            }
        }
        for(int i = 1; i <= n; ++i) dp[n][i] = ar[n][i];

        for(int i = n-1; i >= 1; --i) {
            for(int j = 1; j <= i; ++j) {
                dp[i][j]=max(dp[i+1][j],dp[i+1][j+1])+ar[i][j];
            }
        }
        printf("%d\n", dp[1][1]);
    }
    return 0;
}