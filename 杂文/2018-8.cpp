#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")


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
