/*
uoj jls blog: http://jiry-2.blog.uoj.ac/blog/1404

https://www.cnblogs.com/zwfymqz/p/9671730.html
https://blog.csdn.net/MrBird_to_fly/article/details/77141881
在刚刚结束的水题嘉年华的压轴节目放水大赛中，wyywyy如愿以偿的得到了最假女选手的奖项。但是作为主办人的
C_SUNSHINE为了证明wyywyy确实在放水，决定出一道基础题考察wyywyy的姿势水平。给定一个长度为 N序列，编号
从1 到 N。要求支持下面几种操作：
1.给一个区间[L,R] 加上一个数x 
2.把一个区间[L,R] 里小于x 的数变成x 
3.把一个区间[L,R] 里大于x 的数变成x 
4.求区间[L,R] 的和
5.求区间[L,R] 的最大值
6.求区间[L,R] 的最小值
第一行一个整数 N表示序列长度。
第二行N 个整数Ai 表示初始序列。
第三行一个整数M 表示操作个数。
接下来M 行，每行三或四个整数，第一个整数Tp 表示操作类型，接下来L,R,X 或L,R 表述操作数。
1<=tp<=6,N,M<=5*10^5,|Ai|<=10^8
Tp=1时,|x|<=1000
Tp=2或3时，|x|<=10^8
*/
#include <bits/stdc++.h>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;
typedef long long int64;
const int64 INF = 0x3f3f3f3f3f3f3f3fLL;
const int MXN = 1e6 + 5;
const int MXE = MXN << 2;
int n, m;
int64 ar[MXN];
class node {
    public:
    int l, r;
    int64 mx, cntmx, smx;
    int64 sum;
    int64 flagMin;
    void push_up(const node &ls, const node &rs) {
        if(ls.mx > rs.mx) {
            mx = ls.mx;
            cntmx = ls.cntmx;
            smx = max(ls.smx, rs.mx);
            sum = ls.sum + rs.sum;
        }else if(ls.mx == rs.mx) {
            mx = ls.mx;
            cntmx = ls.cntmx + rs.cntmx;
            smx = max(ls.smx, rs.smx);
            sum = ls.sum + rs.sum;
        }else {
            mx = rs.mx;
            cntmx = rs.cntmx;
            smx = max(rs.smx, ls.mx);
            sum = ls.sum + rs.sum;
        }
    }
}cw[MXE];

void build(int l, int r, int rt) {
    cw[rt].l = l, cw[rt].r = r;
    cw[rt].flagMin = INF;
    if(l == r) {
        cw[rt].mx = ar[l];
        cw[rt].cntmx = 1;
        cw[rt].smx = -1;
        cw[rt].sum = ar[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lson);
    build(mid + 1, r, rson);
    cw[rt].push_up(cw[lson], cw[rson]);
}
void push_down(int rt) {
    if(cw[rt].flagMin == INF) return ;
    if(cw[lson].mx > cw[rt].flagMin) {
        cw[lson].sum -= (cw[lson].mx - cw[rt].flagMin) * cw[lson].cntmx;
        cw[lson].mx = cw[rt].flagMin;
        cw[lson].flagMin = cw[rt].flagMin;
    }
    if(cw[rson].mx > cw[rt].flagMin) {
        cw[rson].sum -= (cw[rson].mx - cw[rt].flagMin) * cw[rson].cntmx;
        cw[rson].mx = cw[rt].flagMin;
        cw[rson].flagMin = cw[rt].flagMin;
    }
    cw[rt].flagMin = INF;
}
void updateMin(int L, int R, int64 v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return ;
    if(cw[rt].mx <= v) return ;
    if(L <= cw[rt].l && cw[rt].r <= R && cw[rt].smx < v) {
        cw[rt].flagMin = v;
        cw[rt].sum -= ((int64)cw[rt].mx - v) * cw[rt].cntmx;
        cw[rt].mx = cw[rt].flagMin;
        return ;
    }
    int mid = (cw[rt].l + cw[rt].r) >> 1;
    push_down(rt);
    if(L > mid) {
        updateMin(L, R, v, rson);
    }else if(R <= mid) {
        updateMin(L, R, v, lson);
    }else {
        updateMin(L, mid, v, lson);
        updateMin(mid + 1, R, v, rson);
    }
    cw[rt].push_up(cw[lson], cw[rson]);
}
int64 queryMax(int L, int R, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return 0;
    if(L <= cw[rt].l && cw[rt].r <= R) {
        return cw[rt].mx;
    }
    int mid = (cw[rt].l + cw[rt].r) >> 1;
    push_down(rt);
    if(L > mid) {
        return queryMax(L, R, rson);
    }else if(R <= mid) {
        return queryMax(L, R, lson);
    }else {
        return max(queryMax(L, mid, lson), queryMax(mid + 1, R, rson));
    }
}
int64 querySum(int L, int R, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return 0;
    if(L <= cw[rt].l && cw[rt].r <= R) {
        return cw[rt].sum;
    }
    int mid = (cw[rt].l + cw[rt].r) >> 1;
    push_down(rt);
    if(L > mid) {
        return querySum(L, R, rson);
    }else if(R <= mid) {
        return querySum(L, R, lson);
    }else {
        return querySum(L, mid, lson) + querySum(mid + 1, R, rson);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        scanf("%d", &m);
        for(int i = 1; i <= n; ++i) {
            scanf("%lld", ar + i);
        }
        build(1, n, 1);
        int opt, x, y;
        int64 v;
        while(m --) {
            scanf("%d", &opt);
            scanf("%d%d", &x, &y);
            switch(opt) {
                case 0:
                scanf("%lld", &v);
                updateMin(x, y, v, 1);
                break;
                case 1:
                printf("%lld\n", queryMax(x, y, 1));
                break;
                case 2:
                printf("%lld\n", querySum(x, y, 1));
                break;
                default:
                break;
            }
        }
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}