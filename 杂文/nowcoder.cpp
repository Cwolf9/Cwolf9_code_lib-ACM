#include<bits/stdc++.h>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)
#define eb emplace_back
#define o2(x) (x)*(x)
using namespace std;
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
const int INF = 0x3f3f3f3f;
const LL mod = 998244353;
const int MXN = 1e3 + 7;

int n, m;
map<pii, int> mp1, mp2;
int main(int argc, char const *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);
#endif
    n = read(), m = read();
    
    return 0;
}