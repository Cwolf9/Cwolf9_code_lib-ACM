//2252: Delivery Delays
#include<bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define  mem(a,b)    memset(a,b,sizeof(a))
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef unsigned long long uLL;
const int MXN = 1e3 + 7;
const int INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;

int n, m, vis[MXN], tot, head[MXN];
LL d[MXN], dis[MXN][MXN];
struct lp {
    int s, u, t;
}cw[MXN];
struct Edge {
    int v, nxt;
    LL w;
} edge[MXN*100];
void init() {
    tot = 0;
    mem ( head, -1 );
}
void add ( int u, int v, LL w ) {
    edge[tot].v = v;
    edge[tot].w = w;
    edge[tot].nxt = head[u];
    head[u] = tot++;
}
struct node {
    LL d, v;
    node ( LL d, LL v ) : d ( d ), v ( v ) {}
    bool operator < ( const node & a ) const {
        return d > a.d;
    }
};
priority_queue<node>q;
void dijstar ( int s ) {
    while ( !q.empty() ) q.pop();
    for ( int i = 0 ; i <= n ; i++ ) d[i] = INFLL, vis[i] = 0;
    d[s] = 0;
    q.push ( node ( 0, s ) );
    while ( !q.empty() ) {
        node temp = q.top();
        q.pop();
        int u = temp.v;
        if ( vis[u] ) continue;
        vis[u] = 1;
        for ( int i = head[u]; ~i ; i = edge[i].nxt ) {
            int v = edge[i].v;
            if ( d[v] > d[u] + edge[i].w && !vis[v] ) {
                d[v] = d[u] + edge[i].w;
                q.push ( node ( d[v], v ) );
            }
        }
    }
}
LL dp[MXN], len[MXN][MXN], late[MXN][MXN];
bool check(LL mid, int Q) {//等待时间不能超过mid
    for(int i = 1; i <= Q; ++i) dp[i] = INFLL;
    dp[0] = 0;
    for(int i = 1; i <= Q; ++i) {
        LL st = 0, Max = INFLL;
        for(int j = 1; j <= i; ++j) {//枚举分段点
            st = max(dp[j-1], (LL)cw[i].t);
            if(late[j][i] + st <= mid) {
                Max = min(Max, len[j][i] + st);
            }
        }
        if(Max == INFLL) return false;
        dp[i] = Max;
    }
    return dp[Q] < INFLL;
}
void gao(int n) {
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) len[i][j]=late[i][j]=INFLL;
    for(int i = 1; i <= n; ++i) {
        LL all = 0, waite = -INFLL;
        int ls = 1;
        for(int j = i; j <= n; ++j) {
            all += dis[ls][cw[j].u];
            waite = max(waite, all - cw[j].s);
            late[i][j] = waite;
            len[i][j] = all + dis[1][cw[j].u];
            ls = cw[j].u;
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);
#endif
    scanf ( "%d%d", &n, &m );
    init();
    for ( int i = 0, u, v ; i < m; i++ ) {
        LL w;
        scanf ( "%d%d%lld", &u, &v, &w );
        add ( u, v, w ), add ( v, u, w );
    }
    for ( int i = 1 ; i <= n ; i++ ) {
        dijstar ( i );
        for(int j = 1; j <= n; ++j) dis[i][j] = d[j];
    }
    int Q; scanf("%d", &Q);
    for(int i = 1; i <= Q; ++i) {
        scanf("%d%d%d", &cw[i].s, &cw[i].u, &cw[i].t), assert(cw[i].t>=cw[i].s);
    }
    gao(Q);
    LL L = 0, R = 1e15, ans = 0, mid;
    while(L <= R) {
        mid = (L + R) >> 1;
        if(check(mid, Q)) ans = mid, R = mid - 1;
        else L = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
/*
#include<bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define  mem(a,b)    memset(a,b,sizeof(a))
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef unsigned long long uLL;
const int MXN = 1e3 + 7;
const int INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;

int n, m, vis[MXN], tot, head[MXN];
LL d[MXN], dis[MXN][MXN];
struct lp {
    int s, u, t;
}cw[MXN];
struct Edge {
    int v, nxt;
    LL w;
} edge[MXN*100];
void init() {
    tot = 0;
    mem ( head, -1 );
}
void add ( int u, int v, LL w ) {
    edge[tot].v = v;
    edge[tot].w = w;
    edge[tot].nxt = head[u];
    head[u] = tot++;
}
struct node {
    LL d, v;
    node ( LL d, LL v ) : d ( d ), v ( v ) {}
    bool operator < ( const node & a ) const {
        return d > a.d;
    }
};
priority_queue<node>q;
void dijstar ( int s ) {
    while ( !q.empty() ) q.pop();
    for ( int i = 0 ; i <= n ; i++ ) d[i] = INFLL, vis[i] = 0;
    d[s] = 0;
    q.push ( node ( 0, s ) );
    while ( !q.empty() ) {
        node temp = q.top();
        q.pop();
        int u = temp.v;
        if ( vis[u] ) continue;
        vis[u] = 1;
        for ( int i = head[u]; ~i ; i = edge[i].nxt ) {
            int v = edge[i].v;
            if ( d[v] > d[u] + edge[i].w && !vis[v] ) {
                d[v] = d[u] + edge[i].w;
                q.push ( node ( d[v], v ) );
            }
        }
    }
}
LL dp[MXN];
bool check(LL mid, int Q) {//等待时间不能超过mid
    for(int i = 1; i <= Q; ++i) dp[i] = INFLL;
    dp[0] = 0;
    for(int i = 0; i < Q; ++i) {//i是分段点
        LL tmp, last = dp[i], ret = 0, Tim = 0, lt = INFLL;
        for(int j = 1, v; j + i <= Q; ++j) {//枚举后续点
            v = j + i;
            if(j == 1) tmp = dis[1][cw[v].u];
            else tmp = dis[cw[v-1].u][cw[v].u];
            Tim += tmp;//单纯走过去的时间
            last = max(dp[i],(LL)cw[v].t);
            if(j == 1) ret = last+tmp-cw[v].s;//最多的等待时间
            else ret = max(ret, last+Tim-cw[v].s);
            lt = min(lt, mid - Tim + cw[v].s);
            if(lt < last) break;
            if(j == 1) dp[v] = min(dp[v], max(dp[i], (LL)cw[v].t) + tmp * 2);
            else dp[v] = min(dp[v], last+Tim+dis[cw[v].u][1]);//回到起点的最短时间
        }
    }
    return dp[Q] < INFLL;
}
int main() {
    scanf ( "%d%d", &n, &m ); init();
    for ( int i = 0, u, v ; i < m; i++ ) {LL w;
        scanf ( "%d%d%lld", &u, &v, &w );
        add ( u, v, w ), add ( v, u, w );
    }
    for ( int i = 1 ; i <= n ; i++ ) {
        dijstar ( i );
        for(int j = 1; j <= n; ++j) dis[i][j] = d[j];
    }
    int Q; scanf("%d", &Q);
    for(int i = 1; i <= Q; ++i) {
        scanf("%d%d%d", &cw[i].s, &cw[i].u, &cw[i].t), assert(cw[i].t>=cw[i].s);
    }
    LL L = 0, R = 1e15, ans = 0, mid;
    while(L <= R) {
        mid = (L + R) >> 1;
        if(check(mid, Q)) ans = mid, R = mid - 1;
        else L = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
*/
