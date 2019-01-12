#include<bits/stdc++.h>
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
const int MXN = 2e6 + 7;

LL n, m, k;
int main() {
    int cas = 0;
    int tim = 1;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%lld%lld%lld", &n, &m, &k);
        LL tmp, temp = n*n*m*m;
        double ans = 0, res, buf;
        //对每个格子求k次之后被染色的概率，其和就是期望
        for(LL i = 1; i <= n; ++i) {
            for(LL j = 1; j <= m; ++j) {
                //全在上部分，下部分，左部分，右部分
                tmp = o2((j-1)*n)+o2((m-j)*n)+o2((i-1)*m)+o2((n-i)*m);
                tmp -= (o2((i-1)*(j-1))+o2((n-i)*(j-1))+o2((i-1)*(m-j))+o2((n-i)*(m-j)));
                res = tmp*1.0/temp;
                tmp = k;
                buf = 1;
                while(tmp) {
                    if(tmp&1) buf = buf*res;
                    res *= res;
                    tmp >>= 1;
                }
                ans += (1 - buf);//1-k次后没被染色的概率
            }
        }
        printf("Case #%d: %.0f\n", ++cas, ans);
    }
    return 0;
}
