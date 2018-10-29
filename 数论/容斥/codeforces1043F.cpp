#include<bits/stdc++.h> 
using namespace std;
typedef long long LL;

const int MXN = 4e5 + 6;
const int INF = 0x3f3f3f3f;

struct fastio{
    char s[100005];
    int it,len;
    fastio(){it=len=0;}
    inline char get(){
        if(it<len)return s[it++];it=0;
        len=fread(s,1,100000,stdin);
        if(len==0)return EOF;else return s[it++];
    }
    bool notend(){
        char c=get();
        while(c==' '||c=='\n')c=get();
        if(it>0)it--;
        return c!=EOF;
    }
}_buff;
#define read(x) x=getnum()
#define write(x) putnum(x),putchar('\n')

inline LL getnum(){
    LL r=0;bool ng=0;char c;c=_buff.get();
    while(c!='-'&&(c<'0'||c>'9'))c=_buff.get();
    if(c=='-')ng=1,c=_buff.get();
    while(c>='0'&&c<='9')r=r*10+c-'0',c=_buff.get();
    return ng?-r:r;
}
template<class T> inline void putnum(T x){
    if(x<0)putchar('-'),x=-x;
    register short a[20]={},sz=0;
    while(x)a[sz++]=x%10,x/=10;
    if(sz==0)putchar('0');
    for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline char getreal(){char c=_buff.get();while(c<=32)c=_buff.get();return c;}
/*
基于一个观察
如果存在恰好选k个数gcd为1的方案
那么一定存在至少选k个数gcd为1的方案
然后解一个恰好选的问题
从一个数x的倍数里选k个数，它们的gcd一定是x的倍数
假设已经算出gcd是2x 3x ...的方案数
那么就可以算出gcd是x的方案数了
对于x还要容斥减去gcd是2x 3x ...的方案数
%%%tls
*/
const int mod[2] = {(int)1e9 + 7, (int)1e9 + 9};
int n, m;
int ar[MXN], sum[MXN];
LL tmp[MXN], f[MXN], inv[2][MXN];;
int gcd(int a,int b) {
    return b == 0? a: gcd(b, a%b);
}
bool ok(int s) {
    for(int o = 0; o < 2; ++o) {
        //预处理组合数C(i, s)
        for(int i = 0; i < s; ++i) f[i] = 0;
        LL cf = 1;
        for(int i = s; i <= n; ++i) {
            f[i] = cf;
            cf = cf * (i+1) % mod[o] * inv[o][i+1-s] % mod[o];
        }
        for(int i = m; i >= 1; --i) {
            tmp[i] = f[sum[i]];
            for(int j = i + i; j <= m; j += i) {
                tmp[i] -= tmp[j];//容斥
                if(tmp[i] < 0) tmp[i] = (tmp[i] + mod[o]) % mod[o];
            }
        }
        if(tmp[1]) return 1;
    }
    return 0;
}
int main() {
    for(int o = 0; o < 2; ++o) {
        LL p = mod[o];
        inv[o][1] = 1;
        for(int i = 2; i < MXN; ++i)//预处理逆元
            inv[o][i] = p - (p / i * inv[o][p % i] % p);
    }
    read(n);
    int p = 0;
    m = 0;
    for(int i = 1; i <= n; ++i) {
        read(ar[i]);
        m = m > ar[i]? m: ar[i];
        p = gcd(p, ar[i]);
        ++ sum[ar[i]];
    }
    if(p != 1) {
        write(-1);
        return 0;
    }
    //预处理每个因子出现的次数
    for(int i = 1; i <= m; ++i) {
        for(int j = i << 1; j <= m; j += i) {
            sum[i] += sum[j];
        }
    }
    int ans = 1, L = 1, R = min(n, 7), mid;
    while(R >= L) {
        mid = (L + R) >> 1;
        if(ok(mid)) ans = mid, R = mid - 1;
        else L = mid + 1;
    }
    write(ans);
    return 0;
}
/*
int main() {
    read(n);
    int p = 0, m = 0;
    //题目要求的是最少k个数, 所以此法正确
    for(int i = 1; i <= n; ++i) {
        read(ar[i]);
        m = m > ar[i]? m: ar[i];
        p = gcd(p, ar[i]);
        sum[ar[i]] = is[ar[i]] = 1;//只关心gcd为i是否存在
    }
    if(p != 1) {
        puts("-1");
        return 0;
    }
    int ans = 1;
    //sum[i]表示选出ans个数gcd为i是否存在, sum[i]累加
    while(1) {
        if(sum[1]) break;
        for(int i = 1; i <= m; ++i) tmp[i] = 0;
        for(int i = m; i >= 1; --i) {
            LL sum1 = 0, sum2 = 0;
            for(int j = i; j <= m; j += i) {
                tmp[i] -= tmp[j];//容斥
                sum1 += sum[j]; sum2 += is[j];
            }
            tmp[i] += sum1 * sum2;
        }
        for(int i = 1; i <= m; ++i) {
            sum[i] = tmp[i] > 0? tmp[i]: 0;
        }
        ans ++;
    }
    write(ans);
    return 0;
}
*/