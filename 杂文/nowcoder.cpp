#include<bits/stdc++.h>
#define endl "\n"
#define fi first
#define se second
#define eb emplace_back
#define mk make_pair
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
typedef vector<int> VI;
typedef vector<pii> VPII;
string to_string(string s) {return '"' + s + '"';}string to_string(const char* s) {return to_string((string) s);}string to_string(bool b) {return (b ? "true" : "false");}template <typename A, typename B>string to_string(pair<A, B> p) {return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";}template <typename A>string to_string(A v) {bool first = true;string res = "{";for (const auto &x : v) {if (!first) {res += ", ";}first = false;res += to_string(x);}res += "}";return res;}void debug_out() { cerr << endl; }template <typename Head, typename... Tail>void debug_out(Head H, Tail... T) {cerr << " " << to_string(H);debug_out(T...);}
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
const LL INFLL = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
const int MOD = 998244353;
const int MXE = 1e6 + 6;
const int MXN = 3e5 + 6;

int n, m;
int ar[MXN];
int nxl[MXN], nxr[MXN];
int lid[MXN][20], rid[MXN][20];
LL lsum[MXN][20], rsum[MXN][20];
int stak[MXN], top;

void init() {
    for(int i = n; i >= 0; --i) {
        while(top && ar[stak[top]] <= ar[i]) -- top;
        if(top == 0) nxr[i] = n;
        else nxr[i] = stak[top];
        stak[++top] = i;
    }
    top = 0;
    for(int i = 0; i <= n; ++i) {
        while(top && ar[stak[top]] <= ar[i]) -- top;
        if(top == 0) nxl[i] = 0;
        else nxl[i] = stak[top];
        stak[++top] = i;
    }
}
void rmq_init() {
    memset(rid, 0x3f, sizeof(rid));
    memset(lid, -1, sizeof(lid));
    for(int i = 0; i <= n; ++i) {
        rid[i][0] = nxr[i]; lid[i][0] = nxl[i];
        rsum[i][0] = (LL)ar[i]*(nxr[i] - i);
        lsum[i][0] = (LL)ar[i]*(i - nxl[i]);
        if(lsum[i][0] >= INF) lsum[i][0] = 0;
        if(rsum[i][0] >= INF) rsum[i][0] = 0;
    }
    for(int j = 1; j < 20; ++j) {
        for(int i = 0; i + (1<<j) - 1 <= n; ++i) {
            rid[i][j] = rid[rid[i][j-1]][j-1];
            rsum[i][j] = rsum[i][j-1] + rsum[rid[i][j-1]][j-1];
        }
    }
    for(int j = 1; j < 20; ++j) {
        for(int i = n; i - (1<<j) + 1 >= 0; --i) {
            lid[i][j] = lid[lid[i][j-1]][j-1];
            lsum[i][j] = lsum[i][j-1] + lsum[lid[i][j-1]][j-1];
        }
    }
}
LL niquery(int st, int ed) {//大小
    LL ans = 0;
    for(int i = 19; i >= 0; --i) {
        if(lid[st][i] >= ed) {
            ans += lsum[st][i];
            st = lid[st][i];
        }
    }
    if(st != ed) ans += lsum[st][0];
    return ans;
}
LL query(int st, int ed) {//小大
    LL ans = 0;
    for(int i = 19; i >= 0; --i) {
        if(rid[st][i] <= ed) {
            ans += rsum[st][i];
            st = rid[st][i];
        }
    }
    if(st != ed) ans += rsum[st][0];
    return ans;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);
#endif
    scanf("%d", &n); ar[0] = ar[n] = INF;
    for(int i = 1; i < n; ++i) scanf("%d", &ar[i]);
    init();
    rmq_init();
    /*for(int i = 0; i <= n; ++i) printf("%d ", nxl[i]); printf("\n");
    for(int i = 0; i <= n; ++i) printf("%d ", nxr[i]); printf("\n");
    for(int i = 0; i <= n; ++i) printf("%lld ", lsum[i][0]); printf("\n");
    for(int i = 0; i <= n; ++i) printf("%lld ", rsum[i][0]); printf("\n");*/
    scanf("%d", &m);
    while(m --) {
        int l, r; scanf("%d%d", &l, &r);
        if(l == r) printf("0\n");
        else if(l < r) printf("%lld\n", niquery(r-1, l-1));
        else printf("%lld\n", query(r, l));
    }
    return 0;
}https://www.jianshu.com/p/b71fc7307e42