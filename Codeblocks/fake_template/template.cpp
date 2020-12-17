#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mk make_pair
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
typedef long long LL;
typedef pair<int, int> pii;
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
const int mod = 998244353;
int ksm(int a, int64 b, int kmod = mod) {int res = 1;for(;b > 0;b >>= 1, a = (int64)a * a % kmod) if(b &1) res = (int64)res * a % kmod;return res;}
const int INF = 0x3f3f3f3f;
const int MXN = 2e5 + 5;

int n, m;
void work() {
    n = read();
}
int main() {
    for(int cas = 1, tim = 1; cas <= tim; ++ cas) {
        // printf("Case #%d:\n", cas);
        work();
    }
    return 0;
}
