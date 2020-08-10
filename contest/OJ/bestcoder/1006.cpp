/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#define LH_LOCAL
// #define LLDO
#pragma comment(linvker, "/STACvk:102400000,102400000")
//#include<bits/stdc++.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long int64;
typedef pair<int, int> pii;
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif

const int MXN = 2e5 + 5;
int vn, vk, vl;
int var[MXN], is[MXN];
int vbr[MXN], br[MXN], tk;
struct lp {
    int l, r, sum;
    lp() { l = r = sum = 0; }
} cw[MXN * 20];
int root[MXN], tot;
void update(int l, int r, int last, int &cur, int x) {
    cw[++tot] = cw[last];
    cw[tot].sum++;
    cur = tot;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) {
        update(l, mid, cw[last].l, cw[cur].l, x);
    } else {
        update(mid + 1, r, cw[last].r, cw[cur].r, x);
    }
}
int query(int l, int r, int last, int cur, int k) {
    if (l == r) return l;
    int l1 = cw[last].l, l2 = cw[cur].l, r1 = cw[last].r, r2 = cw[cur].r;
    int summ = cw[l2].sum - cw[l1].sum;
    int mid = (l + r) >> 1;
    if (k <= summ) {
        return query(l, mid, cw[last].l, cw[cur].l, k);
    } else {
        return query(mid + 1, r, cw[last].r, cw[cur].r, k - summ);
    }
}
long long get_ans(int vn) {
    tk = 1;
    sort(br + 1, br + 1 + vn);
    for (int i = 2; i <= vn; ++i) if (br[i] != br[i - 1]) br[++tk] = br[i];
    root[0] = 0;
    for (int i = 1; i <= vn; ++i) root[i] = 0;
    tot = 0;
    cw[0].l = cw[0].r = cw[0].sum = 0;
    long long ans1 = 0;
    for (int i = 1, now; i <= vn; ++i) {
        now = lower_bound(br + 1, br + 1 + tk, vbr[i]) - br;
        update(1, tk, root[i - 1], root[i], now);
        if (i >= vl) {
            int tmp = query(1, tk, root[i - vl], root[i], vl - vk + 1);
            ans1 += br[tmp];
        }
    }
    return ans1;
}

int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim;
    scanf("%d", &tim);
    while (tim--) {
        scanf("%d%d%d", &vn, &vl, &vk);
        for (int i = 1; i <= vn; ++i) {
            scanf("%d", &var[i]);
            br[i] = var[i];
            is[i] = 0;
        }
        sort(var + 1, var + vn + 1);
        int cnt = vn / vl, las = vn;
        for(int i = 1; i <= cnt; ++i) {
            for(int j = i * vl - vk + 1; j <= i * vl; ++j) vbr[j] = var[las--], is[j] = 1;
        }
        for(int i = vn; i >= 1; --i) {
            if(is[i] == 0) {
                vbr[i] = var[las--];
            }
        }
        int64 ans1 = get_ans(vn);
        printf("%lld ", ans1);
        sort(var + 1, var + vn + 1);
        for (int i = 1; i <= vn; ++i) is[i] = 0;
        cnt = vn / vl, las = vn;
        for(int i = 1; i <= cnt; ++i) {
            for(int j = i * vl - vk + 2; j <= i * vl; ++j) vbr[j] = var[las--], is[j] = 1;
        }
        for(int i = vn; i >= 1; --i) {
            if(is[i] == 0) {
                vbr[i] = var[las--];
            }
        }
        int64 ans2 = get_ans(vn);
        printf("%lld\n", ans2);
    }
#ifdef LH_LOCAL
    // cout << "time cost:" << 1.0 * clocvk() / CLOCvkS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}