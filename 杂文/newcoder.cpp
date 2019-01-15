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
1.17：线段树：李永琦
1.19：基础数论相关：黄迪文
1.22：最短路：彭洋
1.24：并查集&mst：李越
1.26：树状数组：李良伟
1.29：hash&kmp：李行
1.31：RMQ&LCA：刘健博

#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int x,y,k,xx,yy;
bool rook[MAXN][MAXN];
P rk[MAXN];
void mov(int dx,int dy)
{
    if(dx!=0&&dy!=0&&rook[x+dx][y+dy])
    {
        assert(!rook[x][y+dy]);
        printf("%d %d\n",x,y+dy);
        y=y+dy;
        fflush(stdout);
        scanf("%d%d%d",&k,&xx,&yy);
        assert(k==-1);
        exit(0);
    }
    printf("%d %d\n",x+dx,y+dy);
    fflush(stdout);
    x+=dx;y+=dy;
    scanf("%d%d%d",&k,&xx,&yy);
    if(k==-1) exit(0);
    rook[rk[k].F][rk[k].S]=false;
    rook[xx][yy]=true;
    rk[k]=P(xx,yy);
}
int main()
{
    scanf("%d%d",&x,&y);
    for(int i=1;i<=666;i++)
    {
        scanf("%d%d",&xx,&yy);
        rook[xx][yy]=true;
        rk[i]=P(xx,yy);
    }
    while(x<500) mov(1,0);
    while(x>500) mov(-1,0);
    while(y<500) mov(0,1);
    while(y>500) mov(0,-1);
    int cnt0=0,cnt1=0,cnt2=0,cnt3=0;
    for(int i=1;i<=666;i++)
    {
        if(rk[i].F>=500||rk[i].S<=500) cnt0++;
        if(rk[i].F>=500||rk[i].S>=500) cnt1++;
        if(rk[i].F<=500||rk[i].S>=500) cnt2++;
        if(rk[i].F<=500||rk[i].S<=500) cnt3++;
    }
    if(cnt0>=500) while(true) mov(1,-1);
    if(cnt1>=500) while(true) mov(1,1);
    if(cnt2>=500) while(true) mov(-1,1);
    if(cnt3>=500) while(true) mov(-1,-1);
    return 0;
}
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