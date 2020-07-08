/*
链接：
https://vjudge.net/contest/381037#problem/O

题意：
n(1e6)
A，B两个人，每个节点有两个属性$a_i,b_i$，A先选一个节点，B选相邻下一个节点，交替选直到没法选。A想让$\sum (a_i-b_i)$最大，B想让$\sum (b_i-a_i)$最大。两人都足够聪明，问最后$\sum (a_i-b_i)$是多少。

思路：
在AB足够聪明的情况下，A要a-b最大值，答案是dp1[u][0]=min(\sum (a_i-b_i)) = ar[u]-br[u]-dp2[u][0]，在u的儿子中减去min(\sum b_i-a_i)也就是加上max(\sum a_i-b_i))，用最大的\sum a_i-b_i更新答案即可。dp2[u][0]也是用最大的$\sum b_i-a_i$更新答案。
换根DP时：双方最优策略下：对每个节点记录它向上路径中最小的$\sum(a_i-b_i)$=TMP[u]，min(dp1[u][0],TMP[u])是u为根时的答案。
为记录TMP[u]还需记录sta[u]表示u节点向上路径中最大的$\sum(a_i-b_i)$.

本题用最大值来更新最小值，和用最小值来更新最大值，答案是最小值，这有点博弈感觉把。

备注：
https://blog.csdn.net/qq_39599067/article/details/99442586
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <ctime>
#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template<class T>T big(const T &a1, const T &a2) { return a1 > a2 ? a1 : a2; }
template<class T>T sml(const T &a1, const T &a2) { return a1 < a2 ? a1 : a2; }
template<typename T, typename ...R>T big(const T &f, const R &...r) { return big(f, big(r...)); }
template<typename T, typename ...R>T sml(const T &f, const R &...r) { return sml(f, sml(r...)); }
void debug_out() { cout << '\n'; }
template<typename T, typename ...R>void debug_out(const T &f, const R &...r) {cout << f << " ";debug_out(r...);}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template<typename T>
void print(const T &f) {printf(ptout, f);putchar('\n');}
template<typename T, typename ...R>
void print(const T &f, const R &...r) {printf(ptout, f);putchar(' ');print(r...);}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;//998244353
const int MXN = 1e6 + 7;
const int MXE = 1e6 + 7;
int n, m;
int64 ar[MXN], br[MXN];
vector<int> mp[MXN];
int64 dp1[MXN][2], dp2[MXN][2], TMP[MXN];
int son[MXN][2], fa[MXN], num[MXN];
int64 ans;
void dfs1(int u, int ba) {//a - b的minsum, b - a的minsum
    dp1[u][0] = dp1[u][1] = INFLL;
    dp2[u][0] = dp2[u][1] = INFLL;
    fa[u] = ba;num[u] = 0;
    for(auto v: mp[u]) {
        if(v == ba) continue;
        dfs1(v, u);
        num[u]++;
        if(ar[u] - br[u] - dp2[v][0] < dp1[u][0]) {
            son[u][0] = v;
            dp1[u][1] = dp1[u][0];
            dp1[u][0] = ar[u] - br[u] - dp2[v][0];
        }else dp1[u][1] = sml(dp1[u][1], ar[u] - br[u] - dp2[v][0]);
        if(br[u] - ar[u] - dp1[v][0] < dp2[u][0]) {
            son[u][1] = v;
            dp2[u][1] = dp2[u][0];
            dp2[u][0] = br[u] - ar[u] - dp1[v][0];
        }else dp2[u][1] = sml(dp2[u][1], br[u] - ar[u] - dp1[v][0]);
    }
    if(num[u] == 0) dp1[u][0] = dp1[u][1] = ar[u] - br[u], dp2[u][0] = dp2[u][1] = br[u] - ar[u];
}
int64 tmp, sta[MXN];
void dfs2(int u, int ba) {
	for(auto v: mp[u]) {
		if(v == ba) continue;
		tmp = dp1[v][0];
		if(v == son[u][1]) {
			tmp = dp2[u][1];
		}else {
			tmp = dp2[u][0];
		}
		int aim = 4;
//		if(v == aim) debug(tmp, u, mp[u].size())
		if(u != 1) tmp = sml(tmp, -sta[u]);//a-b max
		if(num[u] == 1) {
		    if(num[v] == 0) ans = big(ans,  TMP[v] = ar[v] - br[v] + sta[u]);
		    else ans = big(ans, sml(dp1[v][0], TMP[v] = ar[v] - br[v] + sta[u]));
//		    debug(u, v, ans, dp1[v][0], ar[v] - br[v], sta[u])
		}
		else {
		    if(num[v] == 0) ans = big(ans, TMP[v] = ar[v] - br[v] - tmp);
		    else ans = big(ans, sml(dp1[v][0], TMP[v] = ar[v] - br[v] - tmp));
		}
//		if(v == aim) debug(tmp, sta[u], mp[v].size())
		if(v == son[u][0]) {
		    tmp = dp1[u][1];
		}else {
		    tmp = dp1[u][0];
		}// a-b max  b-a min
		if(num[u] == 1) sta[v] = ar[v] - br[v] + TMP[u];
		else {
		    if(u == 1) sta[v] = ar[v] - br[v] + tmp;
		    else sta[v] = ar[v] - br[v] + sml(tmp, TMP[u]);//a-b max b - a min
		}
//		debug(u, v, ans, son[u][1]);
		dfs2(v, u);
	}
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
//    freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read();
        for(int i = 1; i <= n; ++i) ar[i] = read(), mp[i].clear();
        for(int i = 1; i <= n; ++i) br[i] = read();
        for(int i = 1, a, b; i < n; ++i) {
            a = read(), b = read();
            mp[a].eb(b), mp[b].eb(a);
        }
        dfs1(1, 0);
        for(int i = 1; i <= n; ++i) {
//            printf("%d %d %lld %lld %lld %lld\n", son[i][0], son[i][1], dp1[i][0], dp1[i][1], dp2[i][0], dp2[i][1]);
        }
        sta[0] = -INFLL;
		TMP[1] = sta[1] = ar[1] - br[1];
		ans = dp1[1][0];
		dfs2(1, 0);//max minnum
		printf("%lld\n", ans);
    }
#ifndef ONLINE_JUDGE
//    cout << "time cost:" << 1.0*(clock())/CLOCKS_PER_SEC << "\n";
#endif
    return 0;
}
/*
6
7
-1 -1 -1 0 1 1 1
0 0 0 0 0 0 0
1 2
2 3
3 4
4 5
5 6
6 7
5
-100 1 -100 1 1
0 0 0 0 0
1 2
1 3
2 4
2 5
3
1 1 1
0 2 3
1 2
1 3
5
1 1 1 2 4
0 2 3 3 2
1 2
1 3
2 4
2 5
11
1 1 1 2 4 4 3 2 5 6 2
0 2 3 3 2 0 3 2 6 4 3
1 2
1 3
2 4
2 5
3 6
3 7
4 8
4 9
8 10
8 11
11
2 4 5 3 6 8 1 0 6 4 3
9 3 5 0 6 1 3 5 7 9 0
1 2
1 3
2 4
2 5
3 6
3 7
4 8
4 9
8 10
8 11
*/
