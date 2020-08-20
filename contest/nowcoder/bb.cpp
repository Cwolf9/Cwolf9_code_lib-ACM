/*
gcd(a,b,c,d)=gcd(a,|b-a|,|c-b|,|d-c|)
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for (register int i = s; i < t; ++i)
#define per(i, s, t) for (register int i = s; i >= t; --i)
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
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
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int INF = 0x3f3f3f3f;
const int mod = 998244353;  // 998244353
const int MXN = 2e5 + 5;
int n, m;
int ksm(int a, int b, int MOD) {
    int res = 1;
    for (; b > 0; b >>= 1, a = (int64)a * a % MOD) {
        if (b & 1) res = (int64)res * a % MOD;
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    // for(int t = 1000000000; ; --t) {
    //     int f = 1;
    //     for(int i = 2; i * i <= t; ++i) {
    //         if(t % i == 0) {
    //             f = 0;
    //             break;
    //         }
    //     }
    //     if(f) {
    //         debug(t)
    //         break;
    //     }
    // }
    int tim = read();
    assert(tim <= 500 && tim >= 1);
    int64 cnt = 0;
    while(tim --) {
        int p = read();
        if(p <= 2) {
            printf("0\n");
            continue;
        }
        cnt += p;
        // assert(cnt <= 2000000000);
        int stp = min(100000, p - 1);
        vector<pii> vs, vs2;
        vector<int> inv(stp + 1, 0);
        inv[1] = 1;
        for(int i = 2; i <= stp; ++i) {
            inv[i] = ((int64)p - p / i)*inv[p % i] % p;
            // if(i <= 10 && SZ(vs)) debug(i, inv[i], vs.back().se)
            // if(inv[i] == 0) debug(i)
            if(vs.empty()||inv[i] <= vs.back().se) {
                vs.eb(mk(i, inv[i]));
                if(i != inv[i]) vs2.eb(mk(inv[i], i));
            }
        }
        for(pii x: vs2) vs.eb(x);
        my_unique(vs);
        printf("%d\n", SZ(vs));
        for(pii x: vs) printf("%d %d\n", x.fi, x.se);
        vector<pii>().swap(vs);
        vector<pii>().swap(vs2);
    }
#ifndef ONLINE_JUDGE
#endif
    return 0;
}
/*

*/