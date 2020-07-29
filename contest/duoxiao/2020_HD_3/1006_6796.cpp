/*
**链接**
传送门: [here](http://acm.hdu.edu.cn/showproblem.php?pid=6796)
**题意**
$f(x)$等于$x$中出现次数最多的那一个数字。
问$l,r$中有几个数字$f(x)=d,0\le d\le 9$.
**思路**
$数位dp$同时要记录前面各位选的数字的次数，可用大小为$10$的$array$存起来
为了保证能正确的记忆化，这个$array$应该占$dp$的一维状态，所以只能用$map$表示$dp$状态
$map<array<int, 10>, int64> dp[d][pos][leadZero]$
表示只考虑$d$类数，$pos$前的位数，是否有前导$0$，数字使用情况为$array$的合法方案数。
仅当$!limit$时才记忆化。

当数字使用情况为$array$所记录，且还能使用$pos$位任意$0-9$数字时，想要让众数为d的方案数
可以使用$母函数DP$写出来，复杂度$O(n^4)$。

算法时间复杂度我猜为 $O(进制数*位数+进制数*新增状态数*18^4)$
**备注**

*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <assert.h>
#include <bits/stdc++.h>

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
const int mod = 1e9 + 7;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e2 + 3;
const int MXE = 2e6 + 6;
int n, m;
int64 L, R;
int ar[30], ma;
int64 C[20][20], F[30], ndp[20], rdp[20];
map<array<int,10>, int64> dp[10][20][2];
int64 dfs(int pos, int curA, array<int,10>& vs, bool is, bool limit) {
    int ma = 0;
    for(int i = 0; i < 10; ++i) if(i != m) ma = max(ma, vs[i]);
    if (pos == 0) {
        return curA > ma;
    }else if(ma >= pos + curA) return 0;
    array<int,10> vt = vs;
    swap(vt[m], vt.back());
    sort(vt.begin(), vt.end()-1);
    if(!limit && dp[m][pos][is].find(vt) != dp[m][pos][is].end()) return dp[m][pos][is][vt];
    int64 sum = 0;
    if (!limit && !is) {
        //sort(all(vs));
        for(int i = 0; i <= pos; ++i) {
            for(int j = 0; j <= pos - i; ++j) ndp[j] = 0;//way 1
            ndp[pos - i] = C[pos][i];
            for(int j = 0; j <= 9; ++j) {
                if(j == m) continue;
                if(vs[j] >= curA + i) {
                    ndp[0] = 0;
                    break;
                }
                for(int a = 1; a <= pos - i; ++ a) {//number j can use times
                    for(int b = 1; b <= min(a, curA + i - vs[j] - 1); ++ b) {//use times
                        ndp[a - b] += C[a][b] * ndp[a];//last times ans
                    }
                }
            }
            sum += ndp[0];
            // for(int j = 0; j <= pos - i; ++j) {
            //     ndp[j] = 0;
            //     rdp[i] = 0;//way 2
            // }
            // rdp[0] = 1;
            // for(int h = 0, t; h <= 9; ++h) {
            //     if(h == m) continue;
            //     if(vs[h] >= curA + i) {
            //         rdp[pos - i] = 0;
            //         break;
            //     }
            //     memcpy(ndp, rdp, sizeof(ndp));
            //     memset(rdp, 0, sizeof(rdp));
            //     t = min(pos - i, curA + i - vs[h] - 1);
            //     for(int j = 0; j <= t; ++j) {
            //         for(int k = 0; k + j <= pos - i; ++k) {
            //             rdp[k+j] = rdp[k+j] + ndp[k];
            //         }
            //     }
            // }
            // sum += rdp[pos - i] * C[pos][i];
        }
        return dp[m][pos][is][vt] = sum;
    }
    int up = limit ? ar[pos] : 9;
    for (int i = 0, tmp; i <= up; ++i) {
        if(is && i == 0) tmp = curA;
        else if(i != m) ++ vs[i], tmp = curA;
        else tmp = curA + (i == m), ++ vs[i];
        sum = sum + dfs(pos - 1, tmp, vs, is && i == 0, limit && i == up);
        if(is && i == 0) ;
        else if(i != m) -- vs[i];
        else -- vs[i];
    }
    if(!limit) dp[m][pos][is][vt] = sum;
    return sum;
}
int64 solve(int64 x) {
    if(x < 10) {
        return x == m && x != 0;
    }
    n = 0;
    while(x > 0) {
        ar[++ n] = x % 10;
        x /= 10;
    }
    array<int,10> vs = {0,};
    return dfs(n, 0, vs, 1, 1);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    F[0] = C[0][0] = 1;
    for(int i = 1; i <= 19; ++i) C[i][0] = 1, F[i] = F[i-1] * 10;
    for(int i = 1; i <= 19; ++i) {
        for(int j = 1; j <= i; ++j) {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
    int tim = read();
    while(tim --) {
        scanf("%lld%lld%d", &L, &R, &m);
        // printf("%lld %lld\n", solve(R), solve(L - 1));
        printf("%lld\n", solve(R) - solve(L - 1));
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}
/*
10
5
1
1
1
3
2
2


8
999999999999999990 1000000000000000009 9
3440 3445 4
2 11 1
1 10 2
1 100 0
2 110 1
1 110 2
1 110 3
*/
