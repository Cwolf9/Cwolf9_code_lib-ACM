#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <bitset>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <cmath>
#ifdef LOCAL
#define debug(x) cout<<#x<<" = "<<(x)<<endl;
#else
#define debug(x) 1;
#endif

#define chmax(x,y) x=max(x,y)
#define chmin(x,y) x=min(x,y)
#define lson id<<1,l,mid
#define rson id<<1|1,mid+1,r
#define lowbit(x) x&-x
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const ll MOD = 1e9 + 7;
const double eps = 1e-10;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1e6 + 5;
struct nodes {
    int l, r;
    bool operator <(const nodes &x) const {
        return r < x.r;
    }
} a[MAXN];
int tree[MAXN * 2];
int n, k;
void add(int i, int v) {
    while(i <= n) {
        tree[i] += v;
        i += i&-i;
    }
}
int get(int i) {
    int ret = 0;
    while(i) {
        ret += tree[i];
        i -= i&-i;
    }
    return ret;
}
pii h[MAXN * 2];
int com[MAXN * 2];
int tot;
int id(int x) {
    return lower_bound(com + 1, com + 1 + tot, x) - com;
}
int main() {
    scanf("%d%d", &n, &k);
        int cnt = 0, sz = 0;
        tot = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i].l, &a[i].r);
            h[++sz] = mp(a[i].l, 1);
            h[++sz] = mp(a[i].r, -a[i].l);
            com[++tot] = a[i].l;
            com[++tot] = a[i].r;
        }
        sort(com + 1, com + 1 + tot);
        tot = unique(com + 1, com + 1 + tot) - com - 1;
        sort(h + 1, h + 1 + sz);
        int ans = 0;
        for(int i = 1; i <= sz; i++) {
            if(h[i].second == 1) add(id(h[i].first), 1);
            else {
                int idx = id(h[i].first);
                int l = 1, r = idx - 1;
                while(l <= r) {
                    int mid = (l+r) >> 1;
                    if(get(mid) >= k) r = mid - 1;
                    else l = mid + 1;
                }
                ans = max(ans, com[idx] - com[r + 1]);
                add(id(-h[i].second), -1);
            }
        }
        printf("%d\n", ans);
    return 0;
}