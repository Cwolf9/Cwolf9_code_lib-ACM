#pragma comment(linker, "/STACK:102400000,102400000")
#include <assert.h>
#include <bits/stdc++.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb push_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline LL read() {
    LL x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(LL x, bool f) {
    if (x == 0) {
        putchar('0');
        if (f)
            putchar('\n');
        else
            putchar(' ');
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
    if (f)
        putchar('\n');
    else
        putchar(' ');
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
void debug_out() { cerr << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cerr << f << " ";
    debug_out(r...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 998244353;
const double eps = 1e-6;
const int MOD = 1e9 + 7;  // 998244353
const int INF = 0x3f3f3f3f;
const int MXN = 205;
const int MXE = 2e5 + 7;
int n, m, k;
map<string, int> mp;
set<string> st;
string mp2[MXN];
int ar[MXE], br[MXE], gan[MXE], num[MXN][MXN], wei[MXN], is[MXN];
int main() {
#ifndef ONLINE_JUDGE
    // freopen("E://ADpan//in.in", "r", stdin);
    // freopen("E://ADpan//out.out", "w", stdout);
#endif
    n = read(), m = read(), k = read();
    string sa, sb;
    for(int i = 1; i <= n; ++i) {
        cin >> sa;
        st.insert(sa);
    }
    int ti = 1;
    for(string sa: st) {
        mp[sa] = ti;
        mp2[ti] = sa;
        wei[ti] = 1;
        ++ ti;
    }
    for(int i = 1; i <= m; ++i) {
        cin >> sa >> sb;
        num[mp[sa]][mp[sb]] = num[mp[sb]][mp[sa]] = 1;
    }
    for(int i = 1; i <= k; ++i) {
        cin >> sa;
        ar[i] = mp[sa];
    }
    for(int i = 1; i <= n; ++i) {
        while(wei[i] <= k && ar[wei[i]] != i && num[ar[wei[i]]][i]) ++ wei[i];
        if(wei[i] <= k && ar[wei[i]] == i) is[i] = 1;
    }
    for(int i = 1; i <= k; ++i) {
        int opt = 1;
        for(int j = 1; j <= 200; ++j) {
            if(is[j]) {
                opt = j;
                break;
            }
        }
        br[i] = opt;
        gan[wei[opt]] = 1;
        ++ wei[opt];
        is[opt] = 0;
        for(int j = 1; j <= 200; ++j) {
            while(gan[wei[j]]||(wei[j]<=k&&ar[wei[j]]!=j&&num[ar[wei[j]]][j])) ++ wei[j];
            if(wei[j] <= k && ar[wei[j]] == j) is[j] = 1;
        }
    }
    for(int i = 1; i <= k; ++i) {
        cout << mp2[br[i]];
        if(i == k) cout << "\n";
        else cout << " ";
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}