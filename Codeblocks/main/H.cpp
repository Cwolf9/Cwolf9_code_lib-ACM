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
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 5;
int n, m;
int ar[MXN], br[MXN];
int64 cr[MXN], sum1[MXN<<2], sum2[MXN<<2], ad2[MXN<<2];
void build1(int l, int r, int rt) {
    ad2[rt] = 0;
    if(l == r) {
        sum1[rt] = ar[rt];
        sum2[rt] = cr[rt - 1] + br[rt];
        return;
    }
    int mid = (l + r) >> 1;
    build1(l, mid, rt << 1), build1(mid + 1, r, rt << 1 | 1);
    sum1[rt] = max(sum1[rt << 1], sum1[rt << 1 | 1]);
    sum2[rt] = max(sum2[rt << 1], sum2[rt << 1 | 1]);
}

void push_down2(int rt) {
    if(ad2[rt] == 0) return;
    ad2[rt << 1] += ad2[rt];
    ad2[rt << 1 | 1] += ad2[rt];
    sum2[rt << 1] += ad2[rt];
    sum2[rt << 1 | 1] += ad2[rt];
    ad2[rt] = 0;
}
void update_a(int p, int l, int r, int rt) {
    if(l == r) {
        sum1[rt] = ar[l];
        return ;
    }
    int mid = (l + r) >> 1;
    push_down2(rt);
    if(p <= mid) update_a(p, l, mid, rt << 1);
    else update_a(p, mid + 1, r, rt << 1 | 1);
    sum1[rt] = max(sum1[rt << 1], sum1[rt << 1 | 1]);
    sum2[rt] = max(sum2[rt << 1], sum2[rt << 1 | 1]);
}
void update_c(int L, int R, int64 v, int l, int r, int rt) {
    if(L <= l && r <= R) {
        sum2[rt] += v;
        ad2[rt] += v;
        return;
    }
    int mid = (l + r) >> 1;
    push_down2(rt);
    if(L > mid) update_c(L, R, v, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) update_c(L, R, v, l, mid, rt << 1);
    else {
        update_c(L, mid, v, l, mid, rt << 1);
        update_c(mid + 1, R, v, mid + 1, r, rt << 1 | 1);
    }
    sum1[rt] = max(sum1[rt << 1], sum1[rt << 1 | 1]);
    sum2[rt] = max(sum2[rt << 1], sum2[rt << 1 | 1]);
}
int64 query_lx(int R, int l, int r, int rt) {
    if(r <= R) return sum1[rt];
    int mid = (l + r) >> 1;
    push_down2(rt);
    if(R <= mid) return query_lx(R, l, mid, rt << 1);
    else return max(query_lx(R, l, mid, rt << 1), query_lx(R, mid + 1, r, rt << 1 | 1));
}
int64 query2(int R, int l, int r, int rt) {
    if(l == r) return sum2[rt];
    int mid = (l + r) >> 1;
    push_down2(rt);
    if(R <= mid) return query2(R, l, mid, rt << 1);
    else return query2(R, mid + 1, r, rt << 1 | 1);
}
int query_pos(int p, int L, int R, int l, int r, int rt) {
    if(sum1[rt] < p) return -1;
    if(l == r) return l;
    int mid = (l + r) >> 1;
    push_down2(rt);
    if(L > mid) {
        return query_pos(p, L, R, mid + 1, r, rt << 1 | 1);
    }else if(R <= mid) {
        return query_pos(p, L, R, l, mid, rt << 1);
    }else {
        if(sum1[rt << 1 | 1] >= p) return query_pos(p, mid + 1, R, mid + 1, r, rt << 1 | 1);
        return query_pos(p, L, mid, l, mid, rt << 1);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    // freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    while(~scanf("%d%d", &n, &m)) {
        rep(i, 1, n + 1) ar[i] = read();
        rep(i, 1, n + 1) {
            br[i] = read();
            cr[i] = max((int64)ar[i], cr[i-1] + br[i]);
        }
        build1(1, n, 1);
        while(m --) {
            int opt = read(), x = read();
            if(opt == 1) {
                int y = read();
                if(y > ar[x]) {
                    int64 lm = query_lx(x - 1, 1, n, 1);
                    if(lm >= y) {
                        ar[x] = y;
                        update_a(x, 1, n, 1);
                        continue;
                    }
                    lm = query2(x, 1, n, 1);
                    if(y <= lm) {
                        ar[x] = y;
                        update_a(x, 1, n, 1);
                        continue;
                    }
                    int64 up = y - max((int64)ar[x], lm);
                    lm = query_pos(y, x + 1, n, 1, n, 1);
                    if(lm == -1) lm = n;
                    update_c(x + 1, lm, up, 1, n, 1);
                }else if(y < ar[x]) {
                    int64 lm = query_lx(x - 1, 1, n, 1);
                    if(lm >= y) {
                        ar[x] = y;
                        update_a(x, 1, n, 1);
                        continue;
                    }
                    lm = query2(x, 1, n, 1);
                    if(y <= lm && ar[x] <= lm) {
                        ar[x] = y;
                        update_a(x, 1, n, 1);
                        continue;
                    }
                    int64 up = ar[x] - max((int64)y, lm);
                    lm = query_pos(y, x + 1, n, 1, n, 1);
                    if(lm == -1) lm = n;
                    update_c(x + 1, lm, up, 1, n, 1);
                }
            }else if(opt == 2) {
                int y = read();
                br[x] = y;
            }else {
                printf("%lld\n", max(query2(x, 1, n, 1), query_lx(x, 1, n, 1)));
            }
            break;
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
