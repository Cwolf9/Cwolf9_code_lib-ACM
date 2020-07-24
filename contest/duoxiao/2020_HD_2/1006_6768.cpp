/*
**链接**

**题意**

**思路**

**备注**

*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
#define clr(a, b) memset((a), (b), sizeof((a)))
using namespace std;
typedef long long int64;
typedef pair<int, int> pii;
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T& f, const R&... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
const int HMOD[] = {1000000009, 1004535809};
const int mod = 998244353;
const int mod2 = 1e9 + 9;
const int INF = 0x3f3f3f3f;
const int MXN = 2e6 + 5;
const int MXE = 1e7 + 5;
int n, m, k;
int ar[MXN];
int64 x[MXN], y[MXN];
int64 a[10], b[10];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    x[1] = 1;
    y[1] = 0;
    x[2] = 0;
    y[2] = 1;
    for(int i = 3; i < MXN; ++i) {
        x[i] = (x[i-1] + x[i-2]) % mod;
        y[i] = (y[i-1] + y[i-2]) % mod2;
    }
    int tim = read();
    while (tim--) {
        n = read();
        clr(a, 0);
        clr(b, 0);
        for(int i = 1, z; i <= n; ++i) {
            z = read();
            if(z == 0) continue;
            a[0] += x[i];
            b[0] += y[i];
            a[0] %= mod;
            b[0] %= mod2;
        }
        m = read();
        for(int i = 1, z; i <= m; ++i) {
            z = read();
            if(z == 0) continue;
            a[1] += x[i];
            b[1] += y[i];
            a[1] %= mod;
            b[1] %= mod2;
        }
        // debug(a[0], b[0], a[1], b[1])
        a[3] = (a[0] * b[0] % mod + 2 * a[1] * b[1] % mod)%mod;
        b[3] = (a[0] * b[1] % mod2 + a[1] * b[0] % mod2 + a[1] * b[1] % mod2)%mod2;
        // debug(a[3], b[3])
        k = read();
        for(int i = 1, z; i <= k; ++i) {
            z = read();
            ar[i] = z;
            if(z == 0) continue;
            a[2] += x[i];
            b[2] += y[i];
            a[2] %= mod;
            b[2] %= mod2;
        }
        // debug(a[2], b[2])
        int ans = 0;
        for(int i = 1; i <= k; ++i) {
            if(ar[i] == 0) {
                a[2] += x[i];
                b[2] += y[i];
                a[2] %= mod;
                b[2] %= mod2;
                // debug(a[2], b[2])
                if((a[2]+b[2]+b[2])%HMOD[1] == (a[3] + b[3] + b[3]) % HMOD[1]) {
                    ans = i;
                    break;
                }
                a[2] -= x[i];
                b[2] -= y[i];
                a[2] %= mod;
                b[2] %= mod2;
                if(a[2] < 0) a[2] += mod;
                if(b[2] < 0) b[2] += mod2;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}