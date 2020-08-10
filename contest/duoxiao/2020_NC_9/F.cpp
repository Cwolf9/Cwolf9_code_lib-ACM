/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#define LH_LOCAL
#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <algorithm>
using namespace std;
#pragma optimize("-O3")
inline int read() {
    int x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
const int MXN = 2e6 + 1e4 + 5;
int n, m;
int d[MXN], vis[MXN], cnt;
int val[MXN], id[MXN];
int vt[MXN], szvt;
bool cmp(const int &A, const int &B) {
    return val[A] < val[B];
}
int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    // debug(2e6 * log(2e6) * 2)
    n = read(), m = read();
    int pp = 0;
    for(int i = 1, a, b; i <= n; ++i) {
        a = read();
        while(a --) {
            b = read();
            val[pp] = b;
            vt[pp] = b;
            id[pp++] = i;
        }
    }
    if(m == 0 || n == 0) {
        printf("0\n");
        return 0;
    }
    sort(vt, vt + pp);
    szvt = unique(vt, vt + pp) - vt;
    // debug(szvt, pp)
    for(int i = 0; i < pp; ++i) {
        d[i] = i;
        // val[i] = get_id(val[i]);
    }
    int tn = pp;
    sort(d, d + tn, cmp);
    int L = 0, ans = 1000000000;
    for(int ti = 0, i; ti < tn; ++ti) {
        i = d[ti];
        ++ vis[id[i]];
        if(vis[id[i]] == 1) ++ cnt;
        // debug(i, id[i], val[i], cnt)
        while(cnt == m) {
            ans = min(val[i] - val[d[L]], ans);
            // debug(i, L, vt[val[i]-1], vt[val[L]-1])
            -- vis[id[d[L]]];
            if(vis[id[d[L]]] == 0) -- cnt;
            ++ L;
        }
    }
    printf("%d\n", ans);
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}