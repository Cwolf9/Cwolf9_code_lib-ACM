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
#define my_unique(x) sort(a(x)),x.erase(unique(a(x)),x.end())
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

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 1e9 + 6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 2e6 + 7;

int n, m, p;
int fa[50005];
int Fi(int x) {
    return fa[x] == x? x: fa[x] = Fi(fa[x]);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &p);
    for(int i = 1, a, b; i <= m; ++i) {
        scanf("%d%d", &a, &b);
        int pa = Fi(a), pb = Fi(b);
        if(pa != pb) fa[pa] = pb;
    }
    while(p --) {
        int a, b; scanf("%d%d", &a, &b);
        if(Fi(a) == Fi(b)) {
            printf("YES\n");
        }else {
            printf("NO\n");
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
