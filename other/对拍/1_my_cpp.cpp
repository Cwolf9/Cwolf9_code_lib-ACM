#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
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
const int MXE = 1e6 + 5;
int n, m;
int ar[MXN], sum[MXN<<2], sumfg[MXN<<2], ans[MXN<<2], mn[MXN<<2];
vector<int> num[MXN];
void push_up(int rt) {
    sum[rt] = max(sum[rt << 1], sum[rt << 1 | 1]);
    ans[rt] = min(ans[rt << 1], ans[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
    sumfg[rt] = 0;
    if(l == r) {
        sum[rt] = ar[l];
        ans[rt] = ar[l] - l + 1;
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
    push_up(rt);
    // debug(rt, sum[rt])
}
void push_down(int rt, int l, int mid, int r) {
    if(sumfg[rt] == 0) return;
    sumfg[rt << 1] = max(sumfg[rt << 1], sumfg[rt]);
    sumfg[rt << 1 | 1] = max(sumfg[rt << 1 | 1], sumfg[rt]);
    if(sum[rt << 1] < sumfg[rt]) {
        ans[rt << 1] = sumfg[rt] - mid + 1;
        sum[rt << 1] = sumfg[rt];
    }
    if(sum[rt << 1 | 1] < sumfg[rt]) {
        ans[rt << 1 | 1] = sumfg[rt] - r + 1;
        sum[rt << 1 | 1] = sumfg[rt];
    }
    sumfg[rt] = 0;
}
void update(int L, int R, int v, int l, int r, int rt) {
    // debug(L, R, l, r)
    if(sum[rt] < v && L <= l && r <= R) {
        ans[rt] = v - r + 1;
        sum[rt] = v;
        sumfg[rt] = max(sumfg[rt], v);
        return;
    }
    if(l == r) return;
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) {
        update(L, R, v, mid + 1, r, rt << 1 | 1);
    }else if(R <= mid) {
        update(L, R, v, l, mid, rt << 1);
    }else {
        if(sum[rt << 1] < v) update(mid + 1, R, v, mid + 1, r, rt << 1 | 1);
        update(L, mid, v, l, mid, rt << 1);
    }
    push_up(rt);
}
int main() {
    n = read(), m = read();
    rep(i, 0, m + 1) num[i].eb(0);
    rep(i, 1, n + 1) {
        ar[i] = read();
        num[ar[i]].eb(i);
    }
    rep(i, 1, SZ(num[1])) {
        rep(j, num[1][i-1] + 1, num[1][i] + 1) {
            ar[j] = num[1][i];
            // debug(j, ar[j])
        }
    }
    rep(i, num[1].back() + 1, n + 1) {
        ar[i] = INF;
        // debug(i, ar[i])
    }
    build(1, n, 1);
    printf("%d", ans[1]);
    rep(qi, 2, m + 1) {
        rep(i, 1, SZ(num[qi])) {
            int l = num[qi][i-1], r = num[qi][i];
            update(l + 1, r, num[qi][i], 1, n, 1);
            // debug(l + 1, r, num[qi][i])
        }
        if(num[qi].back() + 1 <= n) {
            update(num[qi].back() + 1, n, INF, 1, n, 1);
            // debug(num[qi].back() + 1, n)
        }
        printf(" %d", ans[1]);
        // return 0;
    }
    printf("\n");
    return 0;
}
