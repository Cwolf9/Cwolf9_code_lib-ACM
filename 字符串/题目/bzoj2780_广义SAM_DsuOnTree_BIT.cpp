#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 30
#define mk make_pair
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef pair<int, int> pii;
inline LL read() {
    LL x = 0;int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(LL x) {
    if (x == 0) {putchar('0'), putchar('\n');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template<class T>T big(const T &a1, const T &a2) { return a1 > a2 ? a1 : a2; }
template<typename T, typename ...R>T big(const T &f, const R &...r) { return big(f, big(r...)); }
template<class T>T sml(const T &a1, const T &a2) { return a1 < a2 ? a1 : a2; }
template<typename T, typename ...R>T sml(const T &f, const R &...r) { return sml(f, sml(r...)); }
void debug_out() { cerr << '\n'; }
template<typename T, typename ...R>void debug_out(const T &f, const R &...r) {cerr << f << " ";debug_out(r...);}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
 
#define print(x) write(x);
 
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 998244353;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 5e5 + 5;
const int MXE = 5e6 + 6;
 
int n, m;
char s[MXN];
int sum[MXN], pre[MXN];
struct Suffix_Automaton {
    static const int maxn = 5e5 + 105;
    //basic
//    map<char,int> nex[maxn * 2];
    int nex[maxn*2][26];
    int link[maxn * 2], len[maxn * 2];
    int last, cnt;
    LL tot_c;//不同串的个数
    void clear() {
        tot_c = 0;
        last = cnt = 1;
        link[1] = len[1] = 0;
//        nex[1].clear();
        memset(nex[1], 0, sizeof(nex[1]));
    }
    void add(int c, int id) {
        int p = last;
        int np = ++cnt;
//        nex[cnt].clear();
        memset(nex[cnt], 0, sizeof(nex[cnt]));
        len[np] = len[p] + 1;
        last = np;
        while (p && !nex[p][c])nex[p][c] = np, p = link[p];
        if (!p)link[np] = 1, tot_c += len[np] - len[link[np]];
        else {
            int q = nex[p][c];
            if (len[q] == len[p] + 1)link[np] = q, tot_c += len[np] - len[link[np]];
            else {
                int nq = ++cnt;
                len[nq] = len[p] + 1;
//                nex[nq] = nex[q];
                memcpy(nex[nq], nex[q], sizeof(nex[q]));
                link[nq] = link[q];
                link[np] = link[q] = nq;
                sum[nq] = sum[q] , pre[nq] = pre[q];
                tot_c += len[np] - len[link[np]];
                while (nex[p][c] == q)nex[p][c] = nq, p = link[p];
            }
        }
        for(p = np; p && pre[p] != id; p = link[p]) pre[p] = id, ++ sum[p];
    }
} sam;
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
//    int Tim = read();
    n = read(), m = read();
    sam.clear();
    for(int i = 1; i <= n; ++i) {
        sam.last = 1;
        scanf("%s", s);
        int ln = strlen(s);
        for(int j = 0; j < ln; ++j) sam.add(s[j] - 'a', i);
    }
    while(m --) {
        scanf("%s", s);
        int u = 1, ln = strlen(s);
        for(int i = 0; i < ln; ++i) u = sam.nex[u][s[i] - 'a'];
        printf("%d\n", sum[u]);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0*clock()/CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}



const int MXN = 2e5 + 5;
const int MXE = 4e5 + 6;

int n, m;
char s[MXE];
int sum[MXN], pre[MXN];
set<int> orz[MXN];
vector<int> mp[MXN];
struct Suffix_Automaton {
    static const int maxn = 2e5 + 105;
    //basic
//    map<char,int> nex[maxn * 2];
    int nex[maxn*2][26];
    int link[maxn * 2], len[maxn * 2];
    int last, cnt;
    LL tot_c;//不同串的个数
    void clear() {
        tot_c = 0;
        last = cnt = 1;
        link[1] = len[1] = 0;
//        nex[1].clear();
        memset(nex[1], 0, sizeof(nex[1]));
    }
    void add(int c, int id) {
        int p = last;
        int np = ++cnt;
//        nex[cnt].clear();
        memset(nex[cnt], 0, sizeof(nex[cnt]));
        len[np] = len[p] + 1;
        last = np;
        orz[np].insert(id);
        while (p && !nex[p][c])nex[p][c] = np, p = link[p];
        if (!p)link[np] = 1, tot_c += len[np] - len[link[np]];
        else {
            int q = nex[p][c];
            if (len[q] == len[p] + 1)link[np] = q, tot_c += len[np] - len[link[np]];
            else {
                int nq = ++cnt;
                len[nq] = len[p] + 1;
//                nex[nq] = nex[q];
                memcpy(nex[nq], nex[q], sizeof(nex[q]));
                link[nq] = link[q];
                link[np] = link[q] = nq;
                tot_c += len[np] - len[link[np]];
                while (nex[p][c] == q)nex[p][c] = nq, p = link[p];
            }
        }
//        for(p = np; p && pre[p] != id; p = link[p]) pre[p] = id, ++ sum[p];
    }
} sam;
set<int>::iterator sit;
void dfs(int u) {
    for(int i = 0, v; i < (int)mp[u].size(); ++ i) {
        v = mp[u][i];
        dfs(v);
        if((int)orz[v].size() > (int)orz[u].size()) swap(orz[u], orz[v]);
        for(sit = orz[v].begin(); sit != orz[v].end(); ++ sit) orz[u].insert(*sit);
    }
    sum[u] = (int)orz[u].size();
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
//    int Tim = read();
    n = read(), m = read();
    sam.clear();
    for(int i = 1; i <= n; ++i) {
        sam.last = 1;
        scanf("%s", s);
        int ln = strlen(s);
        for(int j = 0; j < ln; ++j) sam.add(s[j] - 'a', i);
    }
    for(int i = 2; i <= sam.cnt; ++i) mp[sam.link[i]].push_back(i);
    dfs(1);
    while(m --) {
        scanf("%s", s);
        int u = 1, ln = strlen(s);
        for(int i = 0; i < ln; ++i) u = sam.nex[u][s[i] - 'a'];
        printf("%d\n", sum[u]);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0*clock()/CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}



const int MXN = 4e5 + 5;
const int MXE = 4e5 + 6;

int n, m;
char s[MXE];
int sum[MXN], pre[MXN], bit[MXN];
vector<int> mp[MXN], orz[MXN];
int did[MXN], rid[MXN], lid[MXN], inde;
void bit_add(int x, int v, int N) {
    while(x <= N) {
        bit[x] += v;
        x += lowbit(x);
    }
}
int bit_query(int x) {
    if(x < 0) return 0;
    int res = 0;
    while(x) {
        res += bit[x];
        x -= lowbit(x);
    }
    return res;
}
struct Suffix_Automaton {
    static const int maxn = 2e5 + 105;
    //basic
//    map<char,int> nex[maxn * 2];
    int nex[maxn*2][26];
    int link[maxn * 2], len[maxn * 2];
    int last, cnt;
    void clear() {
        last = cnt = 1;
        link[1] = len[1] = 0;
//        nex[1].clear();
        memset(nex[1], 0, sizeof(nex[1]));
    }
    void add(int c, int id) {
        int p = last;
        int np = ++ cnt;
//        nex[cnt].clear();
        memset(nex[cnt], 0, sizeof(nex[cnt]));
        len[np] = len[p] + 1;
        last = np;
        orz[np].push_back(id);
        while (p && !nex[p][c]) nex[p][c] = np, p = link[p];
        if (!p) link[np] = 1;
        else {
            int q = nex[p][c];
            if (len[q] == len[p] + 1) link[np] = q;
            else {
                int nq = ++cnt;
                len[nq] = len[p] + 1;
//                nex[nq] = nex[q];
                memcpy(nex[nq], nex[q], sizeof(nex[q]));
                link[nq] = link[q];
                link[np] = link[q] = nq;
                while (nex[p][c] == q)nex[p][c] = nq, p = link[p];
            }
        }
//        for(p = np; p && pre[p] != id; p = link[p]) pre[p] = id, ++ sum[p];
    }
} sam;
struct lp {
    int l, r, id;
}cw[MXN];
void dfs(int u) {
    did[u] = ++ inde, rid[inde] = u;
    for(int i = 0, v; i < (int)mp[u].size(); ++ i) {
        v = mp[u][i];
        dfs(v);
    }
    lid[u] = inde;
}
bool cmp(const lp&a,const lp&b) {
    if(a.r != b.r) return a.r < b.r; return a.l < b.l;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
//    int Tim = read();
    n = read(), m = read();
    sam.clear();
    for(int i = 1; i <= n; ++i) {
        sam.last = 1;
        scanf("%s", s);
        int ln = strlen(s);
        for(int j = 0; j < ln; ++j) sam.add(s[j] - 'a', i);
    }
    for(int i = 2; i <= sam.cnt; ++i) mp[sam.link[i]].push_back(i);
    dfs(1);
    for(int i = 1; i <= m; ++i) {
        scanf("%s", s);
        int u = 1, ln = strlen(s);
        for(int j = 0; j < ln; ++j) u = sam.nex[u][s[j] - 'a'];
        cw[i].id = i, cw[i].l = did[u], cw[i].r = lid[u];
        if(u == 1) cw[i].l = cw[i].r = -1, sum[i] = 0;
//        debug(cw[i].l, cw[i].r)
    }
    sort(cw + 1, cw + 1 + m, cmp/*[](const lp&a,const lp&b){ if(a.r != b.r) return a.r < b.r; return a.l < b.l;}*/);
    int j = 1;
    while(cw[j].l == -1 && j <= m) ++ j;
    for(int i = 2; i <= inde; ++i) {
        for(int j = 0, x; j < (int)orz[rid[i]].size(); ++j) {
            x = orz[rid[i]][j];
            bit_add(i, 1, sam.cnt);
            if(pre[x]) bit_add(pre[x], -1, sam.cnt);
            pre[x] = i;
        }
        while(j <= m && cw[j].r <= i) {
            sum[cw[j].id] = bit_query(cw[j].r) - bit_query(cw[j].l - 1);
            ++ j;
        }
    }
    for(int i = 1; i <= m; ++i) printf("%d\n", sum[i]);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0*clock()/CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
