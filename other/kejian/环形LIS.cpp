#include <bits/stdc++.h>
using namespace std;
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
inline long long read() {
    long long x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(long long x, bool f = true) {
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 2e5 + 5;

#define fi first
#define se second
#define mk make_pair
#define o2(x) (x) * (x)
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
int dp[MXN], ar[MXN];
int sum[MXN<<2];
void build(int l, int r, int rt) {
    sum[rt] = INF;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
}
void update(int p, int v, int l, int r, int rt) {
    if(l == r) {
        sum[rt] = v;
        return ;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update(p, v, l, mid, rt << 1);
    else update(p, v, mid + 1, r, rt << 1 | 1);
    sum[rt] = min(sum[rt << 1], sum[rt << 1 | 1]);
}
int query(int L, int R, int l, int r, int rt) {
    if(L > R) return INF;
    if(L <= l && r <= R) return sum[rt];
    int mid = (l + r) >> 1;
    if(L > mid) return query(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) return query(L, R, l, mid, rt << 1);
    else return min(query(L, mid, l, mid, rt << 1), query(mid + 1, R, mid + 1, r, rt << 1 | 1));
}
//暂时有问题
int main() {
#ifdef LH_LOCAL
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
#endif
    int n = read();
    int l = 1, ans = 0;
    rep(i, 1, n + 1) ar[i] = ar[i + n] = read();
    fill(dp, dp + n + n + 1, INF);
    build(1, n + n, 1);
    rep(i, 1, n + n + 1) {
        while(l < i && i - query(l, i - 1, 1, n + n, 1) >= n) ++ l;
        int p = lower_bound(dp + l, dp + n + n + 1, ar[i]) - dp;
        dp[p] = ar[i];
        update(p, i, 1, n + n, 1);
        ans = max(ans, p - l + 1);
        debug(l, p)
    }
    printf("%d\n", ans);
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
/* 
5
2 3 4 5 1
 */
