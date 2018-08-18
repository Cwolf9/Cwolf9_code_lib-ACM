#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define mme(a,b) memset((a),(b),sizeof((a))) 
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
int main(){
  int tim = 1000000/4;
  int tmp = 9999;

  printf("%d\n", tim);

  for(int i=0;i<tim;++i){
    int n=4;
    printf("%d\n", n);
    for(int j=0;j<n;++j){
      printf("%d%c", i%tmp+1," \n"[j==n-1]);
    }
  }
  return 0;
}