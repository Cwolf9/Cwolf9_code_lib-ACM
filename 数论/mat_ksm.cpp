#include<cstring>
#include<cstdio>
#include<algorithm>

typedef long long LL;
using namespace std;
const int N = 1024, mod = 1000000007;
LL n;
int k, a[N], h[N], c[N], b[N];
int tmp[N << 1];

void mul(int *a1, int *a2) {
    for (int i = 0; i <= 2 * k; i++)tmp[i] = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
            tmp[i + j] = (tmp[i + j] + 1ll * a1[i] * a2[j]) % mod;
        }
    }
    for (int i = 2 * k; i >= k; i--) {
        for (int j = 0; j < k; j++) {
            tmp[i - k + j] = (tmp[i - k + j] + 1LL * tmp[i] * a[k - j]) % mod;
        }
        tmp[i] = 0;
    }
    for (int i = 0; i < k; i++) a1[i] = tmp[i];
}

void pow(int *a1, LL t, int *a2) {
    for (; t; t >>= 1) {
        if (t & 1)mul(a2, a1);
        mul(a1, a1);
    }
}
//https://blog.csdn.net/deadpool66/article/details/81330610
//2019牛客2场B题
#define clr(a,b) memset((a),(b),sizeof((a)))
LL powmod(LL a,LL b) {LL res=1;a%=mod; for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
int main(){
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d%lld", &k, &n);
        if (n == -1) {
            printf("%lld\n", 2LL * powmod(k + 1, mod - 2) % mod);
            continue;
        }else if(k == 1) {
            printf("1\n");
            continue;
        }
        LL tmp = powmod(k, mod - 2);
        for (int i = 1; i <= k; i++) a[i] = tmp;
        h[0] = 1;
        for (int i = 1; i <= k; i++) {
            h[i] = 0;
            for(int j = max(0, i - k); j < i; ++j) h[i] = (h[i] + h[j]) % mod;
            h[i] = (LL)h[i] * tmp % mod;
        }
        if (n <= k) {
            printf("%d\n", (h[n]+mod)%mod) ;
            continue;
        }
        -- n;
        memset(b, 0, sizeof(int)*(k+2));
        memset(c, 0, sizeof(int)*(k+2));
        b[1] = 1;
        c[0] = 1;
        pow(b, n, c);
        LL ans = 0;
        for (int i = 0; i < k; i++) {
            ans = (ans + 1LL * c[i] * h[i + 1] % mod) % mod;
        }
        printf("%lld\n", (ans+mod)%mod);
    }
    return 0;
}


/*
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2048;
constexpr int mod = 1e9 + 7;
constexpr int MOD = 1e9 + 7;
typedef long long LL;
inline int add(int a, int b) {
    a += b;
    return a >= mod ? a - mod : a;
}
inline int sub(int a, int b) {
    a -= b;
    return a < 0 ? a + mod : a;
}
inline int mul(LL a, int b) {
    a *= b;
    return a >= mod ? a % mod : a;
}
inline int mpow(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1) {
            r = mul(r, a);
        }
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}
inline int inv(int x) {
    return mpow(x, mod - 2);
}

LL n , m, ik;
constexpr int MAX_N = 1024;
LL dp[MAX_N<<1];

inline void pre_dp() {
    LL bdr = min(n + n , m);
    dp[0] = 1;
    for(LL i = 1; i <= bdr; i++) {
        dp[i] = 0LL;
        for (int j = 1 ; j <= n; ++j) {
            if (i - j < 0 ) break;
            dp[i] = (dp[i] + dp[i - j] * ik % MOD) % MOD;
        }
    }
}
inline vector<LL> mul(vector<LL>& v1 , vector<LL>& v2) {
    int sz1 = (int)v1.size();
    int sz2 = (int)v2.size();
    vector<LL> _v(n + n);
    for(int i = 0; i < n + n; i++) _v[i] = 0;
    // expand
    for(int i = 0; i < sz1; i++) {
        for(int j = 0; j < sz2; j++) {
            (_v[i + j + 1] += v1[i] * v2[j] % MOD) %= MOD;
        }
    }
    // shrink
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= n; j++) {
            (_v[i + j] += _v[i] * ik) %= MOD;
        }
    }
    for(int i = 0; i < n; i++) _v[i] = _v[i + n];
    _v.resize(n);
    return _v;
}
vector<LL> I , A;
inline LL solve() {
    pre_dp();
    if(m <= n + n) return dp[m];
    I.resize(n);
    A.resize(n);
    for(int i = 0; i < n; i++) {
        I[i] = ik;
        A[i] = ik;
    }
    // dp[m] = /Sum_{i=0}^{n-1} A_i * dp[m - i - 1]
    LL dlt = (m - n) / n;
    LL rdlt = dlt * n;
    while(dlt) {
        if(dlt & 1LL) I = mul(I , A);
        A = mul(A , A);
        dlt >>= 1LL;
    }
    LL ans = 0;
    for(int i = 0; i < n; i++) {
        (ans += I[i] * dp[m - i - 1 - rdlt] % MOD) %= MOD;
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    LL n_, k_;
    int t; cin >> t; while (t--) {
        cin >> k_ >> n_;
        n = k_;
        m = n_;
        ik = inv(k_);
        LL ans;
        if (n_ == -1) {
            ans = mul(2, inv(k_ + 1));
        } else {
            ans = solve();
        }
        printf("%lld\n", ans);
    }
}
*/

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2048;
constexpr int mod = 1e9 + 7;
constexpr int MOD = 1e9 + 7;
typedef long long LL;
inline int add(int a, int b) {
    a += b;
    return a >= mod ? a - mod : a;
}
inline int sub(int a, int b) {
    a -= b;
    return a < 0 ? a + mod : a;
}
inline int mul(LL a, int b) {
    a *= b;
    return a >= mod ? a % mod : a;
}
inline int mpow(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1) {
            r = mul(r, a);
        }
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}
inline int inv(int x) {
    return mpow(x, mod - 2);
}

LL n , m, ik;
constexpr int MAX_N = 1024;
LL dp[MAX_N<<1];

inline vector<LL> mul(vector<LL>& v1 , vector<LL>& v2) {
    int sz1 = (int)v1.size();
    int sz2 = (int)v2.size();
    vector<LL> _v(n + n);
    for(int i = 0; i < n + n; i++) _v[i] = 0;
    // expand
    for(int i = 0; i < sz1; i++) {
        for(int j = 0; j < sz2; j++) {
            (_v[i + j + 1] += v1[i] * v2[j] % MOD) %= MOD;
        }
    }
    // shrink
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= n; j++) {
            (_v[i + j] += _v[i] * ik) %= MOD;
        }
    }
    for(int i = 0; i < n; i++) _v[i] = _v[i + n];
    _v.resize(n);
    return _v;
}
vector<LL> I , A;
inline LL solve() {
    I.resize(n);
    A.resize(n);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &ik);
        I[i] = ik;
        A[i] = ik;
    }
    for(int i = 0; i < n; ++i) scanf("%lld", &dp[i]);
    if(m < n) return dp[m];
    // dp[m] = /Sum_{i=0}^{n-1} A_i * dp[m - i - 1]
    LL dlt = (m - n) / n;
    LL rdlt = dlt * n;
    while(dlt) {
        if(dlt & 1LL) I = mul(I , A);
        A = mul(A , A);
        dlt >>= 1LL;
    }
    LL ans = 0;
    for(int i = 0; i < n; i++) {
        (ans += I[i] * dp[m - i - 1 - rdlt] % MOD) %= MOD;
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    LL n_, k_;
    cin >>n_ >>  k_;
    n = k_;
    m = n_ +1;
    ik = inv(k_);
    LL ans;
    ans = solve();
    printf("%lld\n", (ans+mod)%mod);
    return 0;
}
/*
 * https://blog.csdn.net/litble/article/details/81783267
 *
 * */