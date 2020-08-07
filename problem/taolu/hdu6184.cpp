/*
给出一张无向图，求 4 个点构成两个有公共边的三元环的方案数。

给无向边定向，从度数小的连向度数大的（度数相同看编号），然后每次枚举一条
边，枚举这条边两个端点出去的点，如果有相同的点就找到了三元环. 由于是从度
数小的连向度数大的点，所以不会有环（即每个三元环只统计到一遍），并且每个
点的出度不超过 m√m，复杂度也是 O(m√m) ，但是常数小。
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 62
#define mk make_pair
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define clr(a,b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<int, LL> piL;
inline LL read(){
    LL x=0;int f=0;char ch=getchar();
    while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x=f?-x:x;
}
inline void write(LL x) {
    if(x==0){putchar('0'),putchar('\n');return;}
    if(x < 0) {putchar('-');x=-x;}
    static char s[23];int l = 0;
    while(x!=0)s[l++]=x%10+48,x/=10;
    while(l)putchar(s[--l]);
    putchar('\n');
}
int lowbit(int x) {return x&(-x);}
template<class T> T big(const T& a1,const T& a2) { return a1>a2?a1:a2; }
template<typename T, typename ...R> T big (const T& f,const R& ...r) { return big(f, big (r...)); }
template<class T> T sml(const T& a1,const T& a2) { return a1<a2?a1:a2; }
template<typename T, typename ...R> T sml (const T& f,const R& ...r) { return sml(f, sml (r...)); }
void debug_out() { cerr << '\n'; }
template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cerr << f << " "; debug_out (r...); }
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

#define print(x) write(x);

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 998244353 ;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 1e5 + 7;
const int MXE = 2e5 + 7;
int n, m;
int tot;
int du[MXN], last[MXN], vis[MXN];
int head[MXN];
int A[MXE], B[MXE], ans[MXE];
struct lp {
    int v, nex, id;
}cw[MXE];
inline void add_edge(int a, int b, int id) {
    cw[++tot].v = b, cw[tot].nex = head[a], cw[tot].id = id;
    head[a] = tot;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = 0, cas = 0;
    while(~scanf("%d%d", &n, &m)) {
        tot = 0;
        for(int i = 0; i <= n; ++i) head[i] = -1, du[i] = vis[i] = 0;
        for(int i = 1; i <= m; ++i) {
            ans[i] = 0;
            A[i] = read(), B[i] = read();
            ++ du[A[i]], ++ du[B[i]];
        }
        for(int i = 1; i <= m; ++i) {
            if(du[A[i]] > du[B[i]] || (du[A[i]] == du[B[i]] && A[i] > B[i])) add_edge(B[i], A[i], i);
            else add_edge(A[i], B[i], i);
        }
        tim = 1;
        for(int i = 1, a, b; i <= m; ++i) {
            a = A[i], b = B[i];
            for(int j = head[a]; ~j; j = cw[j].nex) {
                vis[cw[j].v] = tim, last[cw[j].v] = cw[j].id;
            }
            for(int j = head[b]; ~j; j = cw[j].nex) {
                if(vis[cw[j].v] == tim) {
                    ++ ans[i], ++ ans[cw[j].id], ++ ans[last[cw[j].v]];
                }
            }
            ++ tim;
        }
        LL ANS = 0;
        for(int i = 1; i <= m; ++i) ANS += (LL) ans[i] * (ans[i] - 1) >> 1;
        printf("%lld\n", ANS);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
