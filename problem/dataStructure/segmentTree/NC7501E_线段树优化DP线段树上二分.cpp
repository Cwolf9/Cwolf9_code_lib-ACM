/*
[toc]

## 线段树优化DP并上线段树上二分好题
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/7501/E)
**题意**
有一个长度为$n$的序列，每个点权值为在范围$[1,m]$内，保证每个值都出现过。
对每个$i(1\le i\le m)$询问包含权值$[1,i]$的区间最小长度。
$1\le 1\le m\le n\le 200000$

**思路**
不太会，只知道答案有单调性，然后听TDM提示了一个$dp$状态定义。
$dp[i][j]$表示以$i$为左端点的区间包含权值$[1,j]$的最小右端点。
暴力$O(n^2)$的写法：
先从小到大枚举$j$，然后枚举$j$的每一次出现的位置$lasJ$，右边没有$j$的赋值为无穷大。
状态转移：$dp[i][j]=max(dp[i][j-1],lasJ)$.

考虑用线段树维护，从小到大枚举$j$，然后更新$n$个点的$dp$值。
线段树每个节点维护两个值：
$sum[rt]$代表子树内$dp[i][j]$的最大值，$ans[rt]$表示子树内的答案即$(dp[i][j]-i+1)$的最小值。

一个显然的性质：对于任何$1\le a\le b\le n$满足$dp[a][j]\le dp[b][j]$。即$dp[i][j]$有一个单调性。
对于某一段区间的更新是区间$sum[rt]$与$lasJ$取最大值的操作。
显然需要更新的是一段前缀，又因为$dp[i][j]$具有单调性，且线段树本来就是一个二分的结构。
那么就可以写一个线段树二分来更新区间$sum[rt]$，当然也可以先二分出右端点再区间覆盖，不过这样复杂度多一个$log$。
当$sum[rt]$被更新时，$ans[rt]$复制为$sum[rt] - r + 1$即可，最小值肯定在右端点取嘛。

$over!$
**备注**
第一次写线段树上二分
时间复杂度：$O(nlog(n))$
空间复杂度：$O(\alpha *n)$
**AC_CODE**
[here](https://github.com/Cwolf9/Cwolf9_code_lib-ACM/blob/master/problem/dataStructure/segmentTree/NC7501E_%E7%BA%BF%E6%AE%B5%E6%A0%91%E4%BC%98%E5%8C%96DP%E7%BA%BF%E6%AE%B5%E6%A0%91%E4%B8%8A%E4%BA%8C%E5%88%86.cpp)
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
                                                                               getchar(); return x = f ? -x : x;
}
inline void write(int64 x, bool f = true) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');else putchar(' ');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');else putchar(' ');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {return a1 > a2 ? a1 : a2;}
template <class T>
T sml(const T &a1, const T &a2) {return a1 < a2 ? a1 : a2;}
template <typename T, typename... R>
T big(const T &f, const R &... r) {return big(f, big(r...));}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {return sml(f, sml(r...));}
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
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 2e5 + 5;
const int MXE = 1e6 + 5;
int n, m;
int ar[MXN], sum[MXN<<2], sumfg[MXN<<2], ans[MXN<<2];
vector<int> num[MXN];
void push_up(int rt) {
    sum[rt] = max(sum[rt << 1], sum[rt << 1 | 1]);
    ans[rt] = min(ans[rt << 1], ans[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
    sumfg[rt] = 0;
    if(l == r) {
        sum[rt] = ar[l];
        ans[rt] = ar[l] - l + 1;
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
    push_up(rt);
    // debug(rt, sum[rt])
}
void push_down(int rt, int l, int mid, int r) {
    if(sumfg[rt] == 0) return;
    sumfg[rt << 1] = max(sumfg[rt << 1], sumfg[rt]);
    sumfg[rt << 1 | 1] = max(sumfg[rt << 1 | 1], sumfg[rt]);
    if(sum[rt << 1] < sumfg[rt]) {
        ans[rt << 1] = sumfg[rt] - mid + 1;
        sum[rt << 1] = sumfg[rt];
    }
    if(sum[rt << 1 | 1] < sumfg[rt]) {
        ans[rt << 1 | 1] = sumfg[rt] - r + 1;
        sum[rt << 1 | 1] = sumfg[rt];
    }
    sumfg[rt] = 0;
}
void update(int L, int R, int v, int l, int r, int rt) {
    // debug(L, R, l, r)
    if(sum[rt] < v && L <= l && r <= R) {
        ans[rt] = v - r + 1;
        sum[rt] = v;
        sumfg[rt] = max(sumfg[rt], v);
        return;
    }
    if(l == r) return;
    int mid = (l + r) >> 1;
    push_down(rt, l, mid, r);
    if(L > mid) {
        update(L, R, v, mid + 1, r, rt << 1 | 1);
    }else if(R <= mid) {
        update(L, R, v, l, mid, rt << 1);
    }else {
        if(sum[rt << 1] < v) update(mid + 1, R, v, mid + 1, r, rt << 1 | 1);
        update(L, mid, v, l, mid, rt << 1);
    }
    push_up(rt);
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("/home/cwolf9/CLionProjects/mtxt/in.txt", "r", stdin);
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
#endif
    n = read(), m = read();
    rep(i, 0, m + 1) num[i].eb(0);
    rep(i, 1, n + 1) {
        ar[i] = read();
        num[ar[i]].eb(i);
    }
    rep(i, 1, SZ(num[1])) {
        rep(j, num[1][i-1] + 1, num[1][i] + 1) {
            ar[j] = num[1][i];
            // debug(j, ar[j])
        }
    }
    rep(i, num[1].back() + 1, n + 1) {
        ar[i] = INF;
        // debug(i, ar[i])
    }
    build(1, n, 1);
    printf("%d", ans[1]);
    rep(qi, 2, m + 1) {
        rep(i, 1, SZ(num[qi])) {
            int l = num[qi][i-1], r = num[qi][i];
            update(l + 1, r, num[qi][i], 1, n, 1);
            // debug(l + 1, r, num[qi][i])
        }
        if(num[qi].back() + 1 <= n) {
            update(num[qi].back() + 1, n, INF, 1, n, 1);
            // debug(num[qi].back() + 1, n)
        }
        printf(" %d", ans[1]);
        // return 0;
    }
    printf("\n");
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
