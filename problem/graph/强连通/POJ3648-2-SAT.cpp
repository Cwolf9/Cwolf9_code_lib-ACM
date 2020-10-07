/*
**全网唯一真题解**
**链接**
传送门: [here](http://poj.org/problem?id=3648)
**题意**
$n(30)$对夫妻，其中第0对夫妻为新婚，其他人是来参加婚礼的。现在有一个长桌只有两边能坐人，每边
有$n$个位置。规定所有夫妻不能坐在同一边。现在有$m$对不和谐关系，拥有不和谐关系的两个人不能同时
坐在妻子对立面。输出任意一种合法座位安排解。
**思路**
为了决定座位顺序，定义和主人公妻子在同一边的人的状态为选中，在主公人妻子对立面的人状态为不选中
所以第0对妻子必选中，第0对丈夫必不选中
一共有2*n个人，每个人有两个状态，选中或者不选中。所以一共有4*n个点
定义：a表示选中，a'表示不选中
若x必选中，建图为：x'->x
若x必不选中，建图为：x->x'
若x与y为一对夫妻，建图为：x->y', x'->y, y->x', y'->x
若x与y有不和谐关系，建图为：x'->y, y'->x
判断合法性：
tarjan缩点，如果x和x'在同一强联通中则无解。
但是这还不够，因为可能还有某对点不能同时不被选中且在同一联通块中，但是你不能说这种情况也无解，因为他们可能被同时选中，这样是合法的。
那就只能在生成解的时候判定。
输出一组合法解：
缩点建新图，连反边。
拓扑序染色，若当前点没有被染色，则选择该点并染为蓝色，并将与其矛盾的点及其子孙染为红色。
最后所有蓝色顶点集合为一组合法解。
将其子孙也染色红色的过程我目前只会当拓扑序完成后，dfs暴力染色。
应该正常性是全网最高的吧，如有问题，务必指出。
**备注**
其实只需要2*n个点不需要4*n个点
*/

// #pragma comment(linker, "/STACK:102400000,102400000")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize(3,"Ofast","inline")
// #pragma GCC optimize("Ofast,no-stack-protector")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
// #include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <assert.h>
using namespace std;
typedef long long LL;
bool Finish_read;
template <class T>
inline void read(T &x) {
    Finish_read = 0;
    x = 0;
    int f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        if (ch == EOF) return;
        ch = getchar();
    }
    while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    x *= f;
    Finish_read = 1;
}
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for (register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for (register int i = (s), LIM=(t); i >= LIM; --i)
#define GKD                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
/*================Header Template==============*/
const int mod = 1e9 + 7;
const int maxn = 3000 + 5;
const int maxe = 2e6 + 5;
const int MXN = 3000 + 5;
int n, m;
int id[MXN][2];
vector<int> mp[MXN], mp2[MXN];
int qltNum, qltMap[MXN], du[MXN], inde, dfn[MXN], low[MXN];
int stk[MXN], top, ins[MXN], col[MXN];
vector<int> conflict[MXN];
queue<int> Q;
//wife:0 husband: 1
#ifndef ONLINE_JUDGE
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
//tarjan缩点
void dfs(int u, int ba) {
    dfn[u] = low[u] = ++ inde;
    stk[++top] = u;
    ins[u] = 1;
    for(int i = 0, v; i < mp[u].size(); ++i) {
        v = mp[u][i];
        if(dfn[v] == 0) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }else if(ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        ++ qltNum;
        int v;
        do {
            v = stk[top --];
            ins[v] = 0;
            qltMap[v] = qltNum;
        }while(u != v);
    }
}
//逆图拓扑序
void tuopu() {
    rep(i, 1, qltNum + 1) {
        if(du[i] == 0) Q.push(i);
    }
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        if(col[u] == 0) {
            col[u] = 1;//1表示选，-1表示不选
            for(int j = 0, v; j < conflict[u].size(); ++j) {//选了u，与其矛盾的必然不能选
                v = conflict[u][j];
                col[v] = -1;
            }
        }
        for(int j = 0, v; j < mp2[u].size(); ++j) {
            v = mp2[u][j];
            -- du[v];
            if(du[v] == 0) {
                if(col[u] == -1) col[v] = -1;//-1标记需要传递
                Q.push(v);
            }
        }
    }
}
//传递-1标记
void gocolor(int u) {
    dfn[u] = 1;
    col[u] = -1;
    for(int i = 0, v; i < mp2[u].size(); ++i) {
        v = mp2[u][i];
        if(dfn[v] == 0) gocolor(v);
    }
}
bool check() {
    bool f = true;
    rep(i, 0, n << 2) {
        if(!dfn[i]) dfs(i, 0);
    }
    rep(i, 1, n << 1) {
        if(qltMap[id[i][0]] == qltMap[id[i][1]]) {//同时选和不选矛盾
            f = false;
            break;
        }else {
            conflict[qltMap[id[i][0]]].push_back(qltMap[id[i][1]]);
            conflict[qltMap[id[i][1]]].push_back(qltMap[id[i][0]]);
        }
    }
    rep(i, 0, n << 2) {
        for(int j = 0, v; j < mp[i].size(); ++j) {
            v = mp[i][j];
            if(qltMap[i] != qltMap[v]) {
                mp2[qltMap[v]].push_back(qltMap[i]);
            }
            int tv = (v >= n + n?v - n - n : v);
            int ti = (i >= n + n?i - n - n : i);
            if(ti == tv) continue;
            if(qltMap[ti] == qltMap[tv]) {
                //不能同时选，但可以同时不选
            }else {//不能同时选的矛盾
                conflict[qltMap[ti]].push_back(qltMap[tv]);
                conflict[qltMap[tv]].push_back(qltMap[ti]);
            }
        }
    }
    //删掉重边
    rep(i, 0, qltNum) {
        my_unique(mp2[i + 1]);
        for(int j = 0, v; j < mp2[i + 1].size(); ++j) {
            v = mp2[i + 1][j];
            ++ du[v];
        }
    }
    tuopu();
    rep(i, 0, n << 2) dfn[i] = 0;
    rep(i, 1, qltNum + 1) {
        if(col[i] == -1 && dfn[i] == 0) gocolor(i);
    }
    //判断所有不能同时选的点是否被同时选中了，判断合法性
    assert(col[qltMap[id[0][1]]] == 1);
    rep(i, 1, n) {
        assert(col[qltMap[id[i * 2][0]]] == col[qltMap[id[i * 2 + 1][1]]]);
        if(col[qltMap[id[i * 2][0]]] == col[qltMap[id[i * 2 + 1][0]]] && col[qltMap[id[i * 2 + 1][0]]] == 1) {
            f = false;
        }
        if(col[qltMap[id[i * 2][0]]] == col[qltMap[id[i * 2][1]]] || col[qltMap[id[i * 2 + 1][0]]] == col[qltMap[id[i * 2 + 1][1]]]) {
            f = false;
        }
    }
    rep(i, 0, n << 2) {
        for(int j = 0, v; j < mp[i].size(); ++j) {
            v = mp[i][j];
            int tv = (v >= n + n?v - n - n : v);
            int ti = (i >= n + n?i - n - n : i);
            if(ti == tv) continue;
            if(col[qltMap[ti]] == col[qltMap[tv]] && col[qltMap[tv]] == 1) f = false;
        }
        if(!f) break;
    }
    return f;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    read(n), read(m);
    while(n + m) {
        qltNum = top = inde = 0;
        while(!Q.empty()) Q.pop();
        rep(i, 0, n << 2) {
            col[i] = du[i] = ins[i] = dfn[i] = low[i] = qltMap[i] = 0;
            mp[i].clear();
            mp2[i].clear();
            conflict[i].clear();
        }
        //为了决定座位顺序，定义和主人公妻子在同一边的人的状态为选中，在主公人妻子对立面的人状态为不选中
        //[0, 2*n)表示n对妻子和丈夫（妻子为偶数丈夫为奇数）的不选中状态
        //[2*n,4*n)表示n对妻子和丈夫（妻子为偶数丈夫为奇数）的选中状态
        //i 与 i + 2*n表示同一个人
        rep(i, 0, n << 1) {
            id[i][0] = i;
            id[i][1] = i + n + n;
            if(i % 2 == 1 && i > 1) {
                rep(j, 0, 2) {//丈夫妻子只能选中一个且必须选中一个
                    mp[id[i][j]].push_back(id[i - 1][j^1]);
                    mp[id[i - 1][j]].push_back(id[i][j^1]);
                }
            }
        }
        mp[id[0][0]].push_back(id[0][1]);//主人公妻子必选
        mp[id[1][1]].push_back(id[1][0]);//主人公丈夫必不选
        rep(i, 0, m) {
            int a, c;
            char b, d;
            scanf("%d%c%d%c", &a, &b, &c, &d);
            a = a * 2 + (b == 'h');
            c = c * 2 + (d == 'h');
            if((a ^ 1) == c || a == 0 || c == 0) continue;
            mp[id[a][0]].push_back(id[c][1]);//不能同时不选
            mp[id[c][0]].push_back(id[a][1]);
        }
        // rep(i, 0, n << 2) {
        //     for(int v: mp[i]) {
        //         cout << i << " " << v << endl;
        //     }
        // }
        if(check()) {
            rep(i, 1, n) {
                // assert(col[qltMap[id[i * 2][0]]] == col[qltMap[id[i * 2 + 1][1]]]);
                if(col[qltMap[id[i * 2][0]]] == col[qltMap[id[0][1]]]) {
                    printf("%dh", i);
                }else {
                    printf("%dw", i);
                }
                if(i != n - 1) printf(" ");
            }
            printf("\n");
        }else printf("bad luck\n");
        read(n), read(m);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}