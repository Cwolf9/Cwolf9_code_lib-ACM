/*
**链接**
传送门: [here](https://codeforces.com/gym/102822/problem/C)
**题意**
建议先浏览一遍题面代码。
给你一段构建字典树的代码：每个节点随机赋予一个权值，保证每个点权值都不相同。
再给你$n(1e5)$个字符串及其执行$query$函数后的结果，问满足这些结果的字典树最少节点数量。
每组数据字符串长度和不超过$100000$。

**思路**
首先将字符串按照权值（即$query$后得到的答案）排序并依次插入进字典树。
对于具有相同权值字符串，他们返回答案的节点一定在字典树$rt$到$lca$路径上的某点处。
对于只有一个字符串的权值，其$lca$就是他自己的末尾节点。
将所有权值对应字符串集合的$lca$标记一下，可以肯定的是每个节点只能作为一种权值的$lca$。

假设有$m$个字符串权值相同，他们在$lca$后的出边是：$a,b,c,d$。
可以肯定的是这四条出边对应节点的子树内不能有其他权值的$lca$节点。
我们将$lca$这些出边对应的节点标记为不可能存在的节点，即$die[node]=1$。

确定一下无解情况：
- 两个字符串相同但是权值不同。
- 多个权值对应的$lca$是同一节点。
- $rt$到某个$lca$路径上存在$die$节点。

再来确定一下$dfs$贪心求解过程，遍历到节点$u$：
- 如果$u$的某条出边的子树内没有$lca$节点，这个子树全部扔掉。
- 如果$u$的某条出边的子树内有多个$lca$节点，那么节点$u$必须保留。
- 如果$u$存在若干条出边的子树内仅有$1$个$lca$节点：
 -- 如果$u$是$lca$节点，这些子树只需要保留一个节点即可，即$u$的儿子。
 -- 如果$u$不是$lca$节点，可以完全抛弃一个子树，剩余子树处理同上。

为什么这样贪心是对的呢？一条条解答：
- 这条出边子树内没有$lca$节点，我的$query$不会走到这里，当然可以全部抛弃掉呀。
- 如果节点$u$不保留，代表$u$的子树都不保留，那这对应两个$lca$的$query$势必会得到同一个答案才对，互相矛盾，所以$u$必须保留。
- 这里分了两个情况：
-- 这些子树内只有一个$lca$节点，那么我询问的时候提前结束肯定最优，也不会影响别人，所以只需要保留$u$的儿子。
-- 因为$u$不是$lca$，我可以把一个子树内的$lca$节点直接提到$u$来。

$over!$稍微复杂点的签到题罢了。

**备注**
下标写错找了一年bug。
```cpp
godie(st[sid[j]], len[sid[j]]);
---->
godie(st[j], len[j]);
想die哦。
```

**AC_CODE**
思路很简单，可惜我代码写的有点冗杂。
[here](https://github.com/Cwolf9/Cwolf9_code_lib-ACM/blob/master/problem/string/hash_manacher_trie/Gym102822C_Code_a_Trie.cpp)
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
using namespace std;
typedef long long int64;
typedef pair<int, int> pii;
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
                                                                               getchar(); return x = f ? -x : x;
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 5e5 + 5;
const int MXE = 1e6 + 5;
int n, m;
char s[MXN];
int st[MXN], len[MXN], val[MXN], sid[MXN];
int nex[MXN][26], cnt[MXN][2], nodeval[MXN], sum[MXN], fk[MXN], die[MXN];
int siz, lasnode, flag, ans;
int new_node() {
    ++ siz;
    clr(nex[siz], -1);
    nodeval[siz] = cnt[siz][0] = cnt[siz][1] = -1;
    sum[siz] = fk[siz] = die[siz] = 0;
    return siz;
}
void upd_lca(int rt, int l) {
    if(cnt[rt][1] != l) cnt[rt][0] = 1, cnt[rt][1] = l;
    else ++ cnt[rt][0];
    if(cnt[rt][0] >= cnt[lasnode][0]) lasnode = rt;
}
void add_str(int st, int len, int l, int val) {
    int rt = 0;
    rep(i, 0, len) {
        upd_lca(rt, l);
        int now = s[st + i] - 'a';
        if(nex[rt][now] == -1) nex[rt][now] = new_node();
        rt = nex[rt][now];
    }
    upd_lca(rt, l);
    if(nodeval[rt] != -1 && nodeval[rt] != val) flag = 0;//无解情况1
    nodeval[rt] = val;
}
void add_lca(int st, int len) {
    if(lasnode == 0) {
        if(fk[0]) flag = 0;//无解情况2
        fk[0] = 1;
        return;
    }
    int rt = 0;
    rep(i, 0, len) {
        int now = s[st + i] - 'a';
        rt = nex[rt][now];
        if(rt == lasnode) break;
    }
    if(fk[rt]) flag = 0;
    fk[rt] = 1;
}
void godie(int st, int len) {
    int rt = 0;
    rep(i, 0, len) {
        int now = s[st + i] - 'a';
        if(rt == lasnode) {
            die[nex[rt][now]] = 1;//不可能存在的节点
            break;
        }
        rt = nex[rt][now];
    }
}
void check(int rt) {
    sum[rt] = fk[rt];
    rep(i, 0, 26) {
        if(nex[rt][i] != -1) {
            check(nex[rt][i]);
            sum[rt] += sum[nex[rt][i]];
            if(sum[nex[rt][i]] == 0) nex[rt][i] = -1;//没有lca节点的子树可以直接扔掉
        }
    }
    if(die[rt] == 1 && sum[rt]) flag = 0;//无解情况3
}
void dfs(int rt) {
    vector<pii> vs;
    rep(i, 0, 26) {
        if(nex[rt][i] == -1) continue;
        if(sum[nex[rt][i]] == 0) nex[rt][i] = -1;
        else vs.eb(mk(sum[nex[rt][i]], i));
    }
    sort(all(vs));
    int lo = -1;
    rep(i, 0, (int)vs.size()) if(vs[i].fi == 1) lo = i;
    if(lo != -1) {
        if(fk[rt] == 0) nex[rt][vs[0].se] = -1;
        rep(i, 0, lo + 1) if(nex[rt][vs[i].se] != -1) clr(nex[nex[rt][vs[i].se]], -1);    
    }
    rep(i, lo + 1, (int)vs.size()) {
        dfs(nex[rt][vs[i].se]);
    }
    vs.clear(); vs.shrink_to_fit();
}
void getAns(int rt, int &ans) {
    ++ ans;
    rep(i, 0, 26) if(nex[rt][i] != -1) getAns(nex[rt][i], ans);
}
bool cmp(const int&a, const int&b) {
    return val[a] < val[b];
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("/home/cwolf9/CLionProjects/mtxt/in.txt", "r", stdin);
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
#endif
    int tim = read(), cas = 0;
    while(tim --) {
        printf("Case #%d: ", ++ cas);
        n = read();
        siz = -1, lasnode = 0, flag = 1, ans = 0;
        new_node();
        int lenl = 0;
        rep(i, 0, n) {
            scanf("%s%d", s + lenl, val + i);
            st[i] = lenl;
            len[i] = strlen(s + lenl);
            lenl += len[i];
            sid[i] = i;
        }
        sort(sid, sid + n, cmp);//把字符串按权值排序，sid对应真实下标
        int l = 0;
        rep(ti, 0, n) {
            int i = sid[ti], ni = sid[ti + 1];
            add_str(st[i], len[i], l, val[i]);
            // debug(i, val[i], val[ni])
            if(ti == n - 1 || val[i] != val[ni]) {
                // debug(lasnode)
                if(l != ti) {
                    rep(j, l, ti + 1) godie(st[sid[j]], len[sid[j]]);
                }
                add_lca(st[i], len[i]);
                l = ti + 1;
                lasnode = 0;
            }
            if(flag != 1) break;
        }
        check(0);
        if(flag == 0) printf("-1\n");
        else {
            dfs(0);
            getAns(0, ans);
            printf("%d\n", ans);
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}
