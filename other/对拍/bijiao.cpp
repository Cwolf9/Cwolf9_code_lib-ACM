//https://blog.csdn.net/code12hour/article/details/51252457
//https://blog.csdn.net/crzbulabula/article/details/48866779

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<windows.h>
using namespace std;

int main(){
    int t = 100;
    while (t--){
        //system("suiji > mi.in");
        //system("cpp1 < mi.in > 1.out");
        //system("cpp2 < mi.in > 2.out");
        if (system("fc 1.out 2.out")){
        	printf("---\n");
			break;
		}
    }
    system("pause");
    return 0;
}