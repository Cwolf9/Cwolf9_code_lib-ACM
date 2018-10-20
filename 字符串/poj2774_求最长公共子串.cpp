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