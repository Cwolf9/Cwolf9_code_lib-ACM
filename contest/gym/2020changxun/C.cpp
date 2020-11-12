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
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;// 998244353
const int MXN = 1e5 + 5;
const int MXE = 1e6 + 5;
const int maxn = 1e5+7;
int64 n, k, s;

int64 Exgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int64 d = Exgcd(b, a % b, x, y);
    int64 t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}
int id[MXN];
int64 ar[MXN];
int fuck(int64 ansL) {
	int64 c = (ansL + ansL + n - 1) * n / 2 - s;
	if(c == (int64)0) {
    	int64 xx = ansL;
    	//debug(xx)
        rep(i, 0, n) printf("%lld%c", xx + i, " \n"[i == n - 1]);
        return 0;
    }
    int64 A = k + 1, B = n, C = c;
    int64 x = 0, y = 0;
    int64 g = __gcd(A, B);
    if(C % g != 0) return 1;
    A /= g, B /= g, C /= g;
    Exgcd(A, B, x, y);
    x *= C;
    y *= C;
    y %= A;
    if(y > 0) {
        y -= A;
    }
    x = (C - B * y) / A;
    rep(tx, 0, 2) {
		int64 nx = x + B * tx;
    	int64 ny = y - A * tx;
    	ar[1] = ansL - ny;
	    rep(i, 2, n + 1) {
	        ar[i] = ar[i - 1] + 1;
	        if(nx >= n - i + 1 && ar[i - 1] - k >= 0) {
	            id[i] = 1;
	            nx -= n - i + 1;
	            ar[i] = ar[i - 1] - k;
	        }
	    }
	    if(nx == 0) {
	    	rep(i, 1, n + 1) printf("%lld%c", ar[i], " \n"[i == n]);
			return 0;	
		}
	}
    return 1;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    // freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    n = read(), k = read(), s = read();
    //debug(n, k, s)
    int64 L = 1, R = s / n, mid, ansL = 0;
    while(L <= R) {
        mid = (L + R) >> 1;
        if((mid + mid + n - 1) * n / 2 >= s) ansL = mid, R = mid - 1;
        else L = mid + 1;
    }
    //ansL = 6;
    //write(ansL);
    rep(i, -1, 1) {
    	int x = fuck(max(ansL + i, (int64)0));
		if(x == 0) return 0;
	}
    printf("-1\n");
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}