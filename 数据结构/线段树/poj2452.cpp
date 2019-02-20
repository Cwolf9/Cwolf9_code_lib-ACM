#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

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
}BUFF;
#define read(x) x=getnum()
#define write(x) putnum(x),putchar(' ')
#define writeln(x) putnum(x),putchar('\n')

inline LL getnum(){
    LL r=0;bool ng=0;char c;c=BUFF.get();
    while(c!='-'&&(c<'0'||c>'9'))c=BUFF.get();
    if(c=='-')ng=1,c=BUFF.get();
    while(c>='0'&&c<='9')r=r*10+c-'0',c=BUFF.get();
    return ng?-r:r;
}
template<class T> inline void putnum(T x){
    if(x<0)putchar('-'),x=-x;
    register short a[20]={},sz=0;
    while(x)a[sz++]=x%10,x/=10;
    if(sz==0)putchar('0');
    for(int i=sz-1;i>=0;i--)putchar('0'+a[i]);
}
inline char getreal(){char c=BUFF.get();while(c<=32)c=BUFF.get();return c;}


const int MXN = 1e5 + 5;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;


int n, m;
int ar[MXN], que[MXN], rightMin[MXN];
pii sum[MXN<<2];
void build(int l,int r,int rt) {
    if(l == r) {
        sum[rt].first = l;
        sum[rt].second = ar[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l,mid,rt<<1), build(mid+1,r,rt<<1|1);
    if(sum[rt<<1].second >= sum[rt<<1|1].second) {
        sum[rt] = sum[rt<<1];
    }else {
        sum[rt] = sum[rt<<1|1];
    }
}
pii query(int L,int R,int l,int r,int rt) {
    if(L == l && r == R) {
        return sum[rt];
    }
    int mid = (l+r)>>1;
    if(L > mid) return query(L,R,mid+1,r,rt<<1|1);
    else if(R <= mid) return query(L,R,l,mid,rt<<1);
    else {
        pii a = query(L,mid,l,mid,rt<<1);
        pii b = query(mid+1,R,mid+1,r,rt<<1|1);
        if(a.second >= b.second) return a;
        return b;
    }
}
int main(){
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &ar[i]);
        }
        build(1, n, 1);
        int front = 0, near = 0;
        for(int i = n; i >= 1; --i) {
            while(front<near&&ar[que[near-1]]>ar[i]) -- near;
            if(front == near) rightMin[i] = -1;
            else rightMin[i] = que[near-1];
            que[near ++] = i;
        }
        /*printf("***\n");
        for(int i = 1; i <= n; ++i) {
            printf("%d ", rightMin[i]);
        }
        printf("\n");*/
        int ans = -1;
        for(int i = 1, tmp; i <= n - 1; ++i) {
            if(rightMin[i] == i + 1) continue;
            tmp = rightMin[i] - 1;
            if(rightMin[i] == -1) tmp = n;
            pii hh = query(i, tmp, 1, n, 1);
            ans = max(ans, hh.first - i);
            if(ans >= n - i) break;
        }
        if(ans == 0) ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}