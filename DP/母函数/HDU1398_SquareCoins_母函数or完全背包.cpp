/*
https://blog.csdn.net/xiaofei_it/article/details/17042651
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<string>
#include<cmath>
#define test printf("***\n")
#define mlr(a) memset((a),0,sizeof((a)))
#define mmx(a) memset((a),0x3f,sizeof((a)))
#define ka getchar();getchar()
#define ka1 getchar()
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 1005;
const int INF = 1e9;
const double eps = 1e-8;
int n;
LL a[N],b[N];
int s[N],e[N],v[N];
void mu(int n){
    memset(a,0,sizeof(a));
    a[0]=1;
    int last=0,last2=0;
    for(int i=0;i<17;++i){//枚举因子
        memset(b,0,sizeof(b));
        last2=min(last+e[i]*v[i],n);
        for(int j=s[i];j<=e[i]&&j*v[i]<=n;++j){//枚举因子个数
            for(int k=0;k+j*v[i]<=last2;++k){//枚举和
                b[k+j*v[i]]+=a[k];
            }
        }
        for(int j=0;j<=e[i];++j)a[j]=b[j];
        last=last2;
    }   
}
int main(){
    for(int i=0;i<17;++i){
        s[i]=0;
        e[i]=300;
        v[i]=(i+1)*(i+1);
    }
    mu(300);
    while(~scanf("%d",&n)&&n){
        printf("%lld\n", a[n]);
    }
    return 0;
}
