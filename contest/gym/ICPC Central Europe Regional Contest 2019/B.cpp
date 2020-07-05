#pragma comment(linker, "/STACK:102400000,102400000")
#include <assert.h>
#include <bits/stdc++.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb push_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline LL read() {
    LL x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(LL x, bool f) {
    if (x == 0) {
        putchar('0');
        if (f)
            putchar('\n');
        else
            putchar(' ');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[23];
    int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f)
        putchar('\n');
    else
        putchar(' ');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {
    return a1 > a2 ? a1 : a2;
}
template <class T>
T sml(const T &a1, const T &a2) {
    return a1 < a2 ? a1 : a2;
}
template <typename T, typename... R>
T big(const T &f, const R &... r) {
    return big(f, big(r...));
}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {
    return sml(f, sml(r...));
}
void debug_out() { cerr << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cerr << f << " ";
    debug_out(r...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 998244353;
const double eps = 1e-6;
const int MOD = 1e9 + 7;  // 998244353
const int INF = 0x3f3f3f3f;
const int MXN = 2e5 + 7;
const int MXE = 2e5 + 7;
int n, m, k;
int ar[MXN], dp[MXN][20], pos[MXN][20];
LL ans, ret;
std::vector<pair<LL,int> > myl[MXN], myr[MXN];
int gcd(int a,int b) {
    return b == 0? a: gcd(b, a%b);
}
void init_ans() {
    for(int j = 1; j < 20; ++j) {
        if((1<<(j-1)) > n) break;
        for(int i = 1; i + (1<<j) - 1 <= n; ++i) {
            if(dp[i][j-1] >= dp[i+(1<<(j-1))][j-1]) {
                dp[i][j] = dp[i][j-1];
                pos[i][j] = pos[i][j-1];
            }else {
                dp[i][j] = dp[i+(1<<(j-1))][j-1];
                pos[i][j] = pos[i+(1<<(j-1))][j-1];
            }
        }
    }
    myl[0].clear();
    for(int i = 1, last; i <= n; ++i) {
        myl[i].clear();
        myl[i].push_back({ar[i], i});
        last = ar[i];
        for(int j = 0, tmp; j < myl[i-1].size(); ++j) {
            tmp = gcd(ar[i], myl[i-1][j].fi);
            if(tmp == last) {
                myl[i].back().se = myl[i-1][j].se;
            }else {
                myl[i].push_back({tmp, myl[i-1][j].se});
            }
            last = tmp;
        }
    }
    myr[n+1].clear();
    for(int i = n, last; i >= 1; --i) {
        myr[i].clear();
        myr[i].push_back({ar[i], i});
        last = ar[i];
        for(int j = 0, tmp; j < myr[i+1].size(); ++j) {
            tmp = gcd(ar[i], myr[i+1][j].fi);
            if(tmp == last) {
                myr[i].back().se = myr[i+1][j].se;
            }else {
                myr[i].push_back({tmp, myr[i+1][j].se});
            }
            last = tmp;
        }
    }
}
inline int query(int l, int r) {
    int k = log(r - l + 1) / log(2);
    if (dp[l][k] >= dp[r - (1 << k) + 1][k]) return pos[l][k];
    return pos[r - (1 << k) + 1][k];
}
LL solve(int l, int r) {
    if(l > r) return 0;
    if(l == r) return (LL)ar[l] * ar[l] % MOD;
    int mid = query(l, r);
    // debug(l, r, mid)
    ans = ret = 0;
    if(r - mid > mid - l) {
        for(int i = l ; i <= mid; ++i) {
            for(int j = 0, L, R; j < SZ(myr[i]); ++j) {
                if(myr[i][j].se < mid) continue;
                else if(myr[i][j].se >= r) {
                    R = r;
                    if(j == 0) L = mid;
                    else L = max(mid, myr[i][j-1].se + 1);
                    ans = (ans + (R-L+1)*myr[i][j].fi % MOD * ar[mid] % MOD) % MOD;
                    break;
                }else {
                    R = myr[i][j].se;
                    if(j == 0) L = mid;
                    else L = max(mid, myr[i][j-1].se + 1);
                    ans = (ans + (R-L+1)*myr[i][j].fi % MOD * ar[mid] % MOD) % MOD;
                }
            }
        }
    }else {
        for(int i = mid; i <= r; ++i) {
            for(int j = 0, L, R; j < SZ(myl[i]); ++j) {
                if(myl[i][j].se > mid) continue;
                else if(myl[i][j].se <= l) {
                    L = l;
                    if(j == 0) R = mid;
                    else R = min(mid, myl[i][j-1].se - 1);
                    ans = (ans + (R-L+1)*myl[i][j].fi % MOD * ar[mid] % MOD) % MOD;
                    break;
                }else {
                    L = myl[i][j].se;
                    if(j == 0) R = mid;
                    else R = min(mid, myl[i][j-1].se - 1);
                    ans = (ans + (R-L+1)*myl[i][j].fi % MOD * ar[mid] % MOD) % MOD;
                }
            }
        }
    }
    // debug(l, r, mid, ans)
    LL rex = ans;
    return (rex + solve(l, mid - 1) + solve(mid + 1, r))%MOD;
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("E://ADpan//in.in", "r", stdin);
    // freopen("E://ADpan//out.out", "w", stdout);
#endif
    n = read();
    for(int i = 1; i <= n; ++i) ar[i] = read(), dp[i][0] = ar[i], pos[i][0] = i;
    init_ans();
    printf("%lld\n", solve(1, n));
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}