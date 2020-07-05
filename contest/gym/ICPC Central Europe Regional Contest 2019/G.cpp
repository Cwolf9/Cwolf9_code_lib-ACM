#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <map>
#include <set>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <queue>

#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 62
#define mk make_pair
#define eb push_back
#define all(x) (x).begin(), (x).end()
#define clr(a,b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, int> pLi;
inline LL read(){
    LL x=0;int f=0;char ch=getchar();
    while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x=f?-x:x;
}
inline void write(LL x) {
    if(x==0){putchar('0'),putchar('\n');return;}
    if(x < 0) {putchar('-');x=-x;}
    static char s[23];int l = 0;
    while(x!=0)s[l++]=x%10+48,x/=10;
    while(l)putchar(s[--l]);
    putchar('\n');
}
template<class T> T big(const T& a1,const T& a2) { return a1>a2?a1:a2; }
template<class T> T sml(const T& a1,const T& a2) { return a1<a2?a1:a2; }
#ifndef ONLINE_JUDGE
void debug_out() { cerr << '\n'; }
template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cerr << f << " "; debug_out (r...); }
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#endif
const int MOD = 1e9+ 7;
const int MXN = 2e3 + 7;
const int MXN_T = 5e4 + 105;
const int CHAR_SIZE = 26;
int mp[130];
/*
 n(10),m(2e9),字符串长度10
 给n个坏的的字符串，问有多少长度为m的合法字符串
 build_ac()可以求出AC_Trie中每个节点加一个字符后在AC_Trie会匹配到达的节点
 然后就可以得到一个数组dis[][]，dis[i][j]表达从节点i走一步到节点j的方案树
 然后这题套个矩阵快速幂就可以啦
 不过记得要把原矩阵中的坏节点全部删掉得到新矩阵
 坏节点：这个节点存在一个后缀是坏字符串
 */
struct AC_Auto {
    struct Trie {
        int nex[CHAR_SIZE];
        int fail, cnt, is;
    } cw[MXN_T];
    int siz, rt;
    void init() {
        siz = rt = 0;
        clr(cw[siz].nex, -1);
        cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
    }
    void add_str(char *s, int len, int id) {
        rt = 0;
        for (int i = 0, now; i < len; ++i) {
            now = mp[s[i]];
            if (cw[rt].nex[now] == -1) {
                cw[rt].nex[now] = ++siz;
                clr(cw[siz].nex, -1);
                cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
            }
            rt = cw[rt].nex[now];
        }
        assert(siz < MXN_T);
        cw[rt].cnt = id;
        cw[rt].is = 1;
    }
    void build_ac() {
        queue<int> Q;
        Q.push(0);
        cw[0].fail = -1;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0, pos; i < CHAR_SIZE; ++i) {
                pos = cw[u].nex[i];
                if (~pos) {
                    assert(pos != -1);
                    if (u == 0) cw[pos].fail = u;
                    else {
                        assert(u != -1);
                        int v = cw[u].fail;
                        while (v != -1) {
                            if (cw[v].nex[i] != -1) {
                                cw[pos].fail = cw[v].nex[i];
                                if(cw[cw[v].nex[i]].is) cw[pos].is = 1;//这个节点存在一个后缀是坏字符串
                                break;
                            }
                            v = cw[v].fail;
                        }
                        if (v == -1) cw[pos].fail = 0;
                    }
                    Q.push(pos);
                }else {
                    if(cw[u].fail >= 0) cw[u].nex[i] = cw[cw[u].fail].nex[i];
                    else cw[u].nex[i] = 0;
                }
            }
        }
    }
}aho;
int n, m;
char ar[MXN];
int dis[MXN][MXN], vis[MXN];
struct mat_lp {
    int ar[205][205];
}A;
mat_lp mat_exe(mat_lp a,mat_lp b,int n,int m,int h){
    mat_lp c; memset(c.ar,0,sizeof(c.ar));
    for(int k = 0; k < m; ++k){
        for(int i = 0; i < n; ++i){
            if(a.ar[i][k] == 0) continue;
            for(int j = 0; j < h; ++j){
                if(b.ar[k][j] == 0) continue;
                c.ar[i][j] = (c.ar[i][j] + (LL)a.ar[i][k] * b.ar[k][j]%MOD)%MOD;
            }}}
    return c;
}
mat_lp mat_ksm(mat_lp a, LL b, int n){
    mat_lp ret;
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) ret.ar[i][j]=(i==j);
    while(b>0){
        if(b&1) ret=mat_exe(ret, a, n, n, n);
        a = mat_exe(a, a, n, n, n); b >>= 1;
    }
    return ret;
}
//typedef vector<long long> vec;
//typedef vector<vec > mat;
//mat c(a.size(), vec(b[0].size(), 0));
int ksm(LL a, int b) {
    LL res = 1;
    while(b) {
        if(b&1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
int main() {
    for(int i = 0; i < 26; ++i) mp['a'+i] = i;
    while(~scanf("%d%d", &m, &n)) {
        aho.init();
        for(int i = 1, ax; i <= n; ++i) {
            scanf("%d%s", &ax, ar);
            aho.add_str(ar, strlen(ar), i);
        }
        aho.build_ac();
        int x = m;
        n = m = aho.siz;
        clr(dis, 0);
        aho.cw[0].fail = 0;
        for(int i= 0; i <= n; ++i) {
            vis[i] = aho.cw[i].is;
            m -= vis[i];
            for(int j = 0; j < 26; ++j) {
                if(aho.cw[i].nex[j] == -1) {
                    dis[i][aho.cw[i].fail] ++;
                }else dis[i][aho.cw[i].nex[j]] ++;
            }
        }
        clr(A.ar, 0);
        for(int i = 0, cntx = 0; i <= n; ++i) {
            int cnty = 0;
            if(vis[i]) continue;
            for(int j = 0; j <= n; ++j) {
                if(vis[j]) continue;
                A.ar[cntx][cnty] = dis[i][j];
                ++ cnty;
            }
            ++ cntx;
        }
        // printf("%d %d %d\n", n, x, m);
        // for(int i = 0; i <= m; ++i) {
        //     for(int j =0 ; j <= m; ++j) printf("%d ", A.ar[i][j]);
        //     printf("\n");
        // }
        A = mat_ksm(A, x, m + 1);
        int ans = 0;
        for(int i = 0; i <= m; ++i) {
            ans = (ans + A.ar[0][i]) % MOD;
        }
        printf("%d\n", ans);
        break;
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}