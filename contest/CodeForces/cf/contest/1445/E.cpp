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
const int MXN = 1e6 + 5;

int n, m, k;
int col[MXN], can_use[MXN], fa[MXN], rnk[MXN];
vector<pii> edge, same;
int Fi(int x) {
	return fa[x] == x? x: Fi(fa[x]);
}
pii ecol(pii e) {
	return mk(col[e.fi], col[e.se]);
}
int top;
struct lh {
    int u, v;
}stak[MXN];
int Union(int a, int b) {
	debug(n)
	int pu = Fi(a), pv = Fi(b + n);
	if(pu == pv) return 0;
	if(rnk[pu] > rnk[pv]) swap(pu, pv);
	fa[pu] = pv, rnk[pv] += rnk[pu];
	stak[++ top] = {pu, pv};
	return 1;
}
void work() {
	n = read(), m = read(), k = read();
	int64 ans = k;
	rep(i, 1, n + 1) col[i] = read();
	rep(i, 0, n + n + 1) fa[i] = i, rnk[i] = 1;
	rep(i, 1, k + 1) can_use[i] = 1;
	rep(i, 1, m + 1) {
		int u = read(), v = read();
		if(col[u] > col[v]) swap(u, v);
		if(col[u] != col[v]) edge.eb(mk(u, v));
		else same.eb(mk(u, v));
	}
	auto cmp = [&](const pii&a, const pii&b) {
		return mk(col[a.fi], col[a.se]) < mk(col[b.fi], col[b.se]);
	};
	sort(all(edge), cmp);
	for(pii e: same) {
		if(Fi(e.fi) == Fi(e.se) || can_use[col[e.fi]] == 0) {
			can_use[col[e.fi]] = 0;
			continue;
		}
		Union(e.fi, e.se);
		Union(e.se, e.fi);
	}
	rep(i, 1, k + 1) if(can_use[i] == 0) -- ans;
	ans = ans * (ans - 1) / 2;
	int L = 0;
	rep(i, 0, SZ(edge)) {
		if(i == SZ(edge) - 1 || ecol(edge[i]) != ecol(edge[i + 1])) {
			int flag = 1, las = top;
			rep(j, L, i + 1) {
				pii e = edge[j];
				if(can_use[col[e.fi]] == 0 || can_use[col[e.se]] == 0) {
					flag = -1;
					break;
				}
				if(Fi(e.fi) == Fi(e.se)) {
					flag = 0;
					break;
				}
				Union(e.fi, e.se);
				Union(e.se, e.fi);
			}
			while(top > las) {
				if(rnk[stak[top].u] > rnk[stak[top].v]) {
					fa[stak[top].v] = stak[top].v;
					rnk[stak[top].u] -= rnk[stak[top].v];
		        }else {
				    fa[stak[top].u] = stak[top].u;
					rnk[stak[top].v] -= rnk[stak[top].u];
				}
				-- top;
			}
			if(flag == 0) -- ans;
			L = i + 1;
		}
	}
	printf("%lld\n", ans);
}
int main() {
#ifdef LH_LOCAL
    freopen("D:/ACM/mtxt/in.txt", "r", stdin);
    // freopen("D:/ACM/mtxt/out.txt", "w", stdout);
#endif
    for(int cas = 1, tim = 1; cas <= tim; ++ cas) {
        // printf("Case #%d:\n", cas);
        work();
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
