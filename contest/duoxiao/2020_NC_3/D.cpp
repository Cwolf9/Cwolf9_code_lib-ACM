/*
链接
https://ac.nowcoder.com/acm/contest/5668/D
题意
给你ab，1<=a,b<=2000000 ， 你要输出bcde, 且 d < b and f < b and 1 <=c,e<=4e12
满足： c/d - e/f = a/b
无解输出-1
思路
左边等于 (c*f-e*d)/(df) = k*gcd(d,f)/df = a/b
把b分成两个互质的数，分给d和f，这样的话就是 k = a，构造一个c和e就好了
如果b不能分成两个互质的数，那么b = p^k，如果gcd(a,b)=1就无解
否者就让 d=f= b/p， c - e = a/p，如果a=p就无解，否则就有解。

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

const int MXN = 2e6 + 5;
int n, m;
int fa[MXN];
int  is[MXN], tim[MXN], kong[MXN];
int head[MXN], tot, last[MXN];
class node {
    public:
    int v, nex;
}cw[MXN + MXN];
void add_edge(int a, int b) {
    cw[++ tot].v = b, cw[tot].nex = head[a];
    if(head[a] == -1) last[a] = tot;
    head[a] = tot; 
    cw[++ tot].v = a, cw[tot].nex = head[b];
    if(head[b] == -1) last[b] = tot;
    head[b] = tot;
}
int Fi(int x) {
    return fa[x] == x? x: fa[x] = Fi(fa[x]);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tims = read();
    while(tims --) {
        n = read(), m = read();
        tot = -1;
        for(int i = 0; i < n; ++i) {
            fa[i] = i;
            head[i] = -1;
            last[i] = -1;
        }
        for(int i = 1, a, b; i <= m; ++i) {
            a = read(), b = read();
            add_edge(a, b);
        }
        int q = read(), opt;
        while(q --) {
            opt = read();
            int pa = Fi(opt), pb;
            if(pa != opt) continue;
            head[n] = -1;
            for(int i = head[opt]; ~i; i = cw[i].nex) {
                pb = Fi(cw[i].v);
                if(pa != pb) {
                    if(head[n] == -1) head[n] = head[pb], last[n] = last[pb];
                    else {
                        cw[last[pb]].nex = head[n];
                        head[n] = head[pb];
                    }
                    fa[pb] = pa;
                }
            }
            head[opt] = head[n], last[opt] = last[n];
        }
        for(int i = 0; i < n; ++i) printf("%d%c", Fi(i), " \n"[i == n - 1]);
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
