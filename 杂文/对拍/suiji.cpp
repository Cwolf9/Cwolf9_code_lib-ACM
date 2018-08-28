#include<cstdio>  
#include<iostream>  
#include<ctime>  
#include<cstdlib>
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))  
using namespace std;  
const int N =200;
const int M =300;
typedef long long LL;
const int maxn=1000000000-3;
int main(){
	srand(time(0)); 
	int n=ran(1,100000);
    int m=ran(1,n);
    printf("%d %d\n", n,m);
	return 0;
} 
/*
//int a=((rand() << 16) + rand())%n+1; 
int main(){
    srand(time(0));  
    int a,b,c;  
    a = rand();
	//(rand() << 16) + rand();  
    //b = rand();// (rand() << 16) + rand();  
    //c = rand(); // (rand() << 16) + rand(); 
    LL d=rand();
    int n=max(rand()%N,1);
	printf("%d %d %lld\n",n,max(rand()%N,1),(d*d)%M );
	for(int i=0;i<n;++i){
		d=rand();
		if(i!=n-1) printf("%lld ",max((d*d)%M,1LL) );
		else printf("%lld\n",max((d*d)%M,1LL) );
	}
    return 0;  
}  */ 
