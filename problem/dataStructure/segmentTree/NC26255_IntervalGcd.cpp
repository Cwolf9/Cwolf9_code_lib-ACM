/*
gcd(a,b,c,d)=gcd(a,|b-a|,|c-b|,|d-c|)
*/
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
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int INF = 0x3f3f3f3f;
const int mod = 998244353;  // 998244353
const int MXN = 2e5 + 5;
int n, m;
int ar[MXN], gap[MXN<<2], sum2[MXN<<2], sum[MXN<<2];
void build(int l, int r, int rt) {
    if(l == r) {
        ar[l] = read();
        sum[rt] = ar[l] - ar[l-1];
        gap[rt] = abs(sum[rt]);
        sum2[rt] = gap[rt];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
    gap[rt] = __gcd(gap[rt << 1], gap[rt << 1 | 1]);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    sum2[rt] = max(sum2[rt << 1], sum2[rt << 1 | 1]);
}

void update_gap(int p, int v, int l, int r, int rt) {
    if(l == r) {
        sum[rt] = ar[l];
        gap[rt] = abs(ar[l]);
        sum2[rt] = gap[rt];
        return ;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update_gap(p, v, l, mid, rt << 1);
    else update_gap(p, v, mid + 1, r, rt << 1 | 1);
    gap[rt] = __gcd(gap[rt << 1], gap[rt << 1 | 1]);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    sum2[rt] = max(sum2[rt << 1], sum2[rt << 1 | 1]);
}
int query_sum(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) return sum[rt];
    int mid = (l + r) >> 1;
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
    if(L > mid) return query_gap(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) return query_gap(L, R, l, mid, rt << 1);
    else {
        return __gcd(query_gap(L, mid, l, mid, rt << 1),
        query_gap(mid + 1, R, mid + 1, r, rt << 1 | 1));
    }
}
int query_sum2(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) return sum2[rt];
    int mid = (l + r) >> 1;
    if(L > mid) return query_sum2(L, R, mid + 1, r, rt << 1 | 1);
    else if(R <= mid) return query_sum2(L, R, l, mid, rt << 1);
    else {
        return max(query_sum2(L, mid, l, mid, rt << 1),
        query_sum2(mid + 1, R, mid + 1, r, rt << 1 | 1));
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read(), m = read();
    build(1, n, 1);
    for(int i = n; i >= 2; --i) ar[i] -= ar[i-1];
    while(m -- ) {
        int opt = read(), l = read(), r = read();
        if(opt == 1) {
            int x = read();
            ar[l] += x;
            update_gap(l, x, 1, n, 1);
            if(r < n) {
                ar[r + 1] -= x;
                update_gap(r + 1, x, 1, n, 1);
            }
        }else if(opt == 2) {
            printf("%d\n", l == r?0:query_sum2(l + 1, r, 1, n, 1));
        }else {
            printf("%d\n", l == r?query_sum(1, l, 1, n, 1):__gcd(query_sum(1, l, 1, n, 1), query_gap(l + 1, r, 1, n, 1)));
        }
    }
#ifndef ONLINE_JUDGE
#endif
    return 0;
}