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
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 2e2 + 5;
int n, m;
int mp[MXN][MXN], vis[MXN][MXN], num[MXN][MXN], ans[MXN][MXN];
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
void dfs(int x, int y, int a, int b) {
    vis[x][y] = 1;
    ++ num[a][b];
    // debug(x, y, a, b, num[a][b])
    rep(i, 0, 4) {
        int px = x + dir[i][0], py = y + dir[i][1];
        if(px < 1 || px > n || py < 1 || py > m) continue;
        if(vis[px][py] == 0 && mp[px][py] == mp[a][b]) {
            dfs(px, py, a, b);
        } 
    }
}
int inde;
bool dfs2(int x, int y, int add) {
    // debug(x, y, a, b, add)
    ans[x][y] += add;
    vis[x][y] = inde;
    rep(i, 0, 4) {
        int px = x + dir[i][0], py = y + dir[i][1];
        if(px < 1 || px > n || py < 1 || py > m) continue;
        if(ans[px][py] == ans[x][y]) {
            if(ans[px][py] != mp[px][py]) {
                ans[x][y] -= add;
                return false;
            }else {
                bool f2 = dfs2(px, py, 1);
                if(!f2) {
                    ans[x][y] -= add;
                    return false;
                }
            }
        }
    }
    return true;
}
void work() {
    inde = 2;
    n = read(), m = read();
    rep(i, 1, n + 1) {
        rep(j, 1, m + 1) {
            ans[i][j] = mp[i][j] = read();
            vis[i][j] = num[i][j] = 0;
        }
    }
    rep(i, 1, n + 1) {
        rep(j, 1, m + 1) {
            if(vis[i][j] == 0) dfs(i, j, i, j);
        }
    }
    rep(i, 1, n + 1) {
        rep(j, 1, m + 1) {
            if(mp[i][j] != ans[i][j]) continue;
            bool ff = 0;
            rep(d, 0, 4) {
                int px = i + dir[d][0], py = j + dir[d][1];
                if(px < 1 || px > n || py < 1 || py > m) continue;
                if(ans[px][py] == ans[i][j]) ff = 1;
            }
            if(ff == 0) continue;
            bool f = dfs2(i, j, 1);
            ++ inde;
            if(!f) {
                dfs2(i, j, 0);
                ++ inde;
            }
        }
    }
    rep(i, 1, n + 1) {
        rep(j, 1, m + 1) {
            printf("%d%c", ans[i][j], " \n"[j == m]);
        }
    }
}
int main() {
#ifdef LH_LOCAL
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
#endif
    for(int cas = 1, tim = read(); cas <= tim; ++ cas) {
        // printf("Case #%d:\n", cas);
        work();
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
