#include <bits/stdc++.h>
using namespace std;
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
inline long long read() {
    long long x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(long long x, bool f = true) {
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
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
#define fi first
#define se second
#define mk make_pair
#define o2(x) (x) * (x)
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;// 998244353
const int MXN = 2e5 + 5;

class Solution {
public:
    /**
     * 找到所有长度子数组中最大值的最小值
     * @param numbers int整型vector 牛牛给出的数据
     * @return int整型vector
     */
    vector<int> getMinimums(vector<int>& numbers) {
        // write code here
        int n = numbers.size();
        vector<int> ans(n, INF), vs, ls(n), rs(n);
        for(int i = 0; i < n; ++i) {
            while(!vs.empty() && numbers[i] >= numbers[vs.back()]) vs.pop_back();
            if(vs.empty()) ls[i] = -1;
            else ls[i] = vs.back();
            vs.push_back(i);
        }
        vs.clear();
        for(int i = n - 1; i >= 0; --i) {
            while(!vs.empty() && numbers[i] >= numbers[vs.back()]) vs.pop_back();
            if(vs.empty()) rs[i] = n;
            else rs[i] = vs.back();
            vs.push_back(i);
        }
        vs.clear();
        for(int i = 0; i < n; ++i) {
            if(rs[i] - ls[i] - 1 <= n)
                ans[rs[i] - ls[i] - 2] = min(ans[rs[i] - ls[i] - 2], numbers[i]);
            debug(rs[i] - ls[i] - 2, numbers[i])
        }
        for(int i = n - 2; i >= 0; --i) if(ans[i] == INF) ans[i] = ans[i + 1];
        for(int i = 1; i < n; ++i) {
            ans[i] = max(ans[i], ans[i - 1]);
        }
        return ans;
    }
};
Solution S;
int main() {
#ifdef LH_LOCAL
    //freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    //freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    
    vector<int> ar;
    int n = read();
    for(int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ar.eb(x);
    }
    auto x = S.getMinimums(ar);
    for(int y: x) printf("%d ", y);
    printf("\n");
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
