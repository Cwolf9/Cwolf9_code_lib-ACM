/*
链接
https://ac.nowcoder.com/acm/contest/5668/E
题意
n = m = q = 8e5
n个点，m条边，每个点属于一个group, q次操作，每次操作给你一个group id 为 o，将与o有边链接
的group的点都合并到o这个group里面去，原来的group就当不存在了；如果输入的o的group不存在了，
就不做操作

思路
看代码比较好理解
用并查集维护group的存在，和它的中心点o 
设o是我这次询问的group id，刚开始就是点o自己 
设V是group o中的点相连的的，v = Fi(v)就是与group o相连的group id 
将与o点相连的点缩点缩到o之后，这些边就没必要再次访问了，因为哪些点已经被合并了
所以利用链式前向星建图的特性，每次缩点之后，给o一个新的head数组，记录外面扩散来的链接点的情况。
我就先遍历o的head记录链式前向星中的点，每次缩点合并儿子 v 的group，就是把v的head数组拼到新的
链式前向星的后面，cw[x].nex = head[v]所以我在用一个last数组记录每个点最早加入的一条边，也就
是cw[tot.nex=-1的tot，这样就很方便合并了


启发式合并n*log*log测评机不抖就能过
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
    if(head[a] == -1) last[a] = tot;//这是第一条边，cw[tot].nex=-1，以后可以把别的链式前向星拼接过来
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

/*
启发式分治的代码
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
*/