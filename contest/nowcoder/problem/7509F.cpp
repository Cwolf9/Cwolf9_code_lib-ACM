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
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
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
constexpr int INF = 0x3f3f3f3f;
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
    // int tid;
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

void gao(int fg) {
    rep(i, 0, n + 2) root[i] = 0;
    inde = 0;
    tr[0] = Node(0);
    sgt.build(1, n, 1);
    int qi = 1;
    if(fg) insert(get_id(0), 0, vsL, vsR, 0, root[0]);
    rep(i, 1, n + 1) {
        int up = get_id(preSum[i]);
        LL las = -1e18, tt = i;
        while(1) {
            LL down = (las + preSum[i] + 1) / 2;
            int ans = query(get_id(down), up, vsL, vsR, root[tt - 1]);
            if(ans == -1) break;
            // debug(i, down, ans, preSum[i] - preSum[ans])
            sgt.modify(1, ans + fg, preSum[i] - preSum[ans], 1, n, 1);
            // debug(ans, preSum[i], preSum[ans])
            assert(preSum[ans] <= preSum[i]);
            if(preSum[ans] == preSum[i] || ans <= 0) break;
            las = preSum[ans];
            tt = ans;
        }
        insert(up, i, vsL, vsR, root[i - 1], root[i]);
        while(qi <= m && qry[qi].r <= i - (fg?0:1)) {
            qry[qi].ans = min(qry[qi].ans, sgt.query(qry[qi].l, qry[qi].r, 1, n, 1));
            ++ qi;
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    read(n), read(m);
    ++ n;
    vs.emplace_back(0);
    rep(i, 1, n + 1) {
        if(i != n) read(arr[i]);
        else arr[n] = 0;
        preSum[i] = preSum[i - 1] + arr[i], vs.emplace_back(preSum[i]);
    }
    my_unique(vs);
    sufSum[n + 1] = 0;
    per(i, n, 1) sufSum[i] = sufSum[i + 1] + arr[i];
    sufSum[n] = abs(sufSum[n]);
    per(i, n - 1, 1) sufSum[i] = min(sufSum[i + 1], abs(sufSum[i]));
    // rep(i, 1, n + 1) debug(i, preSum[i])
    vsL = 1;
    vsR = vs.size() + 1;
    rep(i, 1, m + 1) {
        read(qry[i].l), read(qry[i].r);
        qry[i].id = i;
        qry[i].ans = abs(arr[qry[i].l]);
        if(qry[i].r == n) qry[i].ans = min(qry[i].ans, sufSum[qry[i].l]);
    }
    sort(qry + 1, qry + m + 1);
    gao(1);
    per(i, n / 2, 1) {
        swap(arr[i], arr[n - i + 1]);
        swap(preSum[i], preSum[n - i + 1]);
    }
    // rep(i, 1, n + 1) debug(i, preSum[i])
    // vs.clear();
    // vs.emplace_back(0);
    // rep(i, 1, n + 1) preSum[i] = preSum[i - 1] + arr[i], vs.emplace_back(preSum[i]);
    // my_unique(vs);
    // vsL = 1;
    // vsR = vs.size() + 1;
    rep(i, 1, m + 1) {
        qry[i].l = n - qry[i].l + 1;
        qry[i].r = n - qry[i].r + 1;
        swap(qry[i].l, qry[i].r);
        // debug(qry[i].id, qry[i].l, qry[i].r, qry[i].ans)
    }
    sort(qry + 1, qry + m + 1);
    gao(0);
    rep(i, 1, m + 1) arr[qry[i].id] = qry[i].ans;
    rep(i, 1, m + 1) printf("%lld\n", arr[i]);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
