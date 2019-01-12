#include <cstdio>#include <iostream>#include <cstring>#include <algorithm>#include <queue>#define lson rt << 1#define rson rt << 1 | 1using namespace std;typedef long long LL;const LL INF = 0x3f3f3f3f;const int MXN = 6e5 + 5;const int MXE = 4e6 + 6;int n, m, k;int inde;vector<int>vs, vt;struct lp{    int v, nex;    int w;    friend bool operator < (const lp &a,const lp &b) {        return a.w > b.w;    }}cw[MXE], A, B;int head[MXN], tot;int dis[MXN][12];int vis[MXN][12];void add_edge(int u,int v,int w) {    cw[++tot].v = v; cw[tot].w = w; cw[tot].nex = head[u];    head[u] = tot;}int seg[MXN][2];void build(int id,int l,int r,int rt) {    seg[rt][id] = ++inde;///inde = n;    if(l == r) {        if(id) add_edge(seg[rt][id], l, 0);        else add_edge(l, seg[rt][id], 0);        return;    }    int mid = (l + r) >> 1;    build(id, l, mid, lson); build(id, mid + 1, r, rson);    if(id) {        add_edge(seg[rt][id], seg[lson][id], 0); add_edge(seg[rt][id], seg[rson][id], 0);    }else {        add_edge(seg[lson][id], seg[rt][id], 0); add_edge(seg[rson][id], seg[rt][id], 0);    }}void query(int id,int L,int R,int l,int r,int rt) {    if(L <= l && r <= R) {        if(id) vs.push_back(seg[rt][id]);        else vt.push_back(seg[rt][id]);        return;    }    int mid = (l + r) >> 1;    if(L > mid) query(id, L, R, mid+1, r, rson);    else if(R <= mid) query(id,L,R,l,mid,lson);    else {        query(id,L,mid,l,mid,lson); query(id,mid+1,R,mid+1,r,rson);    }}void dij() {    for(int i = 1; i <= inde; ++i) {        for(int j = 0; j <= k; ++j) {            dis[i][j] = INF;            vis[i][j] = 0;        }    }    dis[1][0] = 0;    A.v = 1; A.w = 0; A.nex = 0;    priority_queue<lp> Q;    Q.push(A);    while(!Q.empty()) {        B = Q.top(); Q.pop();        int u = B.v, t = B.nex;        if(vis[u][t]) continue;        vis[u][t] = 1;        for(int i = head[u]; ~i; i = cw[i].nex) {            int v = cw[i].v;            if(dis[v][t] > dis[u][t] + cw[i].w) {                dis[v][t] = dis[u][t] + cw[i].w;                A.v = v; A.w = dis[v][t]; A.nex = t;                Q.push(A);            }            if(t < k && dis[v][t+1] > dis[u][t]) {                dis[v][t+1] = dis[u][t];                A.v = v; A.w = dis[v][t+1]; A.nex = t+1;                Q.push(A);            }        }    }    int ans = INF;    for(int i = 0; i <= k; ++i) ans = min(ans, dis[n][i]);    if(ans >= INF) printf("CreationAugust is a sb!\n");    else printf("%d\n", ans);}int main() {    int tim;    scanf("%d", &tim);    while(tim --) {        scanf("%d%d%d", &n, &m, &k);        int a, b, c, d, w;        memset(head, -1, sizeof(head));        tot = -1;        inde = n;        build(1, 1, n, 1); build(0, 1, n, 1);        for(int i = 0, ta, tb; i < m; ++i) {            scanf("%d%d%d%d%d", &a, &b, &c, &d, &w);            vs.clear(); vt.clear();            query(1,c,d,1,n,1); query(0,a,b,1,n,1);            ta = vs.size(); tb = vt.size();            for(int i = 0; i < tb; ++i) {                for(int j = 0; j < ta; ++j) {                    add_edge(vt[i], vs[j], w);                }            }            vs.clear(); vt.clear();            query(1,a,b,1,n,1); query(0,c,d,1,n,1);            a = vs.size(); b = vt.size();            for(int i = 0; i < b; ++i) {                for(int j = 0; j < a; ++j) {                    add_edge(vt[i], vs[j], w);                }            }        }        dij();    }    return 0;}/*#include <cstdio>#include <cstring>#include <iostream>#include <queue>#define mme(a,b) memset((a),(b),sizeof((a)))  #define test printf("***\n")#define fuck(x) cout<<"* "<<x<<"\n"#define iis std::ios::sync_with_stdio(false)using namespace std;typedef long long LL;const int INF = 0x3f3f3f3f;const int MXN = 1e4+7;const int MXE = 1e7+7;struct DINIC{  int tot,vt,vs;  int d[MXN],head[MXN];  struct lp{    int v,w,nex;  }cw[MXE];  void add_edge(int a,int b,int c){    cw[++tot].v=b;cw[tot].nex=head[a],cw[tot].w=c;    head[a]=tot;    cw[++tot].v=a;cw[tot].nex=head[b],cw[tot].w=0;    head[b]=tot;  }  bool bfs(){    memset(d,-1,sizeof(d));    queue<int>Q;    Q.push(vt);d[vt]=0;    while(!Q.empty()){      int u=Q.front();      Q.pop();      for(int i=head[u];i!=-1;i=cw[i].nex){        int v=cw[i].v;        if(cw[i^1].w&&d[v]==-1){          d[v]=d[u]+1;          Q.push(v);        }      }    }    return d[vs]!=-1;  }  int dfs(int x,int f){    if(x==vt||f==0) return f;    int use=0,w;    for(int i=head[x];i!=-1;i=cw[i].nex){      int to=cw[i].v;      if(d[to]==d[x]-1 && cw[i].w){        w=dfs(to,min(cw[i].w,f-use));        cw[i].w-=w,cw[i^1].w+=w;        use+=w;        if(use==f) return f;      }    }    //if(!use)d[x]=-1;    return use;  }  void init(int st,int ed){    tot=-1;    memset(head,-1,sizeof(head));    vs=st;vt=ed;  }  int max_flow(){    int ans=0;    while(bfs())ans+=dfs(vs,INF);    return ans;  }}dinic;const int N = 805;int n, m, p;int vs, vt;struct lp{  int m,a[N],b[N];}cw[N];int main(){#ifndef ONLINE_JUDGE    freopen("E://ADpan//in.in", "r", stdin);    //freopen("E://ADpan//out.out", "w", stdout);  #endif  while(~scanf("%d%d",&p,&n)){    vs=0;vt=2*n+1;    dinic.init(vs,vt);      }  return 0;}*//*#include <iostream>#include <cstdio>#include <cmath>#include <cstring>#include <ctime>#include <cstdlib>#include <string>#include <bitset>#include <vector>#include <set>#include <map>#include <queue>#include <algorithm>#include <sstream>#include <stack>#include <iomanip>using namespace std;typedef long long LL;const int MAXN = 605;const int MAXE = 4e5 + 7;const int INF = 0x3f3f3f3f;struct MCMF {    int S, T;//Ô´µã£¬»ãµã    int tot, n;    int st, en, maxflow, mincost;    bool vis[MAXN];    int head[MAXN], cur[MAXN], dis[MAXN];    int roade[MAXN], roadv[MAXN], rsz; //ÓÃÓÚ´òÓ¡Â·¾¶    queue <int> Q;    struct Edge {        int v, cap, cost, nxt, flow;        Edge() {}        Edge(int a, int b, int c, int d) {            v = a, cap = b, cost = c, nxt = d, flow = 0;        }    } E[MAXE], SE[MAXE];    void init(int _n) {        n = _n, tot = 0;        for(int i = 0; i <= n; i++) head[i] = -1;    }    void add_edge(int u, int v, int cap, int cost) {        E[tot] = Edge(v, cap, cost, head[u]);        head[u] = tot++;        E[tot] = Edge(u, 0, -cost, head[v]);        head[v] = tot++;    }    bool adjust() {        int v, min = INF;        for(int i = 0; i <= n; i++) {            if(!vis[i]) continue;            for(int j = head[i]; ~j; j = E[j].nxt) {                v = E[j].v;                if(E[j].cap - E[j].flow) {                    if(!vis[v] && dis[v] - dis[i] + E[j].cost < min) {                        min = dis[v] - dis[i] + E[j].cost;                    }                }            }        }        if(min == INF) return false;        for(int i = 0; i <= n; i++) {            if(vis[i]) {                cur[i] = head[i];                vis[i] = false;                dis[i] += min;            }        }        return true;    }    int augment(int i, int flow) {        if(i == en) {            mincost += dis[st] * flow;            maxflow += flow;            return flow;        }        vis[i] = true;        for(int j = cur[i]; j != -1; j = E[j].nxt) {            int v = E[j].v;            if(E[j].cap == E[j].flow) continue;            if(vis[v] || dis[v] + E[j].cost != dis[i]) continue;            int delta = augment(v, std::min(flow, E[j].cap - E[j].flow));            if(delta) {                E[j].flow += delta;                E[j ^ 1].flow -= delta;                cur[i] = j;                return delta;            }        }        return 0;    }    void spfa() {        int u, v;        for(int i = 0; i <= n; i++) {            vis[i] = false;            dis[i] = INF;        }        Q.push(st);        dis[st] = 0;        vis[st] = true;        while(!Q.empty()) {            u = Q.front(), Q.pop();            vis[u] = false;            for(int i = head[u]; ~i; i = E[i].nxt) {                v = E[i].v;                if(E[i].cap == E[i].flow || dis[v] <= dis[u] + E[i].cost) continue;                dis[v] = dis[u] + E[i].cost;                if(!vis[v]) {                    vis[v] = true;                    Q.push(v);                }            }        }        for(int i = 0; i <= n; i++) {            dis[i] = dis[en] - dis[i];        }    }    int zkw_flow(int s, int t) {        st = s, en = t;        spfa();        mincost = maxflow = 0;        for(int i = 0; i <= n; i++) {            vis[i] = false;            cur[i] = head[i];        }        do {            while(augment(st, INF)) {                memset(vis, false, n * sizeof(bool));            }        } while(adjust());        return mincost;    }}zkw;//u v Á÷Á¿ ·ÑÓÃconst int N = 55;inline int ab(int x){return x<0?-x:x;}int vs,vt;int n,m,p;int main() {#ifndef ONLINE_JUDGE    freopen("E://ADpan//in.in", "r", stdin);    //freopen("E://ADpan//out.out", "w", stdout);  #endif  while(~scanf("%d%d%d",&n,&m,&p)){    vs=n+m+1;vt=n+m+2;      }  return 0;}*//*#include<iostream>#include<cstdio>#include<cstring>#include<algorithm>#include<map>#include<queue>#include<set>#include<string>#include<cmath>#include<bitset>using namespace std;typedef long long LL;const int N=550;const int INF = 0x7fffffff;int n,m;int match[N];int lx[N],ly[N];int sx[N],sy[N];int weight[N][N];int dfs(int x) {    sx[x]=true;    for(int i=0; i<n; i++) {        if(!sy[i]&&lx[x]+ly[i]==weight[x][i]) {            sy[i]=true;            if(match[i]==-1||dfs(match[i])) {                match[i]=x;                return true;            }        }    }    return false;}int fax(int x) {    if(!x) {        for(int i=0; i<n; i++) {            for(int j=0; j<n; j++) {                weight[i][j]=-weight[i][j];            }        }    }    memset(match,-1,sizeof(match));    for(int i=0; i<n; i++) {        ly[i]=0;        lx[i]=-INF;        for(int j=0; j<n; j++) {            if(weight[i][j]>lx[i]) {                lx[i]=weight[i][j];            }        }    }    for(int i=0; i<n; i++) {        while(1) {            memset(sx,0,sizeof(sx));            memset(sy,0,sizeof(sy));            if(dfs(i))break;            int mic=INF;            for(int j=0; j<n; j++) {                if(sx[j]) {                    for(int k=0; k<n; k++) {                        if(!sy[k]&&lx[j]+ly[k]-weight[j][k]<mic) {                            mic=lx[j]+ly[k]-weight[j][k];                        }                    }                }            }            if(mic==0) return -1;            for(int j=0; j<n; j++) {                if(sx[j]) lx[j]-=mic;                if(sy[j]) ly[j]+=mic;            }        }    }    int sum=0;    for(int i=0; i<n; i++) {        if(match[i]>=0) {            sum+=weight[match[i]][i];        }    }    if(!x) sum=-sum;    return sum;}inline int ab(int x){return x<0?-x:x;}int num_boy,num_gril;int boy[N],girl[N];char ar[N];int main() {  while(~scanf("%d%d",&n,&m)&&(n+m)){    for(int i=0;i<=205;++i)      for(int j=0;j<=205;++j)        weight[i][j]=INF;    num_boy=num_gril=0;    for(int i=0;i<n;++i){      scanf("%s",ar);      for(int j=0;j<=m;++j){        if(ar[j]=='H'){          girl[num_gril++]=i*m+j;        }else if(ar[j]=='m'){          boy[num_boy++]=i*m+j;        }      }    }    n=num_boy;    for(int i=0;i<n;++i){      for(int j=0;j<n;++j){        int u=boy[i],v=girl[j];        weight[i][j]=min(ab(u/m-v/m)+ab(u%m-v%m), weight[i][j]);      }    }    printf("%d\n",fax(0));  }  return 0;}#include<bits/stdc++.h>#define fi first#define se second#define lson rt<<1#define rson rt<<1|1using namespace std;typedef long long LL;typedef pair<LL,int> pii;const int mod = 1e9+7;const int MXN = 1e5 + 7;const int MXE = 1e7 + 5e6 + 7;const LL INF = 0x3f3f3f3f3f3f3f3f;int main(){    int tim;scanf("%d", &tim);    while(tim--){        unsigned long long A , B, C, D, E;        scanf("%llu%llu%llu%llu", &A, &B, &C, &D);        E = A+B+C+D;        if(E != 0) {            printf("%llu\n", E);        }else {            if(A == 0&&B == 0&&C == 0&&D == 0) printf("0\n");            else {                printf("18446744073709551616\n");            }        }    }    return 0;}*/