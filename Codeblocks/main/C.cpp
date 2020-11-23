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
    int64 x = 0;int las = 0;char ch = getchar();
    while (ch < '0' || ch > '9') las |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = las ? -x : x;
}
inline void write(int64 x, bool las = true) {
    if (x == 0) {putchar('0'); if(las)putchar('\n');else putchar(' ');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(las)putchar('\n');else putchar(' ');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {return a1 > a2 ? a1 : a2;}
template <class T>
T sml(const T &a1, const T &a2) {return a1 < a2 ? a1 : a2;}
template <typename T, typename... R>
T big(const T &las, const R &... r) {return big(las, big(r...));}
template <typename T, typename... R>
T sml(const T &las, const R &... r) {return sml(las, sml(r...));}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &las, const R &... r) {
    cout << las << " ";
    debug_out(r...);
}
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int mod = 998244353;// 998244353
const int INF = 0x3f3f3f3f;
int ksm(int a, int64 b, int kmod = mod) {int res = 1;for(;b > 0;b >>= 1, a = (int64)a * a % kmod) if(b &1) res = (int64)res * a % kmod;return res;}
const int MXN = 1e2 + 5;

int n, m;
int ar[MXN];
int64 T, ans;
vector<int> vs, vt;
vector<int64> sum, tum;
void work() {
	n = read();
	T = read();
	for(int i = 1; i <= n; ++i) ar[i] = read();
	sort(ar + 1, ar + n + 1);
	for(int i = 1; i <= n; ++i) {
		if(i <= n / 2) vs.eb(ar[i]);
		else vt.eb(ar[i]);
	}
	n = vs.size();
	m = 1 << n;
	for(int i = 1; i < m; ++i) {
		int64 res = 0;
		for(int j = 0; j < n; ++j) 
			if(i & (1 << j)) res += vs[j];
		if(res <= T) ans = max(ans, res);
		if(ans == T) break;
		if(res < T) sum.eb(res);
	}
	n = vt.size();
	m = 1 << n;
	for(int i = 1; i < m; ++i) {
		int64 res = 0;
		for(int j = 0; j < n; ++j) 
			if(i & (1 << j)) res += vt[j];
		if(res <= T) ans = max(ans, res);
		if(ans == T) break;
		if(res < T) tum.eb(res);
	}
	sort(all(tum));
	for(int x: sum) {
		if(x > T) continue;
		int p = upper_bound(all(tum), T - x) - tum.begin();
		if(p != 0) ans = max(ans, tum[p - 1] + x);
        if(ans == T) break;
	}
	printf("%lld\n", ans);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:/ACM/mtxt/in.txt", "r", stdin);
    // freopen("D:/ACM/mtxt/out.txt", "w", stdout);
#endif
    for(int cas = 1, tim = 1; cas <= tim; ++ cas) {
        work();
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}