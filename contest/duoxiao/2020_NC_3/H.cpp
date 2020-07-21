/*

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
// mt19937 rng(time(NULL));
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

const int MXN = 8e5 + 5;
int n, m;
int fa[MXN], rk[MXN];
set<int> mp[MXN];
vector<int> sn[MXN], vs;
int Fi(int x) {
    return fa[x] == x? x: fa[x] = Fi(fa[x]);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read(), m = read();
        for(int i = 0; i < n; ++i) {
            fa[i] = i, rk[i] = 1, mp[i].clear();
            sn[i].clear();
        }
        for(int i = 0; i < n; ++i) {
            sn[i].eb(i);
        }
        for(int i = 1, a, b; i <= m; ++i) {
            a = read(), b = read();
            mp[a].insert(b);
            mp[b].insert(a);
        }
        int q = read(), opt;
        while(q --) {
            opt = read();
            if(Fi(opt) != opt) continue;
            vs.clear();
            for(int x: mp[opt]) vs.eb(Fi(x));
            for(int j: vs) {
                if(Fi(j) == Fi(opt)) mp[opt].erase(j);
                else {
                    if(sn[j].size() > sn[opt].size()) {
                        swap(sn[j], sn[opt]);
                    }
                    for(int x: sn[j]) {
                        sn[opt].eb(x);
                    }
                    sn[j].clear();
                    fa[j] = opt;
                    rk[opt] += rk[j];
                    if(mp[j].size() > mp[opt].size()) swap(mp[j], mp[opt]);
                    for(int i: mp[j]) {
                        if(Fi(i) != Fi(opt)) {
                            if(mp[opt].find(i) == mp[opt].end()) {
                                mp[opt].insert(i);
                                mp[i].insert(opt);
                            }
                        }
                    }
                    mp[j].clear();
                }
            }
            // debug(q);
            // for(int i = 0; i < n; ++i) {
            //     printf("%d %d: ", i, Fi(i));
            //     for(int x: sn[i]) {
            //         printf("%d ", x);
            //     }
            //     printf("\n");
            //     for(int x: mp[i]) {
            //         printf("%d ", x);
            //     }
            //     printf("\n");
            // }
        }
        for(int i = 0; i < n; ++i) {
            if(Fi(i) != i) continue;
            for(int x: sn[i]) {
                fa[x] = i;
            }
        }
        for(int i = 0; i < n; ++i) printf("%d%c", fa[i], " \n"[i == n - 1]);
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
