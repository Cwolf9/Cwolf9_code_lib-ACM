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
int n, m;
LL t[MXN], d[MXN];
/*
n: 1e5
t: 2e6
d: 1e2
时间，每秒伤害，伤害最小
Ti*(sum-Di) = T1*sum - Ti*Di
复杂度nd可以接受
按D分成一百个桶，储存时间最短的
*/
std::vector<LL > vs[205];
int st[205];
int main() {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);
#endif
    n = read();
    assert(n >= 2 && n <= 100000);
    LL sum = 0, res = 0;
    for(int i = 1; i <= n; ++i) {
        t[i] = read(), d[i] = read();
        assert(d[i] >= 1 && d[i] <= 100);
        vs[d[i]].eb(t[i]);
        sum += d[i];
    }
    for(int i = 1; i <= 100; ++i) sort(all(vs[i]));
    for(int M = 0; M < n; ++M) {
        LL ans = INFLL, p = -1;
        for(int i = 1; i <= 100; ++i) {
            if(vs[i].size() == st[i]) continue;
            LL tmp = vs[i][st[i]] * (sum - i);
            if(tmp < ans) {
                ans = tmp; p = i;
            }
        }
        res += ans;
        sum -= p;
        ++ st[p];
    }
    write(res*2);
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
/*
或者反过来考虑，先确定最后一个移动的，最后一个变化的Di要乘上\sum_Ti
SUMT = \sum_Ti
ans = \sum_{Di*SUMT}

*/