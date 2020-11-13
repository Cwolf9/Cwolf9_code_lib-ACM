#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long int64;
bool Finish_read;
inline long long read() {long long x = 0;Finish_read = 0;int f = 1;char ch = getchar();while (!isdigit(ch)) {if (ch == '-') f = -1;if (ch == EOF) return x;ch = getchar();}while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();x *= f;Finish_read = 1;return x;}
template <class T>inline void print(T x) {if(x > 9) print(x / 10);else if(x < 0) putchar('-'), print(-x);else putchar(x % 10 ^ 48);}
template <class T>inline void write(T x, char c = '\n') {print(x);putchar(c);}
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
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
typedef pair<int, int> pii;
#define fi first
#define se second
/*================Header Template2==============*/
constexpr int maxn = 4e5 + 5;
constexpr int maxe = 2e6 + 5;
int n, m;

int main() {
#ifdef LH_LOCAL
    freopen("D:in.txt", "r", stdin);
    freopen("D:out.txt", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read();

    }
#ifdef LH_LOCAL
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
