#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <map>
#include <set>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <queue>
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
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
typedef pair<LL, int> pLi;
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
//template<class T> T big(const T& a1,const T& a2) { return a1>a2?a1:a2; }
//template<typename T, typename ...R> T big (const T& f,const R& ...r) { return big(f, big (r...)); }
//template<class T> T sml(const T& a1,const T& a2) { return a1<a2?a1:a2; }
//template<typename T, typename ...R> T sml (const T& f,const R& ...r) { return sml(f, sml (r...)); }
//void debug_out() { cerr << '\n'; }
//template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cerr << f << " "; debug_out (r...); }
//#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 1e9 + 6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 5e5 + 7;
const int MXN_T = 5e4 + 45;
const int CHAR_SIZE = 256;

LL ksm(LL a, int b) {
    LL res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
int n, m;
LL ten[MXN];
LL sum[MXN<<2], sumMi[MXN<<2];
int flag[MXN<<2];
LL flagl[MXN<<2], flagr[MXN<<2];
/*
 flagl[rt]表示加到右边的数的和
 flagr[rt]表示加到左边的数的和
 flag[rt]表示加到右边的数的位数
 sum[rt]表示区间和
 sumMi[rt]表示区间10^len(a_i)幂次和

 对数字x执行一次wrap操作后，x = d*len(d)*10^(len(x)) + x*10^(len(d)) + d, len(d) = 1
 对一个区间执行此操作后，sum(l,r) = d*10*\sum 10^len(a_i) + sum(l,r) * 10 + d * (r-l+1)
 sumMi(l,r) = \sum 10^len(a_i) = sumMi(l, r) * 100
 */
LL mul(LL a, LL b) {
    a *= b;
    if(a >= MOD) a %= MOD;
    return a;
}
LL add(LL a, LL b) {
    a += b;
    if(a >= MOD) a %= MOD;
    return a;
}
void build(int l, int r, int rt) {
    flag[rt] = flagl[rt] = flagr[rt] = 0;
    if(l == r) {
        sum[rt] = 0;
        sumMi[rt] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1), build(mid + 1, r, rt << 1 | 1);
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    sumMi[rt] = sumMi[rt<<1] + sumMi[rt<<1|1];
}
void push_down(int l, int mid, int r, int rt) {
    if(flag[rt]) {
        flagl[rt<<1] = add(mul(flagl[rt<<1],ten[flag[rt]]), flagl[rt]);
        flagl[rt<<1|1] = add(mul(flagl[rt<<1|1],ten[flag[rt]]), flagl[rt]);

        flagr[rt<<1] = add(mul(flagr[rt],ten[flag[rt<<1]]), flagr[rt<<1]);
        flagr[rt<<1|1] = add(mul(flagr[rt],ten[flag[rt<<1|1]]), flagr[rt<<1|1]);

        flag[rt<<1] += flag[rt], flag[rt<<1|1] += flag[rt];

        sum[rt<<1] = add(mul(ten[flag[rt]],mul(sumMi[rt<<1],flagr[rt])), add(mul(sum[rt<<1],ten[flag[rt]]), mul(flagl[rt],(mid-l+1))));
        sum[rt<<1|1] = add(mul(ten[flag[rt]],mul(sumMi[rt<<1|1],flagr[rt])), add(mul(sum[rt<<1|1],ten[flag[rt]]), mul(flagl[rt],(r-mid))));

        sumMi[rt<<1] = mul(sumMi[rt<<1], ten[flag[rt]*2]);
        sumMi[rt<<1|1] = mul(sumMi[rt<<1|1], ten[flag[rt]*2]);
        flag[rt] = flagl[rt] = flagr[rt] = 0;
    }
}
void update(int L, int R, int d, int l, int r, int rt) {
    if(L <= l && r <= R) {
        flagl[rt] = add(flagl[rt] * 10, d);
        flagr[rt] = add(mul(ten[flag[rt]], d), flagr[rt]);
        flag[rt] ++;
        sum[rt] = add(mul(d,sumMi[rt]*10), add(sum[rt]*10, 1LL*d*(r-l+1)));
        sumMi[rt] = mul(sumMi[rt], 100);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(l, mid, r, rt);
    if (L > mid) update(L, R, d, mid + 1, r, rt << 1 | 1);
    else if (R <= mid) update(L, R, d, l, mid, rt << 1);
    else {
        update(L, mid, d, l, mid, rt << 1), update(mid + 1, R, d, mid + 1, r, rt << 1 | 1);
    }
    sum[rt] = (sum[rt<<1] + sum[rt<<1|1])%MOD;
    sumMi[rt] = (sumMi[rt<<1] + sumMi[rt<<1|1])%MOD;
}
LL query(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) {
        return sum[rt];
    }
    int mid = (l + r) >> 1;
    push_down(l, mid, r, rt);
    if (L > mid) return query(L, R, mid + 1, r, rt << 1 | 1);
    else if (R <= mid) return query(L, R, l, mid, rt << 1);
    else {
        return (query(L, mid, l, mid, rt << 1)+ query(mid + 1, R, mid + 1, r, rt << 1 | 1))%MOD;
    }
}
int main() {
    ten[0] = 1;
    for(int i = 1; i < 400005; ++i) ten[i] = ten[i-1] * 10 % MOD;
    int tim, cas = 0;
    scanf("%d", &tim);
    while(tim --) {
        scanf("%d%d", &n, &m);
        printf("Case %d:\n", ++ cas);
        char s[10];
        int l, r, x;
        build(1, n, 1);
        while(m --) {
            scanf("%s", s);
            if(s[0] == 'w') {
                scanf("%d%d%d", &l, &r, &x);
                update(l, r, x, 1, n, 1);
            }else {
                scanf("%d%d", &l, &r);
                printf("%lld\n", query(l, r, 1, n, 1));
            }
        }
    }
    return 0;
}