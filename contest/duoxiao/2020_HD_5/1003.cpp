/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;

void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int64 ksm(int64 a, int b, int Mod) {int64 res = 1;for(; b; b>>=1, a=a*a%Mod) {if(b&1) res = res * a % Mod;}return res;}
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
vector<int> mp[405], ans[405];
int ar[1100*405], is[1025];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        int n = read(), k = read();
        int all = 1<<k;
        for(int i = 1; i <= all * n * 2; ++i) ar[i] = i;
        for(int i = 1; i <= all; ++i) mp[i].clear(), ans[i].clear();
        vector<int> vs, vt;
        for(int i = 1; i <= n + n;  ++i) vs.eb(i);
        while(k --) {
            vt = vs;
            reverse(all(vt));
            for(int x: vs) vt.eb(x);
            vs = vt;
        }
        for(int i = 1; i <= vs.size(); ++i) {
            // debug(i, vs[i-1], ar[i])
            mp[vs[i-1]].eb(ar[i]);
        }
        for(int t = 1; t <= n + n; ++ t) {
            int len = mp[t].size();
            for(int i = 0; i <= all; ++i) is[i] = 0;
            for(int i = len - 2, h = 0, j = 0 ; j < len; ++j) {                                                    
                // debug(t, i)
                is[i] = 1;
                if(j % 2 == 0) {
                    ans[t].eb(mp[t][i]);
                    i = len - 1 - i;
                }else {
                    ans[t].eb(mp[t][i]);
                    if(h % 2 == 0) ++ i;
                    else -- i;
                    ++ h;
                }
                if(is[i]) i = 0;
            }
            for(int i = 0; i < len; ++i) printf("%d%c", ans[t][i], " \n"[i == len-1&&t==n+n]);
        }
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}