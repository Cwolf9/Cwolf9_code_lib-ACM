/*
链接
https://ac.nowcoder.com/acm/contest/5666/A
题意
n(1e5)的字符串只包含ab两个字母，对它的n个后缀字符串按B值来排序。
字符串的B值是一个向量，bi=min(i - j) 且 1<=j<i,s[j]==s[i]

思路
对于字符串的B值可以将他分成两部分求: 
S=AD, 其中 A = aa...ab or bb...ba
A部分的B值为: 011...10
这是确保后缀S的D部分之前ab都出现过了，对D部分求出来的B值的顺序可以直接
参考后缀数组对整个字符串B值排序的答案。
所以我可以对每个后缀记录三个值: one, isZero, sf
one: A部分中1的个数
isZero: A部分是否有最后一个0，即是否ab都出现了，即是否后面还有值
sf: D部分在后缀数组中的rank
对上面三个值从小到大排序之后的 id 即为答案。

备注
叉姐说当只有两个字符时，有一个论文结论，对源字符串求出C值 ，
ci=min(j - i) 且 1<=i<j,s[j]==s[i]，再末尾补上一个数 n+1 ，
然后对这个 C 值求后缀数组的 sa 反过来就是答案。
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
const int MXN = 3e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
char s[MXN];
int mp[30], ans[MXN], ar[MXN];
class edge{
    public:
    int one, isZero, sf;
    int id;
    bool operator<(const edge& b) const {
        if(one != b.one) return one < b.one;
        if(isZero < b.isZero) return isZero < b.isZero;
        return sf < b.sf;
    }
}cw[MXN];
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
    static const int N = 3e5 + 7;
    int n, len, s[N], M;
    int sa[N], rnk[N], height[N];
    int tmp_one[N], tmp_two[N], c[N];
    int dp[N][21];
    void init_str(int *str, int _n) {
        len = _n;
        n = len + 1;
        for (int i = 0; i < len; ++i) {
            s[i] = str[i] + 1;
            // debug(s[i])
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
        for (i=0; i<n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;//按rank顺序，1<<(j+1)的第二半的rank。sa[i]把自己交给了sa[i]-j
        //现在第二关键字已经有序，在此基础上按第一关键字排序
        for (i=0; i<m; ++i) c[i] = 0;
        for (i=0; i<n; ++i) c[x[y[i]]]++;
        for (i=1; i<m; ++i) c[i] += c[i-1];
        for (i=n-1; i>=0; --i) sa[--c[x[y[i]]]] = y[i];//排第几的后缀是y[i]
        std::swap (x, y);
        for (p=1, x[sa[0]]=0, i=1; i<n; ++i) {//排完序后更新第一关键字
            x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+j] == y[sa[i]+j] ? p - 1 : p++);
        }
        if(p >= n) break;
        m=p;
    }
    calc_height(n-1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    while(~scanf("%d", &n)) {
        scanf("%s", s + 1);
        clr(mp, 0);
        for(int i = 1; i <= n + 2; ++i) ar[i] = 0;
        for(int i = 1; i <= n; ++i) {
            if(mp[s[i]-'a']) ar[i] = i - mp[s[i]-'a'];
            mp[s[i]-'a'] = i;
        }
        // for(int i = 0; i <= n; ++i) printf("%d ", ar[i]);puts("");
        SA.init_str(ar, n + 1);
        SA.build_sa(n + 2);
        // for(int i = 0; i <= n + 1; ++i) printf("%d ", SA.sa[i]);puts("");
        // for(int i = 0; i <= n + 1; ++i) printf("%d ", SA.rnk[i]);puts("");
        clr(mp, 0);
        cw[n].id = n, cw[n].one = 0, cw[n].isZero = cw[n].sf = -1;
        mp[s[n]-'a'] = n;
        for(int i = n - 1; i >= 1; --i) {
            cw[i].id = i;
            mp[s[i]-'a'] = i;
            if(mp[0] == 0) {
                cw[i].one = n + 1 - i;
                cw[i].isZero = cw[i].sf = -1;
            }else if(mp[1] == 0) {
                cw[i].one = n + 1 - i;
                cw[i].isZero = cw[i].sf = -1;
            }else {
                cw[i].one = abs(mp[1] - mp[0]);
                cw[i].isZero = 0;
                cw[i].sf = SA.rnk[max(mp[1], mp[0]) + 1];
                // debug(i, cw[i].sf)
            }
        }
        sort(cw + 1, cw + 1 + n);
        for(int i = 1; i <= n; ++i) printf("%d%c", cw[i].id, " \n"[i == n]);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
