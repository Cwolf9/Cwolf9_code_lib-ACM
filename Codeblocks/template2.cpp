#include <bits/stdc++.h>
using namespace std;
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
typedef long long LL;
bool Finish_read;
inline long long Rd() {long long x = 0;Finish_read = 0;int f = 1;char ch = getchar();while (!isdigit(ch)) {if (ch == '-') f = -1;if (ch == EOF) return x;ch = getchar();}while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();x *= f;Finish_read = 1;return x;}
template <class T>inline void print(T x) {if(x > 9) print(x / 10), putchar(x % 10 ^ 48);else if(x < 0) putchar('-'), print(-x);else putchar(x % 10 ^ 48);}
template <class T>inline void write(T x, char c = '\n') {print(x);putchar(c);}
#define read(x) x = Rd()
#define read2(x, y) x = Rd(), y = Rd()
#define read3(x, y, z) x = Rd(), y = Rd(), z = Rd()

constexpr int mod = 998244353;
constexpr int INF = 0x3f3f3f3f;
constexpr int mxN = 2e5 + 5;
int n, m;
int ans;
void prework() {
    read(n);
    debug(n)
}
void work() {
    
}
void finalwork() {
    write(n);
}
int main() {
    for(int Case = 1, allc = 1; Case <= allc; ++ Case) {
        prework();
        work();
        finalwork();
    }
    return 0;
}