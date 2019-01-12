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
int f[MXN], w[MXN], v[MXN];

int main() {
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) scanf("%d", &w[i]);
        for(int i = 1; i <= n; ++i) scanf("%d", &v[i]);
        for(int i = 0; i <= m; ++i) f[i] = 0;
        /*
        f[j]表示背包容量为j时，背包价值的最大值。
        */
        for(int i = 1; i <= n; ++i){
            for(int j = m; j >= 0; --j){
                if(j >= v[i]) f[j] = max(f[j], f[j - v[i]] + w[i]);
            }
        }
        printf("%d\n", f[m]);
    }
    return 0;
}