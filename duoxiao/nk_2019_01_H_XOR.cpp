#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 63
#define mk make_pair
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define clr(a,b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef pair<int, int> pii;
inline LL read(){
    LL x=0;int f=0;char ch=getchar();
    while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x=f?-x:x;
}
inline void write(LL x) {
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
void debug_out() { cerr << '\n'; }
template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cerr << f << " "; debug_out (r...); }
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

#define print(x) write(x);

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 998244353 ;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 1e5 + 7;
int n, m;
LL id[MXN], bs[MXN], two[MXN], bsB[MXN];
int cnt, inBase[MXN];
LL ksm(LL a, int b) {LL res = 1;for (; b; b >>= 1, a = a * a % MOD)if (b & 1)res = res * a % MOD;return res;}
bool insert(LL x, LL *bs) {
    for(int j = BASE_MAX; j >= 0; --j) {//63
        if(!(x >> j)) continue;
        if(bs[j]) x ^= bs[j];
        else {
            bs[j] = x;
            for(int k = j-1; k >= 0; --k) if(bs[k]&&(bs[j]&(1LL<<k))) bs[j]^=bs[k];
            for(int k = j+1; k <= BASE_MAX; ++k) if(bs[k]&(1LL<<j)) bs[k]^=bs[j];
            return true;
        }
    }
    return false;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    two[0] = 1;
    for(int i = 1; i < MXN; ++i) two[i] = two[i-1] * 2 % MOD;
    while(~scanf("%d", &n)) {
        cnt = 0;
        for(int i = 0; i <= BASE_MAX; ++i) bs[i] = 0;
        vector<LL> baseR;
        for(int i = 1; i <= n; ++i) {
            id[i] = read(), inBase[i] = 0;
            if(insert(id[i], bs)) ++ cnt, inBase[i] = 1, baseR.eb(id[i]);
        }
        if(cnt == n) {
            printf("0\n");
            continue;
        }
        LL ans = (LL)(n - cnt)*two[n - cnt - 1]%MOD;
        for(int i = 0; i <= BASE_MAX; ++i) bs[i] = 0;
        int sizB = 0;
        for(int i = 1; i <= n; ++i) {
            if(inBase[i]) continue;
            if(insert(id[i], bs)) ++ sizB;
        }
//        debug(ans)
        int tmp = sizB;
        for(auto x: baseR) {
            memcpy(bsB, bs, sizeof(LL)* 64);
            sizB = tmp;
            for(auto y: baseR) {
                if(x != y && insert(y, bsB)) ++ sizB;
            }
            if(!insert(x, bsB)) ans = (ans + two[n-sizB-1]) % MOD;
//            debug(flag, sizB)
        }
        printf("%lld\n", (ans+MOD)%MOD);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << (double)clock()/CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
/*
1
0
3
1 2 3
2
1000000000000000000 1000000000000000000

1
3
2
 */