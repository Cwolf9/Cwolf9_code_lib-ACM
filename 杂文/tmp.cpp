#include<bits/stdc++.h>
#define endl "\n"
#define fi first
#define se second
#define eb emplace_back
#define mk make_pair
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;

inline int read() {
  int x=0;int f=0;char ch=getchar();
  while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
  while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
  return x=f?-x:x;
}
inline void write(int x) {
    if(x==0){putchar('0'),putchar('\n');return;}
    if(x < 0) {putchar('-');x=-x;}
    static char s[23];int l = 0;
    while(x!=0)s[l++]=x%10+48,x/=10;
    while(l)putchar(s[--l]);
    putchar('\n');
}

const int MXN = 1e6 + 6;
const int MXE = 2e5 + 6;
const int INF = 0x3f3f3f3f;

int n, m;
struct lp {
    int l, r, sum;
}cw[85000007];
struct node {
    int opt, x, y, old;
}edge[MXE];
int ALL;
int ar[MXN], br[MXN];
int Root[MXN << 2], NODE, yRoot[MXN];
int bit[MXN];
inline int lowbit(int x){return (x&(-x));}
void bit_Add(int x,int c){for(; x <= n; x += lowbit(x)) bit[x]^=c;}
int bit_Query(int x){int ANS = 0;for(; x; x -= lowbit(x)) ANS^=bit[x];return ANS;}

void update(int &cur, int old, int x, int l, int r, int p) {
    cur = ++ NODE;
    cw[cur] = cw[old];
    ++ cw[cur].sum;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(x <= mid) update(cw[cur].l, cw[old].l, x, l, mid, p);
    else update(cw[cur].r, cw[old].r, x, mid+1, r, p);
}
void update(int &cur, int x, int v, int l, int r) {
    if(!cur) cur = ++ NODE;
    if(l == r) {
        cw[cur].sum += v;
        return ;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) update(cw[cur].l, x, v, l, mid);
    else update(cw[cur].r, x, v, mid+1, r);
}
void update1(int &cur, int x, int v, int l, int r) {
    if(!cur) cur = ++ NODE;
    if(l == r) {
        cw[cur].sum = v;
        return ;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) update1(cw[cur].l, x, v, l, mid);
    else update1(cw[cur].r, x, v, mid+1, r);
}
int s_find(int rt, int aim, int l, int r) {
    if(l == r) return cw[rt].sum;
    int mid = (l + r) >> 1;
    if(aim <= mid) return s_find(cw[rt].l, aim, l, mid);
    else return s_find(cw[rt].r, aim, mid+1, r);
}
void s_update(int rt, int p, int aim, int val, int l, int r) {
    if(l == r) {
        update(Root[rt], aim, val, 1, ALL);
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) s_update(rt<<1, p, aim, val, l, mid);
    else s_update(rt<<1|1, p, aim, val, mid+1, r);
    update1(Root[rt],aim,s_find(Root[rt<<1],aim,1,ALL)+s_find(Root[rt<<1|1],aim,1,ALL),1,ALL);
}
int s_query(int L, int R, int l, int r, int aim, int rt) {
    if(L <= l && r <= R) {
        return s_find(Root[rt], aim, 1, ALL);
    }
    int mid = (l + r) >> 1;
    if(L > mid) return s_query(L, R, mid + 1, r, aim, rt<<1|1);
    else if(R <= mid) return s_query(L, R, l, mid, aim, rt<<1);
    else return s_query(L, mid, l, mid, aim, rt<<1) + s_query(mid+1, R, mid+1, r, aim, rt<<1|1);
}
int query(int l, int r, int aim) {
    int ans = s_find(yRoot[r], aim, 1, ALL) - s_find(yRoot[l], aim, 1, ALL);
    return ans + s_query(l+1, r, 1, n, aim, 1);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);
#endif
    n = read(), m = read();
    VI vs; vs.eb(-1); cw[0] = {0,0,0};
    for(int i = 1; i <= n; ++i) ar[i] = read(), vs.eb(ar[i]), bit_Add(i, ar[i]), br[i] = ar[i];
    for(int i = 1, opt, x, y; i <= m; ++i) {
        opt = read(); x = read(); y = read();
        edge[i] = {opt, x, y};
        if(opt == 1) vs.eb(y);
    }
    sort(all(vs));
    vs.erase(unique(all(vs)), vs.end());
    ALL = vs.size();
    for(int i = 1, tmp; i <= n; ++i) {
        tmp = lower_bound(all(vs), br[i]) - vs.begin();
        update(yRoot[i], yRoot[i-1], tmp, 1, ALL, 1);
        assert(tmp >= 1); assert(tmp <= ALL);
    }
    int last = 0;
    for(int i = 1, opt, x, y; i <= m; ++i) {
        opt = edge[i].opt, x = edge[i].x, y = edge[i].y;
        if(opt == 1) {
            x = (x + last) % n + 1;
            bit_Add(x, ar[x]);
            bit_Add(x, y);
            int tmp1 = lower_bound(all(vs), ar[x]) - vs.begin();
            int tmp2 = lower_bound(all(vs), y) - vs.begin();
            ar[x] = y;
            assert(tmp1 >= 1); assert(tmp1 <= ALL);
            assert(tmp2 >= 1); assert(tmp2 <= ALL);
            s_update(1, x, tmp1, -1, 1, n);
            s_update(1, x, tmp2, 1, 1, n);
        }else {
            x = (x + last) % n + 1, y = (y + last) % n + 1;
            if(x > y) swap(x, y);
            edge[i].old = bit_Query(y)^bit_Query(x-1);
            int tmp = lower_bound(all(vs), edge[i].old) - vs.begin();
            assert(tmp >= 1); assert(tmp <= ALL);
            if(tmp == vs.size() || vs[tmp] != edge[i].old) last = (y - x + 1);
            else last = (y - x + 1 - query(x-1, y, tmp));
            write(last);
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}


/*1、TCP面向连接（如打电话要先拨号建立连接）;UDP是无连接的，即发送数据之前不需要建立连接
2、TCP提供可靠的服务。也就是说，通过TCP连接传送的数据，无差错，不丢失，不重复，且按序到达;
UDP尽最大努力交付，即不保证可靠交付
Tcp通过校验和，重传控制，序号标识，滑动窗口、确认应答实现可靠传输。
如丢包时的重发控制，还可以对次序乱掉的分包进行顺序控制。
3、UDP具有较好的实时性，工作效率比TCP高，适用于对高速传输和实时性有较高的通信或广播通信。
4.每一条TCP连接只能是点到点的;UDP支持一对一，一对多，多对一和多对多的交互通信
5、TCP对系统资源要求较多，UDP对系统资源要求较少。
*/
