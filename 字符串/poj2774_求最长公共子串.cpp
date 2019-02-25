//https://www.cnblogs.com/crazyacking/p/3991478.html
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
/*SA,R,H的下标都是 0~n 其中多包括了一个空字符串*/
struct Suffix_Array {
    static const int N = 3e5 + 7;
    int n, len, s[N], M;
    int sa[N], rnk[N], height[N];
    int tmp_one[N], tmp_two[N], c[N];
    int dp[N][33];
    void init_str(char *str);
    void build_sa(int m = 128);
    void calc_height(int n);
    void Out(char *str);
}SA;
void Suffix_Array::init_str(char *str) {
    len = strlen(str);
    n = len + 1;
    for (int i=0; i<len; ++i) {
        s[i] = str[i] - 'a' + 1;
    }
    s[len] = '\0';
}
void Suffix_Array::calc_height(int n) {
    for (int i=0; i<=n; ++i) rnk[sa[i]] = i;
    int k = height[0] = 0;
    for (int i=0; i<n; ++i) {
        if (k) k--;
        int j = sa[rnk[i]-1];
        while (s[i+k] == s[j+k]) k++;
        height[rnk[i]] = k;
    }
}
//m = max(r[i]) + 1，一般字符128足够了
void Suffix_Array::build_sa(int m) {
    int i, j, p, *x = tmp_one, *y = tmp_two;
    for (i=0; i<m; ++i) c[i] = 0;
    for (i=0; i<n; ++i) c[x[i]=s[i]]++;
    for (i=1; i<m; ++i) c[i] += c[i-1];
    for (i=n-1; i>=0; --i) sa[--c[x[i]]] = i;
    for (j=1; j<=n; j<<=1) {
        for (p=0, i=n-j; i<n; ++i) y[p++] = i;
        for (i=0; i<n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i=0; i<m; ++i) c[i] = 0;
        for (i=0; i<n; ++i) c[x[y[i]]]++;
        for (i=1; i<m; ++i) c[i] += c[i-1];
        for (i=n-1; i>=0; --i) sa[--c[x[y[i]]]] = y[i];
        std::swap (x, y);
        for (p=1, x[sa[0]]=0, i=1; i<n; ++i) {
            x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+j] == y[sa[i]+j] ? p - 1 : p++);
        }
        if(p >= n) break;
        m=p;
    }
    calc_height(n-1);
}
const int MXN = 3e5 + 7;
char s1[MXN*2], s2[MXN];
int main(int argc, char const *argv[]){
    while(~scanf("%s%s", s1,s2)){
        int len1 = strlen(s1);
        strcat(s1, "{");
        strcat(s1, s2);
        int len = strlen(s1);
        SA.init_str(s1);
        SA.build_sa();
        int ans = 0;//sa[0] = len, it is empty
        for(int i = 2; i <= len; ++i) {
            if((SA.sa[i]<len1&&SA.sa[i-1]>len1)||(SA.sa[i]>len1&&SA.sa[i-1]<len1)) {
                ans = max(ans, SA.height[i]);
            }
        }
        printf("%d\n", ans);
    }    
    return 0;
}
/*
Description

The little cat is majoring in physics in the capital of Byterland. A piece of sad news comes to him these days: his mother is getting ill. Being worried about spending so much on railway tickets (Byterland is such a big country, and he has to spend 16 shours on train to his hometown), he decided only to send SMS with his mother. 

The little cat lives in an unrich family, so he frequently comes to the mobile service center, to check how much money he has spent on SMS. Yesterday, the computer of service center was broken, and printed two very long messages. The brilliant little cat soon found out: 

1. All characters in messages are lowercase Latin letters, without punctuations and spaces. 
2. All SMS has been appended to each other – (i+1)-th SMS comes directly after the i-th one – that is why those two messages are quite long. 
3. His own SMS has been appended together, but possibly a great many redundancy characters appear leftwards and rightwards due to the broken computer. 
E.g: if his SMS is “motheriloveyou”, either long message printed by that machine, would possibly be one of “hahamotheriloveyou”, “motheriloveyoureally”, “motheriloveyouornot”, “bbbmotheriloveyouaaa”, etc. 
4. For these broken issues, the little cat has printed his original text twice (so there appears two very long messages). Even though the original text remains the same in two printed messages, the redundancy characters on both sides would be possibly different. 

You are given those two very long messages, and you have to output the length of the longest possible original text written by the little cat. 

Background: 
The SMS in Byterland mobile service are charging in dollars-per-byte. That is why the little cat is worrying about how long could the longest original text be. 

Why ask you to write a program? There are four resions: 
1. The little cat is so busy these days with physics lessons; 
2. The little cat wants to keep what he said to his mother seceret; 
3. POJ is such a great Online Judge; 
4. The little cat wants to earn some money from POJ, and try to persuade his mother to see the doctor :( 
Input

Two strings with lowercase letters on two of the input lines individually. Number of characters in each one will never exceed 100000.
Output

A single line with a single integer number – what is the maximum length of the original text written by the little cat.
Sample Input

yeshowmuchiloveyoumydearmotherreallyicannotbelieveit
yeaphowmuchiloveyoumydearmother
Sample Output

27
*/