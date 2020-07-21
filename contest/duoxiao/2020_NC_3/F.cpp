/*
链接
https://ac.nowcoder.com/acm/contest/5668/F
题意
给你ab，1<=a,b<=2000000 ， 你要输出bcde, 且 d < b and f < b and 1 <=c,e<=4e12
满足： c/d - e/f = a/b
无解输出-1
思路
左边等于 (c*f-e*d)/(df) = k*gcd(d,f)/df = a/b
把b分成两个互质的数，分给d和f，这样的话就是 k = a，构造一个c和e就好了
如果b不能分成两个互质的数，那么b = p^k，如果gcd(a,b)=1就无解
否者就让 d=f= b/p， c - e = a/p，如果a=p就无解，否则就有解。

备注

*/
#include<bits/stdc++.h>
using namespace std;
const int MXN = 2e6 + 5;
typedef long long LL;
LL n, m;
int noprime[MXN], pp[MXN], pcnt;
void init_prime() {
    noprime[0] = noprime[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i;
        for(int j = 0; j < pcnt && pp[j] * i < MXN; ++j) {
            noprime[pp[j]*i] = 1;
            if(i % pp[j] == 0) {
                break;
            }
        }
    }
}
vector<int> vs;
int num[MXN], cnt[MXN];
int main() {
    init_prime();
    int tim;
    scanf("%d", &tim);
    int ans = 0;
    for(int i = 2; i < MXN; ++i) {
        int tmp = 1;
        int x = i;
        for(int j = 0; j < pcnt && pp[j] <= x; ++j) {
            if(x % pp[j] == 0) {
                int ret = 2;
                while(x % pp[j] == 0) ++ ret, x /= pp[j];
                tmp *= ret;
            }
            if(x == 1) break;
        }
        if(x > 1) tmp *= 2;
        ans = max(ans, tmp);
    }
    cout << ans << endl;
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}