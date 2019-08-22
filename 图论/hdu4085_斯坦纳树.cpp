//hdu 4085 斯坦纳树模板题
const int maxn=55;
const int maxm=2005;
const int maxstate=1<<11;

int T;
int n,m,k;
int dp[maxn][maxstate];
int st[maxn];
int dp2[maxstate];

struct node {
    int v,w,next;
};
node edges[maxm];
int tot;
int maps[maxn];
void addedge(int u,int v,int w) {
    edges[tot].v=v;
    edges[tot].w=w;
    edges[tot].next=maps[u];
    maps[u]=tot;
    tot++;
}

queue<int>que;
int in[maxn];
void spfa(int sta) {
    while(!que.empty()) {
        int now=que.front();
        que.pop();
        in[now]=0;
        for(int i=maps[now]; i!=-1; i=edges[i].next) {
            int v=edges[i].v;
            int w=edges[i].w;
            if(dp[v][sta]>dp[now][sta]+w) {
                dp[v][sta]=dp[now][sta]+w;
                if(in[v]==0) {
                    in[v]=1;
                    que.push(v);
                }
            }
        }
    }
}
bool check(int sta) {
    int res=0;
    for(int i=0; sta; i++) {
        if(sta&1) {
            if(i<k)
                res++;
            else
                res--;
        }
        sta>>=1;
    }
    return (res==0);
}

void init() {
    //初始化链式前向星
    mst(maps,-1);
    tot=0;
    //初始化spfa的队列和队内元素标记
    while(!que.empty())
        que.pop();
    mst(in,0);
}

void solve() {
    sd(T);
    while(T--) {
        init();
        sddd(n,m,k);
        //建图
        for(int i=0; i<m; i++) {
            int u,v,w;
            sddd(u,v,w);
            addedge(u,v,w);
            addedge(v,u,w);
        }

        //给每个需要联通的点一个状压位
        mst(st,0);
        mst(dp,INF);
        int nowst=1;
        for(int i=1; i<=k; i++) {
            st[i]=nowst;
            dp[i][st[i]]=0;
            nowst<<=1;
        }
        for(int i=n-k+1; i<=n; i++) {
            st[i]=nowst;
            dp[i][st[i]]=0;
            nowst<<=1;
        }

        //核心
        int mxst=1<<(2*k);
        for(int s=0; s<mxst; s++) {
            for(int i=1; i<=n; i++) {
                for(int ss=(s-1)&s; ss; ss=(ss-1)&s) {
                    int now=dp[i][ss]+dp[i][s-ss];
                    dp[i][s]=min(dp[i][s],now);
                }
                if(dp[i][s]!=INF)
                    que.push(i),in[i]=1;
            }
            spfa(s);
        }

        //求出每种联通状态的最小代价
        //dp2[mxst-1]就是全部要求联通点互相联通的代价
        mst(dp2,INF);
        for(int s=0; s<mxst; s++) {
            for(int i=1; i<=n; i++) {
                dp2[s]=min(dp2[s],dp[i][s]);
            }
        }

        for(int s=0; s<mxst; s++) {
            if(!check(s))
                continue;
            for(int ss=(s-1)&s; ss; ss=(ss-1)&s) {
                if(!check(ss))
                    continue;
                int now=dp2[ss]+dp2[s-ss];
                dp2[s]=min(dp2[s],now);
            }
        }
        if(dp2[mxst-1]==INF)
            printf("No solution\n");
        else
            printf("%d\n",dp2[mxst-1]);
    }
    return ;
}

//伪代码

建图
给每个需要联通的点分配一个状压位

初始化需要联通的点到只有自身的联通状态代价为0
枚举每种联通状态s
    对于每个点为根
        对于s的每一种划分（x&y=0,x|y=s）
            更新以当前点为根，联通状态为s的最小值
        如果当前状态代价<INF
            进入spfa队列并标记
    对当前联通状态进行spfa

枚举每种联通状态s
    对于每个点为根
        更新当前联通状态的最小代价
