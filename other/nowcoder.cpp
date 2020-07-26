
// #pragma comment(linker, "/STACK:102400000,102400000")
// #include <bits/stdc++.h>
// using namespace std;
// typedef long long LL;
// typedef pair<int, int> pii;

// const int MXN = 1e5 + 7;
// const int mod = 1000000007;
// const int INF = 0x3f3f3f3f;
// int n, m;
// class A {
// public:
//     A() {}
//     A(int a, int b, int c) :start(a),last(b),wait(b),id(c){}
//     LL start, last, wait, id;
// };
// A req[MXN];
// LL over[MXN], startList[MXN];
// bool cmp(const A&a, const A&b) {
//     if(a.start != b.start) return a.start < b.start;
//     if(a.last != b.last) return a.last < b.last;
//     return a.id < b.id;
// }
// class comp {
// public:
//     comp() {}
//     ~comp() {}
//     bool operator() (const A &a, const A &b) {
//         if(a.last != b.last) return a.last < b.last;
//         return a.id < b.id;
//     }
// };

// priority_queue<A, vector<A>, comp> Q;
// int solve(int n, int m) {
//         // write code here
//         queue<pair<int, int> > Q;
//         Q.push(make_pair(n, 0));
//         map<int, int> mp;
//         mp[n] = 1;
//         int ans = 1000;
//         while(!Q.empty()) {
//             pair<int, int> X = Q.front(); Q.pop();
//             int x = X.first;
//             int y = X.second;
//             if(x == m) ans = min(ans, y);
//             if(x > 1 && mp[x - 1] == 0) {
//                 mp[x - 1] = 1;
//                 Q.push(make_pair(x - 1, y + 1));
//             }
//             if(x < 1000 && mp[x + 1] == 0) {
//                 mp[x + 1] = 1;
//                 Q.push(make_pair(x + 1, y + 1));
//             }
//             if(x * x <= 1000 && x * x > 1 && mp[x * x] == 0) {
//                 mp[x * x] = 1;
//                 Q.push(make_pair(x * x, y + 1));
//             }
//         }
//         return ans;
//     }
// int main() {
// #ifndef ONLINE_JUDGE
//     // freopen("in.in", "r", stdin);
//     // freopen("out.out", "w", stdout);
// #endif
//     debug(solve(3, 10))
//     scanf("%d", &n);
//     for(int i = 0, a, b; i < n; ++i) {
//         scanf("%d%d", &a, &b);
//         req[i] = A(a, b, i);
//     }
//     sort(req, req + n, cmp);
//     for(int i = 0; i < n; ++i) startList[i] = req[i].start;
//     return 0;
// }
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
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MXN = 1e6 + 5;
const int MXE = MXN << 2;
int n, m;
int64 ar[MXN];
class node {
    public:
    int l, r;
    int64 mxv, cntMxv, smxv;//最大值，数量，严格次大值(初始为-INFLL)
    int64 mnv, cntMnv, smnv;//最小值，数量，严格次小值(初始为INFLL)
    int64 sum;//区间和
    int64 flagAdd;
    int64 flagMin;//其实这两个是flag是可以不需要的
    int64 flagMax;
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
    cw[rt].flagMin = INFLL;
    cw[rt].flagMax = -INFLL;
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
void push_add(int rt, int64 v) {
    if(v == 0) return ;
    if(cw[rt].flagMax != -INFLL) cw[rt].flagMax += v;
    if(cw[rt].flagMin != INFLL) cw[rt].flagMin += v;
    if(cw[rt].smxv != -INFLL) cw[rt].smxv += v;
    if(cw[rt].smnv != INFLL) cw[rt].smnv += v;
    cw[rt].mxv += v;
    cw[rt].mnv += v;
    cw[rt].sum += v * (cw[rt].r - cw[rt].l + 1);
    cw[rt].flagAdd += v;
}
void push_down(int rt) {
    if(cw[rt].flagAdd) {
        push_add(lson, cw[rt].flagAdd);
        push_add(rson, cw[rt].flagAdd);
        cw[rt].flagAdd = 0;
    }
    int64 oldMxv = cw[rt].mxv;
    int64 oldMnv = cw[rt].mnv;
    if(cw[lson].mxv > cw[rt].flagMin) {
        cw[lson].mxv = cw[rt].flagMin;
        cw[lson].flagMin = cw[rt].flagMin;
    }
    if(cw[rson].mxv > cw[rt].flagMin) {
        cw[rson].mxv = cw[rt].flagMin;
        cw[rson].flagMin = cw[rt].flagMin;
    }
    cw[rt].flagMin = INFLL;

    if(cw[lson].mnv < cw[rt].flagMax) {
        cw[lson].mnv = cw[rt].flagMax;
        cw[lson].flagMax = cw[rt].flagMax;
    }
    if(cw[rson].mnv < cw[rt].flagMax) {
        cw[rson].mnv = cw[rt].flagMax;
        cw[rson].flagMax = cw[rt].flagMax;
    }
    cw[rt].flagMax = -INFLL;
    if(cw[lson].mxv == cw[lson].mnv) {
        cw[lson].cntMxv = cw[lson].cntMnv = cw[lson].r - cw[lson].l + 1;
        cw[lson].flagMin = INFLL;
        cw[lson].flagMax = -INFLL;
        cw[lson].smnv = INFLL;
        cw[lson].smxv = -INFLL;
        cw[lson].sum = cw[lson].cntMnv * cw[lson]. mnv;
    }else {
        cw[lson].sum -= (oldMxv - cw[lson].mxv) * cw[lson].cntMxv;
        cw[lson].sum -= (cw[lson].mnv - oldMnv) * cw[lson].cntMnv;
    }

    if(cw[rson].mxv == cw[rson].mnv) {
        cw[rson].cntMxv = cw[rson].cntMnv = cw[rson].r - cw[rson].l + 1;
        cw[rson].flagMin = INFLL;
        cw[rson].flagMax = -INFLL;
        cw[rson].smnv = INFLL;
        cw[rson].smxv = -INFLL;
        cw[rson].sum = cw[rson].cntMnv * cw[rson]. mnv;
    }else {
        cw[rson].sum -= (oldMxv - cw[rson].mxv) * cw[rson].cntMxv;
        cw[rson].sum -= (cw[rson].mnv - oldMnv) * cw[rson].cntMnv;
    }
}
void updateAdd(int L, int R, int64 v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return ;
    // if(cw[rt].mxv <= v) return ;
    if(L <= cw[rt].l && cw[rt].r <= R && cw[rt].smxv < v) {
        cw[rt].flagAdd += v;
        if(cw[rt].flagMax != -INFLL) cw[rt].flagMax += v;
        if(cw[rt].flagMin != INFLL) cw[rt].flagMin += v;
        cw[rt].sum += v * (cw[rt].r - cw[rt].l + 1);
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
void updateMin(int L, int R, int64 v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return ;
    if(cw[rt].mxv <= v) return ;
    if(L <= cw[rt].l && cw[rt].r <= R && cw[rt].smxv < v) {
        cw[rt].flagMin = v;
        if(cw[rt].flagMin <= cw[rt].mnv) {
            cw[rt].cntMxv = cw[rt].cntMnv = cw[rt].r - cw[rt].l + 1;
            cw[rt].smnv = INFLL;
            cw[rt].smxv = -INFLL;
            cw[rt].sum = cw[rt].cntMnv * cw[rt].flagMin;
            cw[rt].mnv = cw[rt].flagMin;
            // cw[rt].flagMin = INFLL;
            // cw[rt].flagMax = -INFLL;
        }else {
            cw[rt].sum -= ((int64)cw[rt].mxv - v) * cw[rt].cntMxv;
        }
        cw[rt].mxv = cw[rt].flagMin;
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
void updateMax(int L, int R, int64 v, int rt) {
    if(L > cw[rt].r || R < cw[rt].l) return ;
    // cout << " -- " << cw[rt].mnv << " " << cw[rt].mxv << endl;
    if(cw[rt].mnv >= v) return ;
    if(L <= cw[rt].l && cw[rt].r <= R && cw[rt].smnv > v) {
        cw[rt].flagMax = v;
        // cout << v << " -   - "  << cw[rt].flagMax << endl;
        if(cw[rt].flagMax >= cw[rt].mxv) {
            cw[rt].cntMxv = cw[rt].cntMnv = cw[rt].r - cw[rt].l + 1;
            cw[rt].smnv = INFLL;
            cw[rt].smxv = -INFLL;
            cw[rt].sum = cw[rt].cntMnv * cw[rt].flagMax;
            cw[rt].mxv = cw[rt].flagMax;
            // cw[rt].flagMin = INFLL;
            // cw[rt].flagMax = -INFLL;
        }else {
            cw[rt].sum -= (v - cw[rt].mnv) * cw[rt].cntMxv;
        }
        cw[rt].mnv = cw[rt].flagMax;
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
int64 queryMin(int L, int R, int rt) {
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
int64 queryMax(int L, int R, int rt) {
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
            scanf("%lld", ar + i);
        }
        build(1, n, 1);
        int opt, x, y;
        int64 v;
        scanf("%d", &m);
        while(m --) {
            scanf("%d", &opt);
            scanf("%d%d", &x, &y);
            switch(opt) {
                case 1:
                scanf("%lld", &v);
                updateAdd(x, y, v, 1);
                break;
                case 2:
                scanf("%lld", &v);
                // cout << v << " *" << endl;
                updateMax(x, y, v, 1);
                break;
                case 3:
                scanf("%lld", &v);
                updateMin(x, y, v, 1);
                break;
                case 4:
                // cout << " *" << endl;
                printf("%lld\n", querySum(x, y, 1));
                break;
                case 5:
                printf("%lld\n", queryMax(x, y, 1));
                break;
                case 6:
                printf("%lld\n", queryMin(x, y, 1));
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