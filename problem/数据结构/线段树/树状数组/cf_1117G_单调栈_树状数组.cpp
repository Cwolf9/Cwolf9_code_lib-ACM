#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define eb emplace_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;


const int INF = 0x3f3f3f3f;
const LL mod = 998244353;
const int MXN = 1e6 + 7;
int n, q;
int ar[MXN], ls[MXN], rs[MXN];
int stk[MXN];
LL ans[MXN];
std::vector<int> vs[MXN];
struct FenwickTree {
    LL BIT[MXN], N;
    void init(int n) {N = n+3;for(int i = 0; i <= n+3; ++i) BIT[i] = 0;}
    int lowbit(int x) {return x&(-x);}
    void add(int x, int val) {for(;x <= N; x += lowbit(x)) BIT[x] += val;}
    LL query(int x) {LL ans = 0; for(; x; x -= lowbit(x)) ans += BIT[x]; return ans;}
}bit1, bit2;
void go() {
    for(int i = 1; i <= q; ++i) vs[ls[i]].eb(i);
    int top = 0;
    bit1.init(n), bit2.init(n);
    for(int i = n, j; i >= 1; --i) {
        while(top && ar[stk[top]] < ar[i]) -- top;
        j = n + 1; if(top) j = stk[top];
        stk[++top] = i;
        bit1.add(j, j-i);
        bit1.add(i, -i+1); bit1.add(j, i-1);
        bit2.add(i, 1); bit2.add(j, -1);
        //printf("[%d %d]\n", i, j);
        for(auto id: vs[i]) ans[id] += (bit1.query(rs[id])+rs[id]*bit2.query(rs[id]));
    }
}
int main(int argc, char const *argv[]){
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]);
    for(int i = 1; i <= q; ++i) scanf("%d", &ls[i]);
    for(int i = 1; i <= q; ++i) scanf("%d", &rs[i]);
    go();
    //for(int i = 1; i <= q; ++i) printf("*%lld%c", ans[i], i==q?'\n':' ');
    for(int i = 1; i <= n; ++i) vs[i].clear();
    reverse(ar+1, ar+n+1);
    for(int i = 1; i <= q; ++i) ls[i] = n+1-ls[i], rs[i] = n+1-rs[i];
    for(int i = 1; i <= q; ++i) swap(ls[i], rs[i]);
    go();
    for(int i = 1; i <= q; ++i) printf("%lld%c", ans[i]-(rs[i]-ls[i]+1), i==q?'\n':' ');
    return 0;
}