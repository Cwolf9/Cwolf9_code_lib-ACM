// #pragma comment(linker, "/STACK:102400000,102400000")
// //#include<bits/stdc++.h>
// #include <ctime>
// #include <iostream>
// #include <assert.h>
// #include <vector>
// #include <queue>
// #include <cstdio>
// #include <algorithm>
// #include <cstring>
// #include <set>
// #define fi first
// #define se second
// #define endl '\n'
// #define o2(x) (x)*(x)
// #define BASE_MAX 31
// #define mk make_pair
// #define eb push_back
// #define SZ(x) ((int)(x).size())
// #define all(x) (x).begin(), (x).end()
// #define clr(a, b) memset((a),(b),sizeof((a)))
// #define iis std::ios::sync_with_stdio(false); cin.tie(0)
// #define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
// using namespace std;
// #pragma optimize("-O3")
// typedef long long LL;
// typedef unsigned long long uLL;
// typedef pair<int, int> pii;
// // mt19937 rng(time(NULL));
// // mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// // mt19937_64 generator(std::clock());
// // shuffle(arr, arr + n, generator);
// inline LL read() {
//     LL x = 0;int f = 0;
//     char ch = getchar();
//     while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
//     while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
//     return x = f ? -x : x;
// }
// inline void write(LL x, bool f) {
//     if (x == 0) {putchar('0'); if(f)putchar('\n');return;}
//     if (x < 0) {putchar('-');x = -x;}
//     static char s[23];
//     int l = 0;
//     while (x != 0)s[l++] = x % 10 + 48, x /= 10;
//     while (l)putchar(s[--l]);
//     if(f)putchar('\n');
// }
// int lowbit(int x) { return x & (-x); }
// template<class T>T big(const T &a1, const T &a2) { return a1 > a2 ? a1 : a2; }
// template<class T>T sml(const T &a1, const T &a2) { return a1 < a2 ? a1 : a2; }
// template<typename T, typename ...R>T big(const T &f, const R &...r) { return big(f, big(r...)); }
// template<typename T, typename ...R>T sml(const T &f, const R &...r) { return sml(f, sml(r...)); }
// void debug_out() { cout << '\n'; }
// template<typename T, typename ...R>void debug_out(const T &f, const R &...r) {cout << f << " ";debug_out(r...);}
// #define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
// #define LLDO
// #ifdef LLDO
// const char ptout[] = "%lld";
// #else
// const char ptout[] = "%d";
// #endif
// template<typename T>
// void print(const T &f) {printf(ptout, f);putchar('\n');}
// template<typename T, typename ...R>
// void print(const T &f, const R &...r) {printf(ptout, f);putchar(' ');print(r...);}

// const int HMOD[] = {1000000009, 1004535809};
// const LL BASE[] = {1572872831, 1971536491};
// const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
// const int INF = 0x3f3f3f3f;
// const int mod = 1e9 + 7;
// const int MOD = 1e9 + 7;//998244353
// const int MXN = 1e5 + 5;
// const int MXE = 2e6 + 6;
// int n;
// LL m, k;
// int ans[MXN];
// int ar[MXN], sz[MXN];
// LL dp[MXN];
// vector<pii > mp[MXN];
// void dfs(int u, int ba) {
//     sz[u] = ar[u];
//     for(pii V: mp[u]) {
//         int v = V.fi;
//         LL w = V.se;
//         if(v == ba) continue;
//         dfs(v, u);
//         sz[u] += sz[v];
//         dp[u] += dp[v] + w * sz[v];
//     }
// }
// void dfs2(int u, int ba, LL w) {
//     // debug(u, dp[u])
//     if(ba) {
//         dp[u] = dp[ba] + w * (m - 2 * sz[u]);
//     }
//     for(pii V: mp[u]) {
//         int v = V.fi;
//         if(v == ba) continue;
//         dfs2(v, u, V.se);
//     }
// }
// int main() {
//     n = read();
//     for(int i = 1; i <= n; ++i) {
//         ar[i] = read(), m += ar[i];
//     }
//     for(int i = 2, a, b, c; i <= n; ++i) {
//         a = read(), b = read(), c = read();
//         mp[a].eb(mk(b, c));
//         mp[b].eb(mk(a, c));
//     }
//     dfs(1, 0);
//     dfs2(1, 0, 0);
//     LL ans = INFLL;
//     for(int i = 1; i <= n; ++i) {
//         ans = min(ans, dp[i]);
//     }
//     print(ans);
//     return 0;
// }
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <stack>
#include <map>
#include <set>
#include <vector>
#include <queue>
#define mem(p,k) memset(p,k,sizeof(p));
#define rep(a,b,c) for(int a=b;a<c;a++)
#define pb push_back
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define inf 0x6fffffff
#define ll long long
using namespace std;
int m,n,minn,maxx,x,y,k,cur;
ll dis[210000],sum[210000];
struct edg{
    int to,next;
}edge[410000];
ll head[210000],bk[210000],cnt,dep[210000],ans[210000];
void add(int f,int t){
    edge[cnt].to=t;
    edge[cnt].next=head[f];
    head[f]=cnt++;
}
 
void build(int f){
    struct edg p;
    for(int i=head[f];~i;i=edge[i].next){
            p=edge[i];
            if(!bk[p.to]){
                dis[p.to]=dis[f]+1;
                bk[p.to]=1;
                build(p.to);
                sum[f]+=sum[p.to];
            }
    }
    return ;
}
 
void dfs(int f,int d){
    struct edg p;
    for(int i=head[f];~i;i=edge[i].next){
            p=edge[i];
            if(!bk[p.to]){
                bk[p.to]=1;
                dep[d]=p.to;
                if(f!=1)ans[p.to]=ans[f]+sum[dep[d/2+1]]-2*sum[p.to];
                else ans[p.to]=ans[1];
                dfs(p.to,d+1);
            }
    }
}
 
void solve(){
    mem(head,-1);
    for(int i=0;i<n-1;i++){
        int s,e;
        scanf("%d%d",&s,&e);
        add(s,e);
        add(e,s);
    }
    for(int i=1;i<=n;i++)sum[i]=1,bk[i]=0;
    dis[1]=0;
    bk[1]=1;
    build(1);
 
    ans[1]=0;
    for(int i=2;i<=n;i++)ans[1]+=dis[i];
    //cout<<ans[1]<<endl;
    mem(bk,0);
    bk[1]=1;
    dep[0]=1;
    dfs(1,1);
 
    ll maxx=1e15;
    for(int i=1;i<=n;i++){
        //cout<<i<<"=="<<ans[i]<<endl;
        if(maxx>ans[i]){
            maxx=ans[i];
            printf("%d*\n", i);
        }
    }
 
    printf("%lld\n",maxx);
}
 
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        cnt=0;
        scanf("%d",&n);
        solve();
    }
 
    return 0;
}