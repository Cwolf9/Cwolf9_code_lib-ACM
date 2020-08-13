/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6865)
**题意**
$n(2e5),m(5e4),k(100)$输出长度为$n$序列所有合法的长度为$m$的子
串的首下标带权和。合法定义为与另一个长度为$m$序列相应位置元素异
或和均可以被给定的$k$个数字(线性基)异或出来。
**思路**
考虑如何判断 x ⊕ y ∈ 2S⊕．先求出 S 的线性基 B．
断言．假设 x, y 消去 B 中的位后得到的数分别为 x′, y′, 那么 x ⊕ y ∈ 2S⊕ 的充要条件是 x′ = y′．
充分性: x ⊕ y 必然能写成 x′ ⊕ y′ 再异或上 B 中的一些数的形式．在 x′ = y′ 时即 x ⊕ y ∈ 2S⊕．
必要性: 考虑反证．因为 x′, y′ 都不包含 B 中的位, 所以 x′ ⊕ y′ 不包含 B 中的位．又因为
x′ ̸= y′, 所以 x′ ⊕ y′ 非零, 那么 x′ ⊕ y′ 一定包含 B 无法表示的位, 所以 x ⊕ y ̸∈ 2S⊕．
接下来问题就变简单了．我们只需要把序列 a, b 都消去 B 中的位, 然后做 KMP 即可．时间复
杂度 O((N + M + K) log V )．
**备注**
*/
#define LH_LOCAL
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
mt19937 rng(time(NULL));
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
const int mod = 1e9 + 7;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 3e5 + 5;
const int BASE_MAX = 30;
int n, m, q;
int k;
int ar[MXN], br[MXN];
struct Base {
    int b[BASE_MAX + 1];
    int& operator [](int x) {
        return b[x];
    }
    int operator [](int x)const {
        return b[x];
    }
    void clear(int f) {
        if(f == 0) memset(b, 0, sizeof(int)*(BASE_MAX+1));
        else {
            for(int i = 0; i <= BASE_MAX; ++i) b[i] = (1<<i);
        }
    }
    int check(int x) {
        for(int i = BASE_MAX; i >= 0; --i) {
            if(x & (1 << i)) x ^= b[i];
        }
        return x;
    }
    void out() {
        for(int i = 0; i <= BASE_MAX; ++i) printf("%d ", b[i]);
        printf("\n");
    }
}bs;
bool insert(int x, int *bs) {
    for(int j = BASE_MAX; j >= 0; --j) {
        if(!(x >> j)) continue;
        if(bs[j]) x ^= bs[j];
        else {
            bs[j] = x;
            for(int k = j-1; k >= 0; --k) if(bs[k]&&(bs[j]&(1LL<<k))) bs[j]^=bs[k];
            for(int k = j+1; k <= BASE_MAX; ++k) if(bs[k]&(1LL<<j)) bs[k]^=bs[j];
            return true;
        }
    }
    return false;
}
int two[MXN];
int nex[MXN];
void get_next(){
    nex[0] = -1;
    for(int i = 0,k = -1;i < m;){
        if(k==-1||br[i] == br[k]){
            ++k;++i;
            nex[i]=k;
        }else k = nex[k];
    }
}
int64 kmp(){
    int64 ans = 0;
    int i = 0, j = 0;
    while(i < n&&j<m) {
        if(j==-1||ar[i] == br[j]){
            i++;j++;
            if(j==m){
                int ti = i - m;
                // debug(i, ti)
                ans = (ans + two[ti])%mod;
                j = nex[j];
            }
        }else j=nex[j];
    }
    return ans;
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    two[0] = 1;
    for(int i = 1; i < MXN; ++i) two[i] = two[i-1] * 2 % mod;
    int tim = read();
    while(tim --) {
        n = read(), m = read(), k = read();
        bs.clear(0);
        for(int i = 1; i <= n; ++i) ar[i] = read();
        for(int i = 1; i <= m; ++i) br[i] = read();
        for(int i = 1, x; i <= k; ++i) {
            x = read();
            insert(x, bs.b);
        }
        for(int i = 1; i <= n; ++i) {
            ar[i-1] = bs.check(ar[i]);
            // debug(i, ar[i-1])
        }
        for(int i = 1; i <= m; ++i) {
            br[i-1] = bs.check(br[i]);
            // debug(i, br[i-1])
        }
        get_next();
        printf("%lld\n", kmp());
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}