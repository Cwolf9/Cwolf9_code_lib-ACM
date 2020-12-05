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
const int mod = 998244353;// 998244353
const int MXN = 1e5 + 5;
int n, m;
int ans;
bool noprime[MXN];
int pp[MXN/5], pcnt;
void init_prime() {
    noprime[0] = noprime[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i;
        for(int j = 0; j < pcnt && i*pp[j] < MXN; ++j) {
            noprime[i*pp[j]] = 1;
            if(i % pp[j] == 0) {
                break;
            }
        }
    }
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    n = read();
    m = sqrt(n);
    ans = 1;
    if(n == 1) {
        cout << "C " << 1 << endl;
        return 0;
    }
    for(int i = 0; i < pcnt; ++i) {
        if(pp[i] > n) {
            pcnt = i;
            break;
        }
    }
    int L = 0;
    for(int i = 0; i < pcnt && pp[i] <= m; ++i) {
        cout << "B " << pp[i] << endl;
        read();
        L = i + 1;
    }
    for(int i = 0; i < pcnt && pp[i] <= m; ++i) {
        int tmp = 1, ret = pp[i];
        while(tmp) {
            cout << "A " << ret << endl;
            tmp = read();
            if(tmp) ans *= pp[i];
            ret *= pp[i];
            if(ret > n) break;
        }
    }
    cout << "A " << 1 << endl;
    int res = read();
    // debug(n, m, L, pcnt, ans, pp[L])
    for(int i = L; i < pcnt; ++i) {
        if(ans * pp[i] > n) break;
        cout << "B " << pp[i] << endl;
        int tmp = read();
        if(tmp > 1) {
            ans *= pp[i];
            break;
        }
        if(i % 150 == 0 || i == pcnt - 1) {
            cout << "A " << 1 << endl;
            int res2 = read();
            if(res - res2 != i - L + 1) {
                for(int j = L; j <= i; ++j) {
                    cout << "A " << pp[j] << endl;
                    tmp = read();
                    if(tmp) {
                        ans *= pp[j];
                        break;
                    }
                }
            }
            L = i + 1;
            res = res2;
        }
    }
    cout << "C " << ans << endl;
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}