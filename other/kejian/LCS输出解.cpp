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
class Solution {
public:
    /**
     * longest common substring
     * @param str1 string字符串 the string
     * @param str2 string字符串 the string
     * @return string字符串
     */
    string LCS(string s, string t) {
        // write code here
        int n = s.length(), m = t.length();
        vector<vector<int>> dp(n, vector<int>(m));
        vector<vector<pii>> pre(n, vector<pii>(m, mk(-1, -1)));
        int a = 0, b = 0;
        rep(i, 0, n) {
            rep(j, 0, m) {
                if(s[i] == t[j]) dp[i][j] = 1 + (i > 0 && j > 0?dp[i-1][j-1]:0), pre[i][j] = mk(i-1,j-1);
                else {
                    if((i > 0?dp[i-1][j]:0) > (j > 0?dp[i][j-1]:0)) {
                        dp[i][j] = (i > 0?dp[i-1][j]:0);
                        pre[i][j] = mk(i - 1, j);
                    }else {
                        dp[i][j] = (j > 0?dp[i][j-1]:0);
                        pre[i][j] = mk(i, j - 1);
                    }
                }
                if(dp[i][j] > dp[a][b]) a = i, b = j;
            }
        }
        if(dp[n - 1][m - 1] == 0) return "-1";
        string ans;
        while(1) {
            ans += s[a];
            int x = pre[a][b].first, y = pre[a][b].second;
            a = x, b = y;
            if(a < 0 || b < 0) break;
            x = pre[a][b].first, y = pre[a][b].second;
            while(x != -1 && y != -1 && dp[x][y] == dp[a][b]) {
                a = x, b = y;
                x = pre[a][b].first, y = pre[a][b].second;
            }
        }
        reverse(all(ans));
        return ans;
    }
};
int main() {
#ifdef LH_LOCAL
    //freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
#endif
    Solution S;
    auto x = S.LCS("1AB2345CD", "12345EF");
    debug(x)
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
