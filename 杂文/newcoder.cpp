//#include<bits/stdc++.h>
#include <cstdio>
#include <cmath>
#include <map>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#define fi first
#define se second
#define iis std::ios::sync_with_stdio(false)

namespace lh {
#define o2(x) (x)*(x)
    using namespace std;
    typedef long long LL;
    typedef unsigned long long uLL;
    typedef pair<LL, LL> pii;
}

using namespace lh;

const int MXN = 1e5 + 7;
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
int n;
int mu[MXN], prim[MXN], noprime[MXN], cnt;
void get_mu(int n) {
    mu[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!noprime[i]) { prim[++cnt] = i; mu[i] = -1; }
        for(int j = 1; j <= cnt && prim[j] * i <= n; ++j) {
            noprime[prim[j] * i] = 1;
            if(i % prim[j] == 0) break;
            mu[i * prim[j]] = -mu[i];
        }
    }
}
int main() {
    get_mu(100000);
    while(~scanf("%d", &n)) {
        printf("%d\n", mu[n]);
    }
    return 0;
}
1.17：线段树：ppq
1.19：基础数论相关：pph
1.22：并查集&mst
1.24：最短路：py
1.29：树状数组：llw
2.1：RMQ&LCA
/*int main() {
    int tim; scanf("%d", &tim);
    while(tim --) {
        scanf("%d%d", &n, &m);
        int tn = n, num = 0;
        while(tn % 10 == 0) tn /= 10, num++;
        n = tn;
        bitset<11> a, b;
        for(int i = 0; i < m; ++i) {
            scanf("%d", &ar[i]);
            a.set(ar[i]);
        }
        sort(ar, ar+m);
        LL tmp = ar[0], ret;
        for(int i = 1; i < m; ++i) {
            tmp = tmp * 10 + ar[i];
        }
        if(a.test(0)) tmp *= 10;
        tmp = max(n*1LL, tmp);
        int flag;
        while(1) {
            flag = 1;
            ret = tmp;
            b.reset();
            while(ret) {
                b.set(ret % 10);
                ret /= 10;
            }
            for(int i = 0; i < 10; ++i) {
                if(a.test(i) && b.test(i) == 0) {
                    flag = 0; break;
                }
            }
            if(flag) {
                while(num --) tmp *= 10;
                printf("%lld\n", tmp);
                break;
            }
            tmp += n;
        }
    }
    return 0;
}
*/