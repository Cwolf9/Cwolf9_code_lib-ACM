// #pragma comment(linker, "/STACK:102400000,102400000")
// #include <assert.h>
// #include <bits/stdc++.h>

// #include <algorithm>
// #include <cstdio>
// #include <cstring>
// #include <ctime>
// #include <iostream>
// #include <queue>
// #include <vector>
// #define fi first
// #define se second
// #define endl '\n'
// #define o2(x) (x) * (x)
// #define BASE_MAX 31
// #define mk make_pair
// #define eb push_back
// #define SZ(x) ((int)(x).size())
// #define all(x) (x).begin(), (x).end()
// #define clr(a, b) memset((a), (b), sizeof((a)))
// #define iis                           \
//     std::ios::sync_with_stdio(false); \
//     cin.tie(0)
// #define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
// using namespace std;
// #pragma optimize("-O3")
// typedef long long LL;
// typedef unsigned long long uLL;
// typedef pair<int, int> pii;
// // mt19937 rng(time(NULL));
// // mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// // mt19937_64 generator(std::clock());
// // shuffle(arr, arr + n, generator);
// inline LL read() {
//     LL x = 0;
//     int f = 0;
//     char ch = getchar();
//     while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
//     while (ch >= '0' && ch <= '9')
//         x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
//     return x = f ? -x : x;
// }
// inline void write(LL x, bool f) {
//     if (x == 0) {
//         putchar('0');
//         if (f)
//             putchar('\n');
//         else
//             putchar(' ');
//         return;
//     }
//     if (x < 0) {
//         putchar('-');
//         x = -x;
//     }
//     static char s[23];
//     int l = 0;
//     while (x != 0) s[l++] = x % 10 + 48, x /= 10;
//     while (l) putchar(s[--l]);
//     if (f)
//         putchar('\n');
//     else
//         putchar(' ');
// }
// int lowbit(int x) { return x & (-x); }
// template <class T>
// T big(const T &a1, const T &a2) {
//     return a1 > a2 ? a1 : a2;
// }
// template <class T>
// T sml(const T &a1, const T &a2) {
//     return a1 < a2 ? a1 : a2;
// }
// template <typename T, typename... R>
// T big(const T &f, const R &... r) {
//     return big(f, big(r...));
// }
// template <typename T, typename... R>
// T sml(const T &f, const R &... r) {
//     return sml(f, sml(r...));
// }
// void debug_out() { cerr << '\n'; }
// template <typename T, typename... R>
// void debug_out(const T &f, const R &... r) {
//     cerr << f << " ";
//     debug_out(r...);
// }
// #define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ",
// debug_out(__VA_ARGS__);

// const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
// const int HMOD[] = {1000000009, 1004535809};
// const LL BASE[] = {1572872831, 1971536491};
// const int mod = 998244353;
// const double eps = 1e-6;
// const int MOD = 1e9 + 7;  // 998244353
// const int INF = 0x3f3f3f3f;
// const int MXN = 2505;
// const int MXE = 2e6 + 7;
// int n, m, k;

// int main() {
// #ifndef ONLINE_JUDGE
//     // freopen("E://ADpan//in.in", "r", stdin);
//     // freopen("E://ADpan//out.out", "w", stdout);
// #endif
//     LL a = read(), b = read(), c = sqrt(b*1.0);
//     LL ans = 0;
//     for(int i = 1; i <= c; ++i) {
//         if(a <= i * i && i * i <= b) ans += max(0LL, 2*(b/i-(a-1)/i-1)) + 1;
//         else ans += 2*(b/i-(a-1)/i);
//     }
//     printf("%lld\n", ans);
// #ifndef ONLINE_JUDGE
//     cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
//     system("pause");
// #endif
//     return 0;
// }
#include <bits/stdc++.h>
#define mme(a, b) memset((a), (b), sizeof((a)))
using namespace std;
typedef unsigned long long LL;
const int N = 2e5 + 7;
const int M = 1e5 + 7;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

LL get_sum(LL x) {
    LL ans = 0;
    for (LL left = 1, right; left <= x; left = right + 1) {
        right = x / (x / left);
        ans += (x / left) * (right - left + 1);
    }
    return ans;
}
int main() {
    LL a, b;
    while (~scanf("%lld%lld", &a, &b)) {
        printf("%lld\n", get_sum(b) - get_sum(a - 1));
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}