/*

*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
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
     * 
     * @param potatoNum int整型vector 依次表示序号为1,2,3..的番薯洞各有多少个番薯
     * @param connectRoad int整型vector<vector<>> 每个一维数组[x,y]表示从第x号番薯洞到第y号有路
     * @return string字符串
     */
    vector<int> mp[300];
    int dp[300], du[300], las[300], val[300];
    int ans = 0;
    string tmp = "", ret;
    vector<int> vs;
    void dfs(pair<int, int> u) {
        int f = 1;
        if(dp[u.second] > u.first) return;
        for(int v: mp[u.second]) {
            if(dp[u.second] + val[v] > dp[v]) {
                f = 0;
                dp[v] = dp[u.second] + val[v];
                las[v] = u.second;
                dfs(make_pair(dp[v], v));
            }
        }
        if(f && dp[u.second] > ans) {
            ans = dp[u.second];
            vs.clear();
            vs.emplace_back(u.second);
            int x = u.second;
            while(las[x] != -1) {
                x = las[x];
                vs.emplace_back(x);
            }
            reverse(vs.begin(), vs.end());
            ret = "";
            char c = '0' + vs[0];
            ret += c;
            for(int i = 1; i < vs.size(); ++i) {
                ret += '-';
                c = '0' + vs[i];
                ret += c;
            }
            tmp = ret;
        }
    }
    string digSum(vector<int>& potatoNum, vector<vector<int> >& connectRoad) {
        // write code here
        int n = potatoNum.size();
        for(int i = 1; i <= n; ++i) {
            dp[i] = potatoNum[i-1], du[i] = 0;
            las[i] = -1;
            val[i] = dp[i];
        }
        for(vector<int>& x: connectRoad) {
            if(x[0] > x[1]) swap(x[0], x[1]);
            if(x[0] == x[1]) continue;
            mp[x[0]].emplace_back(x[1]);
            ++ du[x[1]];
        }
        for(int i = 1; i <= n; ++i) if(du[i] == 0) {
            dfs(make_pair(dp[i], i));
        }
        return tmp;
    }
}ss;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    vector<int> a;
    a.eb(5);
    a.eb(100);
    a.eb(20);
    a.eb(5);
    a.eb(4);
    a.eb(5);
    vector<vector<int>> b;
    vector<int> c;
    c.eb(1);
    c.eb(2);
    b.eb(c);
    c.clear();
    c.eb(1);
    c.eb(4);
    b.eb(c);
    c.clear();
    c.eb(2);
    c.eb(4);
    b.eb(c);
    c.clear();
    c.eb(3);
    c.eb(4);
    b.eb(c);
    c.clear();
    c.eb(4);
    c.eb(5);
    b.eb(c);
    c.clear();
    c.eb(4);
    c.eb(6);
    b.eb(c);
    c.clear();
    c.eb(5);
    c.eb(6);
    b.eb(c);
    debug(ss.digSum(a, b))
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}

