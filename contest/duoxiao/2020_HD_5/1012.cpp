/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;

void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 5e6 + 5;
const int MXE = 2e6 + 6;
int64 ksm(int64 a, int b, int Mod) {int64 res = 1;for(; b; b>>=1, a=a*a%Mod) {if(b&1) res = res * a % Mod;}return res;}
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
int64 inv[MXN];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    inv[1] = 1;
    for(int i = 1; i < MXN; ++i) {
        if(i != 1) inv[i] = (mod - mod / i)*inv[mod % i] % mod;
    }
    int tim = read();
    while(tim --) {
        int n = read();
        int m = n / 2;
        for(int i = 1; i <= m; ++i) printf("0 ");
        int ans = ksm(ksm(2, m, mod), mod - 2, mod);
        printf("%d", ans);
        int two = ksm(2, mod - 2, mod);
        // debug(n, m)
        for(int i = m + 1, j = two, h = 2; i < n; ++i, ++h) {
            ans = (int64)ans * i % mod * j % mod;
            // debug(i, j)
            printf(" %d", ans);
            j = (int64)two * inv[h] % mod;
            // j = ksm()
        }
        printf("\n");
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}