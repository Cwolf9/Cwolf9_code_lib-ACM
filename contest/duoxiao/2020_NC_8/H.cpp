/*
**链接**
传送门: [here](https://ac.nowcoder.com/acm/contest/5673/H)
**题意**
$n,|si|\le 3e5$

**思路**

**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<stack>
#include<map>
#include<iostream>
#include<assert.h>
#include <algorithm>

#define fi first
#define se second
#define endl '\n'
#define o2(x) (x)*(x)
#define BASE_MAX 62
#define mk make_pair
#define eb push_back
#define all(x) (x).begin(), (x).end()
#define clr(a,b) memset((a),(b),sizeof((a)))
#define iis std::ios::sync_with_stdio(false); cin.tie(0)
#define my_unique(x) sort(all(x)),x.erase(unique(all(x)),x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, int> pLi;
inline LL read(){
    LL x=0;int f=0;char ch=getchar();
    while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x=f?-x:x;
}
inline void write(LL x) {
    if(x==0){putchar('0'),putchar('\n');return;}
    if(x < 0) {putchar('-');x=-x;}
    static char s[23];int l = 0;
    while(x!=0)s[l++]=x%10+48,x/=10;
    while(l)putchar(s[--l]);
    putchar('\n');
}
int lowbit(int x) {return x&(-x);}
template<class T> T big(const T& a1,const T& a2) { return a1>a2?a1:a2; }
//template<typename T, typename ...R> T big (const T& f,const R& ...r) { return big(f, big (r...)); }
template<class T> T sml(const T& a1,const T& a2) { return a1<a2?a1:a2; }
//template<typename T, typename ...R> T sml (const T& f,const R& ...r) { return sml(f, sml (r...)); }
#ifndef ONLINE_JUDGE
void debug_out() { cout << '\n'; }
template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cout << f << " "; debug_out (r...); }
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#endif
#define print(x) write(x);

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1004535809, 1000000009};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 1e9 + 6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 1e6 + 7 + 3e5;
const int MXE = 3e5 + 3;
struct Suffix_Array {
    static const int N = 1e6 + 7 + 3e5;
    int n, len, s[N], M;
    int sa[N], rnk[N], height[N];
    int tmp_one[N], tmp_two[N], c[N];
    int dp[N][22], pos[N][22];
    void init_str(int *str, int _n) {
        len = _n;
        n = len + 1;
        for (int i = 0; i < len; ++i) {
            s[i] = str[i];
        }
        s[len] = '\0';
    }
    void build_sa(int m = 128);
    void calc_height(int n);
    void Out(char *str);
    void RMQ_init(int n);
    int RMQ_query(int l, int r);
    int RMQ_query_pos(int l, int r);
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
//    if(l == r) return dp[l][0];
    if (l > r) swap(l, r);
//    l++;
    int k = 0; while (1<<(k+1) <= r - l + 1) k++;
    return min(dp[l][k], dp[r-(1<<k)+1][k]);
}
int Suffix_Array::RMQ_query_pos(int l, int r) {
    l = rnk[l]; r = rnk[r];
//    if(l == r) return dp[l][0];
    if (l > r) swap(l, r);
//    l++;
    int k = 0; while (1<<(k+1) <= r - l + 1) k++;
    if(dp[l][k] <= dp[r-(1<<k)+1][k]) return pos[l][k];
    return pos[r-(1<<k)+1][k];
}
void Suffix_Array::RMQ_init(int n) {
    for (int i=0; i<n; ++i) dp[i][0] = height[i], pos[i][0] = i;
    for (int j=1; (1<<j)<=n; ++j) {
        for (int i=0; i+(1<<j)-1<n; ++i) {
            if(dp[i][j-1] <= dp[i+(1<<(j-1))][j-1]) pos[i][j] = pos[i][j-1];
            else pos[i][j] = pos[i+(1<<(j-1))][j-1];
            dp[i][j] = std::min (dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
        }
    }
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
char allStr[MXN];
int stStr[MXE];
int k;
int id[MXN], vis[MXE];
bool is[MXN];
int s[MXN];
unordered_map<int, int> mp;
int nex[MXN];
void get_next(char *t){
    int lent = strlen(t);
    nex[0] = -1;
    for(int i = 0,k = -1;i < lent;){
        if(k==-1||t[i] == t[k]){
            ++k;++i;
            nex[i]=k;
        }else k = nex[k];
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    scanf("%d", &k);
    int Min = INF, Ct = 1, flag = 1, rs;
    for(int i = 1; i <= k; ++i) {
        scanf("%s", allStr + stStr[i]);
        int Len = strlen(allStr + stStr[i]);
        get_next(allStr + stStr[i]);
        // debug(Len, nex[Len])
        if(Len % (Len - nex[Len]) != 0 || nex[Len] * 2 < Len) {
            rs = 0;
            // debug(Len)
            for(int j = 0; j < Len; ++j) {
                rs = (rs * BASE[0] % HMOD[0] + allStr[j + stStr[i]]) % HMOD[0];
            }
            mp[rs] ++;
        }else {
            // debug(Len - nex[Len])
            rs = 0;
            for(int j = 0; j < Len - nex[Len]; ++j) {
                rs = (rs * BASE[0] % HMOD[0] + allStr[j + stStr[i]]) % HMOD[0];
            }
            mp[rs] ++;
        }
        int ret = max(0, 700000-stStr[i]-Len-Len)/Len;
        stStr[i+1] = stStr[i] + Len * (rand()%ret + 1) + 1;
        for(int j = 0; j < stStr[i+1]-stStr[i]-1; ++j) {
            id[j + stStr[i]] = i;
            if(j >= Len) allStr[j + stStr[i]] = allStr[j % Len + stStr[i]];
        }
        Min = min(Min, stStr[i+1]-stStr[i]-1);
    }
    int len = stStr[k+1];
    for(int i = 0; i < len; ++i) {
        s[i] = allStr[i];
        if(s[i] == '\0') {
            s[i] = 'z' + Ct;
            ++ Ct;
        }
    }
    // printf("%s\n", cr);
    // debug(strlen(cr) == len)
    // for(int i = 0; i < len; ++i) printf("%d ", id[i]); printf("\n");
    // return 0;
    SA.init_str(s, len);
    // debug(130 + Ct)
    SA.build_sa(130 + Ct);
//        SA.Out(cr);
    int ans = 0, cnt = 1, aim = k, l = 1;
    LL Ans = 0;
    // for(int i = 1; i <= len; ++i) {
    //     printf("%d, %d, %d, %d, ", i, SA.height[i], SA.sa[i], id[SA.sa[i]]);
    //     printf("%c%c%c%c%c\n", cr[SA.sa[i]], cr[SA.sa[i]+1], cr[SA.sa[i]+2],cr[SA.sa[i]+3],cr[SA.sa[i]+4]);
    // }
    ++ vis[id[SA.sa[1]]];
    for(int i = 2; i <= len; ++i) {
//            if(cnt == 0 && id[SA.sa[i-1]] && i != 1) ++ cnt, ++ vis[id[SA.sa[i-1]]];
        if(vis[id[SA.sa[i]]] == 0 && id[SA.sa[i]]) ++ cnt;
        ++ vis[id[SA.sa[i]]];
        if(cnt >= aim) {
            int tmp = SA.RMQ_query(SA.sa[l+1], SA.sa[i]);
            int pos = SA.RMQ_query_pos(SA.sa[l+1], SA.sa[i]);
            // debug(i, tmp)
            is[pos] = 1;
            ans = max(ans, tmp);
            // Ans += tmp;
        }
        while(l < i && SA.RMQ_query(SA.sa[l+1], SA.sa[i]) == 0) {
            -- vis[id[SA.sa[l]]];
            if(id[SA.sa[l]] && vis[id[SA.sa[l]]] == 0) -- cnt;
            ++ l;
            if(cnt >= aim) {
                int tmp = SA.RMQ_query(SA.sa[l+1], SA.sa[i]);
                int pos = SA.RMQ_query_pos(SA.sa[l+1], SA.sa[i]);
                is[pos] = 1;
                // debug(pos, tmp)
                ans = max(ans, tmp);
                // Ans += tmp;
            }
        }
        while(cnt >= aim && l < i) {
            // for(int i = 1; i <= k; ++i) printf("%d ", vis[i]);
            // printf("\n");
            // debug(l, i, SA.sa[l], id[SA.sa[l]], vis[is[SA.sa[l]]])
            -- vis[id[SA.sa[l]]];
            if(id[SA.sa[l]] && vis[id[SA.sa[l]]] == 0) -- cnt;
            ++ l;
            // for(int i = 1; i <= k; ++i) printf("%d ", vis[i]);
            // printf("\n");
            if(cnt >= aim) {
                int tmp = SA.RMQ_query(SA.sa[l+1], SA.sa[i]);
                int pos = SA.RMQ_query_pos(SA.sa[l+1], SA.sa[i]);
                is[pos] = 1;
                // debug(pos, tmp, cnt)
                ans = max(ans, tmp);
                // Ans += tmp;
            }
        }
    }
    int Max = 0;
    for(int i = 2; i <= len; ++i) {
        // if(is[i]) debug(is[i], i, SA.height[i], Ans, Max)
        if(is[i]) Ans += max(0, SA.height[i] - Max), Max = max(Max, SA.height[i]);
        Max = min(Max, SA.height[i]);
    }
    // debug(ans, Min, Ans)
    if(mp[rs] == k && ans >= Min) printf("-1\n");
    else {
        printf("%lld\n", Ans);
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
//后缀数组(SA[i]存放排名第i大的后缀首字符的下标)
//名次数组（rank[i]存放suffix(i)的优先级(名次)）
//height数组：height[i]是Suffix(sa[i-1])和Suffix(sa[i])的最长公共前缀长度
/*SA,R,H的下标都是 0~n 其中多包括了一个空字符串*/

