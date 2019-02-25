
//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<cctype>
#include<string>
#include<cmath>
#include<bitset>
#include<cassert>
#include<ctime>
using namespace std;
typedef long long LL;
//https://www.cnblogs.com/KonjakJuruo/p/5906164.html
//SA,R,H的下标都是 0~n 其中多包括了一个空字符串
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
    void RMQ_init(int n);
    int RMQ_query(int l, int r);
}SA;
void Suffix_Array::Out(char *str) {
    puts ("[Suffix]");
    for (int i=0; i<n; ++i) {
        printf ("%s\n", str+sa[i]);
    }
}
//LCP(suffix(i), suffix(j))=RMQ_query(rnk[i], rnk[j]);
int Suffix_Array::RMQ_query(int l, int r) {
    l = rnk[l]; r = rnk[r];
    if (l > r) swap(l, r);
    l++;
    int k = 0; while (1<<(k+1) <= r - l + 1) k++;
    return min(dp[l][k], dp[r-(1<<k)+1][k]);
}
void Suffix_Array::RMQ_init(int n) {
    for (int i=0; i<n; ++i) dp[i][0] = height[i];
    for (int j=1; (1<<j)<=n; ++j) {
        for (int i=0; i+(1<<j)-1<n; ++i) {
            dp[i][j] = std::min (dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
        }
    }
}
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
    RMQ_init(n);
}
const int MXN = 3e5 + 7;
char str[MXN];
int rem[MXN];//求一个串他的重复子串重复次数最多
int main(int argc, char const *argv[]){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    freopen("E://ADpan//out.out", "w", stdout);  
#endif
    int cas = 1;
    while(~scanf("%s", str) && str[0] != '#'){
        printf("Case %d: ", cas++);
        int len = strlen(str);
        SA.init_str(str);
        SA.build_sa();
        int ans = 0, num = 0;
        //先枚举len，得到重复次数最多的那些len，然后枚举求解字典序最小
        for(int d = 1; d * 2 <= len; ++d){
            for(int j = 0; (j+1) * d < len; ++j){
                int x = j*d, y = (j+1)*d;
                if(str[x] != str[y]) continue;
                int z = SA.RMQ_query(x, y), k = (z+y-1-x+1)/d;
                int cha = x-(d-z%d);
                if(cha >= 0) {
                    int tz = SA.RMQ_query(cha, cha + d), tk = max(k,(tz+cha+d-1-cha+1)/d);
                    k = tk;
                }
                if(k > ans) {ans=k;num=0;rem[num++]=d;}
                else if(k == ans) {
                    if(num && rem[num-1] == d) continue;
                    rem[num++]=d;
                }
            }
        }
        if(ans == 0){
            printf("%c\n", str[SA.sa[1]]);
        }else{
            for(int _i = 1, i = SA.sa[_i]; _i <= len && ans != -1; ++_i, i = SA.sa[_i]) {
                for(int j = 0, k; j < num; ++j) {
                    k = (SA.RMQ_query(i, i+rem[j])+rem[j])/rem[j];
                    if(k >= ans) {
                        str[i+k*rem[j]] = '\0';
                        printf("%s\n", str+i);
                        ans = -1; break;
                    }
                }
            }
        }
    }
#ifndef ONLINE_JUDGE
  cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
/*
const int MXN = 3e5 + 7;
char str[MXN];
int main(int argc, char const *argv[]){
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    freopen("E://ADpan//out.out", "w", stdout);  
#endif
    int cas = 1;
    while(~scanf("%s", str) && str[0] != '#'){
        printf("Case %d: ", cas++);
        int len = strlen(str);
        SA.init_str(str);
        SA.build_sa();
        int ans = 0, ansL = 0, ansR = 0;
        for(int d = 1; d * 2 <= len; ++d){
            for(int j = 0; (j+1) * d < len; ++j){
                int x = j*d, y = (j+1)*d;
                if(str[x] != str[y]) continue;
                int z = SA.RMQ_query(x, y);
                //printf("%d %d %d\n", x, y, z);
                int st, ed = z + y - 1, tmp;
                for(int k = 0; k < d; ++k){
                    if(str[x-k] != str[y-k] || x-k < 0) break;
                    st = x - k;
                    tmp = (ed-st+1)/d;
                    if(tmp>ans || (tmp==ans&&SA.rnk[st]<SA.rnk[ansL])){
                        ans = tmp;
                        ansL = st;
                        ansR = st+tmp*d-1;
                    }
                }
            }
        }
        if(ans == 0){
            printf("%c\n", str[SA.sa[1]]);
        }else{
            for(int i = ansL; i <= ansR; ++i) putchar(str[i]);
            putchar(10);
        }
    }
#ifndef ONLINE_JUDGE
  cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
*/