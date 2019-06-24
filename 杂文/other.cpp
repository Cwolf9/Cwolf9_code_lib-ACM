#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MXN = 2e6+ 7;
LL mud = 998244353;
LL mod = 998244353;
LL n, m;
int noprime[MXN], pp[MXN], pcnt;
int phi[MXN], mu[MXN], a1[MXN];
LL pre_phi[MXN], pre_g[MXN], g[MXN];
void init_prime() {
    noprime[0] = noprime[1] = 1;
    mu[1] = 1; phi[1] = 1; g[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, phi[i] = i-1, mu[i] = -1, g[i] = 2, a1[i] = 1;
        for(int j = 0; j < pcnt && pp[j] * i < MXN; ++j) {
            noprime[pp[j]*i] = 1;
            phi[pp[j]*i] = (pp[j]-1)*phi[i];
            mu[pp[j]*i] = -mu[i];
            g[i*pp[j]] = g[i] * 2;
            a1[i*pp[j]] = 1;
            if(i % pp[j] == 0) {
                phi[pp[j]*i] = pp[j]*phi[i];
                mu[pp[j]*i] = 0;
                a1[i*pp[j]] = a1[i] + 1;
                g[i*pp[j]] = g[i]*(a1[i*pp[j]]+1)/a1[i*pp[j]];
                break;
            }
        }
    }
}
LL ksm(LL a, int b, LL p) {
    LL res = 1;
    while(b) {
        if(b&1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
// struct Hash_map{
//     static const int mask=0x7fffff;
//     LL p[mask+1],q[mask+1];
//     void clear(){
//         memset(q,0,sizeof(q));
//     }
//     LL& operator [](LL k){
//         LL i;
//         for(i=k&mask;q[i]&&p[i]!=k;i=(i+1)&mask);
//         p[i]=k;
//         return q[i];
//     }
// }mp1, mp2;
unordered_map<LL, LL> mp1, mp2;
LL solve_g(LL n) {
    if(n < MXN) return pre_g[n];
    if(mp1.find(n) != mp1.end()) return mp1[n];
    //if(mp1[n]) return mp1[n];
    //if(mp1.count(n)) return mp1[n];
    LL ans = 0;
    for(LL L = 1, R; L <= n; L = R + 1) {
        R = n/(n/L);
        ans = (ans + ((n/L)*(n/L+1)/2)%mod*((R-L+1)*(L+R)/2)%mod)%mod;
    }
    ans = (ans + mod) % mod;
    mp1[n] = ans;
    return ans;
}
LL solve_phi(LL n) {
    if(n < MXN) return pre_phi[n];
    if(mp2.find(n) != mp2.end()) return mp2[n];
    //if(mp2[n]) return mp2[n];
    //if(mp2.count(n)) return mp2[n];
    LL ans = n*(n+1)/2;
    for(LL L = 2, R; L <= n; L = R + 1) {
        R = n/(n/L);
        ans = (ans - (R-L+1)*solve_phi(n/L)%mod)%mod;
    }
    ans = (ans + mod) % mod;
    mp2[n] = ans;
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);
#endif
    init_prime();
    scanf("%lld%lld%lld", &n, &m, &mud);
    //mp1.clear(); mp2.clear();
    mod = mud - 1;
    for(int i = 1; i < MXN; ++i) {
        pre_phi[i] = (pre_phi[i-1] + phi[i])%mod;
        pre_g[i] = (pre_g[i-1] + i * g[i] % mod)%mod;
    }
    LL ans = 0;
    for(LL L = 1, R; L <= n; L = R + 1) {
        R = n/(n/L);
        ans = (ans + (solve_g(R)-solve_g(L-1))%mod*(solve_phi(n/L)*2LL%mod-1LL)%mod)%mod;
    }
    ans = (ans+mod)%mod;
    printf("%lld\n", ksm(m, ans, mud));
#ifndef ONLINE_JUDGE
  cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}

// 当x≥ϕ(p)时，有a^x ≡ a^(x mod ϕ(p)+ϕ(p)) mod p
// gcd(a,mod)=1  a^(x) = a^(x%ϕ(mod)) % mod
apache-tomcat-9.0.21
there is no configured/running web-servers
update mysql.user set authentication_string=password("123456") where user="cdn";