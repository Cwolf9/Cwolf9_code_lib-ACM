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
struct Point {
    int x;
    int y;
};
struct Interval {
    int start;
    int end;
    Interval(int s, int e) : start(start), end(e) {}
};
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
const int MXN = 1e5 + 5;
int ksm(int a, int64 b, int kmod = mod) {int res = 1;for(;b > 0;b >>= 1, a = (int64)a * a % kmod) if(b &1) res = (int64)res * a % kmod;return res;}

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 
     * @param n string字符串 三角形的长和高
     * @return bool布尔型
     */
    void mul(string &n, int &len) {
        for(int i = 0; i < len; ++i) n[i] = (n[i] - '0') * 2 + '0';
        for(int i = 0; i < len; ++i) {
            if(n[i] > '9') {
                if(i == len - 1) ++ len;
                n[i + 1] += (n[i] - '0') / 10;
                n[i] = (n[i] - '0') % 10 + '0';
            }
        }
    }
    void chu(string &n, int &len) {
        for(int i = len - 1; i >= 0; --i) {
            int x = n[i] - '0';
            if(x % 2 == 0) n[i] = x / 2 + '0';
            else {
                n[i] = x / 2 + '0';
                n[i - 1] += 10;
            }
        }
        while(n[len - 1] == '0') -- len;
    }
    string add1(string n) {
        reverse(n.begin(), n.end());
        int len = n.length();
        n[0] ++;
        for(int i = 0; i < len; ++i) {
            if(n[i] > '9') {
                if(i == len - 1) ++ len, n += '0';
                n[i + 1] += (n[i] - '0') / 10;
                n[i] = (n[i] - '0') % 10 + '0';
            }
        }
        reverse(n.begin(), n.end());
        return n;
    }
    
    bool judge(string n) {
        // write code here
        bool flag = 0;
        n = add1(n);
        // reverse(all(n));
        // int len = n.length();
        // while(1) {
        //     if(len == 1 && n[0] == '1') {
        //         flag = 1;
        //         break;
        //     }
        //     if((n[0] - '0') % 2 == 1) break;
        //     chu(n, len);
        // }
        string x(10005, '0');
        x[0] = '2';
        int len = 1, xn = n.length();
        for(int i = 1; ; ++i) {
            int f = (len == xn);
            rep(j, 0, len) if(f && x[len - 1 - j] != n[j]) {
                f = 0;
                break;
            }
            if(f == 1) {
                flag = 1;
                break;
            }
            mul(x, len);
            if(len > xn) break;
        }
        return flag;
    }
};
Solution S;
int main() {
#ifdef LH_LOCAL
    //freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    //freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    vector<int> arr = vector<int>{1,2,3,4};
    vector<int> arr2 = vector<int>{2,3,1,3};
    vector<Interval> ar = vector<Interval>{Interval(0, 2), Interval(4, 7), Interval(9, 9)};
    vector<vector<int> > br = vector<vector<int> >{{1,2},{2,4},{4,8}};
    vector<Point> par = vector<Point>{{1, 2},{3,4}};
    auto x = S.judge("5");
    debug(x)
    //for(int y: x) printf("%d ", y);
    //printf("\n");
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}
