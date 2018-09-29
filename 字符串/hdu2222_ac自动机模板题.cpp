#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MXN = 1e6 + 6;
const int MXT = 5e5 + 5;

struct AHO {
    struct trie {
        int nex[26];
        int fail, cnt;
        void New() {
            memset(nex, -1, sizeof(nex));
            fail = cnt = 0;
        }
    }cw[MXT];
    int rt, tot;
    void init() {
        rt = tot = 0;
        cw[0].New();
    }
    void add_str(char *S) {
        int len = strlen(S);
        rt = 0;
        for(int i = 0, now; i < len; ++i) {
            now = S[i] - 'a';
            if(cw[rt].nex[now] == -1) {
                cw[rt].nex[now] = ++tot;
                cw[tot].New();
            }
            rt = cw[rt].nex[now];
        }
        cw[rt].cnt++;
    }
    void build_ac(){
        queue<int> Q;
        Q.push(0);
        cw[0].fail = -1;
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = 0, pos; i < 26; ++i) {
                pos = cw[u].nex[i];
                if(~pos) {
                    if(u == 0) cw[pos].fail = 0;
                    else {
                        int v = cw[u].fail;
                        while(~v){
                            if(~cw[v].nex[i]) {
                                cw[pos].fail = cw[v].nex[i];
                                break;
                            }
                            v = cw[v].fail;
                        }
                        if(v == -1) cw[pos].fail = 0;
                    }
                    Q.push(pos);
                }
            }
        }
    }
    int Get(int u) {
        int ans = 0;
        while(u) {
            ans += cw[u].cnt;
            cw[u].cnt = 0;
            u = cw[u].fail;
        }
        return ans;
    }
    int Query(char *S) {
        int len = strlen(S);
        int ans = 0;
        rt = 0;
        for(int i = 0, now, p; i < len; ++i) {
            now = S[i] - 'a';
            if(~cw[rt].nex[now]) {
                rt = cw[rt].nex[now];
            }else {
                p = cw[rt].fail;
                while(p != -1 && cw[p].nex[now] == -1) p = cw[p].fail;
                if(p == -1) rt = 0;
                else rt = cw[p].nex[now];
            }
            if(cw[rt].cnt) ans += Get(rt);
        }
        return ans;
    }
}aho;
char s[MXN];
int main(int argc, char const *argv[]) {
    int tim;
    scanf("%d", &tim);
    while(tim--) {
        int n;scanf("%d", &n);
        aho.init();
        for(int i = 0; i < n; ++i) {
            scanf("%s", s);
            aho.add_str(s);
        }
        aho.build_ac();
        scanf("%s", s);
        printf("%d\n", aho.Query(s));
    }    
    return 0;
}