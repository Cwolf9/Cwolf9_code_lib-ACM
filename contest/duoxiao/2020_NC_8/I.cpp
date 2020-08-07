/*
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/5673/I)
**题意**
$n\le 1e5$
$n$对$(a,b)$，每对中只能选择一个数字，每个数字只能选择一次，问最多选多少个数字。
**思路**
把数字当成图中的点，点对当作边，一个连通图中由超过n-1条边则全选，否则只有一个不能选到
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<stack>
#include<map>
#include<iostream>
#include<assert.h>
#include <algorithm>

#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 62
#define mk make_pair
#define eb push_back
#define all(x) (x).begin(), (x).end()
#define clr(a,b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, int> pLi;
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
//template<typename T, typename ...R> T big (const T& f,const R& ...r) { return big(f, big (r...)); }
template<class T> T sml(const T& a1,const T& a2) { return a1<a2?a1:a2; }
//template<typename T, typename ...R> T sml (const T& f,const R& ...r) { return sml(f, sml (r...)); }
#ifndef ONLINE_JUDGE
void debug_out() { cout << '\n'; }
template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cout << f << " "; debug_out (r...); }
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#endif
#define print(x) write(x);

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 1e9 + 6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 1e6 + 7;
int n;
int fa[MXN], sz[MXN], vis[MXN], sn[MXN];
unordered_map<int,int> mp;
int Fi(int x) {
    return fa[x] == x?x:fa[x] = Fi(fa[x]);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read(), cas = 0;
    while(tim --) {
        n = read();
        mp.clear();
        int ide = 0, ans = 0;
        for(int i = 1; i <= n + n; ++i) {
            fa[i] = i, sz[i] = 0, vis[i] = 0;
            sn[i] = 1;
        }
        for(int i = 1; i <= n; ++i) {
            int a = read(), b = read(), ida, idb;
            if(mp.find(a) == mp.end()) ida = ++ ide, mp[a] = ide;
            else ida = mp[a];
            if(mp.find(b) == mp.end()) idb = ++ ide, mp[b] = ide;
            else idb = mp[b];
            int pa = Fi(ida), pb = Fi(idb);
            // debug(pa, pb)
            if(pa == pb) {
                ++ sz[pa];
            }else {
                fa[pa] = pb;
                sz[pb] += sz[pa] + 1;
                sn[pb] += sn[pa];
            }
        }
        // debug(ide)
        for(int i = 1; i <= ide; ++i) {
            int pa = Fi(i);
            if(vis[pa] == 0) {
                vis[pa] = 1;
                // debug(sz[pa], sn[pa])
                if(sz[pa] >= sn[pa]) ans += sn[pa];
                else ans += sn[pa] - 1;
            }
        }
        printf("Case #%d: %d\n", ++ cas, ans);
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
