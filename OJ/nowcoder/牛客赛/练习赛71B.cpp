/*
三边三角任意给两个条件判断不全等三角形有多少个。
分类讨论。
*/
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
bool Finish_read;
inline long long read() {long long x = 0;Finish_read = 0;int f = 1;char ch = getchar();while (!isdigit(ch)) {if (ch == '-') f = -1;if (ch == EOF) return x;ch = getchar();}while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();x *= f;Finish_read = 1;return x;}
template <class T>
inline void print(T x) {if(x > 9) print(x / 10);else if(x < 0) putchar('-'), print(-x);else putchar(x % 10 ^ 48);}
template <class T>
inline void write(T x, char c = '\n') {print(x);putchar(c);}
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for (register int i = s; i < t; ++i)
#define per(i, s, t) for (register int i = s; i >= t; --i)
#define GKD                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
constexpr int INF = 0x3f3f3f3f;
constexpr int MXN = 1e6 + 5;
constexpr int MXE = 2e6 + 5;
int n, m;
int ar[2][3];
int check(int a, int b, int c) {
    return a + b > c && b + c > a && a + c > b;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while (tim--) {
        int cnt[2] = {0, 0};
        rep(j, 0, 2) rep(i, 0, 3) {
            ar[j][i] = read();
            assert(ar[j][i] == -1 || ar[j][i] > 0);
            if(ar[j][i] != -1) ++ cnt[j];
        }
        int sum = 0;
        rep(j, 0, 3) if(ar[1][j] != -1) sum += ar[1][j];
        
        if(cnt[1] == 3 && sum != 180) {
            printf("0\n");
            continue;
        }
        if(cnt[1] != 3 && sum >= 180) {
            printf("0\n");
            continue;
        }
        assert(cnt[0] + cnt[1] == 3);
        int ans = 0;
        if(cnt[0] == 3) {
            ans = check(ar[0][0], ar[0][1], ar[0][2]);
        }else if(cnt[0] == 1) {
            ans = 1;
        }else if(cnt[0] == 0) {
            ans = INF;
        }else if(cnt[0] == 2) {
            int pos[3] = {0, 1, 2}, pos2[3] = {0, 1, 2};
            rep(i, 0, 3) {
                if(ar[0][i] == -1) swap(pos[0], pos[i]);
                if(ar[1][i] != -1) swap(pos2[0], pos2[i]);
            }
            int id2 = pos2[0], a = pos[1], b = pos[2];
            assert(ar[1][pos2[1]] == -1 && ar[1][pos2[2]] == -1);
            assert(ar[0][pos[0]] == -1);
            if(ar[1][pos[0]] != -1) {//两边夹一角
                ans = 1;
            }else {
                if(a != id2) swap(a, b);
                if(ar[1][id2] >= 90) {//大边对大角
                    if(ar[0][a] > ar[0][b]) ans = 1;
                }else {
                    if(ar[0][a] >= ar[0][b]) ans = 1;//不可能形成90度
                    else if(ar[0][a] - sin(1.0*ar[1][id2]*acos(-1.0)/180) * ar[0][b] < -1e-8) {
                        ans = 0;//对边太短了.....坑
                    }else if(fabs(ar[0][a] - sin(1.0*ar[1][id2]*acos(-1.0)/180) * ar[0][b]) < 1e-8) {
                        ans = 1;
                    }else {
                        ans = 2;
                    }
                }
                assert(a == id2);
            }
        }
        if(ans == INF) printf("syksykCCC\n");
        else printf("%d\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}