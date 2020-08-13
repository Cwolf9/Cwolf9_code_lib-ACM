/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6863)
**题意**
$n(5e6)$是否可以将其均分成$k(大于1即可)$份，每份子串循环同构。
**思路**
合法份数一定是$26$字母出现次数的$因数$，枚举然后$O(n)check$，再
加一点剪枝即可飞快过题。
**备注**
*/

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
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 5e6 + 5;
const int PN = 1e5 + 5;
int n, m;
char s[MXN];
int pre[MXN][26], tmin[MXN];
vector<int> vs;
// bool noprime[PN];
// int pp[PN/2], pcnt;
// void init_prime() {
//     noprime[0] = noprime[1] = 1;
//     for(int i = 2; i < PN; ++i) {
//         if(!noprime[i]) pp[pcnt++] = i;
//         for(int j = 0; j < pcnt && i*pp[j] < PN; ++j) {
//             noprime[i*pp[j]] = 1;
//             if(i % pp[j] == 0) break;
//         }
//     }
// }
bool check(int num, int lL, int L, int n) {
    int k = 0, i = 0, j = 1;
        while (k < n && i < n && j < n) {
        if (s[(i + k) % n + L] == s[(j + k) % n + L]) {
            k++;
        } else {
            s[(i + k) % n + L] > s[(j + k) % n + L] ? i = i + k + 1 : j = j + k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    i = min(i, j);
    tmin[num] = i;
    if(num == 0) return true;
    else {
        int a = tmin[num], b = tmin[num-1];
        // debug(num, a, b, n)
        for(int i = 0; i < n; ++i) {
            if(s[a+L] != s[b+lL]) return false;
            ++ a, ++ b;
            if(a == n) a = 0;
            if(b == n) b = 0;
        }
    }
    return true;
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    // init_prime();
    while(tim --) {
        n = read();
        scanf("%s", s);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < 26; ++j) {
                if(s[i] - 'a' == j) pre[i][j] = pre[i-1][j] + 1;
                else pre[i][j] = pre[i-1][j];
            }
        }
        int g = 0;
        for(int i = 0; i < 26; ++i) g = __gcd(g, pre[n-1][i]);
        if(g == 1) {
            printf("No\n");
            continue;
        }else if(g == n) {
            printf("Yes\n");
            continue;
        }
        vs.clear();
        int stn = sqrt(g), flag = 0;
        vs.eb(g);
        for(int i = 2; i <= stn; ++i) {
            if(g % i == 0) {
                vs.eb(i);
                if((g / i) != i) vs.eb(g / i);
            }
        }
        my_unique(vs);
        // debug(g)
        int len;
        for(int cnt: vs) {
            len = n / cnt;
            assert(n % len == 0);
            // debug(n, len, cnt)
            if(cnt == 1) continue;
            int tf = 1;
            for(int i = 1, st1 = len+len-1, st2 = len-1; i < cnt && tf; ++i) {
                for(int j = 0; j < 26; ++j) {
                    if(pre[st1][j]-pre[st1-len][j] != pre[st2][j]-pre[st2-len][j]) {
                        tf = 0;
                        break;
                    }
                }
                st1 += len;
                st2 += len;
            }
            if(tf) {
                for(int i = 0, st1 = 0, st2 = -len; i < cnt; ++i) {
                    tf = check(i, (i - 1) * len, i * len, len);
                    if(tf == 0) break;
                    st1 += len;
                    st2 += len;
                }
            }
            if(tf) flag = 1;
            if(flag) break;
        }
        printf("%s\n", flag?"Yes":"No");
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}