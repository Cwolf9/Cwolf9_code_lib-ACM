/*
链接
https://ac.nowcoder.com/acm/contest/5668/D
题意

思路

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
    return rng() % 100000000 + rng() % 10 + 100000;
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
            int y = 0, x;
            for(int i = 1; i <= 50; ++i) {
                if((m - i - i) % 2 == 0 && (m - i - i) / 2 * i == n) {
                    y = i;
                    break;
                }
            }
            if(y) {
                printf("Yes\n");
                x = (m - y - y) / 2;
                for(int i = 1; i <= x; ++i) {
                    for(int j = 1; j <= y; ++j) {
                        printf("%d %d\n", i, j);
                    }
                }
                continue;
            }
            vector<pii> vs;
            int flag = 0;
            for(int t = 1; t <= 55 && flag == 0; ++t) {
                int cnt = 0, c = 0;
                while(m > 4 && (m - t - t)/2 * t > n && m - t - t > 0) {
                    ++ cnt;
                    m -= 4;
                    -- n;
                }
                // debug(m, t, c, cnt)
                for(c = 1; ; ++ c) {
                    if(t + t + c + c >= m) {
                        break;
                    }
                }
                if(t + t + c + c == m && t + c - 1 <= n && t * c >= n) {
                    printf("Yes\n");
                    for(int i = 1; i <= c; ++i) printf("%d 1\n", i);
                    for(int i = 2; i <= t; ++i) printf("1 %d\n", i);
                    n -= t + c - 1;
                    for(int i = 2; i <= c; ++i) {
                        for(int j = 2; j <= t; ++j) {
                            if(n > 0) printf("%d %d\n", i, j), -- n;
                        }
                    }
                    while(cnt --) {
                        int x = mrnd();
                        int y = mrnd();
                        printf("%d %d\n", x, y);
                    }
                    // debug(t, c)
                    flag = 1;
                }else m += cnt * 4, n += cnt;
            }
            if(flag == 0) printf("No\n");
        }
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
