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
struct lp {
    int v, nex;
    long long w;
} cw[MXN_T<<1];
int tot, head[MXN];
namespace LCA {
    long long dis[MXN];
	int up[MXN][22], lens[MXN];
    int cnt, dfn[MXN], en[MXN], LOG[MXN];
    void dfs(int u, int ba) {
        lens[u] = lens[ba] + 1;
        dfn[++cnt] = u;
        en[u] = cnt;
        for(int i = head[u], v; ~i; i = cw[i].nex) {
            v = cw[i].v;
            if(v == ba) continue;
            dis[v] = dis[u] + cw[i].w;
            dfs(v, u);
            dfn[++ cnt] = u;
        }
    }
    inline int cmp(int u, int v) {
        return lens[u] < lens[v] ? u: v;
    }
    void init() {
        cnt = 0;
        dfs(1, 0);
        LOG[1] = 0;
        for(int i = 2; i <= cnt; ++i) LOG[i] = LOG[i-1] + ((1<<(LOG[i-1]+1))==i);
        for(int i = 1; i <= cnt; ++i) up[i][0] = dfn[i];
        for(int j = 1; (1<<j) <= cnt; ++j)
            for(int i = 1; i + (1<<j) - 1 <= cnt; ++i)
                up[i][j] = cmp(up[i][j-1], up[i+(1<<(j-1))][j-1]);
    }
    inline int lca(int x, int y) {
        int l = en[x], r = en[y];
        if(l > r) swap(l, r);
        int k = LOG[r - l + 1];
        return cmp(up[l][k], up[r-(1<<k)+1][k]);
    }
    inline long long Len(int i, int j) {
        return dis[i] + dis[j] - 2 * dis[lca(i, j)];
    }
	void add_edge(int a,int b, int w) {
	    cw[++tot].v=b;
	    cw[tot].nex=head[a],cw[tot].w=w;
	    head[a]=tot;
	}
}
int n, m;

int main() {
    //freopen("in.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    while(t --) {
    	scanf("%d%d",&n, &m);
        tot = -1;
        for(int i = 0; i <= n + 2; ++i) head[i] = -1;
        for(int i = 1; i < n; ++i) {
        	int u, v, w;
        	scanf("%d%d%d",&u,&v,&w);
            LCA::add_edge(u,v,w);
            LCA::add_edge(v,u,w);
		}
		LCA::init();
		int X, Y, Z;
		scanf("%d%d%d",&X,&Y,&Z);
        while(m --) {
            int a,b;
            scanf("%d%d",&a,&b);
            long long ans=min((long long)1e18,LCA::Len(a,b));
            ans=min(ans,min(LCA::Len(a,X)+LCA::Len(b,Y)+Z,LCA::Len(a,Y)+LCA::Len(b,X)+Z));
            printf("%lld\n", ans);
        }
    }
    return 0;
}

