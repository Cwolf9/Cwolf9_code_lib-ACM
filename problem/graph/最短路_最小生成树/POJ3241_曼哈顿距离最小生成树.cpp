#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
#define all(x) (x).begin(),(x).end()
#define mme(a,b) memset((a),(b),sizeof((a)))
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int MXN = 1e5 + 7;
const int MXE = 1e6 + 7;
const int INF = 0x3f3f3f3f;
int n, k, tot;
int ar[MXN], fa[MXN];
struct lp{
    int x, y, id;
}cw[MXN], edge[MXE];
bool cmp(const lp &a, const lp &b){
    if(a.x != b.x)return a.x < b.x;
    return a.y < b.y;
}
bool cmp1(const lp &a, const lp &b){
    return a.id < b.id;
}
//树状数组部分
struct BIT{
    int w, p;
}bit[MXN];
int lowbit(int x){
    return x&(-x);
}
void add(int x, int w, int p){
    for(; x > 0; x -= lowbit(x)){
        if(bit[x].w > w)bit[x].w = w, bit[x].p = p;
    }
}
int query(int x){
    int mmax = INF, p = -1;
    for(; x <= n; x += lowbit(x)){
        if(bit[x].w < mmax)mmax = bit[x].w, p = bit[x].p;
    }
    return p;
}
int Fi(int x){
    return fa[x] == x? x: fa[x] = Fi(fa[x]);
}
void add_edge(int u,int v,int w){
    edge[++tot].x = u;edge[tot].y = v;edge[tot].id = w;
}
int abd(int x){return (x < 0)? -x : x;}
int dist(int i, int j){
    return abs(cw[i].x-cw[j].x)+abs(cw[i].y-cw[j].y);
}
void kruskal(){
    sort(edge, edge + tot + 1, cmp1);
    int cnt = n - k, ans;
    for(int i = 0; i <= n; ++i)fa[i] = i;
    for(int i = 0; i <= tot && cnt; ++i){
        int pa = Fi(edge[i].x), pb = Fi(edge[i].y);
        if(pa == pb)continue;
        --cnt;
        ans = edge[i].id;
        fa[pb] = pa;
    }
    printf("%d\n", ans);
}
/*
我们只需考虑在一块区域内的点，其他区域内的点可以通过坐标变换“移动”到这个区域内。为了方
便处理，我们考虑在y轴向右45度的区域。在某个点A(x0,y0)的这个区域内的点B(x1,y1)满足
x1≥x0且y1-x1>y0-x0。这里对于边界我们只取一边，但是操作中两边都取也无所谓。那么
|AB|=y1-y0+x1-x0=(x1+y1)-(x0+y0)。在A的区域内距离A最近的点也即满足条件的点中
x+y最小的点。因此我们可以将所有点按x坐标排序，再按y-x离散，用线段树或者树状数组维护
大于当前点的y-x的(最小的x+y)对应的点。时间复杂度O(NlogN)。
*/
int main(int argc, char const *argv[]){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
    while(~scanf("%d%d", &n, &k)){
        tot = -1;
        for(int i = 0 ; i < n; ++i){
            scanf("%d%d", &cw[i].x, &cw[i].y);
            cw[i].id = i;
        }
        for(int dir = 1; dir <= 4; ++dir){
            //坐标转换
            if(dir % 2 == 0){
                for(int i = 0; i < n; ++i)swap(cw[i].x, cw[i].y);
            }else if(dir == 3){
                for(int i = 0; i < n; ++i)cw[i].x = -cw[i].x;
            }
            //先x再y排序
            sort(cw, cw +n, cmp);
            //Discretize
            for(int i = 0; i <= n; ++i){
                ar[i] = cw[i].y - cw[i].x;
                bit[i].w = INF; bit[i].p = -1;
            }
            sort(ar, ar + n);
            int k = unique(ar, ar + n) - ar;
            for(int i = n - 1; i >= 0; --i){
                //按y-x编号
                int p = lower_bound(ar, ar + k, cw[i].y - cw[i].x) - ar + 1;
                int pos  = query(p);//获取最小的y+x
                if(pos != -1){
                    add_edge(cw[i].id, cw[pos].id, dist(i, pos));
                }
                //添加y+x
                add(p, cw[i].y + cw[i].x, i);
            }
        }
        kruskal();
    }
    return 0;
}