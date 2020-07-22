/*

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
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
    if (x == 0) {putchar('0');if (f) putchar('\n');return;}
    if (x < 0) { putchar('-');x = -x;}
    static char s[23];int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {return a1 > a2 ? a1 : a2;}
template <class T>
T sml(const T &a1, const T &a2) {return a1 < a2 ? a1 : a2;}
template <typename T, typename... R>
T big(const T &f, const R &... r) {return big(f, big(r...));}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {return sml(f, sml(r...));}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {cout << f << " ";debug_out(r...);}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {printf(ptout, f);putchar('\n');}
template <typename T, typename... R>
void print(const T &f, const R &... r) {printf(ptout, f);putchar(' ');print(r...);}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e6 + 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
char ss[MXN];
int st_str[MXN], word[MXN], slen[MXN], vis[MXN];
int64 ans;
const int MXN_T = 1e6 + 105;
const int CHAR_SIZE = 26;
struct AC_Auto {
    struct Trie {
        int nex[CHAR_SIZE];
        int fail, cnt, is, last, len, sz, inson;
    } cw[MXN_T];
    vector<int> ft[MXN];//fail tree
    int fsz[MXN];//fail tree's subtree size
    int siz, rt;
    void init() {
        siz = rt = 0;
        clr(cw[siz].nex, -1);
        cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
        cw[siz].last = 0;
        cw[siz].len = 0;
        cw[siz].sz = 0;
        cw[siz].inson = 0;
    }
    int idx(char c) {
        return c - 'a';
    }
    void add_str(char *s, int len, int id) {
        rt = 0;
        for (int i = 0, now; i < len; ++i) {
            now = idx(s[i]);
            if (cw[rt].nex[now] == -1) {
                cw[rt].nex[now] = ++siz;
                clr(cw[siz].nex, -1);
                cw[siz].fail = cw[siz].cnt = cw[siz].is = 0;
                cw[siz].last = 0;
                cw[siz].len = 0;
                cw[siz].sz = 0;
                cw[siz].inson = 0;
            }
            rt = cw[rt].nex[now];
            cw[rt].len = i + 1;
        }
        ++ cw[rt].is;
        word[id] = rt;
    }
    void build_ac() {
        queue<int> Q;
        Q.push(0);
        cw[0].fail = -1;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int i = 0, pos; i < CHAR_SIZE; ++i) {
                pos = cw[u].nex[i];
                if (~pos) {
                    assert(pos != -1);
                    if (u == 0) cw[pos].fail = u;
                    else {
                        assert(u != -1);
                        int v = cw[u].fail;
                        while (v != -1) {
                            if (cw[v].nex[i] != -1) {
                                cw[pos].fail = cw[v].nex[i];
                                break;
                            }
                            v = cw[v].fail;
                        }
                        if (v == -1) cw[pos].fail = 0;
                    }
                    //last[u] = val[f[u]] ? f[u] : last[f[u]];后缀链接，表示节点rt沿着失配指针往回走遇到的下一个单词节点编号
                    cw[pos].last = cw[cw[pos].fail].is?cw[pos].fail:cw[cw[pos].fail].last;
                    Q.push(pos);
                }else {//建新的边补全图（可选可不选,会改变遍历方式
                //    if(cw[u].fail >= 0) cw[u].nex[i] = cw[cw[u].fail].nex[i];
                //    else cw[u].nex[i] = 0;
                }
            }
        }
    }
    void dfs(int rt) {
        cw[rt].sz = cw[rt].is;
        for(int i = 0; i < 26; ++i) {
            if(cw[rt].nex[i] != -1) {
                dfs(cw[rt].nex[i]);
                cw[rt].sz += cw[cw[rt].nex[i]].sz;
            }
        }
    }
    void dfsf(int rt) {
        fsz[rt] = cw[rt].sz;
        for(int i = 0; i < 26; ++i) {
            if(cw[rt].nex[i] != -1) {
                dfsf(cw[rt].nex[i]);
                cw[rt].sz += cw[cw[rt].nex[i]].sz;
            }
        }
    }
    void get_first_ans() {
        dfs(0);
        for(int i = 1; i <= siz; ++i) ft[cw[i].fail].eb(i);
        dfsf(0);
        for(int i = 0; i < n; ++i) {
            ans += (int64)slen[i] * slen[i] % mod;
            if(ans >= mod) ans %= mod;
            rt = 0;
            for(int j = 0, now; j < slen[i]; ++j) {
                now = idx(ss[st_str[i] + j]);
                rt = cw[rt].nex[now];
                vis[rt] = i + 1;
            }
            int tmp = cw[rt].fail, las = 0;
            while(tmp > 0) {
                if(vis[tmp] != i + 1) ans += ;
            }
        }
    }
}aho;


int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    for(int i = 0; i < n; ++i) {
        scanf("%s", ss + st_str[i]);
        slen[i] = strlen(ss + st_str[i]);
        st_str[i+1] = st_str[i] + slen[i] + 1;
    }
    //for(int i = 0; i < n; ++i) printf("%s\n", ss + st_str[i]);
    aho.init();
    for(int i = 0; i < n; ++i) {
        aho.add_str(ss + st_str[i], slen[i], i);
    }
    aho.build_ac();
    aho.get_first_ans();
    print(ans);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
