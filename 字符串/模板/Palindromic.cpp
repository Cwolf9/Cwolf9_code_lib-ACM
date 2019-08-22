/*
假设我们有一个串S，S下标从0开始，则回文树能做到如下几点：
1.求串S前缀0−i内本质不同回文串的个数（两个串长度不同或者长度相同且至少有一个字符不同便是本质不同）
2.求串S内每一个本质不同回文串出现的次数
3.求串S内回文串的个数（其实就是1和2结合起来）
4.求以下标i结尾的回文串的个数
pos[]数组记录原字符串端点对应回文树上的端点
len[i]表示编号为i的节点表示的回文串的长度（一个节点表示一个回文串）
next[i][c]表示编号为i的节点表示的回文串在两边添加字符c以后变成的回文串的编号（和字典树类似）。
fail[i]表示节点i失配以后跳转不等于自身的节点i表示的回文串的最长后缀回文串（和AC自动机类似）。
cnt[i]表示节点i表示的本质不同的串的个数(建树时求出的不是完全的，最后count()函数跑一遍以后才对)
num[i]表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数。
last指向新添加一个字母后所形成的最长回文串表示的节点。
S[i]表示第i次添加的字符（一开始设S[0] = -1（可以是任意一个在串S中不会出现的字符））。
p表示添加的节点个数。（p-2为本质不同回文串的个数）
n表示添加的字符个数。
一开始回文树有两个节点，0表示偶数长度串的根和1表示奇数长度串的根，且len[0] = 0，len[1] = -1，last = 0，S[0] = -1，n = 0，p = 2（添加了节点0、1）。
*/
struct Palindromic_Tree {
    static const int MAXN = 600005 ;
    static const int CHAR_N = 26 ;
    int nex[MAXN][CHAR_N];//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[MAXN];//fail指针，失配后跳转到fail指针指向的节点
    int cnt[MAXN];
    int num[MAXN];
    int len[MAXN];//len[i]表示节点i表示的回文串的长度
    int S[MAXN];//存放添加的字符
    int last;//指向上一个字符所在的节点，方便下一次add
    int n;//字符数组指针
    int p;//节点指针
    int pos[MAXN];
    int newnode(int l) {//新建节点
        for (int i = 0; i < CHAR_N; ++i) nex[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }
    void init() {//初始化
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        S[n] = -1;//开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }
    int get_fail(int x) {//和KMP一样，失配后找一个尽量最长的
        while (S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }
    void add(int c, int id) {
        c -= 'a';
        S[++n] = c;
        int cur = get_fail(last);//通过上一个回文串找这个回文串的匹配位置
        if (!nex[cur][c]) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);//新建节点
            fail[now] = nex[get_fail(fail[cur])][c];//和AC自动机一样建立fail指针，以便失配后跳转
            nex[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = nex[cur][c];
        cnt[last] ++;
        pos[last] = id;//回文树节点对应字符串下标
    }
    int vis[MXN], res;
    void dfs(int u) {
        vector<int> vs;
        for(int i = u; vis[i] == 0 && i > 1; i = fail[i]) vs.eb(i), ++ res, vis[i] = 1;
        ans += res;
        for(int i = 0; i < CHAR_N; ++i) if(nex[u][i]) dfs(nex[u][i]);
        for(auto v: vs) vis[v] = 0, --res;
    }
    void count() {
        for (int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i], vis[i] = 0;
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
        res = 0;
        dfs(0), dfs(1);
    }
} pt;

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
