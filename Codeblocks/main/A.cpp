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
const int mod = 998244353;// 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 5;
int n, m;
char s[MXN];
bool cmp(const pii&a, const pii&b) {
    return a.se < b.se;
}
int sum[MXN << 2];
void build(int l, int r, int rt) {
    sum[rt] = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
}
void update2(int p, int l, int r, int rt) {
    if(l == r) {
        sum[rt] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update2(p, l, mid, rt << 1);
    else update2(p, mid + 1, r, rt << 1 | 1);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void update(int p, int l, int r, int rt) {
    if(l == r) {
        sum[rt] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update(p, l, mid, rt << 1);
    else update(p, mid + 1, r, rt << 1 | 1);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
int query(int L, int R, int l, int r, int rt) {
    if(sum[rt] == 0 || L > R) return 0;
    if(l == r) {
        sum[rt] = 0;
        return l;
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if(L > mid) ans = query(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) ans = query(L, R, l, mid, rt << 1);
    else {
        if(sum[rt << 1 | 1]) ans = query(mid + 1, R, mid + 1, r, rt << 1 | 1);
        else ans = query(L, mid, l, mid, rt << 1);
    }
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    // freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    while(~scanf("%d", &n)) {
        scanf("%s", s + 1);
        vector<int> two;
        vector<pii> cw;
        for(int i = 1; i <= n; ++i) {
            if(s[i] == '2') two.emplace_back(i);
            else if(s[i] == '0' && !two.empty()) {
                cw.emplace_back(mk(two.back(), i));
                two.pop_back();
            }
        }
        build(1, n, 1);
        reverse(all(cw));
        for(pii x: cw) update(x.fi, 1, n, 1);
        int ans = 0;
        reverse(all(cw));
        for(pii x: cw) {
            // debug(x.fi, x.se)
            int tmp = query(x.se + 1, n, 1, n, 1);
            if(tmp) {
                ++ ans;
            }
            update2(x.fi, 1, n, 1);
        }
        printf("%d\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
