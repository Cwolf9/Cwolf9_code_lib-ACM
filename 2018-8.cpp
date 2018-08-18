#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<queue>
#include<map>
#include<set>
#include<stack>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define bug printf("*********\n");
#define debug(x) cout<<"["<<x<<"]" <<endl;
#define mid (l+r)/2
#define chl 2*k+1
#define chr 2*k+2
#define lson l,mid,chl
#define rson mid,r,chr
#define pb push_back
#define mem(a,b) memset(a,b,sizeof(a));

const long long mod=998244353;
const int maxn=5e5+5;
const int INF=0x7fffffff;
const int inf=0x3f3f3f3f;
const double eps=1e-8;
typedef long long LL;
inline LL gcd(LL a, LL b) {
    return (!b) ? a : gcd(b, a % b);
}
inline void Exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if (!b) {
        d = a, x = 1, y = 0;
    } else {
        Exgcd(b, a % b, d, y, x), y -= x * (a / b);
    }
}
inline LL Solve(LL a, LL b, LL c) {// ax%c=b S.T. (a,c)=1
    LL d, x, y;
    Exgcd(a, c, d, x, y);
    x = (x + c) % c;
    return x * b % c;
}
inline LL Ksm(LL x, LL y, LL p) {
    LL res = 1, t = x;
    for(; y; y >>= 1) {
        if (y & 1) res = res * t % p;
        t = t * t % p;
    }
    return res;
}

#define mod 1313131
struct Hashset {
    LL head[mod], next[maxn], f[maxn], v[maxn], ind;
    void reset() {
        ind = 0;
        memset(head, -1, sizeof head);
    }
    void Insert(LL x, LL _v) {
        LL ins = x % mod;
        for(LL j = head[ins]; j != -1; j = next[j])
            if (f[j] == x) {
                v[j] = min(v[j], _v);
                return;
            }
        f[ind] = x, v[ind] = _v;
        next[ind] = head[ins], head[ins] = ind++;
    }
    LL operator [] (const LL &x) const {
        LL ins = x % mod;
        for(LL j = head[ins]; j != -1; j = next[j])
            if (f[j] == x)
                return v[j];
        return -1;
    }
} S;

LL BSGS(LL C, LL A, LL B, LL p) {// A^x%p=B S.T.(A,p)=1
    if (p <= 100) {
        LL d = 1;
        for(int i = 0; i < p; ++i) {
            if (d == B)
                return i;
            d = d * A % p;
        }
        return -1;
    } else {
        LL m = (int)sqrt(p);
        S.reset();
        LL d = 1, Search;
        for(int i = 0; i < m; ++i) {
            S.Insert(d, i);
            d = d * A % p;
        }
        for(int i = 0; i * m < p; ++i) {
            d = Ksm(A, i * m, p) * C % p;
            Search = S[Solve(d, B, p)];
            if (Search != -1)
                return i * m + Search;
        }
        return -1;
    }
}

int main() {
    LL x, z, k;
    register LL i, j;
    int t;
    scanf("%d",&t);
    while(t--) {
        scanf("%I64d%I64d%I64d", &x, &k, &z);
        LL d = 1;
        bool find = 0;
        for(i = 0; i < 100; ++i) {
            if (d == k) {
                printf("%I64d\n", i);
                find = 1;
                break;
            }
            d = d * x % z;
        }
        if (find)
            continue;

        LL t, C = 1, num = 0;
        bool failed = 0;
        while((t = gcd(x, z)) != 1) {
            z /= t;
            k /= t;
            C = C * x / t % z;
            ++num;
        }
        LL res = BSGS(C, x, k, z);
        if (res == -1)
            puts("No Solution");
        else
            printf("%I64d\n", res + num);
    }
    return 0;
}

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
 
typedef long long LL;
inline LL gcd(LL a, LL b) {
  return (!b) ? a : gcd(b, a % b);
}
inline void Exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
  if (!b) { d = a, x = 1, y = 0; }
  else { Exgcd(b, a % b, d, y, x), y -= x * (a / b); }
}
inline LL Solve(LL a, LL b, LL c) {// ax%c=b S.T. (a,c)=1
  LL d, x, y;
  Exgcd(a, c, d, x, y);
  x = (x + c) % c;
  return x * b % c;
}
inline LL Ksm(LL x, LL y, LL p) {
  LL res = 1, t = x;
  for(; y; y >>= 1) {
    if (y & 1) res = res * t % p;
    t = t * t % p;
  }
  return res;
}
 
#define mod 1313131
struct Hashset {
  int head[mod], next[35010], f[35010], v[35010], ind;
  void reset() {
    ind = 0;
    memset(head, -1, sizeof head);
  }
  void Insert(int x, int _v) {
    int ins = x % mod;
    for(int j = head[ins]; j != -1; j = next[j])
      if (f[j] == x) {
        v[j] = min(v[j], _v);
        return;
      }
    f[ind] = x, v[ind] = _v;
    next[ind] = head[ins], head[ins] = ind++;
  }
  int operator [] (const int &x) const {
    int ins = x % mod;
    for(int j = head[ins]; j != -1; j = next[j])
      if (f[j] == x)
        return v[j];
    return -1;
  }
}S;
 
LL BSGS(LL C, LL A, LL B, LL p) {// A^x%p=B S.T.(A,p)=1
  if (p <= 100) {
    LL d = 1;
    for(int i = 0; i < p; ++i) {
      if (d == B)
        return i;
      d = d * A % p;
    }
    return -1;
  }
  else {
    int m = (int)sqrt(p);
    S.reset();
    LL d = 1, Search;
    for(int i = 0; i < m; ++i) {
      S.Insert(d, i);
      d = d * A % p;
    }
    for(int i = 0; i * m < p; ++i) {
      d = Ksm(A, i * m, p) * C % p;
      Search = S[Solve(d, B, p)];
      if (Search != -1)
        return i * m + Search;
    }
    return -1;
  }
}
 
int main() {
  LL x, z, k;
  register LL i, j;
  int tim;
  scanf("%d",&tim);
  while(tim--){
    scanf("%lld%lld%lld", &x, &k, &z);
    LL d = 1;
    bool find = 0;
    for(i = 0; i < 100; ++i) {
      if (d == k) {
        printf("%lld\n", i);
        find = 1;
        break;
      }
      d = d * x % z;
    }
    if (find)continue;
    LL t, C = 1, num = 0;
    bool failed = 0;
    while((t = gcd(x, z)) != 1) {
      if (k % t != 0) {
        failed = 1;
        break;
      }
      z /= t;
      k /= t;
      C = C * x / t % z;
      ++num;
    }
    LL res = BSGS(C, x, k, z);
    printf("%lld\n", res + num);
  }
  return 0;
}
