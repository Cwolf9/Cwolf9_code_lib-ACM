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
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int mod = 998244353;// 998244353
int ksm(int a, int64 b, int kmod = mod) {int res = 1;for(;b > 0;b >>= 1, a = (int64)a * a % kmod) if(b &1) res = (int64)res * a % kmod;return res;}
const int INF = 0x3f3f3f3f;
const int MXN = 2e2 + 5;

int n, m;
int ar[MXN];
int dp[MXN][MXN][MXN];

void work() {
    n = read();
    rep(i, 1, n + 1) ar[i] = read();
    clr(dp, 0x3f);
    per(i, n - 1, 1) {
        if(i + ar[i] <= n) dp[i][i][n] = 0;
    }
    per(i, n - 2, 1) {
        rep(j, i, n) {
            rep(k, j + 1, n + 1) {
                //i不在当前路径中
                dp[i][j][k] = min(dp[i][j][k], dp[i + 1][j][k] + (i + ar[i] >= j));
                //i在当前路径中
                if(i + ar[i] >= j && i + ar[i] < k) dp[i][i][j] = min(dp[i][i][j], dp[i + 1][j][k]);
            }
        }
    }
    int ans = INF;
    rep(i, 1, n) {
        rep(j, i + 1, n + 1) {
            ans = min(ans, dp[1][i][j]);
        }
    }
    printf("%d\n", ans);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:/ACM/mtxt/in.txt", "r", stdin);
    // freopen("D:/ACM/mtxt/out.txt", "w", stdout);
#endif
    for(int cas = 1, tim = read(); cas <= tim; ++ cas) {
        // printf("Case #%d:\n", cas);
        work();
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
/* 
有$n$个权值，$0\le a_i\le n - i$，当你在第$i$个位置时，你可以移动到$[i+1,i+a_i]$位置中的某一个，最后移动到$n$游戏胜利。
问最少赋值多少个权值为$0$，使得游戏只有一种胜利的走法。
注意：合法的路径中经过的点除了$a_n$不能有$0$。
$2\le n\le 3000$

3
4
1 1 1 0
5
4 3 2 1 0
9
4 1 4 2 1 0 2 1 0

0
3
2
#include<bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int maxn = 3000 + 2;
int dp[maxn][maxn], pre[maxn][maxn], add[maxn], a[maxn];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    for(cin >> t; t; t -= 1){
        int n;
        cin >> n;
        for(int i = 1; i <= n; i += 1) cin >> a[i];
        for(int i = 1; i <= n + 1; i += 1){
            for(int j = 1; j <= n + 1; j += 1){
                dp[i][j] = maxn;
                pre[i][j] = maxn;
            }
            add[i] = 0;
        }
        dp[n][n + 1] = pre[n][n + 1] = 0;
        for(int i = n - 1; i >= 1; i -= 1){
            for(int j = i + 1; j <= n; j += 1)
                if(i + a[i] >= j)
                    dp[i][j] = min(dp[i][j], pre[j][i + a[i] + 1] + add[j]);
                for(int j = n; j > i; j -= 1) pre[i][j] = min(pre[i][j + 1], dp[i][j]);
            for(int j = i + 1; j <= i + a[i]; j += 1) add[j] += 1;
        }
        cout << pre[1][2] << "\n";
    }
    return 0;
}

*/