/*
**题意**
[点我点我](https://codeforces.com/gym/102769/problem/B)
'#'和'.'分别代表干地和湿地，只能在干地上建长方形围墙。
$n,m,q\le 1000$，$n*m$的地图有$q$次操作。
操作1：修改(x,y)干湿性；
操作2：询问经过(x,y)点的长方形围墙的最大面积(长乘宽)。
**解析**
枚举该点在上下左右四条边的情况，旋转地图重来四次答案取最大值即可。
现在只考虑该点在下面这条边：
维护每个点向上向左向右最多有几块干地。
然后枚举上边的高度，线段树查询是否有两个柱子即可。柱子就是左右两条边。
复杂度：$O(4*q*n*log(m)*\alpha)$
**AC_CODE**
[点我点我]()
*/
// #pragma comment(linker, "/STACK:102400000,102400000")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize(3,"Ofast","inline")
// #pragma GCC optimize("Ofast,no-stack-protector")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
const int MXN = 1e3 + 5;
const int MXE = 2e6 + 5;
int n, m;
int q;
char _pic[MXN][MXN], ret[MXN][MXN];
int qry[MXN][3];
int ans[MXN];
class ST {
    public:
    int sum[MXN<<2][2];
    void push_up(int rt) {
        sum[rt][0] = min(sum[rt << 1][0], sum[rt << 1 | 1][0]);
        sum[rt][1] = max(sum[rt << 1][1], sum[rt << 1 | 1][1]);
    }
    void build(int l, int r, int rt) {
        if(l == r) {
            sum[rt][0] = INF;
            sum[rt][1] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
        push_up(rt);
    }
    void single(int p, int l, int r, int rt) {
        if(l == r) {
            sum[rt][0] = l;
            sum[rt][1] = l;
            return;
        }
        int mid = (l + r) >> 1;
        if(p <= mid) single(p, l, mid, rt << 1);
        else single(p, mid + 1, r, rt << 1 | 1);
        push_up(rt);
    }
    int query(int id, int L, int R, int l, int r, int rt) {
        if(L <= l && r <= R) return sum[rt][id];
        int mid = (l + r) >> 1;
        if(L > mid) return query(id, L, R, mid + 1, r, rt << 1 | 1);
        else if(R <= mid) return query(id, L, R, l, mid, rt << 1);
        else {
            int a = query(id, L, mid, l, mid, rt << 1);
            int b = query(id, mid + 1, R, mid + 1, r, rt << 1 | 1);
            if(id == 0) return min(a, b);
            return max(a, b);
        }
    }
}tree;
class Solution {
    public:
    int n, m, q;
    char pic[MXN][MXN];
    int up[MXN][MXN];
    int ls1[MXN][MXN], rs1[MXN][MXN];
    vector<int> vq[MXN];
    void init(int _n, int _m, int _q) {
        n = _n, m = _m, q = _q;
        rep(i, 1, n + 1) memcpy(pic[i] + 1, _pic[i] + 1, m + 2);
        rep(i, 1, n + 1) rs1[i][m + 1] = 0;
        rep(i, 1, n + 1) {
            rep(j, 1, m + 1) {
                if(pic[i][j] == '#') {
                    up[i][j] = up[i - 1][j] + 1;
                    ls1[i][j] = ls1[i][j - 1] + 1;
                }else ls1[i][j] = up[i][j] = 0;
            }
            per(j, m, 1) {
                if(pic[i][j] == '#') rs1[i][j] = rs1[i][j + 1] + 1;
                else rs1[i][j] = 0;
            }
        }
        rep(qi, 1, q + 1) {
            int x = qry[qi][1], y = qry[qi][2];
            if(qry[qi][0] == 1) {
                if(pic[x][y] == '#') pic[x][y] = '.';
                else pic[x][y] = '#';
                rep(i, x, n + 1) {
                    if(pic[i][y] == '#') up[i][y] = up[i - 1][y] + 1;
                    else up[i][y] = 0;
                }
                rep(j, y, m + 1) {
                    if(pic[x][j] == '#') ls1[x][j] = ls1[x][j - 1] + 1;
                    else ls1[x][j] = 0;
                }
                per(j, y, 1) {
                    if(pic[x][j] == '#') rs1[x][j] = rs1[x][j + 1] + 1;
                    else rs1[x][j] = 0;
                }
            }else {
                if(pic[x][y] == '.') continue;
                ans[qi] = max(1, ans[qi]);
                int ls = y - ls1[x][y] + 1, rs = y + rs1[x][y] - 1;
                rep(j, ls, rs + 1) vq[up[x][j]].eb(j);
                // debug(ls, rs)
                tree.build(1, m, 1);
                per(i, n, 1) {
                    if(x - i + 1 < 1) {
                        vq[i].clear();
                        continue;
                    }
                    for(int ps: vq[i]) {
                        tree.single(ps, 1, m, 1);
                    }
                    vq[i].clear();
                    if(pic[x - i + 1][y] == '.') continue;
                    int Mn = tree.query(0, y - ls1[x - i + 1][y] + 1, y + rs1[x - i + 1][y] - 1, 1, m, 1);
                    int Mx = tree.query(1, y - ls1[x - i + 1][y] + 1, y + rs1[x - i + 1][y] - 1, 1, m, 1);
                    if(Mx >= y && Mn <= y) {
                        ans[qi] = max(ans[qi], (Mx - Mn + 1) * i);
                    }
                    // debug(i, Mx, Mn, y, ans[qi])
                }
            }
        }
    }
}sol;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    int cas = 0;
    while(tim --) {
        n = read(), m = read();
        q = read();
        rep(i, 1, n + 1) scanf("%s", _pic[i] + 1);
        rep(i, 1, q + 1) {
            rep(j, 0, 3) scanf("%d", &qry[i][j]);
            ans[i] = 0;
        }
        sol.init(n, m, q);
        // rep(i, 1, q + 1) if(qry[i][0] == 2) printf("%d\n", ans[i]);
        // return 0;
        rep(j, 1, m + 1) {
            rep(i, 1, n / 2 + 1) {
                swap(_pic[i][j], _pic[n + 1 - i][j]);
            }
        }
        rep(i, 1, q + 1) {
            qry[i][1] = n + 1 - qry[i][1];
        }
        sol.init(n, m, q);

        rep(i, 1, n + 1) {
            rep(j, 1, m + 1) {
                ret[j][i] = _pic[i][j];
            }
        }
        swap(n, m);
        rep(i, 1, n + 1) {
            rep(j, 1, m + 1) {
                _pic[i][j] = ret[i][j];
            }
            _pic[i][m + 1] = '\0';
        }
        rep(i, 1, q + 1) swap(qry[i][1], qry[i][2]);
        sol.init(n, m, q);
        
        rep(j, 1, m + 1) {
            rep(i, 1, n / 2 + 1) {
                swap(_pic[i][j], _pic[n + 1 - i][j]);
            }
        }
        rep(i, 1, q + 1) {
            qry[i][1] = n + 1 - qry[i][1];
        }
        sol.init(n, m, q);
        printf("Case #%d:\n", ++ cas);
        rep(i, 1, q + 1) if(qry[i][0] == 2) printf("%d\n", ans[i]);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
/*
2
2 3 2
###
##.
2 2 2
2 1 3
4 3 3
###
#.#
#.#
###
2 3 2
1 3 2
2 3 2

Case #1:
4
3
Case #2:
0
9
*/