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
typedef long long LL;
const int MXN = 1e4 + 7;
const int MXE = 2e5 + 7;
const LL INF = 1e17;
struct DINIC {
    int tot,vt,vs;
    int d[MXN],head[MXN];
    struct lp {
        int v,nex;
        LL w;
    } cw[MXE];
    void add_edge(int a,int b,LL c) {
        cw[++tot].v=b;
        cw[tot].nex=head[a],cw[tot].w=c;
        head[a]=tot;
        cw[++tot].v=a;
        cw[tot].nex=head[b],cw[tot].w=0;
        head[b]=tot;
    }
    bool bfs() {
        memset(d,-1,sizeof(d));
        queue<int>Q;
        Q.push(vt);
        d[vt]=0;
        while(!Q.empty()) {
            int u=Q.front();
            Q.pop();
            for(int i=head[u]; i!=-1; i=cw[i].nex) {
                int v=cw[i].v;
                if(cw[i^1].w&&d[v]==-1) {
                    d[v]=d[u]+1;
                    Q.push(v);
                }
            }
        }
        return d[vs]!=-1;
    }
    LL dfs(int x,LL f) {
        if(x==vt||f==0) return f;
        LL use=0,w;
        for(int i=head[x]; i!=-1; i=cw[i].nex) {
            int to=cw[i].v;
            if(d[to]==d[x]-1 && cw[i].w) {
                w=dfs(to,min(cw[i].w,f-use));
                cw[i].w-=w,cw[i^1].w+=w;
                use+=w;
                if(use==f) return f;
            }
        }
        //if(!use)d[x]=-1;
        return use;
    }
    void init(int st,int ed) {
        tot = -1;
        memset(head,-1,sizeof(head));
        vs=st;
        vt=ed;
    }
    int max_flow() {
        int ans=0;
        while(bfs())ans+=dfs(vs,INF);
        return ans;
    }
} dinic;
int id[400], num[400];
int d[11], y[4] = {2, 3, 5, 7};
vector<pair<int, int>> mp;
int main() {
    //freopen("in.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--) {
        mp.clear();
        int M;
        scanf("%d", &M);
        clr(num, 0);
        clr(id, 0);
        for(int i = 1; i <= 10; ++i) scanf("%d", d + i);
        int vs = 1, vt = 300;
        dinic.init(vs, vt);
        for(int i = 2; i <= 10; ++i) {
            if(i <= M && d[i]) {
                //debug(i, vt, d[i])
                dinic.add_edge(i, vt, d[i]);
            }
        }
        int tmm = 0;
        int sta = 1 << 4, inde = 10;
        for(int j = 1; j < sta; ++j) {
            int tmp = 1;
            for(int k = 0; k < 4; ++k) {
                if(j & (1 << k)) {
                    tmp *= y[k];
                }
            }
            id[tmp] = ++ inde;
            mp.emplace_back(make_pair(-tmp, j));
        }
        sort(mp.begin(), mp.end());
        for(int ti = 0; ti < mp.size(); ++ti) {
            int j = mp[ti].second;
            int tmp = abs(mp[ti].first);
            num[tmp] = M / tmp;
            for(int i = tmp * 2; i <= 210; i += tmp) {
                num[tmp] -= num[i];
            }
            tmm += num[tmp];
        }
        //debug(tmm, M)
        for(int i = 1; i <= 210; ++i) {
            if(i <= M && num[i]) {
                if(i == 2) {
                    int er = ++ inde;
                    int si = ++ inde;
                    int ba = id[2];
                    dinic.add_edge(vs, er, M >= 2);
                    dinic.add_edge(vs, si, M >= 4);
                    dinic.add_edge(vs, ba, num[2]
                                    - (M >= 2) - (M >= 4));
                    for(int j = 2; j <= 10 && j <= M; ++j) {
                        if(j == 2) {
                            dinic.add_edge(er, 2, INF);
                        }else if(j == 4) {
                            dinic.add_edge(er, 2, INF);
                            dinic.add_edge(si, 4, INF);
                        }else if(j == 8) {
                            dinic.add_edge(er, 2, INF);
                            dinic.add_edge(si, 4, INF);
                            dinic.add_edge(ba, 8, INF);
                        }
                    }
                    continue;
                } else if(i == 3) {
                    int san = ++ inde;
                    int jiu = id[3];
                    dinic.add_edge(vs, san, M >= 3);
                    dinic.add_edge(vs, jiu, num[3] - (M >= 3));
                    for(int j = 2; j <= 10 && j <= M; ++j) {
                        if(j == 3) {
                            dinic.add_edge(san, 3, INF);
                        }else if(j == 9) {
                            dinic.add_edge(san, 3, INF);
                            dinic.add_edge(jiu, 9, INF);
                        }
                    }
                    continue;
                }
                dinic.add_edge(vs, id[i], num[i]);
                for(int j = 2; j <= 10 && j <= M; ++j) {
                    int tj = j;
                    if(j == 4 || j == 8) tj = 2;
                    if(j == 9) tj = 3;
                    if(i % tj == 0 && j <= M) {
                        //debug(id[i], j, INF)
                        dinic.add_edge(id[i], j, INF);
                    }
                }
            }
        }
        //debug(min(max(0, M - tmm), d[1]))
        assert(tmm < M);
        int ans = dinic.max_flow();
        printf("%d\n", ans + min(max(0, M - ans), d[1]));
    }
    return 0;
}
