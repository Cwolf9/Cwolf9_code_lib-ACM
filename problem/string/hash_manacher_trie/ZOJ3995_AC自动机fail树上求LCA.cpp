#include <cstdio>
#include <bits/stdc++.h>
#define clr(a, x) memset(a, x, sizeof((a)));
using namespace std;
void debug_out() {
    cout << '\n';
}
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
const int MXN_T = 6e5 + 105;
const int CHAR_SIZE = 26;
const int MXN = 6e5 + 105;
int n;
char s[MXN_T];
int st[MXN], len[MXN], Id[MXN];
struct lp {
    int v, nex;
    int w;
} cw[MXN_T<<1];
int tot, head[MXN];
namespace LCA {
int fa[MXN], sz[MXN], dep[MXN], son[MXN], top[MXN], dis[MXN];
void dfs1(int u,int ba,int d) {
    dep[u] = d;
    fa[u] = ba;
    sz[u] = 1;
    son[u] = 0;
    for(int i = head[u], v; ~i; i = cw[i].nex) {
        v = cw[i].v;
        if(v == ba) continue;
        dis[v] = dis[u] + cw[i].w;
        dfs1(v, u, d + 1);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
}
void rdfs(int u,int ba) {
    if(son[u]) {
        top[son[u]] = top[u];
        rdfs(son[u], u);
    }
    for(int i = head[u], v; ~i; i = cw[i].nex) {
        v = cw[i].v;
        if(v == ba || v == son[u]) continue;
        top[v] = v;
        rdfs(v, u);
    }
}
int lca(int x,int y) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y]? x: y;
}
int query(int x, int y) {
    return dis[x] + dis[y] - 2 * dis[lca(x, y)];
}
void init(int rt) {
    dfs1(rt, rt, 1);
    top[rt] = rt;
    rdfs(rt, rt);
}
void add_edge(int a,int b) {
    cw[++tot].v=b;
    cw[tot].nex=head[a],cw[tot].w=1;
    head[a]=tot;
}

}
struct AC_Auto {
    struct Trie {
        int nex[CHAR_SIZE];
        int fail, cnt, is, last;
    } cw[MXN_T];
    int siz, rt;
    void init() {
        siz = rt = 0;
        clr(cw[siz].nex, -1);
        cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
        cw[siz].last = 0;
    }
    int idx(char c) {
        return c - 'a';
    }
    void add_str(char *s, int len, int id) {
        rt = 0;
        for (int i = 0, now; i < len; ++i) {
            now = idx(s[i]);
            //debug(rt)
            if (cw[rt].nex[now] == -1) {
                cw[rt].nex[now] = ++siz;
                clr(cw[siz].nex, -1);
                cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
                cw[siz].last = 0;
            }
            ++ cw[rt].cnt;
            rt = cw[rt].nex[now];
        }
        //debug(rt)
        ++ cw[rt].cnt;
        cw[rt].is = 1;
        Id[id] = rt;
    }
    void build_ac() {
        queue<int> Q;
        Q.push(0);
        cw[0].fail = -1;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0, pos; i < CHAR_SIZE; ++i) {
                pos = cw[u].nex[i];
                if (~pos) {
                    assert(pos != -1);
                    if (u == 0) cw[pos].fail = u;
                    else {
                        assert(u != -1);
                        int v = cw[u].fail;
                        while (v != -1) {
                            if (cw[v].nex[i] != -1) {
                                cw[pos].fail = cw[v].nex[i];
                                break;
                            }
                            v = cw[v].fail;
                        }
                        if (v == -1) cw[pos].fail = 0;
                    }
                    //last[u] = val[f[u]] ? f[u] : last[f[u]];后缀链接，表示节点rt沿着失配指针往回走遇到的下一个单词节点编号
                    cw[pos].last = cw[cw[pos].fail].is?cw[pos].fail:cw[cw[pos].fail].last;
                    Q.push(pos);
                } else {//建新的边补全图（可选可不选,会改变遍历方式
//                    if(cw[u].fail >= 0) cw[u].nex[i] = cw[cw[u].fail].nex[i];
//                    else cw[u].nex[i] = 0;
                }
            }
        }
        for(int i = 1; i <= siz; ++i) {
            if(cw[i].fail == -1) continue;
            LCA::add_edge(cw[i].fail, i);
        }
        LCA::init(0);
    }
} aho;
int main() {
    //freopen("in.txt", "r", stdin);
    while(~scanf("%d",&n)) {
        tot = -1;
        aho.init();
        int lenl = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%s", s + lenl);
            st[i] = lenl;
            len[i] = strlen(s + lenl);
            lenl += strlen(s + lenl) + 1;
            aho.add_str(s + st[i], len[i], i);
        }
        for(int i = 0; i <= aho.siz; ++i) head[i] = -1;
        aho.build_ac();
//        for(int i = 1; i <= n; ++i) {
//            printf("%d %s\n", st[i], s + st[i]);
//        }
        int Q;
        scanf("%d", &Q);
        aho.cw[0].cnt = 0;
        while(Q --) {
            int a, b;
            scanf("%d%d", &a, &b);
            //debug(Id[a], Id[b], LCA::lca(Id[a], Id[b]))
            if(aho.cw[LCA::lca(Id[a], Id[b])].cnt) printf("%d\n", aho.cw[LCA::lca(Id[a], Id[b])].cnt);
            else printf("N\n");
        }
    }
    return 0;
}