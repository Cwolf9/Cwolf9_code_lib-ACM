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
const int MOD = 1e9 + 9;  // 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN];
int64 sum[MXN<<2], add[MXN<<2], asn[MXN<<2];
int ksm(int a, int b) {
    int res = 1;
    while(b > 0) {
        if(b & 1) res = (int64)res * a % MOD;
        a = (int64) a * a % MOD;
        b >>= 1;
    }
    return res;
}
void build(int l, int r, int rt) {
    add[rt] = 1;
    asn[rt] = 0;
    if(l == r) {
        sum[rt] = l + 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    sum[rt] = sum[rt << 1] * sum[rt << 1 | 1] % MOD;
}
void update(int L, int R, int id, int v, int l, int r, int rt) {
    if(L <= l && r <= R) {
        if(id == 1) {
            add[rt] = v * add[rt] % MOD;;
            sum[rt] = sum[rt] * ksm(v, r - l + 1) % MOD;
        }
        return ;
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D://in.in", "r", stdin);
    freopen("D://out.out", "w", stdout);
#endif
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) ar[i] = read();
    while(m -- ) {

    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}
/*
const int N = 1e4 + 7;const int INF = 0x3f3f3f3f;
LL n, m;int ar[N];LL dp[19][19][3000];
LL dfs(int pos,int mid,int cur,bool lead,bool limit){
  if(pos==-1) return cur==0;
  if(cur<0) return 0;
  if(!limit&&dp[pos][mid][cur]!=-1)return dp[pos][mid][cur];
  int up = limit? ar[pos]: 9;
  LL sum = 0;
  for(int i = 0; i <= up; ++i){
    int tmp = (pos-mid)*i;
    sum += dfs(pos-1,mid,cur+tmp,lead&&i==0,limit&&i==ar[pos]);
  }
  if(!limit) dp[pos][mid][cur] = sum;
  return sum;
}
LL solve(LL x){
  if(x<0) return 0;
  else if(x==0) return 1;
  int pos = 0;
  while(x){
    ar[pos++] = x % 10;
    x /= 10;
  }
  LL sum = 0;
  for(int i = pos-1; i >= 0; --i){
    sum += dfs(pos-1, i, 0, 1, 1);
  }
  return sum-(pos-1);
}
void solve(){
    memset(dp, -1, sizeof(dp));
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", solve(m)-solve(n-1));
}

*/