#include <bits/stdc++.h>
using namespace std;
#define MK make_pair
#define EB emplace_back
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
typedef pair<int,int> pii;
const int MXN = 1e5 + 5;
int n, m, k;
vector<int> adj[MXN];//adj[i]存放与i相邻的点
int du[MXN], del[MXN];//du[i]表示i的度数，del[i]表示set中i是否被删除
void work() {
    cin >> n >> m >> k;
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        adj[u].EB(v), adj[v].EB(u);
        ++ du[u], ++ du[v];
    }
    int flag = 0;
    if(1ll * k * (k-1) > 2 * m) flag = -1;//不可能形成团
    set<pii> Q;//set维护一个pair<int,int>，第一维表示度数，第二维表示点的标号
    rep(i, 1, n + 1) {
        Q.insert(MK(du[i], i));
        sort(adj[i].begin(), adj[i].end());//邻接点先排好序方便判断团
    }
    vector<int> vs;
    while(!Q.empty() && flag == 0) {
        pii u = *Q.begin();
        if(u.first == k - 1) {//判断是否成团
            vs.clear();//vs存放这k个点
            for(int v: adj[u.second]) {
                if(del[v] == 0) {
                    vs.EB(v);
                }
            }
            vs.EB(u.second);
            flag = 2;
            for(int a: vs) {
                if(a == u.second) break;
                for(int b: vs) {
                    if(a != b) {//判断a与b是否有边
                        if(!binary_search(adj[a].begin(), adj[a].end(), b)) {
                            flag = 0;
                            break;
                        }
                    }
                }
                if(flag == 0) break;
            }
            if(flag == 0) {//不成团就删掉这个点
                auto p = Q.lower_bound(MK(du[u.second], u.second));
                Q.erase(p);
                del[u.second] = 1;
                for(int v: adj[u.second]) {
                    if(del[v]) continue;
                    -- du[v];
                    auto p = Q.lower_bound(MK(du[v] + 1, v));
                    Q.erase(p);
                    Q.insert(MK(du[v], v));
                }
            }
        }else if(u.first >= k) {
            flag = 1;
        }else {//删掉这个点
            auto p = Q.lower_bound(MK(du[u.second], u.second));
            Q.erase(p);//set中删除
            del[u.second] = 1;
            for(int v: adj[u.second]) {
                if(del[v]) continue;
                -- du[v];
                //修改邻接点v在set中的度数，先删除再插入
                auto p = Q.lower_bound(MK(du[v] + 1, v));
                Q.erase(p);
                Q.insert(MK(du[v], v));
            }
        }
    }
    if(flag <= 0) printf("-1\n");
    else if(flag == 1) {
        printf("1 %d\n", Q.size());
        for(pii x: Q) printf("%d ", x.second);
        printf("\n");
    }else {
        printf("2\n");
        for(int x: vs) printf("%d ", x);
        printf("\n");
    }
    rep(i, 1, n + 1) {
        adj[i].clear();
        du[i] = del[i] = 0;
    }
}
int main() {
    ios::sync_with_stdio(false);cin.tie(0);
    int tim;
    cin >> tim;
    for(int cas = 1; cas <= tim; ++ cas) work();
    return 0;
}
