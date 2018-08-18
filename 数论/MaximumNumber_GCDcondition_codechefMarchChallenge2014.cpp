//MaximumNumber_GCDcondition_codechefMarchChallenge2014.cpp
//https://www.cnblogs.com/danceonly/p/4029818.html

/*
最近做到的一道蛮有意思的题目(codechef现在的题目确实很赞了)

题意 ：中文题面　(cc的一大好处就是有中文翻译，嘿嘿)

区间Max = max{a_i|gcd(a_i, g) > 1 && x <= i <= y}

做法 ： 一开始我是用分块做的，复杂的O(m * sqrt(n) * C) C 是所含不同素数的个数， C大概最大只有6或7吧

然后裸裸的T了，换了一个姿势：用线段树或者RMQ把查询从sqrt(n) -> log(n)， 这里最初的想法就是直接对于每个素数开一个线段树，但是这样预处理空间和时间都过不了

，但是考虑的其实n个数都分解一下只有C*n个数，那么的话我们可以用动态开线段树的方法，当然这个我不会- - ！，还有一种比较好的实现方式是对于每个素数都建立一段段的RMQ，额，， 具体就是比如 a[] : 2, 3, 4, 6 那么我建立一个RMQ为 ：2 4 6 3 6，前三个是2的倍数，后两个是3的倍数，，并通过一些其他辅助操作可以使得复杂度降为log(n)。
*/

分块做法(TLE) :
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
inline int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
const int MAXN = 100005;
int check[MAXN] = {0};
const int M = 320;
vector<int> prime[MAXN];
int ptot = 0;
int n, m;
int blocks[1<<9][10005];
int a[MAXN];
void init(int N) {
    for (int i = 2; i <= N; i++) {
        if (!check[i]) {
            for (int j = 1; j * i <= N; j++) {
                prime[j * i].push_back(i);
                check[i * j] = 1;
            }
            check[i] = ++ ptot;
        }
    }
}
vector<int> G[MAXN];
int query(int x, int y, int e) {
    return upper_bound(G[e].begin(), G[e].end(), y) - lower_bound(G[e].begin(), G[e].end(), x);
}

int main() {
    init(100000);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        int e = i / M;
        for (int j = 0; j < prime[a[i]].size(); j++) {
            int v = prime[a[i]][j];
            blocks[e][check[v]] = max(blocks[e][check[v]], a[i]);
        }
        G[a[i]].push_back(i);
    }
    while (m --) {
        int g, x, y;
        scanf("%d%d%d", &g, &x, &y);
        int l = x / M, r = y / M, Max = -1;
        if (l == r) {
            for (int i = x; i <= y; i++) {
                if (gcd(g, a[i]) > 1) Max = max(Max, a[i]);
            }
        }else {
            for (int i = x; i < (l+1) * M; i++) {
                if (gcd(g, a[i]) > 1) Max = max(Max, a[i]);
            }
            for (int i = r * M; i <= y; i++) {
                if (gcd(g, a[i]) > 1) Max = max(Max, a[i]);
            }
            for (int i = 0; i < prime[g].size(); i++) {
                int v = prime[g][i];
                for (int j = l + 1; j <= r - 1; j++) {
                    if (blocks[j][v] > 0)Max = max(Max, blocks[j][v]);
                }
            }
        }
        if (Max == -1) printf("-1 -1\n");
        else {
            printf("%d %d\n", Max, query(x, y, Max));
        }
    }
    return 0;
}

RMQ做法:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int MAXN = 100005;
struct RMQ {
    int a[MAXN * 7][20];
    int log2[MAXN * 7];
    void init(int A[], int N) {
        for (int i = 0; i < MAXN * 7; i++) log2[i] = (i == 0 ? -1 : log2[i >> 1] + 1);
        for (int i = 1; i <= N; i++) a[i][0] = A[i];
        for (int j = 1; (1 << j) <= N; j++) {
            for (int i = 1; i + (1<<j) - 1 <= N; i++) {
                a[i][j] = max(a[i][j-1], a[i + (1<<(j-1))][j - 1]);
            }
        }
    }
    int rmq(int L, int R) {
        if (R < L) return 0;
        int k = log2[R - L + 1];
        return max(a[L][k], a[R-(1<<k)+1][k]);
    }
}AC;
vector<int> prime[MAXN];
int check[MAXN] = {0}, ptot = 0;
void init(int N) {
    for (int i = 2; i <= N; i++) {
        if (!check[i]) {
            for (int j = 1; j * i <= N; j++) {
                prime[j * i].push_back(i);
                check[i * j] = 1;
            }
            check[i] = ++ ptot;
        }
    }
}
vector<int> G[MAXN];
int query(int x, int y, int e) {
    return upper_bound(G[e].begin(), G[e].end(), y) - lower_bound(G[e].begin(), G[e].end(), x);
}
int n, m;
int b[MAXN * 7];
int a[MAXN];
int pre[MAXN];
vector<int> gao[MAXN];

int main() {
    init(100000);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        for (int j = 0; j < prime[a[i]].size(); j++) {
            int v = check[prime[a[i]][j]];
            gao[v].push_back(i);
        }
        G[a[i]].push_back(i);
    }
    int tot = 0;
    for (int i = 1; i <= ptot; i++) {
        if (gao[i].size() == 0) continue;
        pre[i] = tot;
        for (int j = 0; j < gao[i].size(); j++) {
            b[++ tot] = a[gao[i][j]];
        }
    }
    AC.init(b, tot);
    while (m--) {
        int g, x, y, Max = -1;
        scanf("%d%d%d", &g, &x, &y);
        for (int i = 0; i < prime[g].size(); i++) {
            int v = check[prime[g][i]];
            int r = upper_bound(gao[v].begin(), gao[v].end(), y) - gao[v].begin() + pre[v] + 1;
            int l = lower_bound(gao[v].begin(), gao[v].end(), x) - gao[v].begin() + pre[v] + 1;
            r --;
            if (r >= l)Max = max(Max, AC.rmq(l, r));
        }
        if (Max == -1) {
            printf("-1 -1\n");
        }else {
            printf("%d %d\n", Max, query(x, y, Max));
        }
    }
    return 0;
}