#include<bits/stdc++.h>
#define o2(x) (x)*(x)
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int mod = 1000000007;
const int INF = 0x3f3f3f3f;
const int MXN = 2e4 + 7;
int n, m;
vector<int> adj[MXN];
int k[MXN], e[MXN], flag;
double A[MXN], B[MXN], C[MXN];
/*
https://www.cnblogs.com/kuangbin/archive/2012/10/02/2710606.html
[点我点我](http://acm.hdu.edu.cn/showproblem.php?pid=4035)
**题意：**
有n(1e4)个房间，由n-1条隧道连通起来，实际上就形成了一棵树.
从结点1出发，开始走，在每个结点i都有3种可能：
1.被杀死，回到结点1处（概率为ki）
2.找到出口，走出迷宫 （概率为ei）
3.和该点相连有m条边，随机走一条
4.$k1=e1=0$
求：走出迷宫所要走的边数的期望值。
**解析：**
列出方程，对方程进行化简，迭代递推。
因为每个节点还可能从父节点转移过来，所以需要记录从父节点转移过来的系数，从上递推
的时候刚好可以化简掉。
1号节点：
$E[1] = A1*E[1] + B1*0 + C1;$
$ans = E[1] = C1/(1 - A1);$
叶子结点：
$E[i] = ki*E[1] + ei*0 + (1-ki-ei)*(E[father[i]] + 1);$
$= ki*E[1] + (1-ki-ei)*E[father[i]] + (1-ki-ei);$
非叶子结点：（m为与结点相连的边数）
$E[i] = ki*E[1] + ei*0 + (1-ki-ei)/m*( E[father[i]]+1 + ∑( E[child[i]]+1 ) );$
$= ki*E[1] + (1-ki-ei)/m*E[father[i]] + (1-ki-ei)/m*∑(E[child[i]]) + (1-ki-ei);$
令：$E[i] = Ai*E[1] + Bi*E[father[i]] + Ci;$
$∑(E[child[i]])=∑Aj*E[1]+∑Bj*E[i]+∑Cj$

$E[i]=ei*E[1] + (1-ki-ei)/m*E[father[i]] + (1-ki-ei)/m*(∑Aj*E[1]+∑Bj*E[i]+∑Cj) + (1-ki-ei)$
$(1-(1-ki-ei)/m*∑Bj)E[i]=(ki+(1-ki-ei)/m*∑Aj)*E[1] + (1-ki-ei)/m*E[father[i]]+(1-ki-ei)/m*∑Cj+(1-ki-ei)$
从叶子到根推出ABC系数即可，当A[1]趋近于1则无解。
卡精度。
**AC_CODE**
[点我点我](https://github.com/Cwolf9/Cwolf9_code_lib-ACM/blob/master/problem/DP/%E6%A6%82%E7%8E%87/hdu4035_%E6%A0%91%E4%B8%8A%E6%A6%82%E7%8E%87DP%E8%BF%AD%E4%BB%A3%E6%B3%95.cpp)

*/
const double eps = 1e-9;
void dfs(int u, int ba) {
    if(e[u] && flag == 0) flag = 1;//是否可以跑出去
    int leaf = 1, m = 0;
    double a = 0, b = 0, c = 0;
    if(k[u] + e[u] != 100) {
        m = adj[u].size();
        for(int v: adj[u]) {
            if(v == ba) continue;
            dfs(v, u);
            leaf = 0, a += A[v], b += B[v], c += C[v];
        }
    }
    if(leaf) {
        A[u] = k[u]/100.0;
        B[u] = 1.0 - (k[u] + e[u])/100.0;
        C[u] = B[u];
    }else {
        double tmp = 1 - (1.0 - (k[u] + e[u])/100.0)/m * b;
        // if(tmp < eps) flag = -1;//注释不注释这句都行
        A[u] = (k[u]/100.0 + (1.0 - (k[u] + e[u])/100.0)/m*a) / tmp;
        B[u] = (1.0 - (k[u] + e[u])/100.0)/m / tmp;
        C[u] = ((1.0 - (k[u] + e[u])/100.0) + (1.0 - (k[u] + e[u])/100.0)/m*c) / tmp;
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim, cas = 0;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%d", &n);
        rep(i, 1, n + 1) adj[i].clear();
        flag = 0;
        rep(i, 1, n) {
            int a, b;
            scanf("%d%d", &a, &b);
            adj[a].emplace_back(b);
            adj[b].emplace_back(a);
        }
        rep(i, 1, n + 1) scanf("%d%d", k + i, e + i);
        dfs(1, 0);
        double ans = C[1] / (1 - A[1]);
        printf("Case %d: ", ++ cas);
        if(fabs(1.0 - A[1]) < eps || flag <= 0) printf("impossible\n");
        else {
            printf("%.6f\n", C[1] / (1.0 - A[1]));
        }
    }
    return 0;
}
