#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;

const double san = 1e5;
const int MXN = 2005;

int n;
struct lh{
    int x, y;
    lh(){}
    lh(int a,int b){x = a, y = b;}
    lh add(lh &a){
        lh b;
        b.x = x + a.x;
        b.y = y + a.y;
        return b;
    }
};
struct lp{
    int x, y, z;
}cw[MXN];
double LEN(double x, double y, double z){
    return x*x+y*y+z*z;
}
double get(double x, double y, double z) {
    double ans = 0;
    for(int i = 0; i < n; ++i) ans = max(ans, LEN(cw[i].x-x,cw[i].y-y,cw[i].z-z));
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
            scanf("%d%d%d", &cw[i].x, &cw[i].y, &cw[i].z);
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
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;

const double san = 1e5;
const int MXN = 2005;

int n;
double X, Y, Z;
struct lh{
    int x, y;
    lh(){}
    lh(int a,int b){x = a, y = b;}
    lh add(lh &a){
        lh b;
        b.x = x + a.x;
        b.y = y + a.y;
        return b;
    }
};
struct lp{
    int x, y, z;
}cw[MXN];
double LEN(double x, double y, double z){
    return x*x+y*y+z*z;
}
double get(double x, double y, double z) {
    double ans = 0;
    for(int i = 0; i < n; ++i) ans = max(ans, LEN(cw[i].x-x,cw[i].y-y,cw[i].z-z));
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
            scanf("%d%d%d", &cw[i].x, &cw[i].y, &cw[i].z);
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
const int maxn=1e2+5;
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


