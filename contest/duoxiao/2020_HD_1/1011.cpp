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

const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 1e6 + 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
char s[MXN];
int64 ksm(int64 a, int64 b) {
    int64 res = 1;
    while(b > 0) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
/*
 *后缀数组，倍增算法实现，复杂度O(nlogn)
 *sa[i]: 第i小的后缀是在字符串位置，即后缀sa[i]
 *rank[i]: 后缀i在sa数组下标，即第rank[i]小
 *height[i]: LCP(suffix(sa[i-1], sa[i]))
 */
//后缀数组(SA[i]存放排名第i大的后缀首字符的下标)
//名次数组（rank[i]存放Suffix(i)的优先级(名次)）
//height数组：height[i]是Suffix(sa[i-1])和Suffix(sa[i])的最长公共前缀长度
//SA,R,H的下标都是 0~n 其中多包括了一个空字符串
struct Suffix_Array {
    static const int N = 2e6 + 7;
    int n, len, s[N], M;
    int sa[N], rnk[N], height[N];
    int tmp_one[N], tmp_two[N], c[N];
    void init_str(char *str, int _n) {
        len = _n;
        n = len + 1;
        for (int i = 0; i < len; ++i) {
            s[i] = str[i] - 'a' + 1;
        }
        s[len] = '\0';
    }
    void build_sa(int m = 128);
    void calc_height(int n);
    void Out(char *str);
}SA;
void Suffix_Array::Out(char *str) {
    puts ("/*Suffix*/");
    for (int i=0; i<n; ++i) {
        printf ("%s\n", str+sa[i]);
    }
}
void Suffix_Array::calc_height(int n) {
    for (int i=0; i<=n; ++i) rnk[sa[i]] = i;
    int k = height[0] = 0;
    for (int i=0; i<n; ++i) {
        if (k) k--;
        int j = sa[rnk[i]-1];
        while (s[i+k] == s[j+k]) k++;
        height[rnk[i]] = k;
    }
}
//m = max(r[i]) + 1，一般字符128足够了
void Suffix_Array::build_sa(int m) {
    int i, j, p, *x = tmp_one, *y = tmp_two;
    for (i=0; i<m; ++i) c[i] = 0;
    for (i=0; i<n; ++i) c[x[i]=s[i]]++;//此时第一关键字是x[i]，第二关键字是i
    for (i=1; i<m; ++i) c[i] += c[i-1];
    for (i=n-1; i>=0; --i) sa[--c[x[i]]] = i;//排第几的后缀是i
    for (j=1; j<=n; j<<=1) {//y就是第二关键字从小到大的位置
        //y[i]表示第二关键字排名为i的数，第一关键字的位置
        for (p=0, i=n-j; i<n; ++i) y[p++] = i;//这些数的第二关键字为0
        for (i=0; i<n; ++i) if (sa[i] >= j) y[p++] = sa[i] -
        j;//按rank顺序，1<<(j+1)的第二半的rank。sa[i]把自己交给了sa[i]-j
        //现在第二关键字已经有序，在此基础上按第一关键字排序
        for (i=0; i<m; ++i) c[i] = 0;
        for (i=0; i<n; ++i) c[x[y[i]]]++;
        for (i=1; i<m; ++i) c[i] += c[i-1];
        for (i=n-1; i>=0; --i) sa[--c[x[y[i]]]] = y[i];//排第几的后缀是y[i]
        std::swap (x, y);
        for (p=1, x[sa[0]]=0, i=1; i<n; ++i) {//排完序后更新第一关键字
            x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+j] == y[sa[i]+j]
            ? p - 1 : p++);
        }
        if(p >= n) break;
        m=p;
    }
    calc_height(n-1);
}
int one[MXN], tmp[MXN], suf[MXN], ans[MXN];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    one[1] = 1;
    for(int i = 2; i <= 1000000; ++i) one[i] = one[i-1] * 1112 % MOD;
    int tim = read();
    while(tim --) {
        scanf("%s", s);
        n = strlen(s);
        SA.init_str(s, n);
        SA.build_sa();
        tmp[0] = 0;
        for(int i = 1; i <= n; ++i) {
            tmp[i] = max(tmp[i-1], n - SA.sa[i]);
            printf("%d ", SA.sa[i]);
        }
        printf("\n");
        for(int i = 1; i <= n; ++i) printf("%d ", tmp[i]);
        printf("\n");
        suf[n + 1] = 0;
        for(int i = n; i >= 1; --i) suf[i] = min(suf[i+1], n - SA.sa[i]);
        int ti = 1;
        for(int i = n, ret; i >= 1; --i) {
            while(ti < n && tmp[ti] < n - i + 1) ++ ti;
            if(ti < n && SA.sa[ti + 1] > SA.sa[ti]) {
                int lcp = SA.height[ti + 1];
                debug(i, lcp, n - i, n - SA.sa[ti+1])
                if(lcp + n - i >= n - SA.sa[ti+1]) ret = SA.sa[ti+1] + 1;
                else ret = SA.sa[ti] + 1;
            }else ret = SA.sa[ti] + 1;
            ans[i] = ret;
            debug(i, ti, SA.sa[ti])
        }
        int64 res = 0;
        for(int i = 1; i <= n; ++i) {
            printf("%d ", ans[i]);
            res = (res + ans[i] * one[i] % mod) % mod;
        }
        printf("\n");
        debug()
        printf("%d\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
