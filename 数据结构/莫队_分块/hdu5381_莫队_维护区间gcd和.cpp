#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<random>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
#define pb push_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int MXN = 1e4 + 5;
const int MXE = 2e5 + 10;

int n, q, m;
int ar[MXN];
struct lp {
    int l, r, id;
}cw[MXN];
int belong[MXN], block;
LL ANS[MXN], ans;
int L, R;
std::vector<pii> myl[MXN], myr[MXN];
bool cmp(const lp &a, const lp &b) {
    if(belong[a.l] != belong[b.l]) return belong[a.l] < belong[b.l];
    return a.r < b.r;
}
int gcd(int a,int b) {
    return b == 0? a: gcd(b, a%b);
}
void init_ans() {
    myl[0].clear();
    for(int i = 1, last; i <= n; ++i) {
        myl[i].clear();
        myl[i].push_back({ar[i], i});
        last = ar[i];
        for(int j = 0, tmp; j < myl[i-1].size(); ++j) {
            tmp = gcd(ar[i], myl[i-1][j].fi);
            if(tmp == last) {
                myl[i].back().se = myl[i-1][j].se;
            }else {
                myl[i].push_back({tmp, myl[i-1][j].se});
            }
            last = tmp;
        }
    }
    myr[n+1].clear();
    for(int i = n, last; i >= 1; --i) {
        myr[i].clear();
        myr[i].push_back({ar[i], i});
        last = ar[i];
        for(int j = 0, tmp; j < myr[i+1].size(); ++j) {
            tmp = gcd(ar[i], myr[i+1][j].fi);
            if(tmp == last) {
                myr[i].back().se = myr[i+1][j].se;
            }else {
                myr[i].push_back({tmp, myr[i+1][j].se});
            }
            last = tmp;
        }
    }
}
void upl(int x, int f) {
    LL sum = 0;
    for(int i = 0, p = x, pp; i < myr[x].size(); ++i) {
        if(myr[x][i].se > R) pp = R;
        else pp = myr[x][i].se;
        sum += (LL)myr[x][i].fi*(pp - p + 1);
        p = pp + 1;
        if(pp == R) break;
    }
    ans += sum * f;
}
void upr(int x, int f) {
    LL sum = 0;
    for(int i = 0, p = x, pp; i < myl[x].size(); ++i) {
        if(myl[x][i].se < L) pp = L;
        else pp = myl[x][i].se;
        sum += (LL)myl[x][i].fi*(p - pp + 1);
        p = pp - 1;
        if(pp == L) break;
    }
    ans += sum * f;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        block = sqrt(n);
        for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]), belong[i] = (i-1)/block+1;
        init_ans();
        scanf("%d", &q);
        for(int i = 1; i <= q; ++i) {
            scanf("%d%d", &cw[i].l, &cw[i].r); cw[i].id = i;
        }
        /*for(int i = 1; i <= n; ++i) {
            for(auto x: myl[i]) {
                printf("[%d %d] ", x.fi, x.se);
            }
            printf("\n");
        }
        for(int i = 1; i <= n; ++i) {
            for(auto x: myr[i]) {
                printf("[%d %d] ", x.fi, x.se);
            }
            printf("\n");
        }*/
        sort(cw + 1, cw + q + 1, cmp);
        L = 1, R = 0;
        ans = 0;
        for(int i = 1; i <= q; ++i) {
            while(R < cw[i].r) upr(++R, 1);
            while(R > cw[i].r) upr(R--, -1);
            while(L < cw[i].l) upl(L++, -1);
            while(L > cw[i].l) upl(--L, 1);
            ANS[cw[i].id] = ans;
        }
        for(int i = 1; i <= q; ++i) printf("%lld\n", ANS[i]);
    }
    return 0;
}
