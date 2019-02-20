/*#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define pb push_back
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;


const int INF = 0x3f3f3f3f;
const LL mod = 998244353;
const int MXN = 2e5 + 7;
map<pii, int> mp;
pii ar[MXN];
int flag, n, k;
void dfs(int id, int x, int y) {
    if(id == n) {
        ar[n] = make_pair(x, y);
        flag = 1;
        return ;
    }
    pii t;
    for(int i = 1; i <= k; ++i) {
        if(i == x) continue;
        for(int j = k; j >= 1; --j) {
            if(i == j || j == y || mp[make_pair(i, j)]) continue;
            mp[make_pair(i, j)] = 1;
            ar[id] = make_pair(i, j);
            dfs(id+1, i, j);
            if(flag) return ;
            mp[make_pair(i, j)] = 0;
        }
    }
}
int main(int argc, char const *argv[]){
    scanf("%d%d", &n, &k);
    for(int i = 2; i <= k; ++i) {
        mp[make_pair(1, i)] = 1;
        ar[1] = make_pair(1, i);
        dfs(1, 1, i);
        mp[make_pair(1, i)] = 0;
        if(flag) break;
    }
    if(flag == 0) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    //for(int i = 1; i <= n; ++i) printf("%d %d\n", ar[i].fi, ar[i].se);
    return 0;
}*/
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
const int MXN = 3e5 + 7;
int n, nd;
int ar[MXN];
int fa[MXN], rk[MXN];
std::vector<int> son[MXN];
int dp[MXN][3], a[3];
void dfs(int u, int ba) {
    dp[u][ar[u]] = 1;
    for(auto v: son[u]) {
        if(v == ba) continue;
        dfs(v, u);
        for(int i = 0; i < 3; ++i) dp[u][i] += dp[v][i];
    }
}
void check(int u, int ba) {
    for(auto v: son[u]) {
        if(v == ba) continue;
        if((dp[v][1] && dp[v][2]) || (a[1] - dp[v][1] && a[2] - dp[v][2])) ++ nd;
        check(v, u);
    }
}
int main(int argc, char const *argv[]){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]), ++a[ar[i]];
    for(int i = 1, a, b; i < n; ++i) {
        scanf("%d%d", &a, &b);
        son[a].push_back(b);
        son[b].push_back(a);
    }
    dfs(1, -1);
    check(1, -1);
    printf("%d\n", n-1-nd);
    return 0;
}
1117G
My solution:

Let l[i] be the biggest number x such that x < i and a[x-1] > a[i] , consider a[0] = inf . 
r[i] be the smallest number x such that x > i and a[x+1] > a[i] ,consider a[n+1] = inf .

The answer for [L,R] is sum(min(r[i],R)-max(l[i],L)+1) for L <= i <= R

Solve the problem offline by using Fenwick tree . 
(solve min(r[i],R) from R large to R small , max(l[i],L) from L small to L large )
