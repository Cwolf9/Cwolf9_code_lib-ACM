/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6799)
**题意**
一个长度为$n(1e5)$的字符串仅包含'(',')'和'*'，'*'是通配符也可以删除，输出一个长度最短
且字典序最小的匹配括号序列，可以为空，可能无解。
**思路**
为'(','*'维护栈，用')'去匹配，匹配优先级：优先编号大的'('，其次编号小的'('，其次
编号小的'*'，最后是编号大的'*'。最后用'*'匹配多余的'('即可。
**备注**
写了第二种稍微麻烦一点的方法，必须要保证优先用编号大的'('不然会过不去。
第二种方法：用一个栈不区分'('和'*'去匹配')'，匹配完之后记录一下栈里剩下的'('的数量，
若等于0，则将匹配了的'*'向前移位，因为前面可能有没有匹配的'*'，向前移位字典序更小。
若大于0，则将匹配过的'*'用前面的'('替换，尽可能用编号大的替换，然后将匹配的'*'向前移
位，然后用后面的'*'匹配多余的'('即可。
提供数据：
1
(****((((())*))
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
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
const int MXN = 2e5 + 3;
int n, m, k;
int stk[MXN], top, stk2[MXN], top2, bt2;
char s[MXN];
int is[MXN];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        top = top2 = bt2 = 0;
        int flag = 1, num = 0;
        for(int i = 1; i <= n; ++i) is[i] = 0;
        for(int i = 1; i <= n; ++i) {
            if(s[i] == ')') {
                if(top == 0 && bt2 == top2) {
                    flag = 0;
                    break;
                }
                if(top) is[stk[top]] = i, -- top;
                else if(bt2 < top2) is[stk2[bt2 + 1]] = i, ++ bt2;
            }else {
                if(s[i] == '(') stk[++top] = i;
                else stk2[++top2] = i;
            }
        }
        for(int i = top2; i > bt2; --i) {
            if(top && stk[top] < stk2[i]) {
                s[stk2[i]] = ')';
                -- top;
            }
        }
        if(flag == 0 || top) printf("No solution!\n");
        else {
            for(int i = 1; i <= n; ++i) {
                if(s[i] == '('||s[i] == ')') putchar(s[i]);
                else if(is[i] && s[i] == '*') putchar('(');
            }
            putchar('\n');
        }
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}

/*
int n, m, k;
pii stk[MXN];
int top;
int is[MXN];
char s[MXN];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        top = 0;
        int flag = 1, num = 0;
        for(int i = 1; i <= n; ++i) is[i] = 0;
        for(int i = 1; i <= n; ++i) {
            if(s[i] == ')') {
                if(top == 0) {
                    flag = 0;
                    break;
                }
                is[stk[top].se] = i;
                if(stk[top].fi == '(') -- num;
                -- top;
            }else {
                stk[++top] = mk(s[i], i);
                if(s[i] == '(') ++ num;
            }
        }
        int cnt2 = 0;
        vector<int> vt;
        if(num == 0) {
            for(int i = 1; i <= n; ++i) {
                if(is[i] == 0 && s[i] == '*') vt.eb(i);
                else if(is[i] > 0 && s[i] == '*' && cnt2 < (int)vt.size()) {
                    is[vt[cnt2]] = is[i];
                    ++ cnt2;
                    is[i] = 0;
                    vt.eb(i);
                }
            }
        }else if(num > 0) {//左括号没用完
            for(int i = 1; i <= top; ++i) {
                if(stk[i].fi == '(') is[stk[i].se] = -1;
            }
            vector<int> vs;
            for(int i = 1; i <= n; ++i) {
                if(is[i] == -1) vs.eb(i);
                else if(is[i] > 0 && s[i] == '*' && !vs.empty()) {
                    is[vs.back()] = is[i];
                    is[i] = 0;
                    -- num;
                    vs.pop_back();
                }
            }
            for(int i = 1; i <= n; ++i) {
                if(is[i] == 0 && s[i] == '*') vt.eb(i);
                else if(is[i] > 0 && s[i] == '*' && cnt2 < (int)vt.size()) {
                    is[vt[cnt2]] = is[i];
                    ++ cnt2;
                    is[i] = 0;
                    vt.eb(i);
                }
            }
            if(!vs.empty()) {
                for(int i = n; i >= 1; --i) {
                    if(is[i] == 0 && s[i] == '*' && !vs.empty() && i > vs.back()) {
                        s[i] = ')';
                        -- num;
                        vs.pop_back();
                    }
                }
                if(num > 0) flag = 0;
            }
        }else flag = 0;
        if(flag == 0) printf("No solution!\n");
        else {
            for(int i = 1; i <= n; ++i) {
                if(s[i] == '(' || s[i] == ')') putchar(s[i]);
                else if(is[i] && s[i] == '*') putchar('(');
            }
            putchar('\n');
        }
    }
    // system("pause");
    return 0;
}
*/