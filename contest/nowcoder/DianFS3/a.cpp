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
const int mod = 55566677;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e6 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
struct Point {
    int x;
    int y;
};
class Solution {
public:
    /**
     * 返回牛牛所能得到的字典序最小的排列
     * @param n int整型 
     * @param m int整型 
     * @param perm int整型vector 
     * @param Pair Point类vector 
     * @return int整型vector
     */
    static const int MXN = 1e5 + 5;
    int fa[MXN], id[MXN], inde, ar[MXN];
    vector<int> vs[MXN], val[MXN];
    int Fi(int x) {
        return fa[x] == x?x:fa[x] = Fi(fa[x]);
    }
    vector<int> solve(int n, int m, vector<int>& perm, vector<Point>& Pair) {
        // write code here
        for(int i = 1; i <= n; ++i) fa[i] = i;
        for(Point a: Pair) {
            int px = Fi(a.x), py = Fi(a.y);
            if(px != py) {
                fa[px] = py;
            }
        }
        for(int i = 1; i <= n; ++i) {
            int pa = Fi(i);
            if(id[pa] == 0) {
                id[pa] = ++ inde;
            }
            vs[id[pa]].emplace_back(i);
            val[id[pa]].emplace_back(perm[i - 1]);
        }
        for(int i = 1; i <= inde; ++i) sort(val[i].begin(), val[i].end());
        for(int i = 1; i <= inde; ++i) {
            for(int j = 0; j < val[i].size(); ++j) {
                ar[vs[i][j]] = val[i][j];
            }
        }
        vector<int> ans;
        for(int i = 1; i <= n; ++i) ans.emplace_back(ar[i]);
        return ans;
    }
}ss;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    vector<int> a;
    a.eb(5);
    a.eb(2);
    a.eb(3);
    a.eb(4);
    a.eb(1);
    vector<Point> b;
    b.eb(Point{2,4});
    b.eb(Point{1,4});
    b.eb(Point{3,4});
    vector<int> ans = ss.solve(5, 3, a, b);
    for(int x: ans) debug(x);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
