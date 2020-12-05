// #define LH_LOCAL
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

const int INF = 1000000007 + 1000000007;
const int mod = 998244353;// 998244353
const int MXN = 5e5 + 5;
int n, m;
int ar[MXN];
class node {
    public:
    int gap, ls, rs, lv, rv;
}cw[MXN*20];
int rk, inde, R = 1000000007, L = 0, no = R + 1;
void update_gap(int id, int p, int v, int l, int r, int &rt) {
    if(rt == 0) {
        rt = ++ inde;
        cw[rt] = node{0, 0, 0, no, no};
    }
    if(l == r) {
        if(id == 1) {
            cw[rt] = node{0, 0, 0, v, v};
        }else {
            cw[rt] = node{0, 0, 0, no, no};
        }
        return ;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update_gap(id, p, v, l, mid, cw[rt].ls);
    else update_gap(id, p, v, mid + 1, r, cw[rt].rs);
    
    cw[rt].gap = big(cw[cw[rt].ls].gap, cw[cw[rt].rs].gap);
    if(cw[cw[rt].rs].lv != no && cw[cw[rt].ls].rv != no) {
        cw[rt].gap = big(cw[rt].gap, cw[cw[rt].rs].lv - cw[cw[rt].ls].rv);
    }
    cw[rt].lv = cw[cw[rt].rs].lv;
    if(cw[cw[rt].ls].lv != no) cw[rt].lv = cw[cw[rt].ls].lv;
    cw[rt].rv = cw[cw[rt].ls].rv;
    if(cw[cw[rt].rs].rv != no) cw[rt].rv = cw[cw[rt].rs].rv;
    // debug(rt, cw[rt].lv, cw[rt].rv)
}
set<int> st;
int getans() {
    if(SZ(st) <= 2) return 0;
    int a = *(st.begin());
    int b = *(--st.end());
    debug(b, a, cw[1].gap)
    return b - a - cw[1].gap;
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    cw[0] = node{0, 0, 0, no, no};
    n = read(), m = read();
    //pos[0] = -inf, pos[1e9 + 2] = inf, pos[i] = i
    // update_gap(1, L, INF, L, R, rk);
    // update_gap(1, R, -INF, L, R, rk);
    debug(cw[1].gap)
    for(int i = 1; i <= n; ++i) {
        int x = read();
        st.insert(x);
        update_gap(1, x, x, L, R, rk);
        debug(cw[1].gap)
    }
    print(getans());
    for(int i = 0; i < m; ++i) {
        int id = read(), x = read();
        if(id == 1) {
            st.insert(x);
        }else {
            st.erase(x);
        }
        update_gap(id, x, x, L, R, rk);
        print(getans());
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}