#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for (register int i = s; i < t; ++i)
#define per(i, s, t) for (register int i = s; i >= t; --i)
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
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
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {
    return a1 > a2 ? a1 : a2;
}
template <class T>
T sml(const T &a1, const T &a2) {
    return a1 < a2 ? a1 : a2;
}
template <typename T, typename... R>
T big(const T &f, const R &... r) {
    return big(f, big(r...));
}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {
    return sml(f, sml(r...));
}

const int INF = 0x3f3f3f3f;
const int mod = 998244353;  // 998244353
const int MXN = 2e5 + 5;
int n, m;
int ar[MXN], gap[MXN<<2];
int64 sum[MXN<<2], lazy[MXN<<2];
void build(int l, int r, int rt) {
    lazy[rt] = 0;
    if(l == r) {
        sum[rt] = ar[l];
        gap[rt] = abs(ar[l + 1] - ar[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
    gap[rt] = max(gap[rt << 1], gap[rt << 1 | 1]);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void push_down(int rt, int l, int mid, int r) {
    if(lazy[rt] == 0) return;
    lazy[rt << 1] += lazy[rt];
    lazy[rt << 1 | 1] += lazy[rt];
    sum[rt << 1] += lazy[rt] * (mid - l + 1);
    sum[rt << 1 | 1] += lazy[rt] * (r - mid);
    lazy[rt] = 0;
}
void update(int L, int R, int v, int l, int r, int rt) {
    if(L <= l && r <= R) {
        sum[rt] += v * (r - l + 1);
        lazy[rt] += v;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) update(L, R, v, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) update(L, R, v, l, mid, rt << 1);
    else {
        update(L, mid, v, l, mid, rt << 1);
        update(mid + 1, R, v, mid + 1, r, rt << 1 | 1);
    }
    gap[rt] = max(gap[rt << 1], gap[rt << 1 | 1]);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void update_gap(int p, int v, int l, int r, int rt) {
    if(l == r) {
        gap[rt] = abs(sum[rt] - v);
        return ;
    }
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(p <= mid) update_gap(p, v, l, mid, rt << 1);
    else update_gap(p, v, mid + 1, r, rt << 1 | 1);
    gap[rt] = max(gap[rt << 1], gap[rt << 1 | 1]);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
int64 query_sum(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) return sum[rt];
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) return query_sum(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) return query_sum(L, R, l, mid, rt << 1);
    else {
        return query_sum(L, mid, l, mid, rt << 1) + 
        query_sum(mid + 1, R, mid + 1, r, rt << 1 | 1);
    }
}
int query_gap(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) return gap[rt];
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) return query_gap(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) return query_gap(L, R, l, mid, rt << 1);
    else {
        return max(query_gap(L, mid, l, mid, rt << 1),
        query_gap(mid + 1, R, mid + 1, r, rt << 1 | 1));
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) ar[i] = read();
    build(1, n, 1);
    while(m -- ) {
        int opt = read(), l = read(), r = read();
        if(opt == 1) {
            int x = read();
            update(l, r, x, 1, n, 1);
            if(l > 1) {
                x = query_sum(l, l, 1, n, 1);
                update_gap(l - 1, x, 1, n, 1);
            }
            if(r < n) {
                x = query_sum(r + 1, r + 1, 1, n, 1);
                update_gap(r, x, 1, n, 1);
            }
        }else if(opt == 2) {
            printf("%d\n", l == r?0:query_gap(l, r - 1, 1, n, 1));
        }else {
            printf("%lld\n", l == r?query_sum(l, l, 1, n, 1):__gcd(query_sum(l, r - 1, 1, n, 1), query_sum(r, r, 1, n, 1)));
        }
    }
#ifndef ONLINE_JUDGE
#endif
    return 0;
}