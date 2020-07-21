/*
链接
https://ac.nowcoder.com/acm/contest/5667/H
题意
1. 插入一个x
2. 删除一个x
3. 询问是否有两个数可以和x形成三角形

思路
动态开点权值线段树
对于查询只有三种情况，x是三边之中最大的，x是三边之中第二大的，x是三边之中最小的

备注

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
const int MXR = 1000000001;
int n, m;
int noprime[MXN], pp[MXN], pcnt, mindiv[MXN];
vector<int> mp[MXN], son[MXN];
int id[MXN], d[MXN], is[MXN];
void init_prime() {
    noprime[0] = noprime[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, mindiv[i] = i;
        for(int j = 0; j < pcnt && pp[j] * i < MXN; ++j) {
            noprime[pp[j]*i] = 1;
            mindiv[pp[j]*i] = pp[j];
            if(i % pp[j] == 0) {
                break;
            }
        }
    }
    for(int i = 2; i < MXN; ++i) {
        int j = i, las = -1;
        
        for(j = i; j != 1; j /= mindiv[j]) {
            if(mindiv[j] != las && mindiv[j] != 1) mp[i].eb(mindiv[j]);
            las = mindiv[j];
        }
        reverse(all(mp[i]));
    }
}
bool cmp(int x, int y) {
    int lx = mp[x].size(), ly = mp[y].size();
    int ln = min(lx, ly);
    for(int i = 0; i < ln; ++i) {
        if(mp[x][i] > mp[y][i]) return 1;
        else if(mp[x][i] < mp[y][i]) return 0;
    }
    return lx > ly;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    init_prime();
    vector<pii> vs;
    vector<int> vt, two, tp;
    int tim = read();
    while(tim --) {
        n = read();
        vs.clear();
        vt.clear();
        two.clear();
        for(int i = 2; i <= n; ++i) son[i].clear(), is[i] = id[i] = 0;
        for(int i = 2; i <= n; ++i) son[mindiv[i]].eb(i);
        for(int i = 0; i < pcnt && pp[i] <= n; ++i) {
            if((int)son[pp[i]].size() % 2 == 0 && (int)son[pp[i]].size()) {
                for(int j = 0; j < (int)son[pp[i]].size(); j += 2) {
                    vs.eb(mk(son[pp[i]][j], son[pp[i]][j+1]));
                }
            }else if((int)son[pp[i]].size()) {
                vt.eb(pp[i]);
                int fg = 0;
                for(int x: son[pp[i]]) {
                    if(x % 2 == 0) {
                        fg = x; break;
                    }
                }
                if(fg) two.eb(fg);
            }
            // for(int x: son[pp[i]]) {
            //     printf("%d ", x);
            // }
            // printf("\n");
        }
        if(vt.size()) {
            int len = vt.size();
            for(int i = 0; i < len; ++i) {
                if(vt[i] == 2) continue;
                tp.clear();
                int fg = 0;
                for(int x: son[vt[i]]) {
                    if(fg) tp.eb(x);
                    else if(x % 2 == 0) fg = 1;
                    else tp.eb(x);
                }
                int ln = tp.size();
                debug(ln, vt[i])
                for(int i = 0; i + 1 < ln; i += 2) {
                    vs.eb(mk(tp[i], tp[i+1]));
                    // debug(tp[i], tp[i+1])
                }
            }
            if(vt[0] == 2) {
                for(int x: son[2]) two.eb(x);
            }
            int ln = two.size();
            for(int i = 0; i + 1 < ln; i += 2) {
                vs.eb(mk(two[i], two[i+1]));
            }
        }
        printf("%d\n", vs.size());
        for(pii x: vs) printf("%d %d\n", x.fi, x.se);
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
