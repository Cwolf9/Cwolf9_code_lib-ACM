/*
**链接**
传送门: [here](https://hihocoder.com/problemset/problem/1526)
**题意**
给定一个长度为 n(1e5) 的序列 a[1..n]，定义函数 f(b[1..m]) 的值为在 [0,m-1] 内满足如下条件的 i 的数目：
b 中前 i 个数异或起来的值小于 b 中前 i +1个数异或起来的值。
对于 a[1..n] 的每个子序列 b[1..m]，求f(b[1..m])之和。

**思路**
用c[j][0/1]维护前i个数里第j位是0/1的子序列的个数
对于第i个数，如果最高位是j，则对答案的贡献为c[j][0]*2^(n-i)
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 62
#define mk make_pair
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define clr(a,b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef pair<int, int> pii;
typedef pair<int, int64> piL;
inline int64 read(){
    int64 x=0;int f=0;char ch=getchar();
    while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x=f?-x:x;
}
inline void write(int64 x) {
    if(x==0){putchar('0'),putchar('\n');return;}
    if(x < 0) {putchar('-');x=-x;}
    static char s[23];int l = 0;
    while(x!=0)s[l++]=x%10+48,x/=10;
    while(l)putchar(s[--l]);
    putchar('\n');
}
int lowbit(int x) {return x&(-x);}
template<class T> T big(const T& a1,const T& a2) { return a1>a2?a1:a2; }
template<typename T, typename ...R> T big (const T& f,const R& ...r) { return big(f, big (r...)); }
template<class T> T sml(const T& a1,const T& a2) { return a1<a2?a1:a2; }
template<typename T, typename ...R> T sml (const T& f,const R& ...r) { return sml(f, sml (r...)); }
void debug_out() { cout << '\n'; }
template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cout << f << " "; debug_out (r...); }
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

#define print(x) write(x);

const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const int64 BASE[] = {1572872831, 1971536491};
const int mod = 998244353 ;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 1e5 + 7;
const int MXE = 2e5 + 7;
int n, m;
int cr[MXN][2];
int64 two[MXN];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    n = read();
    two[0] = 1;
    for(int i = 1; i <= n; ++i) two[i] = two[i-1] * 2 % mod;
    int64 ans = 0, tx, ty;
    for(int i = 1, x, y; i <= n; ++i) {
        x = read();
        y = -1;
        for(int j = 30; j >= 0; --j) {
            tx = cr[j][0], ty = cr[j][1];
            if(x & (1 << j)) {
                if(y == -1) {
                    y = j;
                    ans = (ans + (two[n - i] * cr[y][0]) % mod) % mod;
                }
                cr[j][0] = (ty + tx)%mod;
                cr[j][1] = (1 + tx + ty)%mod;
            }else {
                cr[j][0] = (1 + tx + tx)%mod;
                cr[j][1] = (ty + ty)%mod;
            }
            // if(cr[j][0] || cr[j][1]) debug(j, cr[j][0], cr[j][1])
        }
        if(i == n) ans = (ans + cr[0][0] + cr[0][1]) % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
