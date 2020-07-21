/*
链接
https://ac.nowcoder.com/acm/contest/5667/H
题意
1. 插入一个x
2. 删除一个x
3. 询问是否有两个数可以和x形成三角形
 
思路
动态开点权值线段树
对于查询只有三种情况，x是三边之中最大的，x是三边之中第二大的，x是三边之中最小的
 
备注

*/
#include<bits/stdc++.h>
#define fi first
#define se second
#define mk make_pair
using namespace std;
typedef long long int64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
 
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int MXN = 2e6 + 5;
const int MXE = 6e6 + 5;
const int MXR = 1000000002;
int n, m;
class node {
    public:
    int ls, rs;
    int64 mnv, gap;
    int mxv, smxv;
    int cnt;
    node() {
        ls = rs = cnt = 0;
        mxv = smxv = -1;
        mnv = gap = INFLL;
    }
    // node(int a, int b, int c, int d, int e, int f, int g):
    // ls(a),rs(b),mnv(c), mxv(d),smxv(e),gap(f),cnt(g) {}
}cw[MXE];
int tot_n;
void push_up(int rt) {
    cw[rt].mnv = min(cw[cw[rt].ls].mnv, cw[cw[rt].rs].mnv);
    cw[rt].gap = min(cw[cw[rt].ls].gap, cw[cw[rt].rs].gap);
    if(cw[cw[rt].rs].mnv != INFLL && cw[cw[rt].ls].mxv != -1) cw[rt].gap 
    = min(cw[rt].gap, cw[cw[rt].rs].mnv - cw[cw[rt].ls].mxv);
    if(cw[cw[rt].ls].mxv > cw[cw[rt].rs].mxv) {
        cw[rt].mxv = cw[cw[rt].ls].mxv;
        cw[rt].smxv = max(cw[cw[rt].ls].smxv, cw[cw[rt].rs].mxv);
    }else if(cw[cw[rt].ls].mxv < cw[cw[rt].rs].mxv) {
        cw[rt].mxv = cw[cw[rt].rs].mxv;
        cw[rt].smxv = max(cw[cw[rt].rs].smxv, cw[cw[rt].ls].mxv);
    }else {
        cw[rt].mxv = cw[cw[rt].ls].mxv;
        cw[rt].smxv = cw[cw[rt].ls].mxv;
    }
}
void insert_wst(int v, int l, int r, int &rt) {
    if(rt == 0) rt = ++ tot_n;
    if(l == r) {
        if(cw[rt].cnt == 0) {
            cw[rt].mnv = cw[rt].mxv = l;
            cw[rt].smxv = -1;
            cw[rt].gap = INFLL;
            cw[rt].cnt = 1;
        }else {
            cw[rt].smxv = l;
            cw[rt].gap = 0;
            ++ cw[rt].cnt;
        }
        return ;
    }
    int mid = (l + r) >> 1;
    if(v <= mid) insert_wst(v, l, mid, cw[rt].ls);
    else insert_wst(v, mid + 1, r, cw[rt].rs);
    push_up(rt);
}
void erase_wst(int v, int l, int r, int rt) {
    if(rt == 0) return;
    if(l == r) {
        if(cw[rt].cnt > 2) {
            -- cw[rt].cnt;
        }else if(cw[rt].cnt == 2) {
            cw[rt].mnv = cw[rt].mxv = l;
            cw[rt].smxv = -1;
            cw[rt].gap = INFLL;
            cw[rt].cnt = 1;
        }else {
            cw[rt].mnv = INFLL;
            cw[rt].mxv = -1;
            cw[rt].smxv = -1;
            cw[rt].gap = INFLL;
            cw[rt].cnt = 0;
        }
        return ;
    }
    int mid = (l + r) >> 1;
    if(v <= mid) erase_wst(v, l, mid, cw[rt].ls);
    else erase_wst(v, mid + 1, r, cw[rt].rs);
    push_up(rt);
}
//left two val max sum
pair<int,int> query1_wst(int v, int l, int r, int rt) {
    // if(rt == 0) rt = ++ tot_n;
    if(rt == 0) return mk(-1, -1);
    if(v >= r) return mk(cw[rt].mxv, cw[rt].smxv);
    int mid = (l + r) >> 1;
    if(v <= mid) return query1_wst(v, l, mid, cw[rt].ls);
    else {
        pair<int, int> a = mk(cw[cw[rt].ls].mxv, cw[cw[rt].ls].smxv);
        pair<int, int> b = query1_wst(v, mid + 1, r, cw[rt].rs);
        int A, B;
        if(a.first >= b.first) A = a.first, B = max(a.second, b.first);
        else A = b.first, B = max(a.first, b.second);
        return mk(A, B);
    }
}
//right min gap
int64 query2_wst(int v, int l, int r, int rt) {
    // if(rt == 0) rt = ++ tot_n;
    if(rt == 0) return INFLL;
    if(v <= l) return cw[rt].gap;
    int mid = (l + r) >> 1;
    if(v > mid) return query2_wst(v, mid + 1, r, cw[rt].rs);
    else {
        int64 a = query2_wst(v, l, mid, cw[rt].ls);
        int64 b = cw[cw[rt].rs].gap;
        if(cw[cw[rt].ls].mxv >= v) b = min(b, cw[cw[rt].rs].mnv - cw[cw[rt].ls].mxv);
        return min(a, b);
    }
}
//right min val
int64 query3_wst(int v, int l, int r, int rt) {
    // if(rt == 0) rt = ++ tot_n;
    if(rt == 0) return INFLL;
    if(v <= l) return cw[rt].mnv;
    int mid = (l + r) >> 1;
    if(v > mid) return query3_wst(v, mid + 1, r, cw[rt].rs);
    else {
        int64 a = query3_wst(v, l, mid, cw[rt].ls);
        int64 b = cw[cw[rt].rs].mnv;
        return min(a, b);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    m = read();
    int opt, x, flag, rt = 0;
    int64 gap, mval, ret;
    pair<int, int> tmp;
    while(m --) {
        opt = read(), x = read();
        if(opt == 1) {
            insert_wst(x, 1, MXR, rt);
        }else if(opt == 2) {
            erase_wst(x, 1, MXR, rt);
        }else {
            flag = 0;
            //x是最大值，查看左边最大两个值的和
            tmp = query1_wst(x, 1, MXR, rt);
            if(tmp.first + tmp.second > x) flag = 1;
            else {
                //x是最小值，查看右边最小间隙
                gap = query2_wst(x, 1, MXR, rt);
                if(gap < x) flag = 1;
                else if(tmp.first != -1) {
                    //x是中间值，取左边一个和右边一个
                    mval = query3_wst(x + 1, 1, MXR, rt);
                    if(x + tmp.first > mval) flag = 1;
                }
            }
            printf("%s\n", flag?"Yes":"No");
        }
    }
    // debug(cw[0].ls, cw[0].rs, cw[0].cnt, cw[0].mxv, cw[0].mnv, cw[0].smxv, cw[0].gap)
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}