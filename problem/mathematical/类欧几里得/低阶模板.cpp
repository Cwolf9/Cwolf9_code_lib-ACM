//https://blog.csdn.net/werkeytom_ftd/article/details/53812718
//n 1e9, f O(logn), g和h大概O(1e7)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 998244353;
int ksm(int a, int b, int modd) {
    int res = 1;
    for (; b > 0; b >>= 1, a = (LL)a * a % modd) {
        if (b & 1) res = (LL)res * a % modd;
    }
    return res;
}
const int inv2 = ksm(2, mod - 2, mod), inv6 = ksm(6, mod - 2, mod);
int a, b, c;
//abcn>=0,c!=0
struct Data {
    int f;//$Sigma_{i=0}^{n} floor((a*i+b)/c)$
    int g;//$Sigma_{i=0}^{n} i*floor((a*i+b)/c)$
    int h;//$Sigma_{i=0}^{n} (floor((a*i+b)/c))^2$
};
Data solve(LL a, LL b, LL c, LL n) {
    Data ans, tmp;
    if (a == 0) {
        ans.f = (n + 1) * (b / c) % mod;
        ans.g = (b / c) * n % mod * (n + 1) % mod * inv2 % mod;
        ans.h = (n + 1) * (b / c) % mod * (b / c) % mod;
        return ans;
    }
    if (a >= c || b >= c) {
        tmp = solve(a % c, b % c, c, n);
        if(n >= mod) n %= mod;
        ans.f = (tmp.f + (a / c) * n % mod * (n + 1) % mod * inv2 % mod + (b / c) * (n + 1) % mod) % mod;
        ans.g = (tmp.g + (a / c) * n % mod * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod + (b / c) * n % mod * (n + 1) % mod * inv2 % mod) % mod;
        ans.h = ((a / c) * (a / c) % mod * n % mod * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod + 
                (b / c) * (b / c) % mod * (n + 1) % mod + (a / c) * (b / c) % mod * n % mod * (n + 1) % mod + 
                tmp.h + 2 * (a / c) % mod * tmp.g % mod + 2 * (b / c) % mod * tmp.f % mod) % mod;
        return ans;
    }
    LL m = (a * n + b) / c;
    tmp = solve(c, c - b - 1, a, m - 1);
    if(n >= mod) n %= mod;
    if(m >= mod) m %= mod;
    ans.f = (n * (m % mod) % mod - tmp.f) % mod;
    ans.g = (n * (n + 1) % mod * (m % mod) % mod - tmp.f - tmp.h) % mod * inv2 % mod;
    ans.h = (n * (m % mod) % mod * ((m + 1) % mod) % mod - 2 * tmp.g - 2 * tmp.f - ans.f) % mod;
    return ans;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:/in.in", "r", stdin);
#endif
    int tim;
    int n, a, b, c;
    scanf("%d", &tim);
    while (tim--) {
        scanf("%d%d%d%d", &n, &a, &b, &c);
        Data ans = solve(a, b, c, n);
        ans.f = (ans.f % mod + mod) % mod;
        ans.g = (ans.g % mod + mod) % mod;
        ans.h = (ans.h % mod + mod) % mod;
        printf("%d %d %d\n", ans.f, ans.h, ans.g);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}