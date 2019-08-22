struct Suffix_Automaton {
    static const int maxn = 2e5 + 105;
    static const int MAXN = 2e5 + 5;
    //basic
//    map<char,int> nex[maxn * 2];
    int nex[maxn*2][26];
    int link[maxn * 2], len[maxn * 2], isend[maxn*2];
    int last, cnt;
    LL tot_c;//不同串的个数
    //extension
    int cntA[MAXN * 2], A[MAXN * 2];//辅助拓扑更新
    int nums[MAXN * 2];//每个节点代表的所有串的出现次数
    int pos[maxn*2], dep[maxn*2];
    void clear() {
        tot_c = 0;
        last = cnt = 1;
        link[1] = len[1] = 0;
//        nex[1].clear();
        memset(nex[1], 0, sizeof(nex[1]));
    }
    void init_str(char *s) {
        while (*s) {
            add(*s - 'a', 1);
            ++ s;
        }
    }
    void add(int c, int id) {
        int p = last;
        int np = ++cnt;
        isend[cnt] = (c == 10);
//        nex[cnt].clear();
        memset(nex[cnt], 0, sizeof(nex[cnt]));
        len[np] = len[p] + 1;
        pos[id] = np;
        last = np;
        while (p && !nex[p][c])nex[p][c] = np, p = link[p];
        if (!p)link[np] = 1, tot_c += len[np] - len[link[np]];
        else {
            int q = nex[p][c];
            if (len[q] == len[p] + 1)link[np] = q, tot_c += len[np] - len[link[np]];
            else {
                int nq = ++cnt;
                isend[nq] = (c == 10);
                len[nq] = len[p] + 1;
//                nex[nq] = nex[q];
                memcpy(nex[nq], nex[q], sizeof(nex[q]));
                link[nq] = link[q];
                link[np] = link[q] = nq;
                //sum[nq] = sum[q] , pre[nq] = pre[q];
                tot_c += len[np] - len[link[np]];
                while (nex[p][c] == q)nex[p][c] = nq, p = link[p];
            }
        }
        //for(p = np; p && pre[p] != id; p = link[p]) pre[p] = id, ++ sum[p];
        //广义SAM记录上一个经过他的是哪一个字符串以及有多少字符串经过这个字符串。
    }
    //求这个串的出现次数
    int query(int n, int an) {
        int u = 1, LEN = 0, ans = 0;
        vector<int> vs;
        for(int i = 0; i < an; ++i) {
            if(nex[u][s[i]-'a']) {
                u = nex[u][s[i]-'a'];
                ++ LEN;
            }else {
                while (u && nex[u][s[i] - 'a'] == 0) u = link[u];
                if (u == 0) u = 1, LEN = 0;
                else {
                    LEN = len[u] + 1;
                    u = nex[u][s[i] - 'a'];
                }
            }
            if(LEN > n) {
                while(len[link[u]] >= n) u = link[u], LEN = len[u];
            }
            if(LEN >= n && vis[u] == 0) {
                vis[u] = 1;
                ans += nums[u];
                vs.eb(u);
            }
        }
        for(auto x: vs) vis[x] = 0;
//        debug(u, LEN)
        return ans;
    }
    //长度至少为k的公共子串数量
    void query() {
        int u = 1, LEN = 0;
        for(int i = 0; i < m; ++i) {
            if(nex[u][t[i]-'A']) {
                u = nex[u][t[i]-'A'];
                ++ LEN;
            }else {
                while (u && nex[u][t[i] - 'A'] == 0) u = link[u];
                if (u == 0) u = 1, LEN = 0;
                else {
                    LEN = len[u] + 1;
                    u = nex[u][t[i] - 'A'];
                }
            }
            if(LEN >= k) {
                ANS += (LL)nums[u] * (LEN - big(len[link[u]], k - 1));
                if (len[link[u]]) lazy[link[u]] ++;
            }
        }
        for(int i = cnt, x; i >= 1; --i) {
            x = A[i];
            if(len[x] >= k && lazy[x]) {
                ANS += lazy[x] * nums[x] * (len[x] - big(len[link[x]], k - 1));
                if(len[link[x]]) lazy[link[x]] += lazy[x];
            }
        }
    }
    //本质不同的公共子串数量
    void query() {
        int u = 1, LEN = 0;
        for(int i = 0; i < n; ++i) {
            if(nex[u][t[i]-'a']) {
                u = nex[u][t[i]-'a'];
                ++ LEN;
            }else {
                while (u && nex[u][t[i] - 'a'] == 0) u = link[u];
                if (u == 0) u = 1, LEN = 0;
                else {
                    LEN = len[u] + 1;
                    u = nex[u][t[i] - 'a'];
                }
            }
            if(vis[u] == 0) {
                ANS += 1 * (LEN - len[link[u]]);
//                debug(i, t[i], LEN - len[link[u]])
                if (len[link[u]]) lazy[link[u]] = 1;
                vis[u] = LEN;
            }else if(LEN > vis[u]) {
                ANS += 1 * (LEN - vis[u]);
//                debug(i, t[i], LEN - vis[u])
                vis[u] = LEN;
            }
        }
        for(int i = cnt, x; i >= 1; --i) {
            x = A[i];
            if(vis[x] == 0 && len[x] && lazy[x]) {
                ANS += len[x] - len[link[x]];
                vis[x] = len[x];
                if(len[link[x]]) lazy[link[x]] = 1;
            }else if(lazy[x] && vis[x] < len[x]) {
                ANS += len[x] - vis[x];
                vis[x] = len[x];
                if(len[link[x]]) lazy[link[x]] = 1;
            }
            if(len[link[x]]) lazy[link[x]] = 1;
        }
    }
    void build(int n) {
        memset(cntA, 0, sizeof cntA);
        memset(nums, 0, sizeof nums);//where to init?
        for (int i = 1; i <= cnt; i++)cntA[len[i]]++;
        for (int i = 1; i <= n; i++)cntA[i] += cntA[i - 1];
        for (int i = cnt; i >= 1; i--)A[cntA[len[i]]--] = i;
        //更行主串节点
        int temps = 1;
//        for(int i = 1; i <= cnt; ++i) debug(i, isend[i])
        for (int i = 1; i <= n; ++i) {
            nums[temps = nex[temps][t[i-1] - 'a']] = 1;
//            debug(temps, s[i-1])
        }
        //拓扑更新
        for (int i = cnt, x; i >= 1; i--) {
            //basic
            x = A[i];
            nums[link[x]] += nums[x];
        }
//        for(int i = 1; i <= cnt; ++i) debug(nums[i])
        for (int i = 1, t; i <= cnt; i++) {
            t = A[i];
            dep[t] = dep[link[t]] + 1;
            nex[t][0] = link[t];
//            for (int j = 1; bin[j] <= dep[t]; j++)
            for (int j = 1; j < 20; j++)
                if(bin[j] <= dep[t]) nex[t][j] = nex[nex[t][j - 1]][j - 1];
                else nex[t][j] = 0;
        }
    }
    //子串(l,r)出现次数
    int RMQ_query(int l, int r) {
        int mid = pos[r];
        for (int i = 19; i >= 0; i--) {
            int t = nex[mid][i];
            if (len[t] >= r - l + 1) mid = t;
        }
        ANS[r-l+1] += nums[mid];
    }
//    void DEBUG() {
//        for (int i = cnt; i >= 1; i--) {
//            printf("nums[%d]=%d numt[%d]=%d len[%d]=%d link[%d]=%d\n", i, nums[i], i, nums[i], i, len[i], i, link[i]);
//        }
//    }
} sam;

struct Suffix_Automaton {
    static const int maxn = 1e6 + 105;
    static const int MAXN = 1e5 + 5;
    //basic
    int nxt[maxn * 2][26], link[maxn * 2], len[maxn * 2];
    int last, cnt;
    LL tot_c;//不同串的个数
    //extension
    int cntA[MAXN * 2], A[MAXN * 2];//辅助拓扑更新
    int nums[MAXN * 2], numt[MAXN * 2];//每个节点代表的所有串的出现次数
    int weights[MAXN * 2], weightt[MAXN * 2];
    void clear() {
        tot_c = 0;
        last = cnt = 1;
        link[1] = len[1] = 0;
        memset(nxt[1], 0, sizeof nxt[1]);
    }
    void init_str(char *s) {
        while (*s) {
            add(*s - 'a');
            ++ s;
        }
    }
    void add(int c) {
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt], 0, sizeof nxt[cnt]);
        len[np] = len[p] + 1;
        last = np;
        while (p && !nxt[p][c])nxt[p][c] = np, p = link[p];
        if (!p)link[np] = 1, tot_c += len[np] - len[link[np]];
        else {
            int q = nxt[p][c];
            if (len[q] == len[p] + 1)link[np] = q, tot_c += len[np] - len[link[np]];
            else {
                int nq = ++cnt;
                len[nq] = len[p] + 1;
                memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
                link[nq] = link[q];
                link[np] = link[q] = nq;
                tot_c += len[np] - len[link[np]];
                while (nxt[p][c] == q)nxt[p][c] = nq, p = link[p];
            }
        }
    }
    void build(int n) {
        memset(cntA, 0, sizeof cntA);
        memset(nums, 0, sizeof nums);
        memset(numt, 0, sizeof numt);
        for (int i = 1; i <= cnt; i++)cntA[len[i]]++;
        for (int i = 1; i <= n; i++)cntA[i] += cntA[i - 1];
        for (int i = cnt; i >= 1; i--)A[cntA[len[i]]--] = i;
        //更行主串节点
        int temps = 1, tempt = 1;
        for (int i = 1; i <= n; i++) {//注意下标
            nums[temps = nxt[temps][s[i] - 'a']] = 1;
            numt[tempt = nxt[tempt][t[i] - 'a']] = 1;
        }
        //拓扑更新
        for (int i = cnt; i >= 1; i--) {
            //basic
            int x = A[i];
            nums[link[x]] += nums[x];
            numt[link[x]] += numt[x];
        }
    }
    void DEBUG() {
        for (int i = cnt; i >= 1; i--) {
            printf("nums[%d]=%d numt[%d]=%d len[%d]=%d link[%d]=%d\n", i, nums[i], i, numt[i], i, len[i], i, link[i]);
        }
    }
    LL query() {
        LL res = 0;
        for (int i = 1; i <= cnt; i++) {
            res += 1LL * nums[i] * numt[i] * (len[i] - len[link[i]]);
        }
        return res;
    }
    LL query2() {
        LL res = 0;
        for (int i = 1; i <= cnt; i++) {
            res += 1LL * weights[i] * numt[i] * (len[i] - len[link[i]]);
            res += 1LL * weightt[i] * nums[i] * (len[i] - len[link[i]]);
        }
        return res;
    }
} sam;




#include <bits/stdc++.h>
#define int ll
using namespace std;
typedef __int128_t ll;
const int maxn = 4e5+100;
char s[maxn];
char t[maxn];
long long n;
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    //extension
    int cntA[maxn*2],A[maxn*2];/*辅助拓扑更新*/
    int nums[maxn*2],numt[maxn*2];/*每个节点代表的所有串的出现次数*/
    int weights[maxn*2],weightt[maxn*2];
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s-'a');
            s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;
        last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];
                fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    void build(){
        memset(cntA,0,sizeof cntA);
        memset(nums,0,sizeof nums);
        memset(numt,0,sizeof numt);
        for (int i=1;i<=cnt;i++)cntA[l[i]]++;
        for (int i=1;i<=n;i++)cntA[i]+=cntA[i-1];
        for (int i=cnt;i>=1;i--)A[cntA[l[i]]--] =i;
        /*更行主串节点*/
        int temps=1,tempt = 1;
        for (int i=1;i<=n;i++){
            nums[temps = nxt[temps][s[i]-'a']] = 1;
            numt[tempt = nxt[tempt][t[i]-'a']] = 1;
        }
        /*拓扑更新*/
        for (int i=cnt;i>=1;i--){
            //basic
            int x = A[i];
            nums[fa[x]]+=nums[x];
            numt[fa[x]] += numt[x];
        }
    }

    void debug(){
        for (int i=cnt;i>=1;i--){
            printf("nums[%d]=%d numt[%d]=%d l[%d]=%d fa[%d]=%d\n",i,nums[i],i,numt[i],i,l[i],i,fa[i]);
        }
    }

    ll query(){
        ll res = 0;
        for (int i=1;i<=cnt;i++){
            res += 1LL*nums[i] * numt[i] * (l[i] - l[fa[i]]);
        }
        return res;
    }
    ll query2(){
        ll res = 0;
        for (int i=1;i<=cnt;i++){
            res += 1LL*weights[i] * numt[i] *(l[i] - l[fa[i]]);
            res += 1LL*weightt[i] * nums[i] *(l[i] - l[fa[i]]);
        }
        return res;
    }
}sam;