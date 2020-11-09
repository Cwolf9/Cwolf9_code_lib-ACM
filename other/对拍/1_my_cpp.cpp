#include <bits/stdc++.h>

using namespace std;

#define MAXN 100010

int n, m, t;
int tree[MAXN][26];
bool node[MAXN];
char s[MAXN];
map<int, int> u_map;
vector<string> str[MAXN];

void Read(){
    node[0] = false;
    memset(tree[0], 0, sizeof(tree[0]));
    m = t = 0;
    u_map.clear();
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) str[i].clear();
    for(int i = 1, u; i <= n; ++i){
        scanf("%s %d", s, &u);
        if(!u_map[u]) u_map[u] = ++m;
        str[u_map[u]].push_back(s);
    }
}

int dfs(int u){
    int ret = 0, cnt = 0;
    
    for(int i = 0; i < 26; ++i){
        if(tree[u][i] <= 0) continue;
        
        int res = dfs(tree[u][i]);
        
        if(!res){
            if(node[u]) ++res;
            else if(cnt > 0) ++res;
            ++cnt;
        }
        ret += res;
    }
    
    return ret ? ret + 1: 0;
}

void Work(){
    for(int j = 1, p; j <= m; ++j){
        for(p = 0; ; ++p){
            int flag = p < (int)str[j][0].size();

            for(int i = 1; flag && i < (int)str[j].size(); ++i)
                if(p == (int)str[j][i].size() || str[j][i][p] != str[j][i - 1][p])
                    flag = false;

            if(!flag) break;
        }
        
        for(int _p = 0, index = 0; _p <= p; ++_p){
            if(_p == p){
                for(int i = 0; i < (int)str[j].size(); ++i){
                    if(p == (int)str[j][i].size())
                        continue;
                    if(tree[index][str[j][i][p] - 'a'] > 0){
                        printf("-1\n");
                        return;
                    }
                    
                    tree[index][str[j][i][p] - 'a'] = -1;
                }
                
                if(node[index]){
                    printf("-1\n");
                    return;
                }
                node[index] = true;
                break;
            }
            
            if(!tree[index][str[j][0][_p] - 'a']){
                tree[index][str[j][0][_p] - 'a'] = ++t;
                node[t] = false;
                memset(tree[t], 0, sizeof(tree[t]));
            }
            else if(tree[index][str[j][0][_p] - 'a'] == -1){
                printf("-1\n");
                return;
            }
            
            index = tree[index][str[j][0][_p] - 'a'];
        }
    }
    
    printf("%d\n", max(1, dfs(0)));
}

int main() {
    int i, T;
    for(scanf("%d", &T), i = 1; i <= T; ++i){
        Read();
        printf("Case #%d: ", i);
        Work();
    }
    return 0;
}
