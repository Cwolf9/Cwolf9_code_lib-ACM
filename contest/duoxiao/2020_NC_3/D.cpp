/*
链接
https://ac.nowcoder.com/acm/contest/5668/D
题意
你需要在全白色的格点图内，涂黑$n$个点，使得存在$m$对黑白点对曼哈顿距离为$1$.
思路
$O(n^3)$枚举即可
备注
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
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
mt19937 rng(time(NULL));
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

const int MXN = 2e3 + 5;
int n, m;
int ar[MXN];
int mrnd() {
    static int x = 2000000000;
    return x--/2;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tims = read();
    while(tims --) {
        n = read(), m = read();
        if(m < 4 || m > 4 * n || m % 2 == 1) {
            printf("No\n");
        }else if(m == n * 4) {
            printf("Yes\n");
            while(n --) {
                int x = mrnd();
                int y = mrnd();
                printf("%d %d\n", x, y);
            }
        }else {
            vector<pii> vs;
            int flag = 0;
            for(int four = 0; four < n && flag == 0; ++ four) {
                int tn = n - four, tm = m - four * 4;
                for(int c = 1; c <= tn && flag == 0 && tm > 0; ++ c) {
                    for(int r = 1; r <= tn && flag == 0; ++ r) {
                        if(r + c - 1 <= tn && tn <= r * c && (r + c) * 2 == tm) {
                            flag = 1;
                            printf("Yes\n");
                            while(four --) {
                                int x = mrnd();
                                int y = mrnd();
                                printf("%d %d\n", x, y);
                            }
                            for(int i = 1; i <= c; ++i) printf("%d 1\n", i);
                            for(int i = 2; i <= r; ++i) printf("1 %d\n", i);
                            tn -= r + c - 1;
                            for(int i = 2; i <= c; ++i) {
                                for(int j = 2; j <= r; ++j) {
                                    if(tn > 0) printf("%d %d\n", i, j), -- tn;
                                }
                            }
                        }
                    }
                }
            }
            if(flag == 0) printf("No\n");
        }
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
