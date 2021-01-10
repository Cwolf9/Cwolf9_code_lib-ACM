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
struct Point {
    int x;
    int y;
};
struct Interval {
    int start;
    int end;
    Interval(int s, int e) : start(start), end(e) {}
};
/*================Header Template==============*/
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
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;// 998244353
const int MXN = 1e5 + 5;
const int MXE = MXN * 2 + 1;
class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size(), all = 1 << n;
        if(k >= n) {
            int ans = 0;
            for(int i: jobs) ans = max(ans, i);
            return ans;
        }
        vector<int> val(1 << n, 0), num(all, 0);
        for(int i = 1; i < all; ++i) {
            int res = 0, ret = 0;
            for(int j = 0; j < n; ++j) {
                if(i & (1 << j)) res += jobs[j], ++ ret;
            }
            val[i] = res;
            num[i] = ret;
        }
        vector<vector<int>> dp(all, vector<int>(k + 1, 0));
        for(int i = 1; i < all; ++i) {
            for(int j = 1; j <= k; ++j) {
                if(j > num[i]) continue;
                if(j == 1) {
                    dp[i][j] = val[i];
                    continue;
                }
                for(int h = 1; h < i; ++h) {
                    if((h & i) == h) {
                        if(dp[i][j] == 0 && num[h] >= j - 1) {
                            dp[i][j] = max(dp[h][j - 1], val[i ^ h]);
                        }else if(num[h] >= j - 1) {
                            dp[i][j] = min(dp[i][j], max(dp[h][j - 1], val[i ^ h]));
                        }
                    }
                }
            }
        }
        return dp[all - 1][k];
    }
};
Solution s;
int main() {
#ifdef LH_LOCAL
    //freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    //freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    vector<int> U = vector<int>{3,4,6, 16};
    vector<int> V = vector<int>{1,3,4,5,2,6,8,7,9};
    vector<int> VAL = vector<int>{1,7,4,0,9,4,8,8,2,4};
    vector<Interval> IntV = vector<Interval>{Interval(0, 2), Interval(4, 7), Interval(9, 9)};
    vector<vector<int> > vvInt = vector<vector<int> >{{1,2},{2,4},{4,8}};
    vector<Point> par = vector<Point>{{1, 2},{3,4}};
    auto x = s.minimumTimeRequired(U, 3);
    if(1) {
        debug(x)
    }else {
        // for(int y: x) printf("%d ", y);
        printf("\n");
    }
#ifdef LH_LOCAL
#endif
    return 0;
}

/*

*/
