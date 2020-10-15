/**
 * 贪心每次把前面连续的的(i+1,i+2,i+3,...)放到i后面即可。
 */
#define LH_LOCAL
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

const int INF = 0x3f3f3f3f;
const int mod = 1e6 + 3;// 998244353
const int MXN = 5e5 + 5;
const int MXE = 1e6 + 5;
int n, m;

int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    vector<int> ar(n), pos(n + 1);
    rep(i, 0, n) ar[i] = read();
    vector<vector<int>> ans;
    while(!is_sorted(all(ar)) && (int)ans.size() < n) {
        vector<int> vs;
        int one = -1, two = -1;
        rep(i, 0, n) {
            pos[ar[i]] = i;
        }
        rep(i, 1, n) {
            if(pos[i] > pos[i + 1]) {
                one = pos[i + 1], two = pos[i];
                break;
            }
        }
        int x = one, len = 1;
        while(ar[x] == ar[x + 1] - 1) ++ x, ++ len;
        if(one) vs.eb(one);
        vs.eb(len);
        vs.eb(two - one - len + 1);
        if(n - 1 - two) vs.eb(n - 1 - two);
        while(vs.back() == 0) vs.pop_back();
        ans.eb(vs);
        // for(int x: vs) printf("%d ", x); puts("");
        reverse(all(vs));
        vector<int> tmp, ret;
        int ti = 0, tj = n;
        for(int x: vs) {
            while(x --) {
                tmp.eb(ar[--tj]);
            }
            reverse(all(tmp));
            for(int y: tmp) ret.eb(y);
            tmp.clear();
        }
        ar = ret;
        // for(int x: ar) printf("%d ", x); printf("\n");
    }
    // for(int x: ar) printf("%d ", x); printf("\n");
    printf("%d\n", ans.size());
    for(auto x: ans) {
        printf("%d ", x.size());
        for(int y: x) {
            printf("%d ", y);
        }
        printf("\n");
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}