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

struct Suffix_Array {
    static const int MAXN = 3e5 + 7;
    int n, len, s[MAXN], M;
    int sa[MAXN], rnk[MAXN], height[MAXN];
    int tmp_one[MAXN], tmp_two[MAXN], c[MAXN];
    int dp[MAXN][33];
    char yuan[MAXN];
    void init_str(char *str);
    void build_sa(int m = 128);
    void calc_height(int n);
    void Out(char *str);
    void RMQ_init(int n);
    int RMQ_query(int l, int r);
    int cmp_suffix(const char* pattern, int p){//判断是否为后缀p的前缀
        return strncmp(pattern, yuan + sa[p], M);
    }
    int find(char* P){//Omlog(n)
        M = strlen(P);
        if(cmp_suffix(P, 0) < 0) return -1;
        if(cmp_suffix(P, n-1) > 0) return -1;
        int L = 0, R = n - 1;
        while(R >= L){
            int mid = L + (R - L) / 2;
            int res = cmp_suffix(P, mid);
            if(!res) return mid;
            if(res < 0) R = mid - 1; else L = mid + 1;
        }
        return -1;
    }
}SA;
void Suffix_Array::Out(char *str) {
    puts ("/*Suffix*/");
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
        s[i] = str[i];
        yuan[i] = str[i];
    }
    yuan[len] = s[len] = '\0';
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
    for (i=0; i<n; ++i) ++c[x[i]=s[i]];//第一关键字是x[i]，第二关键字是i
    for (i=1; i<m; ++i) c[i] += c[i-1];
    for (i=n-1; i>=0; --i) sa[--c[x[i]]] = i;//sa辅助更新第二关键字
    for (j=1; j<=n; j<<=1) {//y就是第二关键字从小到大的位置
        for (p=0, i=n-j; i<n; ++i) y[p++] = i;//第二关键字为0，最小
        for (i=0; i<n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;//错位，这个第一关键字作为前j位元素的第二关键字
        //现在第二关键字已经有序，在此基础上按第一关键字排序
        for (i=0; i<m; ++i) c[i] = 0;
        for (i=0; i<n; ++i) c[x[y[i]]]++;
        for (i=1; i<m; ++i) c[i] += c[i-1];
        for (i=n-1; i>=0; --i) sa[--c[x[y[i]]]] = y[i];
        std::swap(x, y);
        for (p=1, x[sa[0]]=0, i=1; i<n; ++i) {//拍完序后更新第一关键字
            x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+j] == y[sa[i]+j] ? p - 1 : p++);
        }
        if(p >= n) break;
        m=p;
    }
    calc_height(n-1);
    RMQ_init(n);
}
const int MXN = 2e5 + 7;
char s[MXN], t[MXN];
int k, ls, lt, len;
int stk[MXN], top;
int na[MXN], nb[MXN];
int main(int argc, char const *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);
#endif
    while(scanf("%d", &k) && k) {
        scanf("%s%s", s, t);
        ls = strlen(s), lt = strlen(t);
        len = ls + lt + 1;
        s[ls] = '#';//把两个串拼在一起并加入分隔符
        memcpy(s + ls + 1, t, sizeof(char) * (lt + 1));
        SA.init_str(s);
        SA.build_sa(128);
        for(int i = 2; i <= len; ++i) SA.height[i] = max(0, SA.height[i]-k+1);
        LL ans = 0, w1 = 0, w2 = 0;
        top = na[0] = nb[0] = 0;
        //维护一个单调递增的栈，分别记录两个串的贡献
        //pop的元素合并到栈顶元素里去并记录数量，方便计算减少的贡献
        for(int i = 2; i <= len; ++i) {
            //sa[i-1]和sa[i]的lcp
            stk[++top] = SA.height[i];
            if(SA.sa[i-1] < ls) na[top]=1,nb[top]=0,w1+=SA.height[i];
            else na[top]=0,nb[top]=1,w2+=SA.height[i];
            while(top > 1 && stk[top] <= stk[top-1]) {
                w1 -= na[top-1]*(stk[top-1]-stk[top]);//减少的贡献
                w2 -= nb[top-1]*(stk[top-1]-stk[top]);
                na[top-1] += na[top]; nb[top-1] += nb[top];
                stk[top-1] = stk[top];
                -- top;
            }
            if(SA.sa[i] < ls) ans += w2;
            else ans += w1;
        }
        printf("%lld\n", ans);
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
  return 0;
}

