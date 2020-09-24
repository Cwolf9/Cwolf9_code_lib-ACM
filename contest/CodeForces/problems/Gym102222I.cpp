#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int T, n, k, mod;
LL bit[55];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    // vector<int> vs;
    // for(int i = 1; i < 6; ++i) vs.emplace_back(i);
    // do{
    //     vector<int> vt;
    //     for(int x: vs) vt.emplace_back(x);
    //     for(int i = 1; i < vt.size(); ++i) {
    //         if(vt[i-1] > vt[i]) swap(vt[i-1], vt[i]);
    //     }
    //     for(int i = 1; i < vt.size(); ++i) {
    //         if(vt[i-1] > vt[i]) swap(vt[i-1], vt[i]);
    //     }
    //     vector<int> dp(6, 0x3f3f3f3f);
    //     int len = 0, ans = 1;
    //     for(int x: vt) {
    //         int p = lower_bound(begin(dp), begin(dp) + 6, x) - begin(dp);
    //         dp[p] = x;
    //         ans = p + 1;
    //     }
    //     if(ans >= 5) {
    //         for(int x: vs) printf("%d ", x);
    //         printf("\n");
    //     }
    // }while(next_permutation(begin(vs), end(vs)));
    scanf("%d", &T);
    for (int z = 1; z <= T; ++z) {
        scanf("%d%d%d", &n, &k, &mod);
        printf("Case #%d: ", z);
        if (k >= n) {
            LL ans = 1;
            for (int i = 1; i <= n; ++i) ans = ans * i % mod;
            printf("%lld\n", ans);
            continue;
        }
        bit[0] = 1;
        for (int i = 1; i <= n; ++i) bit[i] = 1LL * bit[i - 1] * (k + 1) % mod;
        LL ans = 0;
        // sorted
        ans = bit[n - k];
        cout << ans << endl;
        // left shift
        for (int len = 2; len <= n - k; ++len)
            ans += 1LL * (n - k - len + 1) * bit[n - k - 1] % mod, ans %= mod;
        // right shift
        for (int len = 3; len <= n - k; ++len)
            ans += 1LL * (n - k - len + 1) * bit[n - k - len + 1] % mod,
                ans %= mod;
        // last k
        for (int i = 1; i <= k; ++i) ans = ans * i % mod;
        printf("%lld\n", ans);
    }
    return 0;
}