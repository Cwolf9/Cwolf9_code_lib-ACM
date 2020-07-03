#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 30
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
const int MXN = 1e6 + 7;

int n, m;
struct Linear_Bases {
    int b[BASE_MAX + 1], rpos[BASE_MAX+1];
}bs[MXN];
bool insert(int x, int r, int *bs, int *pos) {
    for(int j = BASE_MAX; j >= 0; --j) {
        if(!(x >> j)) continue;
        if(bs[j]) {
            if(pos[j] < r) {
                swap(pos[j], r);
                swap(bs[j], x);
            }
            x ^= bs[j];
        }else {
            bs[j] = x;
            pos[j] = r;
//            for(int k = j-1; k >= 0; --k) if(bs[k]&&(bs[j]&(1<<k))) bs[j]^=bs[k];
//            for(int k = j+1; k <= BASE_MAX; ++k) if(bs[k]&(1<<j)) bs[k]^=bs[j];
            return true;
        }
    }
    return false;
}
int query(int l, int r) {
    int ans = 0;
    for(int i = BASE_MAX; i >= 0; --i) if(bs[r].b[i] && bs[r].rpos[i] >= l) ans = max(bs[r].b[i]^ans, ans);
    return ans;
}
int ar[10];
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    int tim = read();
    while(tim --) {
        n = read(), m = read();
        for(int i = 0; i <= BASE_MAX; ++i) bs[0].b[i] = bs[0].rpos[i] = 0;
        for(int i = 1, x; i <= n; ++i) {
            x = read();
            bs[i] = bs[i-1];
            insert(x, i, bs[i].b, bs[i].rpos);
        }
        int lastans = 0;
        while(m --) {
            int opt = read(), l = read();
            if (opt == 0) {
                int r = read();
                l = (l ^ lastans) % n + 1;
                r = (r ^ lastans) % n + 1;
                if(l > r) swap(l, r);
                lastans = query(l, r);
                printf("%d\n", lastans);
            } else {
                l = l ^ lastans;
                ++ n;
                bs[n] = bs[n - 1];
                insert(l, n, bs[n].b, bs[n].rpos);
            }
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}

/*
 * 分块：https://www.cnblogs.com/Juanzhang/p/10877782.html
 * 分治：https://hk-cnyali.com/2019/02/11/%E3%80%8CCF1100F%E3%80%8DIvan-and-Burgers-%E7%BA%BF%E6%80%A7%E5%9F%BA-%E5%88%86%E6%B2%BB/
 * */

