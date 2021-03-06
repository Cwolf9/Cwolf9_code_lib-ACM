/*
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/5671/J)
**题意**
$n(1e5),n*m(1e6)$，对长度为$n$的序列做$m$轮约瑟夫环，每轮做$x$次$k-out$的约瑟夫环，输出最后序列。
**思路**
树状数组模拟出约瑟夫环出环序列，然后维护一下每个位置的变换即可。
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
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
inline void write(int64 x, bool f) {
    if (x == 0) {
        putchar('0');
        if (f) putchar('\n');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[23];
    int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
}
constexpr int lowbit(int x) { return x & (-x); }
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
#define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {
    printf(ptout, f);
    putchar('\n');
}
template <typename T, typename... R>
void print(const T &f, const R &... r) {
    printf(ptout, f);
    putchar(' ');
    print(r...);
}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e5 + 5;
const int MXE = 2e6 + 6;
int n, m;
int k, x;
int ori[MXN], cgk[MXN], bel[MXN], pos[MXN], vis[MXN];
vector<int> mp[MXN];
class FenwickTree {
    public:
    int BIT[MXN], N;
    void clear(int _n, int f) {
        N = _n + 1;
        if(f == 0) memset(BIT, 0, sizeof(int)*(N+1));
        else for(int i = 1; i <= N; ++i) BIT[i] = lowbit(i);
    }
    // constexpr int lowbit(int x) {return x&(-x);}
    void add_bit(int x, int val) {for(;x <= N; x += lowbit(x)) BIT[x] += val;}
    int query_bit(int x) {int ans = 0; for(; x > 0; x -= lowbit(x)) ans += BIT[x]; return ans;}
    //2^17 - 1 = 131072 - 1
    int find_kth(int k) {
        int s = 0, sum = 0;
        for (int i = 16; i >= 0; -- i) {
            s += (1 << i);
            if (s > N || BIT[s] + sum >= k)
                s -= (1 << i);
            else
                sum += BIT[s];
        }
        return s + 1;
    }
}bit;
// int get_Q(int n, int k, int q) {
//     long long N = (long long)q * k;
//     while(N > n){
//         N = (N - n - 1) / (k - 1) + N - n;
//     }
//     return (int)N;
// }
int kmodn(int k, int n) {
    return k % n == 0? n: (k % n);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) ori[i] = pos[i] = i;
    while(m --) {
        k = read(), x = read();
        bit.clear(n, 1);
        int las = 0, tn = n, all, left;
        for(int i = 1; i <= n; ++ i, -- tn) {
            vis[i] = 0;
            mp[i].clear();
            all = bit.query_bit(n);
            left = bit.query_bit(las);
            // debug(all, left)
            left = all - left >= k? k + left: kmodn(k - all + left, tn);
            cgk[i] = bit.find_kth(left);
            bit.add_bit(cgk[i], -1);
            las = cgk[i];
            // debug(i, cgk[i], left)
        }
        for(int t = 1; t <= n; ++t) {
            for(int i = t; vis[i] == 0; i = cgk[i]) {
                mp[t].eb(i);
                vis[i] = 1;
                bel[i] = t;
            }
        }
        for(int i = 1, j; i <= n; ++i) {
            // debug(i, bel[i])
            j = 1;
            for(int a: mp[i]) {
                int b = mp[i][kmodn(j + x, SZ(mp[i])) - 1];
                // debug(i, a, b)
                ori[pos[b]] = a;
                ++ j;
            }
        }
        for(int i = 1; i <= n; ++i) pos[ori[i]] = i;
    }
    // for(int i = 1; i <= n; ++i) debug(i, pos[i], ori[i])
    for(int i = 1; i <= n; ++i) printf("%d%c", pos[i], " \n"[i == n]);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    system("pause");
#endif
    return 0;
}
/*
int find_kth(int k) {
    int s = 0, sum = 0;
    for (int i = 20; i >= 0; i--) {
        s += (1 << i);
        if (s > maxn || c[s] + sum >= k)
            s -= (1 << i);
        else
            sum += c[s];
    }
    return s + 1;
}
*/