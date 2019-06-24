//P3402 【模板】可持久化并查集
#include<bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
const int MXN = 4e5 + 7;

int n, m;
int Root[MXN];
struct lp {
    int l, r, fat, rk;
}cw[MXN*20];
int tot_z;
void insert(int l, int r, int old, int &cur, int p, int v) {
    cur = ++ tot_z;
    cw[cur] = cw[old];
    if(l == r) {
        cw[cur].fat = v;
        cw[cur].rk = cw[old].rk;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) insert(l, mid, cw[old].l, cw[cur].l, p, v);
    else insert(mid+1, r, cw[old].r, cw[cur].r, p, v);
}
int z_query(int p, int cur, int l, int r) {
    if(l == r) {
        return cur;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) return z_query(p, cw[cur].l, l, mid);
    else return z_query(p, cw[cur].r, mid+1, r);
}
int Fi(int x,int rt) {
    int f_id = z_query(x, rt, 1, n);
    return cw[f_id].fat == x? x: Fi(cw[f_id].fat, rt);
}
int main() {
    scanf("%d%d", &n, &m);
    cw[0].l = cw[0].r = cw[0].fat = 0;
    int opt, l, r;
    for(int i = 1; i <= n; ++i) insert(1, n, Root[0], Root[0], i, i);
    //printf("**\n");
    for(int t = 1; t <= m; ++t) {
        scanf("%d", &opt);
        if(opt == 1) {
            scanf("%d%d", &l, &r);
            Root[t] = Root[t-1];
            int pa = Fi(l, Root[t]), pb = Fi(r, Root[t]);
            if(cw[pa].rk > cw[pb].rk) swap(pa, pb);
            insert(1, n, Root[t-1], Root[t], pa, pb);
            cw[pb].rk = cw[pa].rk + 1;
        }else if(opt == 2) {
            scanf("%d", &r);
            Root[t] = Root[r];
        }else {
            scanf("%d%d", &l, &r);
            Root[t] = Root[t-1];
            if(Fi(l, Root[t]) == Fi(r, Root[t])) puts("1");
            else puts("0");
        }
    }
    return 0;
}
/*
1 a b 合并a,b所在集合
2 k 回到第k次操作之后的状态(查询算作操作)
3 a b 询问a,b是否属于同一集合，是则输出1否则输出0
5 6
1 1 2
3 1 2
2 0
3 1 2
2 1
3 1 2
1
0
1
*/
