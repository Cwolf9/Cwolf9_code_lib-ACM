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
分块复杂度$O(n*\sqrt(n))$, 1170ms
线段树复杂度$O(n*\sqrt(n)*log(n))$, 1560MS
树状数组+二分求mex复杂度$O(n*\sqrt(n)*log(n)*log(n))$, 1092MS
树状数组求mex复杂度$O(n*\sqrt(n)*log(n)*log(n))$, 1762MS
动态开点线段树TLE
分块维护每个块内数字第一次出现的次数，$O(1)$修改，$O(\sqrt(n))$查询
线段树维护mex其实就是维护最小值
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
const int block_size = 350;
// int tot_n, rk[MXN];
int isBig[MXN], du[MXN], val[MXN], ap_num[MXN], nid[MXN], inde;
vector<int> myBig[MXN], myedge[MXN];
vector<int> vtm[MXN];
pii qEdge[MXN];
void init() {
    inde = 0;
    for (int i = 1; i <= n; ++i) {
        val[i] = io.read();
        du[i] = 0;
        myedge[i].clear();
        myBig[i].clear();
        vtm[i].clear();
    }
}
class Block {
    public:
int n, block_num, block_size;
vector<int> ls, mex, bel, ap_num;
void clear() {
    ls.clear();
    ls.shrink_to_fit();
    mex.clear();
    mex.shrink_to_fit();
    bel.clear();
    bel.shrink_to_fit();
    ap_num.clear();
    ap_num.shrink_to_fit();
}
void build(int N) {//index start from 1
    n = N;
    block_size = sqrt(n);
    block_num = n / block_size + (n%block_size>0?1:0);
    ls.resize(block_num + 1);
    mex.assign(block_num + 1, 0);
    bel.resize(N + 1);
    ap_num.assign(N + 1, 0);
    for(int i = 1; i <= block_num; ++i) {
        ls[i] = (i - 1) * block_size + 1;
    }
    for(int i = 1; i <= n; ++i) {
        bel[i] = (i-1) / block_size + 1;
    }
}
void insert(int x, int f) {
    int id = bel[x];
    ap_num[x] += f;
    mex[id] += f;
}
int query() {
    if(ap_num[1] == 0) return 1;
    int Mn = INF;
    for(int i = 1, rs; i < block_num; ++i) {
        if(mex[i] != block_size) {
            for(int j = ls[i], k = 0; k < block_size; ++ k, ++ j) {
                if(ap_num[j] == 0) {
                    Mn = j;
                    break;
                }
            }
            break;
        }
    }
    if(Mn == INF) {
        for(int i = ls[block_num]; i <= n; ++i) {
            if(ap_num[i] == 0) {
                Mn = i;
                break;
            }
        }
    }
    return Mn;
}
}cw[block_size + block_size];

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = io.read();
    while (tim--) {
        n = io.read(), m = io.read();
        init();
        int opt, a, b;
        for (int i = 1; i <= m; ++i) {
            a = io.read(), b = io.read();
            ++ du[a], ++ du[b];
            qEdge[i] = mk(a, b);
        }
        for (int i = 1; i <= n; ++i) {
            if (du[i] >= block_size) {
                nid[i] = ++ inde;
                cw[inde].clear();
                cw[inde].build(du[i] + 2);
                isBig[i] = 1;
                vtm[i].assign(du[i]+2, 0);
            } else {
                isBig[i] = 0;
            }
        }
        for (int i = 1; i <= m; ++i) {
            a = qEdge[i].fi, b = qEdge[i].se;
            if (isBig[a]) {
                if (val[b] <= du[a]) {
                    ++ vtm[a][val[b]];
                    if(vtm[a][val[b]] == 1) {
                        cw[nid[a]].insert(val[b] + 1, 1);
                    }
                }
                myBig[b].eb(a);
            } else {
                myedge[a].eb(b);
            }
            if (isBig[b]) {
                if (val[a] <= du[b]) {
                    ++ vtm[b][val[a]];
                    if(vtm[b][val[a]] == 1) {
                        cw[nid[b]].insert(val[a] + 1, 1);
                    }
                }
                myBig[a].eb(b);
            } else {
                myedge[b].eb(a);
            }
        }
        k = io.read();
        int ans = 0;
        while (k --) {
            opt = io.read();
            a = io.read();
            if (opt == 1) {
                b = io.read();
                for (int v : myBig[a]) {
                    if(val[a] <= du[v]) {
                        -- vtm[v][val[a]];
                        if(vtm[v][val[a]] == 0) {
                            cw[nid[v]].insert(val[a] + 1, -1);
                        }
                    }
                    if(b <= du[v]) {
                        ++ vtm[v][b];
                        if(vtm[v][b] == 1) {
                            cw[nid[v]].insert(b + 1, 1);
                        }
                    }
                }
                val[a] = b;
            } else {
                if (isBig[a]) {
                    ans = cw[nid[a]].query() - 1;
                } else {
                    for (int i = 0; i <= du[a]; ++i) {
                        ap_num[i] = 0;
                    }
                    for (int x : myedge[a]) {
                        if (val[x] <= du[a]) ++ap_num[val[x]];
                    }
                    for (int i = 0; i <= du[a]; ++i) {
                        if (ap_num[i] == 0) {
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
