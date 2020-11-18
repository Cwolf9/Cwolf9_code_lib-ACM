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
const int MXN = 5e3 + 5;
int n, m;
class SegT1 {
    public:
#define lson rt << 1
#define rson rt << 1 | 1
    int N;
    vector<int> lazy;
    vector<int64_t> sum;
    SegT1(int N = 0) : N(N), lazy((N << 2) + 5), sum((N << 2) + 5) {}
    void pop(int rt) {
        sum[rt] = (sum[lson] + sum[rson]);
    }
    void build(int l, int r, int rt) {
        lazy[rt] = 0;
        if(l == r) {
            sum[rt] = 1;
            return ;
        }
        int mid = (l + r) >> 1;
        build(l, mid, lson), build(mid + 1, r, rson);
        pop(rt);
    }
    void push(int rt, int l, int r) {
        if(lazy[rt] == 0) return ;
        int mid = (l + r) >> 1;
        lazy[lson] += lazy[rt];
        lazy[rson] += lazy[rt];
        sum[lson] += lazy[rt] * (mid - l + 1);
        sum[rson] += lazy[rt] * (r - mid);
        lazy[rt] = 0;
    }
    void apply(int rt, int l, int r, int v) {
        lazy[rt] += v;
        sum[rt] += v * (r - l + 1);
    }
    void update(int v, int L, int R, int l, int r, int rt) {
        if(L <= l && r <= R) {
            apply(rt, l, r, v);
            return ;
        }
        int mid = (l + r) >> 1;
        push(rt, l, r);
        if(L > mid) {update(v, L, R, mid + 1, r, rson);}
        else if(R <= mid) {update(v, L, R, l, mid, lson);}
        else {
            update(v, L, mid, l, mid, lson);
            update(v, mid + 1, R, mid + 1, r, rson);
        }
        pop(rt);
    }
    int query(int L, int R, int l, int r, int rt) {
        if(L <= l && r <= R) {
            return sum[rt];
        }
        int mid = (l + r) >> 1, ans = 0;
        push(rt, l, r);
        if(L > mid) {ans += query(L, R, mid + 1, r, rson);}
        else if(R <= mid) {ans += query(L, R, l, mid, lson);}
        else {
            ans += query(L, mid, l, mid, lson);
            ans + query(mid + 1, R, mid + 1, r, rson);
        }
        return ans;
        pop(rt);
    }
#undef lson
#undef rson
};
int main() {
#ifdef LH_LOCAL
    //freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
#endif
    for(int cas = 1, tim = 1; cas <= tim; ++ cas) {
        // printf("Case #%d:\n", cas);
        
    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
