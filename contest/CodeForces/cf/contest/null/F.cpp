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
const int MXN = 2e5 + 5;

int n, m;
char s[MXN];
int ori[MXN], dwn[MXN];
/*
origin[i] 表示i位置的字符是否原本就在i。
down[i] 表示i位置的字符能否循环移动。
如果i+1的字符能移动到i，需要保证i+1原本就在i+1。
如果i+2的字符能移动到i，需要保证i+1原本就在i+1。
如果经过合法改变后，从i来的字符是最小的就选i位置保持不变，否则如果从i+1来的字符是最小的就选i+1位置，否则如果从i+2来的字符是最小的就选i+2位置，否则就不变。
*/
void work() {
    n = read(), m = read();
    rep(i, 0, n) ori[i] = dwn[i] = 0;
    scanf("%s", s);
    rep(i, 0, n) {
        int a = s[i] - 'a', b = (i + 1 < n && ori[i + 1] == 0? s[i + 1] - 'a': INF), c = (i + 2 < n && ori[i + 1] == 0? s[i + 2] - 'a': INF);
        if(dwn[i] == 0) a = sml(a, (a + 1) % m, (a + m - 1) % m);
        if(b != INF && ori[i] == 0 && dwn[i + 1] == 0 && ori[i + 1] == 0) b = sml(b, (b + 1) % m, (b + m - 1) % m);
        if(a <= b && a <= c) {
            s[i] = a + 'a';
        }else if(b <= a && b <= c) {
            swap(s[i], s[i + 1]);
            if(s[i] != b + 'a') {
                s[i] = b + 'a';
                dwn[i + 1] = ori[i + 1] = 1;
            }else {
                ori[i + 1] = 1;
            }
            if(dwn[i]) dwn[i + 1] = 1;
            if(ori[i]) ori[i + 1] = 1;
        }else if(c <= a && c <= b){
            swap(s[i], s[i + 2]);
            swap(s[i + 1], s[i + 2]);
            if(dwn[i]) dwn[i + 1] = 1;
            ori[i + 1] = 1;
            ori[i + 2] = dwn[i + 2] = 1;
        }
        // debug(i, s)
    }
    printf("%s\n", s);
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
