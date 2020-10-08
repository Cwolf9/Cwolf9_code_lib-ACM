#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
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
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
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

const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MXN = 2e5 + 5;
struct FenwickTree {
//sum[i] = sigma(ar[x])+(i+1)*sigma(delta[x])-sigma(x*delta[x])
//delta[]是差分数组
    int n;
    int pre[MXN], delta[MXN], deltai[MXN];
    void add(int *a, int x, int v){
        while(x <= n){
            a[x] += v;
            x += lowbit(x);
        }
    }
    int query(int *a, int x){
        int sum = 0;
        while(x > 0){
            sum += a[x];
            x -= lowbit(x);
        }
        return sum;
    }
    void init(int *ar, int _n) {
        n = _n;
        pre[0] = 0;
        for(int i = 1; i <= n; ++i) pre[i] = pre[i-1] + ar[i];
    }
    void update(int l, int r, int x){
        add(delta, l, x);add(delta, r+1, -x);
        add(deltai, l, l*x);add(deltai, r+1, -x*(r+1));
    }
    int range(int l, int r){
        int sum1 = pre[l-1]+l*query(delta, l-1)-query(deltai, l-1);
        int sum2 = pre[r]+(r+1)*query(delta, r)-query(deltai, r);
        return sum2-sum1;
    }
}bit;

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    string s;
    while(getline(cin, s)) {
        cout << "\"" << s << "\",\n";
    }
    return 0;
}