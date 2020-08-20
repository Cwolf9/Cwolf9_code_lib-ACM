#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
typedef long long ll;
ll dp[maxn][maxn];
int cnt,nxt[maxn<<1],to[maxn<<1],w[maxn<<1],head[maxn];
void add(int u,int v,int c){
    ++cnt,to[cnt]=v,nxt[cnt]=head[u],w[cnt]=c,head[u]=cnt;
    ++cnt,to[cnt]=u,nxt[cnt]=head[v],w[cnt]=c,head[v]=cnt;
}
void dfs(int u,int pre){
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];
        if(v == pre) continue;
        dfs(v,u);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v = to[i];
        if(v==pre) continue;
        for(int h=400;h>=0;h--){
            for(int k=0;k<=h-2*w[i];k++){
                dp[u][h] = max(dp[u][h],dp[v][k]+dp[u][h-k-2*w[i]]);
            }
        }
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int n,T;
    scanf("%d%d",&n,&T);
    for(int i=1;i<=n;i++){
        scanf("%lld",&dp[i][0]);
        dp[i][0] = max(dp[i][0],0ll);
    }
    for(int i=1;i<n;i++){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        add(u,v,c);
    }
    dfs(1,0);
    ll ans = 0;
    for(int i=0;i<=T;i++) ans=max(ans,dp[1][i]);
    printf("%lld\n", ans);
    return 0;
}