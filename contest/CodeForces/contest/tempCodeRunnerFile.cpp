#define LH_LOCAL
// #define LLDO
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
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
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
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
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
#ifdef LLDO
    const char ptout[] = "%lld";
#else
    const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {printf(ptout, f);putchar('\n');}
template <typename T, typename... R>
void print(const T &f, const R &... r) {printf(ptout, f);putchar(' ');print(r...);}

const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;// 998244353
const int MXN = 1e6 + 5;
int n, m;
int cnt[9];
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    // freopen("D:out.out", "w", stdout);
#endif
    cnt[1] = cnt[2] = cnt[4] = 1;
    cnt[3] = cnt[5] = cnt[6] = 2;
    cnt[7] = 3;
    scanf("%d%d\n", &n, &m);
    if(n >= 4 && m >= 4) {
        printf("-1\n");
    }else if(n == 1 || m == 1) {
        printf("0\n");
    }else {
        vector<vector<char>> ar(n + 1, vector<char>(m+1, 0));
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                ar[i][j] = getchar();
            }
            getchar();
        }
        vector<vector<int64>> dp(m + 1, vector<int64>(9, INF));
        if(n == 2) {
            int tx = 4;
            for(int i = 0; i < tx; ++i) {
                dp[1][i] = 0;
                for(int j = 0; j < n; ++j) {
                    if(ar[1][j + 1] - '0' != ((i>>j)&1)) {
                        ++ dp[1][i];
                    }
                }
            }
            for(int i = 2; i <= m; ++i) {
                for(int j = 0; j < tx; ++j) {
                    int tnum = 0;
                    for(int h = 0; h < n; ++h) {
                        if(ar[i][h + 1] - '0' != ((i>>h)&1)) {
                            ++ tnum;
                        }
                    }
                    for(int k = 0; k < tx; ++k) {
                        int flag = 1, num = cnt[j] + cnt[k];
                        if(num % 2 == 1) {
                            dp[i][j] = min(dp[i][j], dp[i-1][k] + tnum);
                        }
                    }
                }
            }
            for(int i = 0; i < tx; ++i) dp[m][0] = min(dp[m][0], dp[m][i]);
        }else {
            int tx = 8;
            for(int i = 0; i < tx; ++i) {
                dp[1][i] = 0;
                for(int j = 0; j < n; ++j) {
                    if(ar[1][j + 1] - '0' != ((i>>j)&1)) {
                        ++ dp[1][i];
                    }
                }
            }
            for(int i = 2; i <= m; ++i) {
                for(int j = 0; j < tx; ++j) {
                    int tnum = 0;
                    for(int h = 0; h < n; ++h) {
                        if(ar[i][h + 1] - '0' != ((i>>h)&1)) {
                            ++ tnum;
                        }
                    }
                    for(int k = 0; k < tx; ++k) {
                        int flag = 1, num1 = cnt[j & 3] + cnt[k & 3];
                        int num2 = cnt[j>>1] + cnt[k>>1];
                        if(num1 % 2 == 1 && num2 % 2 == 0) {
                            dp[i][j] = min(dp[i][j], dp[i-1][k] + tnum);
                        }
                    }
                }
            }
            for(int i = 0; i < tx; ++i) dp[m][0] = min(dp[m][0], dp[m][i]);
        }
        printf("%d\n", dp[m][0]);
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}