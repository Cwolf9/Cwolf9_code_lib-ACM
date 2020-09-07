#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6+7;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7;
int n,m;
int ans;
int ar[N],belong[N],br[N],now[N];
int Ans[N];
int cnt[N],in_left[N];
struct lp{
    int l,r,id;
}cw[N];
bool cmp(const lp &a,const lp &b){
    if(belong[a.l]==belong[b.l]){
        return a.r<b.r;
    }
    return belong[a.l]<belong[b.l];
}
int L, R;
void update_left(int x,int f){
    if(x == ar[x]) ++ ans, cnt[x] = 1;
}
inline void update(int x){
    if(R - ans <= ar[x] && R >= ar[x]) ++ ans, cnt[x] = 1;
}
#define LH_LOCAL
int main(){
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    scanf("%d%d",&n,&m);
    int block=(int)sqrt(n*1.0);
    for(int i=1;i<=n;++i){
        scanf("%d",&ar[i]);
        belong[i]=(i-1)/block+1;
    }
    for(int i=1;i<=m;++i){
        scanf("%d%d",&cw[i].l,&cw[i].r);
        cw[i].l++;
        cw[i].r = n - cw[i].r;
        cw[i].id=i;
    }
    memset(cnt,0,sizeof(cnt));
    sort(cw+1,cw+m+1,cmp);
    L=1,R=0;
    int limit;
    LL last_ans=0;
    ans=0;cw[0].l=0;belong[0]=0;
    for(int i=1;i<=m;++i){
        if(belong[cw[i-1].l]!=belong[cw[i].l]){
            memset(cnt,0,sizeof(cnt));
            limit=belong[cw[i].l]*block;
            R=limit;
            ans=last_ans=0;
        }
        L=min(limit+1,cw[i].r+1);
        int tmpp = ans;
        last_ans = ans;
        while(L>cw[i].l)update_left(--L,1);
        tmpp = ans - tmpp;
        ans = last_ans;
        while(R<cw[i].r){
            update(++R);
        }
        last_ans = ans;
        Ans[cw[i].id]=ans + tmpp;
        ans+=tmpp;
        for(int j=L;j<=cw[i].r&&j<=limit;++j){
            if(cnt[j] == 1) -- ans;
            cnt[j] = 0;
        }
        ans=last_ans;
    }
    for(int i=1;i<=m;++i){
        printf("%d\n",Ans[i] );
    }
    return 0;
}