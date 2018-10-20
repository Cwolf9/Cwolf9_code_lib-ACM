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
            nums[temps = nxt[temps][s[i]-'a'] ]=1;
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
struct Manacher{
    char ch[maxn*2];
    int lc[maxn*2];
    int N;
    void init(const char *s){
        N = 2*n+1;
        ch[N] = '#';
        for (int i=n;i>=1;i--){
            ch[i*2] = s[i];
            ch[i*2-1] = '#';
        }
        ch[0] = 'z'+1;
        ch[N+1] = '\0';
        manacher();
    }
    void manacher(){
        lc[1] = 1;
        int k = 1;
        for (int i=2;i<=N;i++){
            int p = k + lc[k] -1;
            if (i <= p){
                lc[i] = min(lc[2*k-i],p-i+1);
            }else{
                lc[i] = 1;
            }
            while (ch[i+lc[i]] == ch[i-lc[i]])lc[i] ++;
            if (i+lc[i] > k+lc[k]) k = i;
        }
    }
    int query(int x){
        return lc[x]>>1;
    }
    void debug(){
        for (int i=1;i<=N;i++){
            printf("lc[%d]=%d\n",i,lc[i]);
        }
    }
}mas,mat;



#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define LL __int128_t
 
using namespace std;
 
const int Maxn=2e5+10;
int n,pos,d[Maxn*2];
char s[Maxn*2],S[Maxn*2];
LL ans,sum;
 
template <class T>
void print(T a){
    if (a>9) print(a/10);
    putchar(a%10+'0');
}
struct Palindrome{
    int N,last;
    struct T{
        int Next[30],fail,cnt,num,len;
    }tree[Maxn];
    void init(){
        for (int i=0; i<=N; i++){
            for (int j=0; j<26; j++) tree[i].Next[j]=0;
            tree[i].fail=tree[i].cnt=tree[i].num=tree[i].len=0;
        }
        N=1,tree[N].len=-1,tree[N].fail=1;
        N++,tree[N].len=0,tree[N].fail=1;
        last=2;
    }
 
    int get_fail(int x){
        while (s[pos-1-tree[x].len]!=s[pos]) x=tree[x].fail;
        return x;
    }
 
    void Add(int c){
        int Now=get_fail(last);
        if (!tree[Now].Next[c]){
            last=++N;
            tree[N].len=tree[Now].len+2;
            int f=get_fail(tree[Now].fail);
            tree[N].fail=tree[f].Next[c]?tree[f].Next[c]:2;
            tree[N].num=tree[tree[N].fail].num+1;
            tree[Now].Next[c]=N;
        } else last=tree[Now].Next[c];
        tree[last].cnt++;
    }
}palindrome;
 
struct SAM{
    int mm,son[Maxn*4][30],pre[Maxn*4],step[Maxn*4],last,total,root,p[Maxn*4],q[Maxn*4],h[Maxn*4];
    LL f[Maxn*4],g[Maxn*4];
    void init(){
        for (int i=0; i<=total; i++){
            for (int j=0; j<30; j++) son[i][j]=0;
            pre[i]=step[i]=f[i]=g[i]=p[i]=q[i]=0;
        }
        total=last=root=1;
    }
    struct node{
        int node,Next;
    }G[Maxn*4];
    void Insert(int a,int b){
        mm++;
        G[mm].node=b;
        G[mm].Next=h[a];
        h[a]=mm;
    }
    inline void Push(int v) {step[++total]=v;}
    void Extend(int ch){
        Push(step[last]+1);
        int p=last,np=total;
        for ( ; !son[p][ch]; p=pre[p]) son[p][ch]=np;
        if (!p) pre[np]=root; 
        else{
            int q=son[p][ch];
            if (step[p]+1!=step[q]){
                Push(step[p]+1);
                int nq=total;
                memcpy(son[nq],son[q],sizeof(son[q]));
                pre[nq]=pre[q];
                pre[q]=pre[np]=nq;
                for ( ; son[p][ch]==q; p=pre[p]) son[p][ch]=nq;
            } else pre[np]=q;
        }
        last=np;
    }
    void dfs(int u,int fa){
        for (int Now=h[u]; Now!=-1; Now=G[Now].Next){
            int v=G[Now].node;
            if (v==fa) continue;
            dfs(v,u);
            f[u]+=f[v];
        }
//        printf("fff%d %lld\n",u,f[u]);
    }
    void dfs1(int u,int fa){
        g[u]=f[u]*(step[u]-step[fa]);
        g[u]+=g[fa];
        for (int Now=h[u]; Now!=-1; Now=G[Now].Next){
            int v=G[Now].node;
            if (v==fa) continue;
            dfs1(v,u);
        }
        if (q[u]>=1 && q[u]<=n){
            ans+=g[u]*d[q[u]+1];
            sum+=g[u];
//            printf("aaa%d %lld\n",u,g[u]);
        }
    }
    void Build(){
        init();
        for (int i=1; i<=2*n+1; i++) Extend(s[i]-'a');
        int temp=1;
        for (int i=1; i<=2*n+1; i++){
            temp=son[temp][s[i]-'a'];
            p[i]=temp;
            q[temp]=i;
            if (i>n+1) f[temp]=1;
        }
        mm=-1;
        for (int i=0; i<=total; i++) h[i]=-1;
        for (int i=2; i<=total; i++) Insert(pre[i],i);
        dfs(root,root);
        dfs1(root,root);
    }
}sam;