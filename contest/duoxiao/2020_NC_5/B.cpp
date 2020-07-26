/*
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/5670/B)
**题意**
[xor最小生成树](https://codeforces.com/contest/888/problem/G)
[Boruvka算法](https://www.cnblogs.com/lher/p/10393232.html)
任意两点之间的边权的路径边权值的异或和，求mst。
**思路**
求1到任意点的路径权值异或和，问题转化为任意两点之间的边权等于
两点点权异或和，xor mst裸题。
**做法1：启发式合并**
920 ms
点权做trie树，遍历整个trie树，若某点左右儿子内都有权值，则遍历size小的
一方，再另一方查询最小异或和。
复杂度：$O(n*log(n)*30)$

**做法2：逐位合并贪心**
561 ms
把点权从小到大排序，然后从最高位开始，按照每一位的01状态分割成两边(同时再递归下去)，
对于这一层遍历该为为0的一边的点权建立trie树，再遍历另一边点权求min xor sum。
注意若从小到大排序则必须从最高为开始求解。
复杂度：$O(n*log(n)*log(n))$

**做法3：暴搜贪心+玄学难卡**
623 ms 这个有点玄学复杂度，而且很难卡， hdu6625
点权做trie树，遍历整个trie树，若某点左右儿子内都有权值，则左右儿子
两棵字典树同时往下走，求两棵字典树最小xor sum。
复杂度：$O(能过)$
**备注**
听说dreamoon出hdu6625的灵感就是来源本题cf888G
*/

#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <assert.h>
#include<unordered_map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
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
#define clr(a, b) memset((a), (b), sizeof((a)))
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
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
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {
        putchar('0');
        if (f) putchar('\n');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[23];
    int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {
    return a1 > a2 ? a1 : a2;
}
template <class T>
T sml(const T &a1, const T &a2) {
    return a1 < a2 ? a1 : a2;
}
template <typename T, typename... R>
T big(const T &f, const R &... r) {
    return big(f, big(r...));
}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {
    return sml(f, sml(r...));
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {
    printf(ptout, f);
    putchar('\n');
}
template <typename T, typename... R>
void print(const T &f, const R &... r) {
    printf(ptout, f);
    putchar(' ');
    print(r...);
}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n;
vector<pii> mp[MXN];
int ar[MXN];
const int MXN_T = 5e6 + 5;
struct AC_Auto {
    struct Trie {
        int nex[2];
    } cw[MXN_T];
    int siz, rt;
    vector<int> tson[MXN_T];
    void init() {
        siz = rt = 0;
        clr(cw[siz].nex, -1);
    }
    void add_str(int x, int id) {
        rt = 0;
        for (int i = 30, now; i >= 0; --i) {
            now = (x >> i) & 1;
            if (cw[rt].nex[now] == -1) {
                cw[rt].nex[now] = ++ siz;
                clr(cw[siz].nex, -1);
            }
            rt = cw[rt].nex[now];
            // tson[rt].eb(id);//solve_qfs
        }
    }
    int query(int rt, int x, int d) {
        int ans = 0;
        for (int i = d, now; i >= 0; --i) {
            now = (x >> i) & 1;
            if (cw[rt].nex[now] == -1) rt = cw[rt].nex[!now], ans += (1 << i);
            else rt = cw[rt].nex[now];
        }
        return ans;
    }
    int query2(int x) {
        rt = 0;
        int ans = 0;
        for (int i = 30, now; i >= 0; --i) {
            now = (x >> i) & 1;
            if (cw[rt].nex[now] == -1) rt = cw[rt].nex[!now], ans += (1 << i);
            else rt = cw[rt].nex[now];
        }
        return ans;
    }
    //920 ms
    int64 solve_qfs(int rt, int dep) {//0, 30
        int64 ans = 0;
        if(cw[rt].nex[0] != -1) ans += solve_qfs(cw[rt].nex[0], dep - 1);
        if(cw[rt].nex[1] != -1) ans += solve_qfs(cw[rt].nex[1], dep - 1);
        if(cw[rt].nex[0] != -1 && cw[rt].nex[1] != -1) {
            int l = cw[rt].nex[0], r = cw[rt].nex[1], tmp = (1 << 30) - 1;
            if((int)tson[l].size() > (int)tson[r].size()) swap(l, r);
            for(int x: tson[l]) {
                tmp = min(tmp, query(r, ar[x], dep - 1));
            }
            ans += tmp + (1 << dep);
        }
        return ans;
    }
    //561 ms
    int64 solve_deptx(int l, int r, int dep) {//1, n, 30
        if(l >= r || dep == -1) return 0;
        int64 ans = 0;
        int mid = l - 1;
        while(mid < r && (ar[mid+1]>>dep) % 2 == 0) ++ mid;
        ans += solve_deptx(l, mid, dep - 1) + solve_deptx(mid + 1, r, dep - 1);
        if(mid - l + 1 > 0 && r - mid > 0) {
            init();
            int tmp = (1 << 30) - 1;
            for(int i = l; i <= mid; ++i) add_str(ar[i], i);
            for(int i = mid + 1; i <= r; ++i ) tmp = min(tmp, query2(ar[i]));
            ans += tmp;
        }
        return ans;
    }
    int check_min(int l, int r, int dep) {
        if(dep == -1) return 0;
        int ans = (1 << 30) - 1;
        for(int i = 0; i < 2; ++ i) {
            if(cw[l].nex[i] != -1 && cw[r].nex[i] != -1) ans = min(ans, check_min(cw[l].nex[i], cw[r].nex[i], dep - 1));
        }
        if(ans == (1 << 30) - 1) {
            for(int i = 0; i < 2; ++ i) {
                if(cw[l].nex[i] != -1 && cw[r].nex[!i] != -1) ans = min(ans, (1 << dep) + check_min(cw[l].nex[i], cw[r].nex[!i], dep - 1));
            }
        }
        return ans;
    }
    //623 ms 这个有点玄学复杂度，而且很难卡， hdu6625
    int64 solve_mi(int rt, int dep) {//0, 30
        int64 ans = 0;
        if(cw[rt].nex[0] != -1) ans += solve_mi(cw[rt].nex[0], dep - 1);
        if(cw[rt].nex[1] != -1) ans += solve_mi(cw[rt].nex[1], dep - 1);
        if(cw[rt].nex[0] != -1 && cw[rt].nex[1] != -1) {
            ans += check_min(cw[rt].nex[0], cw[rt].nex[1], dep - 1) + (1 << dep);
        }
        return ans;
    }
}ac;

void dfs(int u, int ba) {
    for(pii V: mp[u]) {
        if(V.fi == ba) continue;
        ar[V.fi] = ar[u] ^ V.se;
        dfs(V.fi, u);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    for(int i = 1, a, b, c; i < n; ++i) {
        a = read() + 1, b = read() + 1, c = read();
        mp[a].eb(mk(b, c));
        mp[b].eb(mk(a, c));
    }
    dfs(1, 0);
    ac.init();
    for(int i = 1; i <= n; ++i) {
        // ar[i] = read();
        ac.add_str(ar[i], i);
    }
    // sort(ar + 1, ar + 1 + n);
    printf("%lld\n", ac.solve_mi(0, 30));
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
