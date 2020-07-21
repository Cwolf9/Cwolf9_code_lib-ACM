/*
链接
https://ac.nowcoder.com/acm/contest/5668/B
题意
每次把字符串一个前缀移到后面去，询问某个位置字母的值

思路
记录一下变换的前缀和，然后循环取余即可

备注

*/
#include <bits/stdc++.h>
#include <ext/rope>
 
using namespace std;
using namespace __gnu_cxx;
 
char s[2000006];
int main(){
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
	int N,M;
	scanf("%s%d", s, &M);
    N = strlen(s);
    int a;
    char ss[2];
    long long cnt = 0;
    for(int i=1 ; i<=M ; ++i){
        scanf("%s%d",ss,&a);
        if(ss[0] == 'A'){
            printf("%c\n",s[(a-1+cnt)%N]);
        }
        else {
            cnt += a;
        }
    }
	return 0;
}