#include<cstdio>  
#include<iostream>  
#include<ctime>  
#include<cstdlib>
#include <map>
#define ran(a,b) ((((rand()<<15)^rand())%((b)-(a)+1))+(a))  
using namespace std;

const int N =1e6;
const int M =300;
typedef long long LL;
map<int,int> mp;
int main(){
#ifndef ONLINE_JUDGE
    //freopen("E://ADpan//in.in", "r", stdin);
    freopen("E://ADpan//out.out", "w", stdout);  
#endif
	srand(time(0));
    int tim = 20;
    printf("20\n");
    while(tim--){
        int n = ran(100,1000);
        printf("%d\n", n);
        for(int i = 0; i < n;) {
            int k = ran(1, N);
            if(mp[k] == 0){
                if(i == n-1) printf("%d\n", k);
                else printf("%d ", k);
                ++ i;
            }
            mp[k] = 1;
        }
    }
	return 0;
} 
/*
//int a=((rand() << 16) + rand())%n+1; 
int main(){
    srand(time(0));  
    int a,b,c;  
    //a = (rand() << 16) + rand();  
    //b = (rand() << 16) + rand();  
    //c = (rand() << 16) + rand(); 
    LL d=rand();
    int n=max(rand()%N,1);
	printf("%d %d %lld\n",n,max(rand()%N,1),(d*d)%M );
	for(int i=0;i<n;++i){
		d=rand();
		if(i!=n-1) printf("%lld ",max((d*d)%M,1LL) );
		else printf("%lld\n",max((d*d)%M,1LL) );
	}
    return 0;  
}
*/