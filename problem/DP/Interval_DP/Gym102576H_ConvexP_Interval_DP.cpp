/*
链接：
[点我点我](https://codeforces.com/gym/102576/problem/H)
题意：
输入按逆时针方向给出n个点的凸多边形，以及m条可行路径。
输出一条不自交的最长路径的长度。
思路：
区间dp
dp[i][j][0]表示只考虑凸包逆时针[i,j]内的点，下一步从i出发的最远距离
dp[i][j][1]表示只考虑凸包逆时针[i,j]内的点，下一步从j出发的最远距离
转移的时候枚举区间外的点，由小区间更新大区间，我为人人
*/
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 3e2 + 5;
const int MXE = MXN * MXN + 5;
int n, m;

typedef pair<int64, int64> pLL;
int main() {
#ifdef LH_LOCAL
    freopen("D:in.txt", "r", stdin);
    //freopen("D:out.txt", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read();
        vector<pLL> pnt(n + 1);
        vector<vector<bool>> mp(n + 1, vector<bool>(n + 1, false));
        vector<vector<double>> dis(n + 1, vector<double>(n + 1));
        vector<vector<vector<double>>> dp(n + 1, vector<vector<double>>(n + 1, vector<double>(2, -1e18)));
        rep(i, 1, n + 1) {
            pnt[i].fi = read(), pnt[i].se = read();
        }
        function<double(pLL, pLL)> dis_p_p = [](pLL a, pLL b) {
            return sqrt((double)(a.fi - b.fi)*(a.fi - b.fi) + (double)(a.se - b.se)*(a.se - b.se));
        };
        function<int(int, int)> nxt = [n](int x, int d) {
            x = (x + d) % n;
            if(x == 0) return n;
            return x;
        };
        rep(i, 1, n + 1) {
            rep(j, i, n + 1) {
                dis[i][j] = dis[j][i] = dis_p_p(pnt[i], pnt[j]);
            }
            dp[i][i][0] = dp[i][i][1] = 0;
        }
        m = read();
        rep(i, 1, m + 1) {
            int a = read(), b = read();
            mp[a][b] = mp[b][a] = true;
            dp[a][b][0] = dp[a][b][1] = dis[a][b];
            dp[b][a][0] = dp[b][a][1] = dis[b][a];
        }
        rep(d, 1, n) {
            rep(i, 1, n + 1) {
                int j = nxt(i, d);
                for(int k = nxt(j, 1); k ^ i; k = nxt(k, 1)) {
                    if(mp[i][k]) {
                        dp[i][k][1] = big(dp[i][k][1], dis[i][k] + dp[i][j][0]);
                        dp[k][j][0] = big(dp[k][j][0], dis[i][k] + dp[i][j][0]);
                    }
                    if(mp[j][k]) {
                        dp[i][k][1] = big(dp[i][k][1], dis[j][k] + dp[i][j][1]);
                        dp[k][j][0] = big(dp[k][j][0], dis[j][k] + dp[i][j][1]);
                    }
                }
            }
        }
        double ans = 0;
        rep(i, 1, n + 1) {
            rep(j, 1, n + 1) {
                ans = big(dp[i][j][0], dp[i][j][1], ans);
                //debug(i, j, dp[i][j][0], dp[i][j][1])
            }
        }
        printf("%.10f\n", ans);
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
