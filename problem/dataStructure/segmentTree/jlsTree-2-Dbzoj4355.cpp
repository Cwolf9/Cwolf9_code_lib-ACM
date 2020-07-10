/*
uoj jls blog: http://jiry-2.blog.uoj.ac/blog/1404

https://www.cnblogs.com/zwfymqz/p/9671730.html
https://blog.csdn.net/MrBird_to_fly/article/details/77141881
维护一个长度为N的序列a，现在有三种操作：
1）给出参数U,V,C，将a[U],a[U+1],...,a[V-1],a[V]都赋值为C。
2）给出参数U,V,C，对于区间[U,V]里的每个数i，将a[i]赋值为max(a[i]+C,0)。
3）给出参数U,V，输出a[U],a[U+1],...,a[V-1],a[V]里值为0的数字个数。
第一行包含两个正整数N,M(1<=N,M<=300000)，分别表示序列长度和操作个数。
第二行包含N个整数，其中第i个数表示a[i](0<=a[i]<=10^9)，描述序列的初始状态。
接下来M行描述M个操作，保证1<=U<=V<=N，对于操作1，0<=C<=10^9，对于操作2，|C|<=10^9。
*/
#include <bits/stdc++.h>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;
typedef long long int64;
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MXN = 1e6 + 5;
const int MXE = MXN << 2;
int n, m;
int64 ar[MXN];
class node {
    public:
    int l, r;
    int64 mnv, cntMnv, smnv;//最小值，数量，严格次小值(初始为INFLL)
    // int64 sum;//可以不管，本题不需要，自动忽略
    int64 flagMax;//子节点权值与其取max
    int64 flagAdd;//子节点全部加上此值
    //TODO
    void push_up(const node &ls, const node &rs) {
        if(ls.mnv < rs.mnv) {
            mnv = ls.mnv;
            cntMnv = ls.cntMnv;
            smnv = min(ls.smnv, rs.mnv);
            // sum = ls.sum;
        }else if(ls.mnv == rs.mnv) {
            mnv = ls.mnv;
            cntMnv = ls.cntMnv + rs.cntMnv;
            smnv = min(ls.smnv, rs.smnv);
            // sum = ls.sum + rs.sum;
        }else {
            mnv = rs.mnv;
            cntMnv = rs.cntMnv;
            smnv = min(rs.smnv, ls.mnv);
            // sum = rs.sum;
        }
    }
}cw[MXE];

void build(int l, int r, int rt) {
    cw[rt].l = l, cw[rt].r = r;
    cw[rt].flagMax = -1;
    cw[rt].flagAdd = 0;
    if(l == r) {
        cw[rt].mnv = ar[l];
        cw[rt].cntMnv = 1;
        cw[rt].smnv = INFLL;
        // cw[rt].sum = (ar[l] == 0);
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lson);
    build(mid + 1, r, rson);
    cw[rt].push_up(cw[lson], cw[rson]);
}
void push_add(int rt, int64 v) {
    if(v == 0) return ;
    cw[rt].flagAdd += v;
    if(cw[rt].flagMax != -1) cw[rt].flagMax += v;
    if(cw[rt].smnv != INFLL) cw[rt].smnv += v;
    cw[rt].mnv += v;
    // cw[rt].sum = cw[rt].cntMnv * (cw[rt].mnv == 0);
}
void push_down(int rt) {
    push_add(lson, cw[rt].flagAdd);
    push_add(rson, cw[rt].flagAdd);
    cw[rt].flagAdd = 0;
    if(cw[rt].flagMax == -1) return ;
    if(cw[lson].mnv < cw[rt].flagMax) {
        cw[lson].mnv = cw[rt].flagMax;
        cw[lson].flagMax = cw[rt].flagMax;
    }
    if(cw[rson].mnv < cw[rt].flagMax) {
        cw[rson].mnv = cw[rt].flagMax;
        cw[rson].flagMax = cw[rt].flagMax;
    }
    cw[rt].flagMax = -1;
}
//赋值操作，递归到值全部相同的子树为止，然后变成做区间 add 操作
void updateAsn(int L, int R, int64 v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return ;
    if(L <= cw[rt].l && cw[rt].r <= R && cw[rt].smnv == INFLL) {
        push_add(rt, v - cw[rt].mnv);
        return ;
    }
    int mid = (cw[rt].l + cw[rt].r) >> 1;
    push_down(rt);
    if(L > mid) {
        updateAsn(L, R, v, rson);
    }else if(R <= mid) {
        updateAsn(L, R, v, lson);
    }else {
        updateAsn(L, mid, v, lson);
        updateAsn(mid + 1, R, v, rson);
    }
    cw[rt].push_up(cw[lson], cw[rson]);
}
//区间max(ar[i] + c, 0)，先区间加c再区间取max
void updateMax(int L, int R, int64 v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l || (cw[rt].smnv == INFLL && cw[rt].mnv == 0 && v <= 0)) return ;
    // if(cw[rt].mnv <= v) return ;
    if(L <= cw[rt].l && cw[rt].r <= R) {
        if(cw[rt].mnv + v >= 0) {
            push_add(rt, v);
            return ;
        }else if(cw[rt].smnv == INFLL || cw[rt].smnv + v > 0) {
            push_add(rt, v);
            //赋值为 0
            cw[rt].mnv = 0;
            cw[rt].flagMax = 0;
            return ;
        }        
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

int64 queryZeroSum(int L, int R, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return 0;
    if(L <= cw[rt].l && cw[rt].r <= R) {
        return cw[rt].mnv == 0? cw[rt].cntMnv: 0;
    }
    int mid = (cw[rt].l + cw[rt].r) >> 1;
    push_down(rt);
    if(L > mid) {
        return queryZeroSum(L, R, rson);
    }else if(R <= mid) {
        return queryZeroSum(L, R, lson);
    }else {
        return queryZeroSum(L, mid, lson) + queryZeroSum(mid + 1, R, rson);
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
                case 1:
                scanf("%lld", &v);
                updateAsn(x, y, v, 1);
                break;
                case 2:
                scanf("%lld", &v);
                updateMax(x, y, v, 1);
                break;
                case 3:
                printf("%lld\n", cw[1].mnv == 0?queryZeroSum(x, y, 1):0);
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