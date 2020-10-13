/*
https://blog.nowcoder.net/n/8da642eb6e87433a8e2db118448224d9
https://ac.nowcoder.com/acm/contest/7509/F
https://ac.nowcoder.com/acm/problem/211736
题意：
多次询问区间内，子区间权值和的绝对值的最小值
题解：
首先前缀和，然后变成求区间内求绝对值最小的两个数的差。设前缀和数组为A.
考虑离线，将询问按右端点排序。我们从小到大枚举询问区间的右端点r, 同时用数据结构维护每个左端点的答案。
考虑新增一个数A_r与它前面的点构成数对产生的贡献。
{
1.只考虑x<r且A_x<=A_r的x与r组成数对的贡献，首先找到最大的x满足A_x<=A_r记为x_1，对于所有l<=x_1+1的询问的答案都要和A_r-A_{x_1}取最小值。
然后依次下去找最大的x满足x<x_1且A_x1<A_x<=A_r记为x_2，对于所有l<=x_2+1的询问的答案都要和A_r-A_{x_2}取最小值。
2.只考虑x<r且A_x>A_r的x与r组成数对的贡献，处理方法同上类似。（可以正着找较大的x_i，也可以全部逆序之后按上述同样的方法处理一遍，不过这样要注意细节。）
}
问题是，最坏情况下每个点寻找x的次数可能达到O(n)级别。
观察到这样一个性质：当我们寻找x_2时，如果A_{x_2}-A_{x_1}<=A_r-A_{x_2}时，数对{x_2,r}对答案没有任何贡献。
所以我们每次只寻找那些⌈(A_x_1+A_r)/2⌉<=A_x<=A_r的最大x作为x_2计算贡献。
这样每次的查询值域区间都不超过上次的一半长度，这样最多只会有O(logW)次。
寻找x_i可以使用主席树，维护答案可以用线段树。
时间复杂度：O(n*lognlogW).
*/ 
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
bool Finish_read;
template<class T>inline void read(T &x){Finish_read=0;x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
constexpr int maxn = 3e5 + 5;
constexpr int maxe = 2e6 + 5;
constexpr long long INF = 1e18;
int n, m;
class Query {
    public:
    int l, r, id;
    LL ans;
    bool operator<(const Query &B) const {
        return r < B.r;
    }
}qry[maxn];
class Node {
    public:
    int val, ls, rs;
    Node() {val = ls = rs = 0;}
    Node(int _val):val(_val) {ls = rs = 0;}
}tr[maxn*20];
int root[maxn], inde;
LL arr[maxn], preSum[maxn], sufSum[maxn];
vector<LL> vs;
int vsL, vsR;
int get_id(LL x) {
    return lower_bound(all(vs), x) - vs.begin() + 1;
}
void insert(int p, int v, int l, int r, int las, int &rt) {
    if(rt == 0) rt = ++ inde;
    tr[rt] = tr[las];
    if(l == r) {
        tr[rt].val = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) insert(p, v, l, mid, tr[las].ls, tr[rt].ls);
    else insert(p, v, mid + 1, r, tr[las].rs, tr[rt].rs);
    tr[rt].val = max(tr[tr[rt].ls].val, tr[tr[rt].rs].val);
}
int query(int L, int R, int l, int r, int rt) {
    if(rt == 0 || L > R) return -1;
    if(L <= l && r <= R) {
        return tr[rt].val;
    }
    int mid = (l + r) >> 1;
    if(L > mid) return query(L, R, mid + 1, r, tr[rt].rs);
    else if(R <= mid) return query(L, R, l, mid, tr[rt].ls);
    else return max(query(L, mid, l, mid, tr[rt].ls), query(mid + 1, R, mid + 1, r, tr[rt].rs));
}

class ST {
    public:
    LL sum[maxn<<2], fg[maxn<<2];
    void build(int l, int r, int rt) {
        fg[rt] = INF;
        if(l == r) {
            sum[rt] = abs(arr[l]);
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
        sum[rt] = min(sum[rt << 1], sum[rt << 1 | 1]);
    }
    void push_down(int rt) {
        if(fg[rt] == INF) return;
        sum[rt<<1] = min(sum[rt<<1], fg[rt]);
        sum[rt<<1|1] = min(sum[rt<<1|1], fg[rt]);
        fg[rt<<1] = min(fg[rt<<1], fg[rt]);
        fg[rt<<1|1] = min(fg[rt<<1|1], fg[rt]);
        fg[rt] = INF;
    }
    void modify(int L, int R, LL v, int l, int r, int rt) {
        if(L > R) return ;
        if(L <= l && r <= R) {
            sum[rt] = min(sum[rt], v);
            fg[rt] = min(fg[rt], v);
            return;
        }
        push_down(rt);
        int mid = (l + r) >> 1;
        if(L > mid) modify(L, R, v, mid + 1, r, rt << 1 | 1);
        else if(R <= mid) modify(L, R, v, l, mid, rt << 1);
        else {
            modify(L, mid, v, l, mid, rt << 1);
            modify(mid + 1, R, v, mid + 1, r, rt << 1 | 1);
        }
        sum[rt] = min(sum[rt << 1], sum[rt << 1 | 1]);
    }
    LL query(int L, int R, int l, int r, int rt) {
        if(L <= l && r <= R) return sum[rt];
        push_down(rt);
        int mid = (l + r) >> 1;
        if(L > mid) return query(L, R, mid + 1, r, rt << 1 | 1);
        else if(R <= mid) return query(L, R, l, mid, rt << 1);
        else {
            LL a = query(L, mid, l, mid, rt << 1);
            LL b = query(mid + 1, R, mid + 1, r, rt << 1 | 1);
            return min(a, b);
        }
    }
}sgt;

void gao() {
    rep(i, 0, n + 2) root[i] = 0;
    inde = 0;
    tr[0] = Node(0);
    sgt.build(1, n, 1);
    int qi = 1;
    rep(i, 1, n + 1) {
        int up = get_id(preSum[i]);
        LL las = -1e18, tt = i;
        while(1) {
            LL down = (las + preSum[i] + 1) / 2;
            int ans = query(get_id(down), up, vsL, vsR, root[tt - 1]);
            if(i == 1) debug(ans, preSum[0])
            if(ans == -1) break;
            // debug(i, down, ans, preSum[i] - preSum[ans])
            sgt.modify(1, ans + 1, preSum[i] - preSum[ans], 1, n, 1);
            // debug(ans, preSum[i], preSum[ans])
            assert(preSum[ans] <= preSum[i]);
            if(preSum[ans] == preSum[i] || ans <= 0) break;
            las = preSum[ans];
            tt = ans;
        }
        insert(up, i, vsL, vsR, root[i - 1], root[i]);
        while(qi <= m && qry[qi].r <= i) {
            qry[qi].ans = min(qry[qi].ans, sgt.query(qry[qi].l, qry[qi].r, 1, n, 1));
            ++ qi;
        }
    }
}
void gao2() {//把前缀和数组反过来做同样的处理，注意差分！！！
    rep(i, 0, n + 2) root[i] = 0;
    inde = 0;
    tr[0] = Node(0);
    sgt.build(1, n, 1);
    int qi = 1;
    rep(i, 1, n + 1) {
        int up = get_id(preSum[i]);
        LL las = -1e18, tt = i;
        while(1) {
            LL down = (las + preSum[i] + 1) / 2;
            int ans = query(get_id(down), up, vsL, vsR, root[tt - 1]);
            if(i == 1) debug(ans, preSum[0])
            if(ans == -1) break;
            // debug(i, down, ans, preSum[i] - preSum[ans])
            sgt.modify(1, ans, preSum[i] - preSum[ans], 1, n, 1);
            // debug(ans, preSum[i], preSum[ans])
            assert(preSum[ans] <= preSum[i]);
            if(preSum[ans] == preSum[i] || ans <= 0) break;
            las = preSum[ans];
            tt = ans;
        }
        insert(up, i, vsL, vsR, root[i - 1], root[i]);
        while(qi <= m && qry[qi].r + 1 <= i) {//注意差分！！！
            qry[qi].ans = min(qry[qi].ans, sgt.query(qry[qi].l, qry[qi].r, 1, n, 1));
            ++ qi;
        }
    }
    //注意最后一项会漏算贡献
    int up = get_id(0);
    LL las = -1e18, tt = n + 1;
    while(1) {
        LL down = (las + 0 + 1) / 2;
        int ans = query(get_id(down), up, vsL, vsR, root[tt - 1]);
        if(ans == -1) break;
        // debug(i, down, ans, 0 - preSum[ans])
        sgt.modify(1, ans, 0 - preSum[ans], 1, n, 1);
        // debug(ans, 0, preSum[ans])
        assert(preSum[ans] <= 0);
        if(preSum[ans] == 0 || ans <= 0) break;
        las = preSum[ans];
        tt = ans;
    }
    while(qi <= m && qry[qi].r <= n) {
        qry[qi].ans = min(qry[qi].ans, sgt.query(qry[qi].l, qry[qi].r, 1, n, 1));
        ++ qi;
    }
}
int main() {
#ifndef ONLINE_JUDGE
    //freopen("D:in.in", "r", stdin);
    //freopen("D:out.out", "w", stdout);
#endif
    read(n), read(m);
    vs.emplace_back(0);
    rep(i, 1, n + 1) {
        read(arr[i]);
        preSum[i] = preSum[i - 1] + arr[i], vs.emplace_back(preSum[i]);
    }
    my_unique(vs);
    vsL = 1;
    vsR = vs.size() + 1;
    sufSum[n + 1] = 0;
    per(i, n, 1) sufSum[i] = sufSum[i + 1] + arr[i];
    sufSum[n] = abs(sufSum[n]);
    per(i, n - 1, 1) sufSum[i] = min(sufSum[i + 1], abs(sufSum[i]));
    // rep(i, 1, n + 1) debug(i, preSum[i])
    rep(i, 1, m + 1) {
        read(qry[i].l), read(qry[i].r);
        qry[i].id = i;
        qry[i].ans = abs(arr[qry[i].l]);
        if(qry[i].r == n) qry[i].ans = min(qry[i].ans, sufSum[qry[i].l]);
    }
    sufSum[1] = abs(preSum[1]);
    rep(i, 2, n + 1) sufSum[i] = min(sufSum[i - 1], abs(preSum[i]));
    rep(i, 1, m + 1) {
        if(qry[i].l == 1) qry[i].ans = min(qry[i].ans, sufSum[qry[i].r]);
    }
    sort(qry + 1, qry + m + 1);
    gao();
    per(i, n / 2, 1) {
        swap(arr[i], arr[n - i + 1]);
        swap(preSum[i], preSum[n - i + 1]);
    }
    rep(i, 1, m + 1) {
        qry[i].l = n - qry[i].l + 1;
        qry[i].r = n - qry[i].r + 1;
        swap(qry[i].l, qry[i].r);
    }
    sort(qry + 1, qry + m + 1);
    gao2();
    rep(i, 1, m + 1) arr[qry[i].id] = qry[i].ans;
    rep(i, 1, m + 1) printf("%lld\n", arr[i]);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}