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
const int mod = 55566677;
const int MOD = 1e9 + 7;  // 998244353
// const int MXN = 1e6 + 5;
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
     * @param array int整型一维数组 array
     * @param arrayLen int array数组长度
     * @return long长整型
     */
    typedef long long ll;
    static const int MXN = 1e5 + 5;
    int n;
    int ar[MXN], lmn[MXN], rmn[MXN], lmx[MXN], rmx[MXN];
    ll ans;
    long long MaxMin(int* array, int arrayLen) {
        // write code here
        n = arrayLen;
        for(int i = 0; i < n; ++i) {
            ar[i + 1] = array[i];
        }
        vector<int> sk1, sk2, sk3, sk4;
        for(int i = 1; i <= n; ++i) {
            while(!sk1.empty() && ar[sk1.back()] >= ar[i]) sk1.pop_back();
            lmn[i] = sk1.empty()?0:sk1.back();
            while(!sk2.empty() && ar[sk2.back()] <= ar[i]) sk2.pop_back();
            lmx[i] = 0;
            int L = 0, R = sk2.size() - 1, mid;
            while(L <= R) {
                mid = (L + R) >> 1;
                if(ar[sk2[mid]] >= ar[i] + ar[i]) lmx[i] = sk2[mid], L = mid + 1;
                else R = mid - 1;
            }
            sk1.push_back(i), sk2.push_back(i);
        }
        for(int i = n; i >= 1; --i) {
            while(!sk3.empty() && ar[sk3.back()] > ar[i]) sk3.pop_back();
            rmn[i] = sk3.empty()?n+1:sk3.back();
            while(!sk4.empty() && ar[sk4.back()] <= ar[i]) sk4.pop_back();
            rmx[i] = n + 1;
            int L = 0, R = sk4.size() - 1, mid;
            while(L <= R) {
                mid = (L + R) >> 1;
                if(ar[sk4[mid]] >= ar[i] + ar[i]) rmx[i] = sk4[mid], L = mid + 1;
                else R = mid - 1;
            }
            sk3.push_back(i), sk4.push_back(i);
        }
        ans = 0;
        for(int i = 1; i <= n; ++i) {
            ans += 1LL*max(0, lmx[i]-lmn[i]) * (rmn[i]-i) + 1LL*max(0,rmn[i]-rmx[i])*(i-lmn[i]);
            ans -= 1LL*max(0, lmx[i]-lmn[i]) * max(0,rmn[i]-rmx[i]);
            // debug(ans)
            // debug(lmn[i], lmx[i], rmn[i], rmx[i])
        }
        return ans;
    }
};
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int ar[4] = {2, 1, 1, 2};
    Solution ss;
    ss.MaxMin(ar, 4);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
