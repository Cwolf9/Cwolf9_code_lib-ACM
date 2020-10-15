/**
 * $T:2e3$, $abcd:1e9$
 * 问有多少对$(x, y)$满足$|x-y|\le c$且$x\bigoplus y \le d, 0\le x\le a, 0\le y\le b$。
 */
#pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(int64 x, bool f = true) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');else putchar(' ');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');else putchar(' ');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {return a1 > a2 ? a1 : a2;}
template <class T>
T sml(const T &a1, const T &a2) {return a1 < a2 ? a1 : a2;}
template <typename T, typename... R>
T big(const T &f, const R &... r) {return big(f, big(r...));}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {return sml(f, sml(r...));}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 5;
LL a, b, c, d;
LL dp[32][2][3][3][2][2];
/*
xor, ip1 = 1 means equal to c, ip1 = 0 means less than c
abs:
|x - y| <= m.
即 x - y <= m && x - y >= -m.
即 m - x + y >= 0 && m + x - y >= 0.
m, x, y 可取 0 或 1, 上述式子取值可以是 -1, 0, 1, 2.
若 [高位] >= 1 , 后面数位就算全取-1最后结果还满足条件，x，y取值不受限制，此位就算大于1也可以按1考虑；
若 [高位] < -1 ,后面就算全取2也一定不行 ，所以直接返回0就行；
又因为只有两个值同时大于等于1的时候才可以返回1。
所以只需考虑上述式子取值为1或0或-1的情况。
为避免负数下标，令-1为0，0为1，1为2
*/
int gp(LL x, int p) {
    return (x >> p) & 1;
}
// vector<pii> vs;
__attribute__((target("avx"), optimize("O3", "unroll-loops")))
LL dfs(int pos, int ip1, int v1, int v2, int lima, int limb, int A, int B) {
    if(v1 < 0 || v2 < 0) return 0;
    if(pos == -1) {
        // if(v1 >= 1 && v2 >= 1) vs.eb(mk(A, B));
        return v1 >= 1 && v2 >= 1;
    }
    if(dp[pos][ip1][v1][v2][lima][limb] != -1) return dp[pos][ip1][v1][v2][lima][limb];
    int upa = lima?gp(a, pos):1;
    int upb = limb?gp(b, pos):1;
    int tc = gp(c, pos), td = gp(d, pos);
    LL ans = 0;
    rep(i, 0, upa + 1) {
        rep(j, 0, upb + 1) {
            int ta = A | (i << pos), tb = B | (j << pos);
            if(ip1 == 1 && (i ^ j) > tc) continue;
            int tip1 = ip1 && (i ^ j) == tc;
            int tv1 = v1, tv2 = v2;
            int x = td + i - j, y = td - i + j;
            tv1 = (tv1 - 1) * 2 + x + 1;
            tv2 = (tv2 - 1) * 2 + y + 1;
            if(v1 >= 2 || tv1 >= 2) tv1 = 2;
            if(v2 >= 2 || tv2 >= 2) tv2 = 2;
            ans += dfs(pos - 1, tip1, tv1, tv2, lima && i == upa, limb && j == upb, ta, tb);
        }
    }
    return dp[pos][ip1][v1][v2][lima][limb] = ans;
}
/*
1. x,y are integers
2. x∈[0,A],y∈[0,B]
3. |x"y|≤K
4. x xor y≤W
*/
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        clr(dp, -1);
        a = read(), b = read(), d = read(), c = read();
        LL ans = dfs(31, 1, 1, 1, 1, 1, 0, 0);
        printf("%lld\n", ans);
        // sort(all(vs));
        // printf("%d\n", vs.size());
        // for(auto x: vs) {
        //     int i = x.fi, j = x.se;
        //     debug(i, j);
        // }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}