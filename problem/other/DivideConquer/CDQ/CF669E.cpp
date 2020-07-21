/*
动态开点树状数组

CDQ分治
*/
#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int MXN = 1e5 + 5;
int n, m, k;
map<int, int> mp[MXN], rey;
int Opt[MXN], X[MXN], Y[MXN];
void add(int id, int x, int v, int N) {
    while(x <= N) {
        mp[id][x] += v;
        x += (x&(-x));
    }
}
int query(int id, int x) {
    int ans = 0;
    while(x > 0) {
        ans += mp[id][x];
        x -= (x&(-x));
    }
    return ans;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = 1;
    // scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        int id = 0, id2 = 0;
        vector<int> vs;
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", &Opt[i], &X[i], &Y[i]);
            if(rey[Y[i]] == 0) rey[Y[i]] = ++id, Y[i] = id;
            else Y[i] = rey[Y[i]];
            vs.emplace_back(X[i]);
        }
        sort(vs.begin(), vs.end());
        vs.erase(unique(vs.begin(), vs.end()), vs.end());
        id2 = vs.size() + 1;
        for(int i = 0; i < n; ++i) {
            // printf("%d %d %d\n", Opt[i], X[i], Y[i]);
            X[i] = lower_bound(vs.begin(), vs.end(), X[i]) - vs.begin() + 1;
            if(Opt[i] == 1) {
                add(Y[i], X[i], 1, id2);
            }else if(Opt[i] == 2) {
                add(Y[i], X[i], -1, id2);
            }else {
                printf("%d\n", query(Y[i], X[i]));
            }
        }
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

/*
#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
typedef long long LL;
 
const int MXN = 2e6 + 5;
const int MXE = 1e7 + 3e6 + 6;
const int INF = 0x3f3f3f3f;
 
int n, m, k;
struct lp {
    int x, tim, flag, ans, ip;
}cw[MXN], temp[MXN];
int ar[MXN], ans[MXN];
 
int bit[MXN];
int lowbit(int x){return (x&(-x));}
void ADD(int x,int c,int N){for(; x <= N; x += lowbit(x)) bit[x]+=c;}
int QUERY(int x){int ANS = 0;for(; x; x -= lowbit(x)) ANS+=bit[x];return ANS;}
 
void solve(int l, int r) {
    if(l == r) return ;
    int mid = (l + r) >> 1;
    solve(l, mid); solve(mid + 1, r);
    int j = l;
    for(int i = mid + 1; i <= r; ++i) {
        for(; j <= mid && cw[j].tim <= cw[i].tim; ++j) {
            if(cw[j].flag == 1) ADD(cw[j].x, 1, k);
            else if(cw[j].flag == 2) ADD(cw[j].x, -1, k);
        }
        if(cw[i].flag == 3) cw[i].ans += QUERY(cw[i].x) - QUERY(cw[i].x-1);
    }
    for(-- j; j >= l; -- j) {
        if(cw[j].flag == 1) ADD(cw[j].x, -1, k);
        else if(cw[j].flag == 2) ADD(cw[j].x, 1, k);
    }
    int p1 = l, p2 = mid + 1, cnt = l;
    while(p1 <= mid && p2 <= r) {
        if(cw[p1].tim <= cw[p2].tim) temp[cnt++] = cw[p1], ++p1;
        else temp[cnt++] = cw[p2], ++p2;
    }
    while(p1 <= mid) temp[cnt++] = cw[p1], ++p1;
    while(p2 <= r) temp[cnt++] = cw[p2], ++p2;
    for(int i = l; i <= r; ++i) cw[i] = temp[i];
}
int main() {
    scanf("%d", &n);
    int totq = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &cw[i].flag, &cw[i].tim, &cw[i].x);
        if(cw[i].flag == 3) ++ totq;
        ar[i] = cw[i].x;
        cw[i].ip = totq;
    }
    sort(ar + 1, ar + 1 + n);
    k = unique(ar + 1, ar + 1 + n) - ar;
    for(int i = 1; i <= n; ++i) cw[i].x = lower_bound(ar + 1, ar + k, cw[i].x) - ar;
    solve(1, n);
    for(int i = 1; i <= n; ++i) if(cw[i].flag == 3) ans[cw[i].ip] = cw[i].ans;
    for(int i = 1; i <= totq; ++i) printf("%d\n", ans[i]);
    return 0;
}
*/