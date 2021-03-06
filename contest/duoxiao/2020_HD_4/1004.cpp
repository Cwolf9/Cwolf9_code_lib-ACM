/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <set>
#include <deque>
#include <list>
#include <bitset>
#include <complex>
#include <cassert>
#include <ctime>
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
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
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
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
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
void print(const T &f) {printf(ptout, f);putchar('\n');}
template <typename T, typename... R>
void print(const T &f, const R &... r) {printf(ptout, f);putchar(' ');print(r...);}

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m, s, t, x;
char ip[MXN];
int vis[MXN][2];
int64 dis[MXN][2];
vector<pii> mp[MXN];
typedef pair<int64, pii> ppii;
void dij(){
    priority_queue<ppii,vector<ppii> ,greater<ppii> >Q;
    while(!Q.empty()) Q.pop();
    for(int i = 1; i <= n; ++i) {
        dis[i][0] = dis[i][1] = INFLL;
        vis[i][0] = vis[i][1] = 0;
    }
    if(ip[s] == 'L') {
        dis[s][0] = 0;
        Q.push(mk(0, mk(s, 0)));
    }else if(ip[s] == 'R') {
        dis[s][1] = 0;
        Q.push(mk(0, mk(s, 1)));
    }else {
        dis[s][0] = 0;
        Q.push(mk(0, mk(s, 0)));
        dis[s][1] = 0;
        Q.push(mk(0, mk(s, 1)));
    }
    while(!Q.empty()) {
        ppii a=Q.top(); Q.pop();
        int u=a.se.fi, id = a.se.se;
        if(dis[u][id] < a.fi) continue;
        // debug(u, id, dis[u][id])
        // if(vis[u][id]) continue;
        // vis[u][id] = 1;
        for(pii V: mp[u]) {
            int v = V.fi;
            if(ip[v] == 'M') {
                if(dis[v][id] > dis[u][id] + V.se) {
                    dis[v][id] = dis[u][id] + V.se;
                    Q.push(mk(dis[v][id], mk(v, id)));
                }
                if(dis[v][!id] > dis[u][id] + V.se + x) {
                    dis[v][!id] = dis[u][id] + V.se + x;
                    Q.push(mk(dis[v][!id], mk(v, !id)));
                }
            }else if(ip[v] == 'L') {
                if(id == 0) {
                    if(dis[v][id] > dis[u][id] + V.se + 0) {
                        dis[v][id] = dis[u][id] + V.se + 0;
                        Q.push(mk(dis[v][id], mk(v, id)));
                    }
                }else {
                    if(dis[v][!id] > dis[u][id] + V.se + x) {
                        dis[v][!id] = dis[u][id] + V.se + x;
                        Q.push(mk(dis[v][!id], mk(v, !id)));
                    }
                }
            }else {
                if(id == 0) {
                    if(dis[v][!id] > dis[u][id] + V.se + x) {
                        dis[v][!id] = dis[u][id] + V.se + x;
                        Q.push(mk(dis[v][!id], mk(v, !id)));
                    }
                }else {
                    if(dis[v][id] > dis[u][id] + V.se + 0) {
                        dis[v][id] = dis[u][id] + V.se + 0;
                        Q.push(mk(dis[v][id], mk(v, id)));
                    }
                }
            }
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read(), m = read(), s = read(), t = read(), x = read();
        scanf("%s", ip + 1);
        for(int i = 1; i <= n; ++i) mp[i].clear();
        for(int i = 1, a, b, c; i <= m; ++i) {
            a = read();b = read();c = read();
            mp[a].eb(mk(b, c));
            mp[b].eb(mk(a, c));
        }
        dij();
        printf("%lld\n", min(dis[t][0], dis[t][1]));
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}