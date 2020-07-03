#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<cmath>
#define test printf("***\n")
#define ka getchar();getchar()
#define ka1 getchar()
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
const int N = 200005;
const int INF = 0x3f3f3f3f;
const LL mod = 1000000007;
const double eps = 1e-8;
LL ar[N];
LL ab(LL x){
    return x<0?0-x:x;
}
int main(){
    int n;
    while(~scanf("%d",&n),n){
        for(int i=0;i<n;++i){
            scanf("%lld",&ar[i]);
        }
        map<LL,int>mp;
        map<LL,int>::iterator it;
        pair<LL,int> ans(ab(ar[0]),1);
        int state=1<<(n/2);
        for(int i=1;i<state;++i){
            LL sum=0;int cnt=0;
            for(int j=0;j<n/2;++j){
                if((i>>j)&1){
                    sum+=ar[j];
                    cnt++;
                }
            }
            ans=min(ans,make_pair(ab(sum),cnt));
            if(mp[sum]){
                mp[sum]=min(mp[sum],cnt);
            }else{
                mp[sum]=cnt;
            }
        }
        state=1<<(n-n/2);
        for(int i=1;i<state;++i){
            LL sum=0;int cnt=0;
            for(int j=0;j<(n-n/2);++j){
                if((i>>j)&1){
                    sum+=ar[j+n/2];
                    cnt++;
                }
            }
            ans=min(ans,make_pair(ab(sum),cnt));
            it=mp.lower_bound(-sum);
            if(it!=mp.end()){
                ans=min(ans,make_pair(ab(sum+it->first),cnt+it->second));
            }
            if(it!=mp.begin()){
                it--;
                ans=min(ans,make_pair(ab(sum+it->first),cnt+it->second));
            }
        }
        printf("%lld %d\n",ans.first,ans.second);
    }
    return 0;
}