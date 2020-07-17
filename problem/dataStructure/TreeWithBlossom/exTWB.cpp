#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int getint() {
    int w = 0, q = 0;
    char c = getchar();
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') q = 1, c = getchar();
    while (c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
    return q ? -w : w;
}
class Dhs {
   public:
    static const int D_MXN = 520;
    static const int D_MXE = 300005;
    static const int D_MXQL = 10005;
    int n;
    int eCnt, head[D_MXN], nex[D_MXE], to[D_MXE];
    int dui[D_MXQL], hed, tail;
    int fa[D_MXN], id[D_MXN], pre[D_MXN], match[D_MXN], vis[D_MXN], Tim;
    inline void add_edge(int u, int v) {
        nex[++eCnt] = head[u];
        to[eCnt] = v;
        head[u] = eCnt;
    }
    inline int Fi(int x) {
        if (fa[x] != x) fa[x] = Fi(fa[x]);
        return fa[x];
    }
    inline int lca(int x, int y) {
        Tim++;
        while (vis[x] != Tim) {
            if (x) {
                x = Fi(x);
                if (vis[x] == Tim) return x;
                vis[x] = Tim;
                if (match[x] != 0)
                    x = Fi(pre[match[x]]);
                else
                    x = 0;
            }
            swap(x, y);
        }
        return x;
    }

    inline void change(int x, int y, int k) {  
        //把奇环上的点缩成一个点，并且把原来是奇点的点变成偶点，加入队列
        while (Fi(x) != k) {
            pre[x] = y;
            int z = match[x];
            if (id[z] == 1) {
                id[z] = 0;
                dui[++tail] = z;
            }
            if (Fi(z) == z) fa[z] = k;
            if (Fi(x) == x) fa[x] = k;
            y = z;
            x = pre[y];
        }
    }

    inline bool bfs(int ini) {
        for (int i = 1; i <= n; i++) id[i] = -1, fa[i] = i;
        hed = tail = 0;
        dui[++tail] = ini;
        id[ini] = 0;
        int u;
        while (hed < tail) {
            u = dui[++hed];
            for (int i = head[u]; i; i = nex[i]) {
                int v = to[i];
                if (id[v] == -1) {
                    pre[v] = u;
                    id[v] = 1;
                    if (!match[v]) {
                        int last, t, now = v;
                        while (now != 0) {
                            t = pre[now];
                            last = match[t];
                            match[t] = now;
                            match[now] = t;
                            now = last;
                        }
                        return true;
                    }
                    id[match[v]] = 0;
                    dui[++tail] = match[v];
                } else if (id[v] == 0 && Fi(u) != Fi(v)) {  
                    //出现奇环且不是在同一个环中
                    int g = lca(u, v);
                    change(u, v, g);
                    change(v, u, g);
                }
            }
        }
        return false;
    }
    void init(int _n) {
        n = _n;
        eCnt = Tim = 0;
        for (int i = 0; i <= 500; ++i)
            assert(head[i] == 0 && match[i] == 0 && vis[i] == 0 && pre[i] == 0);
    }
    int max_match() {
        int ans = 0;
        for (int i = 1; i <= n; i++)
            if (!match[i] && bfs(i)) ans++;
        printf("%d\n", ans);
        for (int i = 1; i <= n; i++) printf("%d ", match[i]);
        puts("");
        return ans;
    }
} dhs;
int main() {
    dhs.max_match();
    system("pause");
    return 0;
}
