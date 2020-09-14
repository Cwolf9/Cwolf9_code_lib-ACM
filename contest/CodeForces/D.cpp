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

const int INF = 0x3f3f3f3f;
const int mod = 1e6 + 3;// 998244353
const int MXN = 5e5 + 5;
const int MXE = 1e6 + 5;
int n, m;
int ar[MXN];
class FenwickTree {
    public:
    int64 BIT[MXN];
    int N;
    void clear(int _n) {N = _n + 1;memset(BIT, 0, sizeof(int64)*(N+1));}
    int lowbit(int x) {return x&(-x);}
    void add_bit(int x, int val) {for(;x <= N; x += lowbit(x)) BIT[x] += val;}
    int64 query_bit(int x) {int64 ans = 0; for(; x; x -= lowbit(x)) ans += BIT[x]; return ans;}
}bit[2];
void add1(int a, int b, int64 cha) {
    if(cha == 0) return;
    if(b == n) {
        bit[0].add_bit(a, cha);
        bit[0].add_bit(b + 1, -cha);
        return;
    }
    bit[0].add_bit(a, cha);
    bit[0].add_bit(n + 1, -cha);

    bit[1].add_bit(b + 1, -cha);
    bit[1].add_bit(n + 1, cha);
}
void add2(int a, int b, int64 cha) {
    if(cha == 0) return;
    if(a == 1) {
        bit[1].add_bit(a, cha);
        bit[1].add_bit(b + 1, -cha);
        return;
    }
    bit[1].add_bit(1, cha);
    bit[1].add_bit(b + 1, -cha);

    if(a > 1) {
        bit[0].add_bit(1, -cha);
        bit[0].add_bit(a, cha);
    }
}

void sub1(int a, int b, int64 cha) {
    if(cha == 0) return;
    if(a == 1) {
        bit[0].add_bit(a, cha);
        bit[0].add_bit(b + 1, -cha);
        return;
    }
    bit[0].add_bit(1, cha);
    bit[0].add_bit(b + 1, -cha);
    if(a > 1) {
        bit[1].add_bit(1, -cha);
        bit[1].add_bit(a, cha);
    }
}
void sub2(int a, int b, int64 cha) {
    if(cha == 0) return;
    if(b == n) {
        bit[1].add_bit(a, cha);
        bit[1].add_bit(b + 1, -cha);
        return;
    }
    bit[1].add_bit(a, cha);
    bit[1].add_bit(n + 1, -cha);

    bit[0].add_bit(b + 1, -cha);
    bit[0].add_bit(n + 1, cha);
}
void check(int ip, int a, int b, int64 &x) {
    if(x == 0) return;
    if(ip == 0 && b < n) {
        int64 tmp = min(bit[0].query_bit(b + 1) - bit[0].query_bit(b), x);
        x -= tmp;
        bit[0].add_bit(a, tmp);
        bit[0].add_bit(b + 1, -tmp);
        return;
    }else if(ip == 1 && a > 1) {
        int64 tmp = min(bit[1].query_bit(a - 1) - bit[1].query_bit(a), x);
        x -= tmp;
        bit[1].add_bit(a, tmp);
        bit[1].add_bit(b + 1, -tmp);
        return;
    }
}
void check2(int ip, int a, int b, int64 &x) {
    if(x == 0) return;
    if(ip == 0 || a == 1) {
        int64 tmp = min(bit[0].query_bit(a) - bit[0].query_bit(a - 1), x);
        if(a == 1) tmp = x;
        x -= tmp;
        bit[0].add_bit(a, -tmp);
        bit[0].add_bit(b + 1, tmp);
        return;
    }else if(ip == 1 || b == n) {
        int64 tmp = min(bit[1].query_bit(b) - bit[1].query_bit(b + 1), x);
        if(b == n) tmp = x;
        x -= tmp;
        bit[1].add_bit(a, -tmp);
        bit[1].add_bit(b + 1, tmp);
        return;
    }
}
void query(int a, int b, int64 x) {
    if(x == 0) return;
    if(x > 0) {
        int f = 0;
        if(x == 7) f = 1;
        check(0, a, b, x), check(1, a, b, x);
        if(x == 0) return;
        int64 mx1 = bit[0].query_bit(n);
        int64 mx2 = bit[1].query_bit(1);
        if(mx1 < mx2) {
            int64 cha = min(x, mx2 - mx1);
            add1(a, b, cha);
            x -= cha;
            add1(a, b, x / 2);
            add2(a, b, x - x / 2);
        }else if(mx1 > mx2) {
            int64 cha = min(x, mx1 - mx2);
            add2(a, b, cha);
            x -= cha;
            add1(a, b, x / 2);
            add2(a, b, x - x / 2);
        }else {
            add1(a, b, x / 2);
            add2(a, b, x - x / 2);
        }
    }else {
        x = -x;
        check2(0, a, b, x), check2(1, a, b, x);
        if(x == 0) return;
        int64 mx1 = bit[0].query_bit(n);
        int64 mx2 = bit[1].query_bit(1);
        if(mx1 < mx2) {
            int64 cha = min(x, mx2 - mx1);
            sub2(a, b, -cha);
            x -= cha;
            sub1(a, b, -(x / 2));
            sub2(a, b, -(x - x / 2));
        }else if(mx1 > mx2) {
            int64 cha = min(x, mx1 - mx2);
            sub1(a, b, -cha);
            x -= cha;
            sub1(a, b, -(x / 2));
            sub2(a, b, -(x - x / 2));
        }else {
            sub1(a, b, -(x / 2));
            sub2(a, b, -(x - x / 2));
        }
    }
}
int64 get_ans() {
    return big(bit[0].query_bit(n), bit[1].query_bit(1));
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    bit[0].clear(n + 1);
    bit[1].clear(n + 1);
    for(int i = 1; i <= n; ++i) {
        int x = read();
        query(i ,i, x);
        debug(max(bit[0].query_bit(n), bit[1].query_bit(1)))
        for(int j = 1; j <= n; ++j) printf("%d ", bit[0].query_bit(j)); printf("\n");
        for(int j = 1; j <= n; ++j) printf("%d ", bit[1].query_bit(j)); printf("\n");
    }
    printf("%lld\n", get_ans());
    m = read();
    while(m --) {
        int a = read(), b = read(), x = read();
        query(a, b, x);
        printf("%lld\n", get_ans());
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}