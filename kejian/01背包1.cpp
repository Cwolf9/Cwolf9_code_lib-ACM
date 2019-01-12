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

int n, m;
int f[MXN][MXN], w[MXN], v[MXN];

int main() {
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) scanf("%d", &w[i]);
        for(int i = 1; i <= n; ++i) scanf("%d", &v[i]);
        f[0][0] = 0;
        for(int i = 1; i <= n; ++i){
            for(int j = 0; j <= m; ++j){
                if(j>=v[i]) f[i][j] = max(f[i-1][j],f[i-1][j-v[i]]+w[i]);
                else f[i][j] = f[i-1][j];
            }
        }
        printf("%d\n", f[n][m]);
    }
    return 0;
}