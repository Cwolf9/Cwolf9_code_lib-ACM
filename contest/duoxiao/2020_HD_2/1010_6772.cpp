/*
**链接**

**题意**

**思路**

**备注**

*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long int64;
typedef pair<int, int> pii;
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T& f, const R&... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
const int INF = 0x3f3f3f3f;
const int MXN = 1e2 + 5;
const int MXE = 1e7 + 5;
int n, m, k;
class node{
    public:
    int a, b, c, d;
}cw[MXN];
vector<int> mp[MXN];
int ar[MXN];
// mt19937 rng(time(NULL));

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    srand(time(NULL));
    int tim = read();
    while (tim--) {
        n = read(), m = read();
        for(int i = 1; i <= m; ++i) mp[i].clear();
        for(int i = 1, opt; i <= n; ++i) {
            opt = read();
            cw[i].a = read();
            cw[i].b = read();
            cw[i].c = read();
            cw[i].d = read();
            mp[opt].eb(i);
        }
        for(int i = 1; i <= m; ++i) {
            if((int)mp[i].size()) random_shuffle(all(mp[i]));
        }
        int64 ans = 0;
        int64 a = 100 , b = 100, c = 100, d = 100;
        int64 ta, tb, tc, td;
        for(int t = 0; t < 1000; ++ t) {
            a = 100 , b = 100, c = 100, d = 100;
            for(int i = 1; i <= m; ++i) {
                if(SZ(mp[i]) == 0) {
                    ar[i] = -1;
                    continue;
                }
                ar[i] = rand() % SZ(mp[i]);
                // debug(ar[i], SZ(mp[i]))
                a += cw[mp[i][ar[i]]].a;
                b += cw[mp[i][ar[i]]].b;
                c += cw[mp[i][ar[i]]].c;
                d += cw[mp[i][ar[i]]].d;
            }
            int64 tmp = a * b * c * d;
            // break;
            for(int i = 1; i <= m; ++i) {
                int j = 0;
                for(int x: mp[i]) {
                    if(x != mp[i][ar[i]]) {
                        ta = a + cw[x].a - cw[mp[i][ar[i]]].a;
                        tb = b + cw[x].b - cw[mp[i][ar[i]]].b;
                        tc = c + cw[x].c - cw[mp[i][ar[i]]].c;
                        td = d + cw[x].d - cw[mp[i][ar[i]]].d;
                        if(ta * tb * tc * td > tmp) {
                            a = ta;
                            b = tb;
                            c = tc;
                            d = td;
                            tmp = ta * tb * tc * td;
                            ar[i] = j;
                        }
                    }
                    ++ j;
                }
            }
            ans = max(ans, tmp);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

