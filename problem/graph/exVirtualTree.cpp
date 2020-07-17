#include<bits/stdc++.h>
using namespace std;
typedef long long int64;
namespace VT {
    struct lp {
        int v, nex;
        int64 w;
    } cw[MXE];
    int tot, head[MXN], stak[MXN], top, d[MXN], is[MXN];
    void add_edge(int a, int b, int64 c) {
        cw[++tot].v = b, cw[tot].nex = head[a], cw[tot].w = c;
        head[a] = tot;
        cw[++tot].v = a, cw[tot].nex = head[b], cw[tot].w = c;
        head[b] = tot;
    }
    bool cmp(const int &a, const int &b) {///tid is dfs number
        return LCA::tid[ar[a]] < LCA::tid[ar[b]];
    }
    void build(int n) {//询问的n个点是ar[i], 下面假设1不包含在内，注意自己判断
        tot = head[1] = -1;
        stak[top = 1] = 1;
        for(int i = 1; i <= n; ++i) d[i] = i, is[ar[i]] = 1;
        sort(d + 1, d + 1 + n, cmp);
        for(int i = 1; i <= n; ++i) {
            if(ar[d[i]] == 1) continue;//有1就pass
            int lca = LCA::lca(ar[d[i]], stak[top]);
            if(lca != stak[top]) {//栈顶不是lca
                while(LCA::tid[lca] < LCA::tid[stak[top-1]]) {//把另一条链弹出去并连边
                    add_edge(stak[top], stak[top-1], LCA::query(stak[top], stak[top-1]));
                    -- top;
                }
                if(lca == stak[top-1]) {
                    add_edge(stak[top], stak[top-1], LCA::query(stak[top], stak[top-1]));
                    -- top;
                }else {//把栈顶和lca的边补上，并替换栈顶
                    head[lca] = -1;
                    add_edge(lca, stak[top], LCA::query(lca, stak[top]));
                    stak[top] = lca;
                }
            }
            stak[++top] = ar[d[i]];
            head[stak[top]] = -1;
        }
        for(int i = 2; i <= top; ++i) add_edge(stak[i], stak[i-1], LCA::query(stak[i], stak[i-1]));
    }
    int64 dp[MXN];
    void dfs(int u, int ba) {
        dp[u] = 0;
        for(int i = head[u], v; ~i; i = cw[i].nex) {
            v = cw[i].v;
            if(v == ba) continue;
            dfs(v, u);
            if(is[v]) dp[u] += cw[i].w;
            else dp[u] += sml(dp[v], cw[i].w);
        }
    }
}

int main() {

    return 0;
}