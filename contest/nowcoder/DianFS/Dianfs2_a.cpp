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
class Solution {
public:
    /**
     * 
     * @param n long长整型 
     * @param m long长整型 
     * @param a long长整型 
     * @param b long长整型 
     * @param x long长整型 
     * @param y long长整型 
     * @return long长整型
     */
    long long mod = 998244353;
    long long getUpX(long long n, long long m, long long x, long long st, long long ed) {
        if(st > ed) return 0;
        long long a = (x + st - 1) % m;
        if(a == 0) a = m;
        long long len = ed - st + 1;
        long long ans = 0;
        debug(a)
        while(a <= m) {
            ans += a;
            -- len;
            if(a == m || len == 0) break;
            ++ a;
        }
        debug(ans, len)
        if(len == 0) return ans;
        long long cnt = len / m;
        long long tmp = len % m;
        if(tmp == 0) tmp = m;
        long long ret = tmp;
        debug(((ans + (ret+1)*ret/2) % mod+((m+1)*m/2)%mod*cnt)%mod)
        return ((ans + (ret+1)*ret/2) % mod+((m+1)*m/2)%mod*cnt)%mod;
    }
    long long getDownX(long long n, long long m, long long x, long long st, long long ed) {
        if(st > ed) return 0;
        long long a = ((x - st) % m + m)%m + 1;
        long long len = ed - st + 1;
        long long ans = 0;
        debug(a, len)
        while(a >= 1) {
            ans += a;
            -- len;
            if(a == 1 || len == 0) break;
            -- a;
        }
        debug(ans, len)
        if(len == 0) return ans;
        long long cnt = len / m;
        long long tmp = len % m;
        if(tmp == 0) tmp = m;
        long long ret = m - tmp + 1;
        debug(ret)
        debug(((ret+m)*(m-ret+1)/2) % mod+((m+1)*m/2)%mod*cnt)
        return ((ans + (ret+m)*(m-ret+1)/2) % mod+((m+1)*m/2)%mod*cnt%mod)%mod;
    }
    long long work(long long n, long long m, long long a, long long b, long long x, long long y) {
        // write code here
        if(x > 2 * b) return 0;
        if(y > 2 * b) y = 2 * b;
        long long st1 = (x + 1)/ 2, ed1 = (y + 1) / 2;
        long long st2 = (x + 1)/ 2, ed2 = (y) / 2;
        long long up = a % m + 1;
        long long down = (up - 1);
        debug(up, down, st1, ed1, st2, ed2)
        if(down == 0) down = m;
        return (getUpX(n, m, up, st1, ed1) + getDownX(n, m, down, st2, ed2)) % mod;
    }
};
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    Solution aa;
    cout << aa.work(4,5,17,6,3,14) << endl;
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
