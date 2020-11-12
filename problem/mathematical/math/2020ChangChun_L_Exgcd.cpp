/*
## 2020 CCPC Changchun gym102832L

 **题意**
 链接：[点我点我](https://codeforces.com/gym/102832)
你需要构造出一个长度为$n$的序列满足以下三个条件：
1. $a_i\ge 0$
2. $(\sum_{i=1}^na_i)=s$
3. 对于任意$i\ge 2,\; a_i=a_{i-1}+1$或者$a_i=a_{i-1}-k$

$1\le n,k\le 1e5,1\le s\le 1e18$

**思路**
首先假设当$i\ge 2$的时候恒定有$a_i=a_{i-1}+1$成立，现在需要选出几个特殊的下标$i$令$a_i=a_{i-1}-k$，其他下标依然满足$a_i=a_{i-1}+1$。

如果第$i$个数转为满足条件$B$的话，序列权值和会减少$(n-i+1)*(k+1)$
修改操作只会让序列权值减少，如果初始时一定要保证序列权值大于等于$s$才行。

所以初始$a_1$至少等于最小非负整数$ansL$满足$\frac {(a_1+a_1+n-1)*n}{2}$大于等于$s$，令$c=\frac {(a_1+a_1+n-1)*n}{2}-s$.
如果$c=0$直接输出解即可。

所以我现在只有两种操作：
1. $a_1=a_1+1$，权值和加$n$；
2. 选择一个$i(2\le i\le n)$，令$a_i=a_{i-1}-k$，权值和减少$(n-i+1)*(k+1)$且每个$i$只能被选中依次。

求出一组合法解$(a,b)$满足$c+b*n = (k+1)*a$且$a\le \frac {n*(n-1)}2$即可。
使用扩展欧几里得求出$a$的最小整数解即可还原出整个数组来，但是要满足$a_i\le 0$。
又因为最小整数解是一组通解，所以我还可以得到任意多组解，包括$a$的次小整数解。

实测只需要使用$a$的最小整数解和次小整数解即可通过本题。

使用$a$还原数组的过程就是尽可能选择小的下标进行操作2。

**AC_CODE**
[点我点我](https://github.com/Cwolf9/Cwolf9_code_lib-ACM/blob/master/contest/gym/2020changxun/L.cpp)




> My approach to 2020 Changchun by Shanghai JTU Problem L is as follows:

*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
#define GKD std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long LL;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));//std::clock()
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(arr, arr + n, rng64);
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
inline void write(int64 x, bool f = true) {
    if (x == 0) {putchar('0'); if(f)putchar('\n');else putchar(' ');return;}
    if (x < 0) {putchar('-');x = -x;}
    static char s[23];
    int l = 0;
    while (x != 0)s[l++] = x % 10 + 48, x /= 10;
    while (l)putchar(s[--l]);
    if(f)putchar('\n');else putchar(' ');
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
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
/*================Header Template==============*/
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;// 998244353
const int MXN = 1e5 + 5;
const int MXE = 1e6 + 5;
const int maxn = 1e5+7;
int64 n, k, s;

int64 Exgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int64 d = Exgcd(b, a % b, x, y);
    int64 t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}
int id[MXN];
int64 ar[MXN];
int fuck(int64 ansL) {
	int64 c = (ansL + ansL + n - 1) * n / 2 - s;
	if(c == (int64)0) {
    	int64 xx = ansL;
    	//debug(xx)
        rep(i, 0, n) printf("%lld%c", xx + i, " \n"[i == n - 1]);
        return 0;
    }
    int64 A = k + 1, B = n, C = c;
    int64 x = 0, y = 0;
    int64 g = __gcd(A, B);
    if(C % g != 0) {
        printf("-1\n");
        return 1;
    }
    A /= g, B /= g, C /= g;
    Exgcd(A, B, x, y);
    x *= C;
    y *= C;
    y %= A;
    if(y > 0) {
        y -= A;
    }
    x = (C - B * y) / A;
    rep(tx, 0, 2) {
		int64 nx = x + B * tx;
    	int64 ny = y - A * tx;
    	ar[1] = ansL - ny;
	    rep(i, 2, n + 1) {
	        ar[i] = ar[i - 1] + 1;
	        if(nx >= n - i + 1 && ar[i - 1] - k >= 0) {
	            id[i] = 1;
	            nx -= n - i + 1;
	            ar[i] = ar[i - 1] - k;
	        }
	    }
	    if(nx == 0) {
	    	rep(i, 1, n + 1) printf("%lld%c", ar[i], " \n"[i == n]);
			return 0;	
		}
	}
    printf("-1\n");
    return 1;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\ACM\\mtxt\\in.txt", "r", stdin);
    // freopen("D:\\ACM\\mtxt\\out.txt", "w", stdout);
#endif
    n = read(), k = read(), s = read();
    //debug(n, k, s)
    int64 L = 0, R = s / n, mid, ansL = 0;
    while(L <= R) {
        mid = (L + R) >> 1;
        if((mid + mid + n - 1) * n / 2 >= s) ansL = mid, R = mid - 1;
        else L = mid + 1;
    }
    // ansL = 6;
    // write(ansL);
    fuck(ansL);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "s" << endl;
    // system("pause");
#endif
    return 0;
}