/*
 
 
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
const int MXN = 300 + 5;
const int MXE = 2e6 + 6;
int n, S;
int ar[MXN][MXN], id[MXN], inde, cnt[MXN], d[MXN], mp[MXN];
char s[MXE];
bool cmp(int a, int b) {
    return cnt[a] < cnt[b];
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        scanf("%d%d", &n, &S);
        scanf("%s", s);
        int tid = 0;
        for(int i = 0; i < n - 1; ++i) {
            for(int j = i + 1; j < n; ++j) {
                ar[i][j] = s[tid] - '0';
                ar[j][i] = ar[i][j];
                ++ tid;
            }
        }
        for(int i = 0; i < n; ++i) id[i] = mp[i] = 0;
        inde = 0;
        vector<int> vs;
        int cas = 0;
        for(int i = 0; i < n; ++i) {
            if(id[i]) continue;
            vs.clear();
            vs.eb(i);
            for(int j = 0; j < n; ++j) {
                if(ar[i][j] && id[j] == 0) vs.eb(j);
                cnt[j] = 0;
            }
            // debug("point", ++cas)
            for(int x: vs) {
                for(int j = 0; j < n; ++j) {
                    if(ar[x][j]) ++ cnt[j];
                }
                // printf("%d ", x);
            }
            // printf("\n");
            for(int i = 0; i < n; ++i) d[i] = i;
            sort(d, d + n, cmp);
            int Mx = -1, pos = 0;
            for(int i = 0; i < n; ++i) {
                if(cnt[d[i]] && (i + 1 < n && cnt[d[i+1]] - cnt[i] > Mx)) {
                    Mx = cnt[d[i+1]] - cnt[i];
                    pos = i + 1;
                }
            }
            ++ inde;
            for(int j = pos; j < n; ++j) {
                if(id[d[j]] == 0) {
                    id[d[j]] = inde;
                    // printf("%d ", j);
                }
            }
            // printf("\n");
        }
        inde = 0;
        int tmp;
        for(int i = 0; i < n; ++i) {
            if(mp[id[i]-1] == 0) mp[id[i]-1] = ++ inde, tmp = inde - 1;
            else tmp = mp[id[i]-1] - 1;
            printf("%d%c", tmp, " \n"[i == n-1]);
        }
        // debug("end")
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}