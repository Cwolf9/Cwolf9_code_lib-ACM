/*

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
const int mod = 1e9 + 7;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 3;
const int MXE = 2e6 + 6;
int n, m, k;
pii stk[MXN];
int top;
char s[MXN], t[MXN];
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
        int cnt = 0;
        vector<int> vs;
        
        if(num == 0) {
            for(int i = 1; i <= n; ++i) {
                if(is[i] == 0 && s[i] == '*') vs.eb(i);
                else if(is[i] > 0 && s[i] == '*' && cnt < (int)vs.size()) {
                    is[vs[cnt]] = is[i];
                    is[i] = 0;
                    ++ cnt;
                    vs.eb(i);
                }
            }
        }else if(num > 0) {//*(*)*
            // debug(num)
            for(int i = 1; i <= top; ++i) {
                if(stk[i].fi == '(') is[stk[i].se] = -1;
                // debug(i, (char)stk[i].fi, stk[i].se, is[stk[i].se])
            }
            cnt = 0;
            vs.clear();
            for(int i = 1; i <= n; ++i) {
                // debug(i, is[i], s[i], cnt)
                if(is[i] == -1) vs.eb(i);
                else if(is[i] > 0 && s[i] == '*' && cnt < (int)vs.size()) {
                    is[vs[cnt]] = is[i];
                    is[i] = 0;
                    ++ cnt;
                }
            }

            int cnt2 = 0;
            vector<int> vt;
            for(int i = 1; i <= n; ++i) {
                // debug(i, is[i], s[i])
                if(is[i] == 0 && s[i] == '*') vt.eb(i);
                else if(is[i] > 0 && s[i] == '*' && cnt2 < (int)vt.size()) {
                    is[vt[cnt2]] = is[i];
                    is[i] = 0;
                    ++ cnt2;
                    vt.eb(i);
                }
            }
            if(cnt != num) {
                num -= cnt;
                for(int i = n; i >= 1; --i) {
                    // debug(i, s[i], num)
                    if(is[i] == 0 && s[i] == '*' && num > 0 && i > vs[num-1]) {
                        s[i] = ')';
                        -- num;
                    }
                }
                if(num > 0) flag = 0;
            }
        }else {
            flag = 0;
        }
        if(flag == 0) printf("No solution!\n");
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
