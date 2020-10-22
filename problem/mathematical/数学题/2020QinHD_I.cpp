/*
**题意**
[点我点我](https://codeforces.com/gym/102769/problem/I)
执行$n(1e5)$次操作，共有两类操作：
操作1：获得skill(x,y)，可以随时任意次操作(a+x,b+y)或(a-x,b-y)。
操作2：在(x,y)出现价值为w的宝藏，经过这个地方即可获得。
问获得宝藏的总价值。
**解析**
把每个技能当作一个向量，由两个向量$a,b$构成的张成$span{ra+sb|r,s\in\mathbb{Z}}$等价于
$span{u(a-b)+vb|u,v\in\mathbb{Z}}$，同理可以通过辗转相除法将其中一个向量变成$x$轴方向偏移为$0$。
这样可以轻易判断某个点是否属于张成内。
做法如下：
- 令向量$b$的$x$轴方向偏移为$0$，向量$a$不做约束，新准备加入的向量为$c$。
- 首先让向量$a,c$做辗转相除操作使得向量$c$的$x$轴方向偏移为$0$。
- 然后将向量$c$合并到向量$b$中，新的向量在$y$轴方向偏移为$b_y,c_y$绝对值的最小公因数。
- 为了避免辗转相除过程中$a_y$过大，可以做$a_y%=b_y$处理。
**AC_CODE**
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
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 5;
int n, m;
class Vec {
    public:
    int64 x, y;
    void init() {
        x = y = 0;
    }
    void Rd() {
        x = read();
        y = read();
    }
    void dg() {
        debug(x, y)
    }
}A, B, C;
void Gcd(Vec &A, Vec &C) {
    if(A.x < C.x) swap(A, C);
    if(C.x == 0) return;
    int64 tmp = A.x / C.x;
    A.x = A.x - (tmp * C.x);
    A.y = A.y - (tmp * C.y);
    swap(A, C);
    Gcd(A, C);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    int cas = 0;
    while(tim --) {
        n = read();
        A.init(), B.init();
        long long ans = 0;
        for(int i = 1; i <= n; ++i) {
            int opt = read();
            C.Rd();
            if(opt == 1) {
                if(A.x == 0 && A.y == 0) {
                    A = C;
                }else {
                    Gcd(A, C);
                    B.y = __gcd(B.y, abs(C.y));
                    if(B.y) A.y %= B.y;
                }
                if(B.y < 0) B.y = -B.y;
                // debug(i)
                // debug(A.x, A.y)
                // debug(B.x, B.y)
            }else {
                int w = read();
                // debug(i)
                // A.dg();
                // B.dg();
                if(A.x != 0 && C.x != 0) {
                    int64 tmp = C.x / A.x;
                    C.x = C.x - (A.x * tmp);
                    C.y = C.y - (A.y * tmp);
                }
                if(C.x != 0) continue;
                if(C.y == 0) ans += w;
                else if(B.y != 0 && abs(C.y) % abs(B.y) == 0) ans += w;
            }
        }
        printf("Case #%d: ", ++ cas);
        printf("%lld\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
/*
3
10
1 296196 169349
1 408210 238879
2 489401 201531 141171248
1 447006 359733
1 192393 108966
2 542901 395727 373649074
1 265047 276728
2 309670 417659 533480054
2 360731 340107 280407174
1 382944 320314
3
1 1 1
1 2 1
2 3 2 3
4
1 1 1
2 3 1 1
1 1 3
2 3 1 2
Case #1: 373649074
Case #2: 3
Case #3: 2
*/