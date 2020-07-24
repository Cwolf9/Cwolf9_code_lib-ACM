/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6756)
**题意**
$n,m,q\le 1e5$无向图, $S_u={A_v|(u,v)\in E}$,$F_u=mex(S_u)$
type 1: 1 u x, change A_u = x
type 2: 2 u, query F_u
**思路**
度数大于$\sqrt(m)$的超级点不超多$\sqrt(m)$个。
小点暴力算，超级点用分块或者bit，线段树
分块复杂度$O(n*\sqrt(n))$
线段树复杂度$O(n*\sqrt(n)*log(n))$, 1560MS
树状数组+二分求mex复杂度$O(n*\sqrt(n)*log(n)*log(n))$, 1092MS
树状数组求mex复杂度$O(n*\sqrt(n)*log(n)*log(n))$, 1762MS
动态开点线段树TLE
**备注**

*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
using namespace std;
typedef long long int64;
typedef pair<int, int> pii;
struct FastIO {
    static const int S = 200;
    int wpos;
    // char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int read() {
        int s = 1, c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    ~FastIO() {
        // if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T& f, const R&... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
const int INF = 0x3f3f3f3f;
const int MXN = 1e5 + 5;
const int MXE = 1e7 + 5;
const int MR = 100002;
int n, m, k;
const int block = 350;
// int tot_n, rk[MXN];
int isBig[MXN], du[MXN], val[MXN], num[MXN];
vector<int> myBig[MXN], myedge[MXN];
vector<int> tree[MXN], vtm[MXN];//, ori[MXN];//2
pii qEdge[MXN];
void init() {
    for (int i = 1; i <= n; ++i) {
        val[i] = io.read();
        du[i] = 0;
        myedge[i].clear();
        myBig[i].clear();
        vtm[i].clear();
        // ori[i].clear();//2
        // ori[i].shrink_to_fit();
        tree[i].clear();
        tree[i].shrink_to_fit();
    }
}
inline int lowbit(int x) { return x & (-x); }
void insert(int x, int v, int id) {
    int N = du[id] + 2;
    while(x <= N) {
        tree[id][x] += v;
        x += lowbit(x);
    }
}
int mquery(int x, int id) {
    int ans = 0;
    while(x >= 1) {
        ans += tree[id][x];
        x -= lowbit(x);
    }
    return ans;
}
// void insewrt(int x, int v, int id) {//2
//     int N = du[id] + 2;
//     ori[id][x] = v;
//     while (x <= N) {
//         tree[id][x] = ori[id][x];
//         v = lowbit(x);
//         for (int i = 1; i < v; i <<= 1) {
//             tree[id][x] = min(tree[id][x], tree[id][x - i]);
//         }
//         x += lowbit(x);
//     }
// }
// int query(int x, int id) {//2
//     int ans = INF;
//     while (x >= 1) {
//         ans = min(ans, ori[id][x]);
//         for (--x; x - lowbit(x) >= 1; x -= lowbit(x)) {
//             ans = min(ans, tree[id][x]);
//         }
//     }
//     return ans;
// }

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim;
    tim = io.read();
    while (tim--) {
        n = io.read(), m = io.read();
        init();
        int opt, a, b;
        for (int i = 1; i <= m; ++i) {
            a = io.read(), b = io.read();
            ++du[a], ++du[b];
            qEdge[i] = mk(a, b);
        }
        for (int i = 1; i <= n; ++i) {
            if (du[i] >= block) {
                isBig[i] = 1;
                tree[i].assign(du[i]+5, 0);
                // tree[i].resize(du[i] + 5);//2
                // ori[i].resize(du[i] + 5);
                // for (int j = 0; j <= du[i]; ++j) {
                //     insewrt(j + 1, j, i);
                // }
                vtm[i].assign(du[i] + 2, 0);
            } else {
                isBig[i] = 0;
            }
        }
        for (int i = 1; i <= m; ++i) {
            a = qEdge[i].fi, b = qEdge[i].se;
            if (isBig[a]) {
                if (val[b] <= du[a]) {
                    ++vtm[a][val[b]];
                    if (vtm[a][val[b]] == 1)
                        insert(val[b] + 1, 1, a);
                        // insewrt(val[b] + 1, INF, a);//2
                }
                myBig[b].eb(a);
            } else {
                myedge[a].eb(b);
            }
            if (isBig[b]) {
                if (val[a] <= du[b]) {
                    ++vtm[b][val[a]];
                    if (vtm[b][val[a]] == 1)
                        insert(val[a] + 1, 1, b);
                        // insewrt(val[a] + 1, INF, b);//2
                }
                myBig[a].eb(b);
            } else {
                myedge[b].eb(a);
            }
        }
        k = io.read();
        int ans = 0;
        while (k--) {
            opt = io.read(), a = io.read();
            if (opt == 1) {
                b = io.read();
                if(val[a] == b) continue;
                for (int v : myBig[a]) {
                    if (val[a] <= du[v]) {
                        --vtm[v][val[a]];
                        if (vtm[v][val[a]] == 0)
                            insert(val[a] + 1, -1, v);
                            // insewrt(val[a] + 1, val[a], v);//2
                    }
                    if (b <= du[v]) {
                        ++vtm[v][b];
                        if (vtm[v][b] == 1)
                            insert(b + 1, 1, v);
                            // insewrt(b + 1, INF, v);//2
                    }
                }
                val[a] = b;
            } else {
                if (isBig[a]) {
                    ans = 1;
                    int mid, L = 1, R = du[a] + 1;
                    while(L <= R) {
                        mid = (L + R) >> 1;
                        if(mquery(mid, a) == mid) L = mid + 1;
                        else R = mid - 1, ans = mid;
                    }
                    -- ans;
                    // ans = query(du[a] + 1, a);//2
                } else {
                    for (int i = 0; i <= du[a]; ++i) {
                        num[i] = 0;
                    }
                    for (int x : myedge[a]) {
                        if (val[x] <= du[a]) ++num[val[x]];
                    }
                    for (int i = 0; i <= du[a]; ++i) {
                        if (num[i] == 0) {
                            ans = i;
                            break;
                        }
                    }
                }
                printf("%d\n", ans);
            }
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}