//500ms 600ms 1000ms wa3
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;

const double san = 1e5;
const int MXN = 2005;

int n;
struct buf{
    int x, y;
    buf(){}
    buf(int a,int b){x = a, y = b;}
    buf add(buf &a){
        buf b;
        b.x = x + a.x;
        b.y = y + a.y;
        return b;
    }
};
struct node{
    int x, y, z;
}edge[MXN];
double LEN(double x, double y, double z){
    return x*x+y*y+z*z;
}
double get(double x, double y, double z) {
    double ans = 0;
    for(int i = 0; i < n; ++i) ans = max(ans, LEN(edge[i].x-x,edge[i].y-y,edge[i].z-z));
    return ans;
}
double getz(double x, double y) {
    double L = -san, R = san, mid1, mid2, ans;
    for(int i = 0; i < 60; ++i) {
        mid1 = (L+R)/2;
        mid2 = (mid1+R)/2;
        if(get(x, y, mid1) < get(x, y, mid2)) R = mid2, ans = mid1;
        else L = mid1, ans = mid2;
    }
    return ans;
}
pair<double,double> getyz(double x) {
    double L = -san, R = san, mid1, mid2, z1, z2;
    pair<double,double> ans;
    for(int i = 0; i < 60; ++i) {
        mid1 = (L+R)/2;
        mid2 = (mid1+R)/2;
        z1 = getz(x, mid1);
        z2 = getz(x, mid2);
        if(get(x, mid1, z1) < get(x, mid2, z2)) {
            R = mid2, ans.first = mid1, ans.second = z1;
        }else {
            L = mid1, ans.first = mid2, ans.second = z2;
        }
    }
    return ans;
}
int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].z);
        }
        double L = -san, R = san, mid1, mid2, ans;
        pair<double,double> x1, x2, x3;
        for(int i = 0; i < 60; ++i) {
            mid1 = (L+R)/2;
            mid2 = (mid1+R)/2;
            x1 = getyz(mid1);
            x2 = getyz(mid2);
            if(get(mid1,x1.first,x1.second) < get(mid2,x2.first,x2.second)) {
                R = mid2, ans = mid1; x3 = x1;
            }else {
                L = mid1, ans = mid2; x3 = x2;
            }
        }
        ans = get(ans, x3.first, x3.second);
        printf("%.10f\n", sqrt(ans));
    }
    return 0;
}


#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;

const double san = 1e5;
const int MXN = 2005;

int n;
double X, Y, Z;
struct buf{
    int x, y;
    buf(){}
    buf(int a,int b){x = a, y = b;}
    buf add(buf &a){
        buf b;
        b.x = x + a.x;
        b.y = y + a.y;
        return b;
    }
};
struct node{
    int x, y, z;
}edge[MXN];
double LEN(double x, double y, double z){
    return x*x+y*y+z*z;
}
double get(double x, double y, double z) {
    double ans = 0;
    for(int i = 0; i < n; ++i) ans = max(ans, LEN(edge[i].x-x,edge[i].y-y,edge[i].z-z));
    return ans;
}
double getz(double x, double y) {
    double L = -san, R = san, mid1, mid2;
    for(int i = 0; i < 60; ++i) {
        mid1 = (L+R)/2;
        mid2 = (mid1+R)/2;
        if(get(x, y, mid1) < get(x, y, mid2)) R = mid2;
        else L = mid1;
    }
    double tmp = (mid1+mid2)/2, ans = min(get(x,y,L),get(x,y,R));
    ans = min(ans, min(get(x,y,mid1),get(x,y,mid2)));
    return min(ans, get(x,y,tmp));
}
double getyz(double x) {
    double L = -san, R = san, mid1, mid2;
    for(int i = 0; i < 60; ++i) {
        mid1 = (L+R)/2;
        mid2 = (mid1+R)/2;
        if(getz(x, mid1) < getz(x, mid2)) R = mid2;
        else L = mid1;
    }
    double tmp = (mid1+mid2)/2, ans = min(getz(x,L),getz(x,R));
    ans = min(ans, min(getz(x,mid1),getz(x,mid2)));
    return min(ans, getz(x,tmp));
}
int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].z);
        }
        double L = -san, R = san, mid1, mid2;
        for(int i = 0; i < 60; ++i) {
            mid1 = (L+R)/2;
            mid2 = (mid1+R)/2;
            if(getyz(mid1) < getyz(mid2)) R = mid2;
            else L = mid1;
        }
        double tmp = (mid1+mid2)/2, ans = min(getyz(L),getyz(R));
        ans = min(ans, min(getyz(mid1),getyz(mid2)));
        ans = min(ans, getyz(tmp));
        printf("%.10f\n", sqrt(ans));
    }
    return 0;
}


#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const double eps=1e-7;
typedef struct {double p[3];}point;
point a[maxn];
int n;
double cal(point now){
    double ans=0.0;
    for(int i=0;i<n;i++)
        ans=max(ans,sqrt((a[i].p[0]-now.p[0])*(a[i].p[0]-now.p[0])+(a[i].p[1]-now.p[1])*(a[i].p[1]-now.p[1])+(a[i].p[2]-now.p[2])*(a[i].p[2]-now.p[2])));
    return ans;
}
point del(point now,int cnt){
    if(cnt>=3) return now;
    double r=100000,l=-100000;
    double dr,dl;
    point tp1,tp2,ans1,ans2,ans;
    tp1=tp2=ans=now;
    while(r-l>eps){
        dr=(2*r+l)/3;
        dl=(2*l+r)/3;
        tp1.p[cnt]=dl;
        tp2.p[cnt]=dr;
        ans1=del(tp1,cnt+1);
        ans2=del(tp2,cnt+1);
        if(cal(ans1)>cal(ans2)){
            l=dl;
            ans=ans1;
        }else{
            r=dr;
            ans=ans2;
        }
    }
    return ans;
}
int main(){
    while(scanf("%d",&n)!=EOF){
        for(int i=0;i<n;i++)
            scanf("%lf%lf%lf",&a[i].p[0],&a[i].p[1],&a[i].p[2]);
        point ans;
        printf("%.10f\n",cal(del(ans,0)));
    }
    return 0;
}
3
0 0 0
3 0 0
0 4 0
4
0 0 0
1 0 0
0 1 0
0 0 1
2.500000590252103
0.816496631812619

https://www.cnblogs.com/heisenberg-/p/6827790.html
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const double eps=1e-7;
struct point3D{
    double x,y,z;
} data[105];
int n;
double dis(point3D a,point3D b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
double solve(){
    double step=1000,ans=1e30,mt;
    point3D z;
    z.x=z.y=z.z=0;
    int s=0;
    while(step>eps){
        for(int i=0; i<n; i++)
            if(dis(z,data[s])<dis(z,data[i])) s=i;
        mt=dis(z,data[s]);
        ans=min(ans,mt);
        z.x+=(data[s].x-z.x)/mt*step;
        z.y+=(data[s].y-z.y)/mt*step;
        z.z+=(data[s].z-z.z)/mt*step;
        step*=0.98;
    }
    return ans;
}
int main(){
    double ans;
    while(scanf("%d",&n)!=EOF){
        for(int i=0; i<n; i++)
            scanf("%lf%lf%lf",&data[i].x,&data[i].y,&data[i].z);
        ans=solve();
        printf("%.7f\n",ans);
    }
    return 0;
}




#include <bits/stdc++.h>
#define o2(x) (x)*(x)
using namespace std;
typedef long long LL;
const int MXN = 1e5 + 5;
int n;
int x[MXN], y[MXN], z[MXN];
double len(double X, double Y, double Z, int i) {
    return o2(X-x[i])+o2(Y-y[i])+o2(Z-z[i]);
}
double exe3(double X, double Y, double Z) {
    double ans = 0;
    for(int i = 1; i <= n; ++i) ans = max(ans, len(X,Y,Z,i));
    return ans;
}
double exe2(double X, double Y) {
    double l = -1e6, r = 1e6, midl, midr, ans;
    for(int i = 0; i < 70; ++i) {
        midl = (l+r)/2;
        midr = (midl+r)/2;
        if(exe3(X, Y, midl) <= exe3(X, Y, midr)) {
            r = midr, ans = midl;
        }else {
            l = midl, ans = midr;
        }
    }
    return exe3(X, Y, ans);
}
double exe1(double X) {
    double l = -1e6, r = 1e6, midl, midr, ans;
    for(int i = 0; i < 70; ++i) {
        midl = (l+r)/2;
        midr = (midl+r)/2;
        if(exe2(X, midl) <= exe2(X, midr)) {
            r = midr, ans = midl;
        }else {
            l = midl, ans = midr;
        }
    }
    return exe2(X, ans);
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d%d%d", &x[i], &y[i], &z[i]);
    double l = -1e6, r = 1e6, midl, midr, ans;
    for(int i = 0; i < 70; ++i) {
        midl = (l+r)/2;
        midr = (midl+r)/2;
        if(exe1(midl) <= exe1(midr)) {
            r = midr, ans = midl;
        }else {
            l = midl, ans = midr;
        }
    }
    double tmp = exe1(ans);
    printf("%.9f\n", sqrt(tmp));
    return 0;
}