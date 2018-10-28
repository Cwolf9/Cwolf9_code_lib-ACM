#include <bits/stdc++.h>
using namespace std;

int n, m;

int main(){
    
    return 0;
}

/*//模拟退火
#include <iostream>
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
*/

//当手机开机时，它处于空闲状态(idle)，当用户使用电话呼叫某人