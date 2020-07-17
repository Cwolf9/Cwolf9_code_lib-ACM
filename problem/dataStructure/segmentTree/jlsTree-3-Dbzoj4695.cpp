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
const int INFLL = 0x3f3f3f3f;
const int MXN = 1e6 + 7;
const int MXE = MXN << 2;
int n, m;
int ar[MXN];
class node {
    public:
    int l, r;
    int mxv, cntMxv, smxv;//最大值，数量，严格次大值(初始为-INFLL)
    int mnv, cntMnv, smnv;//最小值，数量，严格次小值(初始为INFLL)
    int64 sum;//区间和
    int flagAdd;
    void push_up(const node &ls, const node &rs) {
        sum = ls.sum + rs.sum;
        if(ls.mnv < rs.mnv) {
            mnv = ls.mnv;
            cntMnv = ls.cntMnv;
            smnv = min(ls.smnv, rs.mnv);    
        }else if(ls.mnv == rs.mnv) {
            mnv = ls.mnv;
            cntMnv = ls.cntMnv + rs.cntMnv;
            smnv = min(ls.smnv, rs.smnv);            
        }else {
            mnv = rs.mnv;
            cntMnv = rs.cntMnv;
            smnv = min(rs.smnv, ls.mnv);
        }
        if(ls.mxv > rs.mxv) {
            mxv = ls.mxv;
            cntMxv = ls.cntMxv;
            smxv = max(ls.smxv, rs.mxv);    
        }else if(ls.mxv == rs.mxv) {
            mxv = ls.mxv;
            cntMxv = ls.cntMxv + rs.cntMxv;
            smxv = max(ls.smxv, rs.smxv);            
        }else {
            mxv = rs.mxv;
            cntMxv = rs.cntMxv;
            smxv = max(rs.smxv, ls.mxv);
        }
    }
}cw[MXE];

void build(int l, int r, int rt) {
    cw[rt].l = l, cw[rt].r = r;
    cw[rt].flagAdd = 0;
    if(l == r) {
        cw[rt].mxv = cw[rt].mnv = ar[l];
        cw[rt].cntMxv = cw[rt].cntMnv = 1;
        cw[rt].smxv = -INFLL;
        cw[rt].smnv = INFLL;
        cw[rt].sum = ar[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lson);
    build(mid + 1, r, rson);
    cw[rt].push_up(cw[lson], cw[rson]);
}
void push_add(int rt, int v) {
    if(cw[rt].smxv != -INFLL) cw[rt].smxv += v;
    if(cw[rt].smnv != INFLL) cw[rt].smnv += v;
    cw[rt].mxv += v;
    cw[rt].mnv += v;
    cw[rt].sum += (int64)v * (cw[rt].r - cw[rt].l + 1);
    cw[rt].flagAdd += v;
}
void push_down(int rt) {
    if(cw[rt].flagAdd) {
        push_add(lson, cw[rt].flagAdd);
        push_add(rson, cw[rt].flagAdd);
        cw[rt].flagAdd = 0;
    }
    int oldMxvL = cw[lson].mxv;
    int oldMnvL = cw[lson].mnv;
    int oldMxvR = cw[rson].mxv;
    int oldMnvR = cw[rson].mnv;
    if(cw[lson].mxv > cw[rt].mxv) {
        if(cw[lson].mxv == cw[lson].mnv) cw[lson].mnv = cw[rt].mxv;
        cw[lson].mxv = cw[rt].mxv;
    }
    if(cw[lson].mnv < cw[rt].mnv) {
        if(cw[lson].mxv == cw[lson].mnv) cw[lson].mxv = cw[rt].mnv;
        cw[lson].mnv = cw[rt].mnv;
    }
    if(cw[lson].mxv == cw[lson].mnv) {            
        cw[lson].cntMxv = cw[lson].cntMnv = cw[lson].r - cw[lson].l + 1;
        cw[lson].smnv = INFLL;
        cw[lson].smxv = -INFLL;
        cw[lson].sum = (int64)cw[lson].cntMnv * cw[lson]. mnv;
    }else {
        if(cw[lson].smnv != INFLL && cw[lson].smnv > cw[lson].mxv) cw[lson].smnv = cw[lson].mxv;
        if(cw[lson].smxv != -INFLL && cw[lson].smxv < cw[lson].mnv) cw[lson].smxv = cw[lson].mnv;
        cw[lson].sum -= ((int64)oldMxvL - cw[lson].mxv) * cw[lson].cntMxv;
        cw[lson].sum += ((int64)cw[lson].mnv - oldMnvL) * cw[lson].cntMnv;
    }

    if(cw[rson].mxv > cw[rt].mxv) {
        if(cw[rson].mxv == cw[rson].mnv) cw[rson].mnv = cw[rt].mxv;
        cw[rson].mxv = cw[rt].mxv;
    }
    if(cw[rson].mnv < cw[rt].mnv) {
        if(cw[rson].mxv == cw[rson].mnv) cw[rson].mxv = cw[rt].mnv;
        cw[rson].mnv = cw[rt].mnv;
    }
    if(cw[rson].mxv == cw[rson].mnv) {
        cw[rson].cntMxv = cw[rson].cntMnv = cw[rson].r - cw[rson].l + 1;
        cw[rson].smnv = INFLL;
        cw[rson].smxv = -INFLL;
        cw[rson].sum = (int64)cw[rson].cntMnv * cw[rson]. mnv;
    }else {
        if(cw[rson].smnv != INFLL && cw[rson].smnv > cw[rson].mxv) cw[rson].smnv = cw[rson].mxv;
        if(cw[rson].smxv != -INFLL && cw[rson].smxv < cw[rson].mnv) cw[rson].smxv = cw[rson].mnv;
        cw[rson].sum -= ((int64)oldMxvL - cw[rson].mxv) * cw[rson].cntMxv;
        cw[rson].sum += ((int64)cw[rson].mnv - oldMnvL) * cw[rson].cntMnv;
    }
}
void updateAdd(int L, int R, int v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return ;
    // if(cw[rt].mxv <= v) return ;
    if(L <= cw[rt].l && cw[rt].r <= R) {
        cw[rt].flagAdd += v;
        cw[rt].sum += (int64)v * (cw[rt].r - cw[rt].l + 1);
        cw[rt].mxv += v;
        cw[rt].mnv += v;
        if(cw[rt].smxv != -INFLL) cw[rt].smxv += v;
        if(cw[rt].smnv != INFLL) cw[rt].smnv += v;
        return ;
    }
    int mid = (cw[rt].l + cw[rt].r) >> 1;
    push_down(rt);
    if(L > mid) {
        updateAdd(L, R, v, rson);
    }else if(R <= mid) {
        updateAdd(L, R, v, lson);
    }else {
        updateAdd(L, mid, v, lson);
        updateAdd(mid + 1, R, v, rson);
    }
    cw[rt].push_up(cw[lson], cw[rson]);
}
void updateMin(int L, int R, int v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return ;
    if(cw[rt].mxv <= v) return ;
    if(L <= cw[rt].l && cw[rt].r <= R && cw[rt].smxv < v) {
        cw[rt].sum -= ((int64)cw[rt].mxv - v) * cw[rt].cntMxv;
        if(cw[rt].mxv == cw[rt].mnv) cw[rt].mnv = v;
        if(cw[rt].smnv != INFLL && cw[rt].smnv > v) cw[rt].smnv = v;
        cw[rt].mxv = v;
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
void updateMax(int L, int R, int v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return ;
    // cout << " -- " << cw[rt].mnv << " " << cw[rt].mxv << endl;
    if(cw[rt].mnv >= v) return ;
    if(L <= cw[rt].l && cw[rt].r <= R && cw[rt].smnv > v) {
        cw[rt].sum += ((int64)v - cw[rt].mnv) * cw[rt].cntMnv;
        if(cw[rt].mxv == cw[rt].mnv) cw[rt].mxv = v;
        if(cw[rt].smxv != - INFLL && cw[rt].smxv < v) cw[rt].smxv = v;
        cw[rt].mnv = v;
        return ;
    }
    int mid = (cw[rt].l + cw[rt].r) >> 1;
    push_down(rt);
    if(L > mid) {
        updateMax(L, R, v, rson);
    }else if(R <= mid) {
        updateMax(L, R, v, lson);
    }else {
        updateMax(L, mid, v, lson);
        updateMax(mid + 1, R, v, rson);
    }
    cw[rt].push_up(cw[lson], cw[rson]);
}
int queryMin(int L, int R, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return 0;
    if(L <= cw[rt].l && cw[rt].r <= R) {
        return cw[rt].mnv;
    }
    int mid = (cw[rt].l + cw[rt].r) >> 1;
    push_down(rt);
    if(L > mid) {
        return queryMin(L, R, rson);
    }else if(R <= mid) {
        return queryMin(L, R, lson);
    }else {
        return min(queryMin(L, mid, lson), queryMin(mid + 1, R, rson));
    }
}
int queryMax(int L, int R, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return 0;
    if(L <= cw[rt].l && cw[rt].r <= R) {
        return cw[rt].mxv;
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
    int tim = 1;
    // scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", ar + i);
        }
        build(1, n, 1);
        int opt, x, y;
        int v;
        scanf("%d", &m);
        while(m --) {
            scanf("%d", &opt);
            scanf("%d%d", &x, &y);
            switch(opt) {
                case 1:
                scanf("%d", &v);
                updateAdd(x, y, v, 1);
                break;
                case 2:
                scanf("%d", &v);
                updateMax(x, y, v, 1);
                break;
                case 3:
                scanf("%d", &v);
                updateMin(x, y, v, 1);
                break;
                case 4:
                printf("%lld\n", querySum(x, y, 1));
                break;
                case 5:
                printf("%d\n", queryMax(x, y, 1));
                break;
                case 6:
                printf("%d\n", queryMin(x, y, 1));
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