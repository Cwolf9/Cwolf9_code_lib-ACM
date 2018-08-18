//ZOJ5332_Calculation离线+线段树.cpp
//https://www.cnblogs.com/danceonly/p/4004749.html
/*
比赛的时候没有做出来，赛后看了官方题解，虽然各种orz但是依旧只能orz(标程写得真是犀利),然后可耻的到网上找了下题解。。。

做法是线段树 + 离线搞， 网上那种对于[l, r]中的l从大到小排序很精妙(有一篇竟然说是以r为关键字,,,然后代码里面却是l。。。汗)， 再注意到gcd()对于每一个起点来说，是单调递减的，这样可以乱搞了... 

如果还不是很明白，搜下其他的blog吧，他们写得很丰富。。

贴贴代码，，可耻滚粗。

 ps .... zoj为何有时能过有时候又被卡了。。。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
//#include <cmath>

using namespace std;
#define lson rt<<1, l, mid
#define rson rt<<1|1, mid+1, r
typedef pair<int, int> PII;
//typedef __int64 lld;
typedef long long lld;
const int MAXN = 100005;

struct Q {
    int l, r, id;
    Q() {}
    Q(int a, int b, int c):l(a), r(b), id(c) {}
    bool operator < (const Q& cmp) const {
        return l > cmp.l;
    }
};
vector<Q> GS[55];
int a[MAXN];
lld sum[MAXN << 2];
lld add[MAXN << 2];
int n, m, q;
lld out[MAXN];
int log2[MAXN];

struct RMQ {
    int a[MAXN][22];
    void init(int A[], int N) {
        for (int i = 1; i <= N; i++) a[i][0] = A[i];
        for (int j = 1; (1 << j) <= N; j++) {
            for (int i = 1; i + (1<<j) - 1 <= N; i++) {
                a[i][j] = __gcd(a[i][j-1], a[i + (1<<(j-1))][j - 1]);
            }
        }
    }
    int rmq(int L, int R) {
      //  if (R < L) while (1);
        if (R < L) return 0;
        int k = log2[R - L + 1];
        return __gcd(a[L][k], a[R-(1<<k)+1][k]);
    }
}AC;

/*     *segment tree*    */
void build() {
    memset(add, 0, sizeof(add));
    memset(sum, 0, sizeof(sum));
}
void Down(int rt, int l, int r) {
    if (add[rt]) {
        int mid = r + l >> 1;
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        sum[rt<<1] += (lld)(mid - l + 1) * add[rt];
        sum[rt<<1|1] += (lld)(r - mid) * add[rt];
        add[rt] = 0;
    }
    return ;
}
void Up(int rt) {
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
void update(int rt, int l, int r, int L, int R) {
    if (L > R) return ;
    if (l >= L && r <= R) {
        add[rt] += 1;
        sum[rt] += r - l + 1;
        return ;
    }
    Down(rt, l, r);
    int mid = r + l >> 1;
    if (mid >= L) update(lson, L, R);
    if (R > mid) update(rson, L, R);
    Up(rt);
}
lld query(int rt, int l, int r, int L, int R) {
    if (L > R) return 0LL;
    if (l >= L && r <= R) {
        return sum[rt];
    }
    Down(rt, l, r);
    int mid = r + l >> 1;
    lld ret = 0;
    if (mid >= L) ret += query(lson, L, R);
    if (R > mid) ret += query(rson, L, R);
    return ret;
}
/*     *segment tree*    */

PII arr[MAXN];
void solve(vector<Q> vec, int M) {
    sort(vec.begin(), vec.end());
    build();
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i] % M != 0 || AC.rmq(i, n) % M == 0 && AC.rmq(i, n) > M) {
            arr[i] = make_pair(-1, -1);
        }else {
            l = max(l, i); //r = max(r, i);
            while (l <= n && AC.rmq(i, l) % M == 0 && AC.rmq(i, l) > M) ++ l;
            r = max(l, r);
            while (r+1 <= n && AC.rmq(i, r+1) == M) ++ r;
            if (AC.rmq(i, l) == M) {
                arr[i] = make_pair(l, r);
            }else {
                arr[i] = make_pair(-1, -1);
            }
        }
    }
    int now = n, siz = vec.size();
    for (int i = 0; i < siz; i++) {
        Q e = vec[i];
        while (now >= 1 && e.l <= now) {
            if (arr[now].first != -1) {
                update(1, 1, n, max(1, arr[now].first), arr[now].second);
            }
            -- now;
        }
        out[e.id] = query(1, 1, n, e.l, e.r);
    }
}
/*

4 4 4
1 2 3 4
1 2 3 4
0 4 1
0 4 2
0 4 3
0 4 4

4 4 4
1 2 3 4
1 2 3 4
0 4 1
0 4 2
0 2 1
3 4 4

*/

int gs[55];
int main() {
    for (int i = 0; i < MAXN; i++) {
        log2[i] = (i == 0 ? -1 : log2[i >> 1] + 1);
    }
    while (scanf("%d%d%d", &n, &m, &q) == 3) {
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        AC.init(a, n);
        for (int i = 0; i < m; i++) scanf("%d", &gs[i]);
        sort(gs, gs + m);
        for (int i = 0; i < m; i++) GS[i].clear();
        for (int i = 1; i <= q; i++) {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            x = lower_bound(gs, gs + m, x) - gs;
            GS[x].push_back(Q(l + 1, r, i));
        }
        for (int i = 0; i < m; i++) {
            solve(GS[i], gs[i]);
        }
        for (int i = 1; i <= q; i++) printf("%lld\n", out[i]);
    }
    return 0;
}