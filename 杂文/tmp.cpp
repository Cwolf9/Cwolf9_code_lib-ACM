#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;

struct fastio{
    char s[100005];
    int it,len;
    fastio(){it=len=0;}
    inline char get(){
        if(it<len)return s[it++];it=0;
        len=fread(s,1,100000,stdin);
        if(len==0)return EOF;else return s[it++];
    }
    bool notend(){
        char c=get();
        while(c==' '||c=='\n')c=get();
        if(it>0)it--;
        return c!=EOF;
    }
}BUFF;
#define read(x) x=getnum()
#define write(x) putnum(x),putchar(' ')
#define writeln(x) putnum(x),putchar('\n')

inline LL getnum(){
    LL r=0;bool ng=0;char c;c=BUFF.get();
    while(c!='-'&&(c<'0'||c>'9'))c=BUFF.get();
    if(c=='-')ng=1,c=BUFF.get();
    while(c>='0'&&c<='9')r=r*10+c-'0',c=BUFF.get();
    return ng?-r:r;
}
template<class T> inline void putnum(T x){
    if(x<0)putchar('-'),x=-x;
    register short a[20]={},sz=0;
    while(x)a[sz++]=x%10,x/=10;
    if(sz==0)putchar('0');
    for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline char getreal(){char c=BUFF.get();while(c<=32)c=BUFF.get();return c;}


const int MXN = 1e6 + 5;
const int mod = 1e9 + 7;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
std::vector<pair<int,int> > mp[MXN], edge[MXN];
int dfn[MXN], low[MXN], inde;
int qltMap[MXN], qltNum;
int vis[MXN];
int stak[MXN], top;
int fa[MXN];
LL dis[MXN], ans, ANS[MXN];
void init() {
    for(int i = 1; i <= n; ++i) {
        mp[i].clear();
        edge[i].clear();
        dis[i] = 0;
        dfn[i] = low[i] = 0;
        vis[i] = 0;
        ANS[i] = -1;
    }
    top = inde = qltNum = 0;
}
void dfs(int u,int ba) {
    dfn[u] = low[u] = ++ inde;
    stak[++top] = u;
    vis[u] = 1;
    for(auto V: mp[u]) {
        int v = V.first;
        if(v == ba) continue;
        if(!dfn[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }else if(vis[v] == 1) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int v;
        ++ qltNum;
        do{
            v = stak[top --];
            vis[v] = 2;
            qltMap[v] = qltNum;
        }while(v != u);
    }
}
void dfs1(int u,int ba,LL d) {
    dis[u] = d;
    for(auto x: edge[u]) {
        if(x.first == ba) continue;
        dfs1(x.first, u, x.second + d);
        fa[x.first] = u;
    }
}
int main(){
    int tim;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 1, a, b, c; i <= m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            mp[a].push_back({b,c}); mp[b].push_back({a,c});
        }
        for(int i = 1; i <= n; ++i) {
            if(vis[i] == 0) {
                dfs(i, -1);
            }
        }
        for(int i = 1; i <= n; ++i) {
            for(auto v: mp[i]) {
                if(qltMap[i] != qltMap[v.first]) {
                    edge[qltMap[i]].push_back({qltMap[v.first],v.second});
                }
            }
        }
        dfs1(1, -1, 0);
        int tmp = 1;
        LL mmax = dis[1];
        for(int i = 2; i <= qltNum; ++i) {
            if(dis[i] > mmax) {
                mmax = dis[i];
                tmp = i;
            }
        }
        int vs = tmp;
        dfs1(vs, -1, 0);
        tmp = 1; mmax = dis[1];
        for(int i = 2; i <= qltNum; ++i) {
            if(dis[i] > mmax) {
                mmax = dis[i];
                tmp = i;
            }
        }
        int vt = tmp;
        ans = INF;
        while(tmp != vs) {
            LL a = max(dis[tmp], dis[vt]-dis[tmp]);
            ANS[tmp] = a;
            if(a < ans) ans = a;
            tmp = fa[tmp];
        }
        for(int i = 1; i <= n; ++i) {
            if(ANS[qltMap[i]] == ans) {
                printf("%d %lld\n", i, ans);
                break;
            }
        }
    }
    return 0;
}
