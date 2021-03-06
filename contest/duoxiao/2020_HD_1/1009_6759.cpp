/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6759)
**题意**
有$n(1e5)$辆车在数轴正半轴，每个车在初始位置在$p_i$、初速度$0$，加速度$a_i$，可能
有车信息完全相同，问有多少辆车存在某一个时刻它走在当之无愧的第一名，也就是没有并列。
**思路**
1.把所有车子$unique$一下，相同车子记录他的个数(当然如果它个数大于$1$，我是不会算它的贡献滴)
2.用单调栈预处理一下，去掉永远不可能在第一位的车子。
3.用$rs[]$记录每个车子下一个要超过的车子的编号
4.优先队列保存每个车子$i$超过车子$rs[i]$的时间，优先队列每次取出时间最短的那个车子
6.判断他是否超车到了第一位，若是就记录，并且若这是最初排在最后一位的车子就break结束
5.然后去掉$rs[i]$这个车子，因为他还没到第一就已经被车子$i$超车了
6.复杂度$O(n*log(n))$
**备注**
去年多校也有一个车子过红绿灯贪心题HDU Vacation
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <assert.h>
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
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
const int MXN = 1e5 + 5;
const int MXE = 8e6 + 5;
const int MR = 1000000001;
int n, m, k;
class car{
    public:
    int p, a, id, cnt;
}cw[MXN];
int stk[MXN], top, rs[MXN], is[MXN], rm[MXN];
bool cmp(const car &A, const car &B) {
    if(A.p != B.p) return A.p < B.p;
    return A.a > B.a;
}
class node {
    public:
    int64 d, a;
    int id;
    node(){}
    node(int64 D, int64 A, int Id):d(D),a(A),id(Id){}
    bool operator<(const node&B) const {
        if(d * B.a != B.d * a) return d * B.a > B.d * a;
        else return a < B.a;
    }
}n1, n2;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while (tim--) {
        n = read();
        for(int i = 1; i <= n; ++i) {
            cw[i].p = read();
            cw[i].a = read();
            cw[i].id = i;
            cw[i].cnt = 1;
        }
        if(n == 1) {
            printf("1\n");
            continue;
        }
        sort(cw + 1, cw + 1 + n, cmp);
        int ti = 1, flag = 1;
        if(cw[n].p == cw[n-1].p) flag = 0;
        for(int i = 2; i <= n; ++i) {
            if(cw[i].p == cw[i-1].p && cw[i].a < cw[i-1].a) ;
            //else if(cw[i].p == cw[i-1].p && cw[i].a == cw[i-1].a) ++ cw[ti].cnt;
            else if(cw[i].p == cw[ti].p && cw[i].a == cw[ti].a) ++ cw[ti].cnt;
            else cw[++ ti] = cw[i];
        }
        n = ti;
        top = 0;
        for(int i = 1; i <= n; ++i) {
            while(top && cw[i].a >= cw[stk[top]].a) -- top;
            stk[++top] = i;
        }
        ti = 0;
        for(int i = 1; i <= top; ++i) {
            cw[++ti] = cw[stk[i]];
        }
        n = ti;
        //前面是预处理
        for(int i = 1; i <= n; ++i) {
            // debug(cw[i].p, cw[i].a, cw[i].cnt)
            is[i] = rm[i] = 0;
            cw[i].id = i;
        }
        //if(flag) 
            if(cw[n].cnt == 1) is[n] = 1;
        if(n > 1) {
            int64 D, A;
            priority_queue<node> Q;
            for(int i = 1; i < n; ++i) {
                rs[i] = i + 1;
                D = cw[rs[i]].p - cw[i].p;
                A = cw[i].a - cw[rs[i]].a;
                // debug(D, A)
                Q.push(node(D, A, i));
            }
            int ed = 0;
            rs[n] = ed;
            while(!Q.empty()) {
                n1 = Q.top();
                Q.pop();
                if(rm[n1.id]) continue;
                if(rs[n1.id] == ed) {
                    // debug(n1.id, cw[n1.id].cnt)
                    if(cw[n1.id].cnt == 1) is[n1.id] = 1;
                    ed = n1.id;
                    if(n1.id == 1) break;
                }else if(rs[rs[n1.id]] == 0) {
                    rm[rs[n1.id]] = 1;
                    rs[n1.id] = rs[rs[n1.id]];
                    D = cw[rs[n1.id]].p - cw[n1.id].p;
                    A = cw[n1.id].a - cw[rs[n1.id]].a;
                    Q.push(node(D, A, n1.id));
                }else {
                    rm[rs[n1.id]] = 1;
                    rs[n1.id] = rs[rs[n1.id]];
                    D = cw[rs[n1.id]].p - cw[n1.id].p;
                    A = cw[n1.id].a - cw[rs[n1.id]].a;
                    Q.push(node(D, A, n1.id));
                }
            }
        }
        int cnt = 0;
        for(int i = 1; i <= n; ++i) if(is[i] && cw[i].cnt == 1) cnt += cw[i].cnt;
        printf("%d\n", cnt);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
