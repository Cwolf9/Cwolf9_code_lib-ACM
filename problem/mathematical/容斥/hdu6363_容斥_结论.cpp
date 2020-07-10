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
const LL mod = 1e9 + 7;
const int MXN = 2e6 + 7;

LL n, k;
int Inv[MXN], F[MXN], invF[MXN];
LL g[MXN], fib[MXN];
void init() {
    Inv[0] = F[0] = invF[0] = 1; Inv[1] = F[1] = invF[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        F[i] = (LL)F[i-1] * i % mod;
        Inv[i] = (mod-mod/i)*(LL)Inv[mod%i] % mod;
        invF[i] = (LL)invF[i-1] * Inv[i] % mod;
    }
    fib[0] = 0; fib[1] = 1;
    for(int i = 2; i < MXN; ++i) fib[i] = (fib[i-1] + fib[i-2]) % (mod-1);
}
LL COMB(int x, int y) {
    if(x < y) return 0;
    if(x == y || y == 0) return 1;
    return (LL)F[x]*invF[y]%mod*invF[x-y]%mod;
}
LL ksm(LL a, int b) {
    LL res = 1;
    for(;b;b>>=1,a=a*a%mod) {
        if(b&1) res=res*a%mod;
    }
    return res;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
    init();
    int tim; tim = read();
    while(tim --) {
        n = read(), k = read();
        LL ans = 0, cnt = 0;
        for(int i = 0; i <= n; ++i) g[i] = 0;
        for(int i = n; i >= 1; --i) {//枚举gcd
            if(n % i) continue;
            g[i] = COMB((n/i)+k-1, k-1);
            for(int j = i*2; j <= n; j += i) {
                g[i] = (g[i] - g[j] + mod) % mod;
            }
            ans = (ans + ksm(2, fib[i])*g[i]%mod)%mod;
            cnt = (cnt + g[i]) % mod;
        }
        write((ans*ksm(cnt, mod-2)%mod-1+mod)%mod);
    }
    return 0;
}