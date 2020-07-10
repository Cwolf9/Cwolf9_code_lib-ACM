#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<stack>
#include<map>
#include<iostream>
#include<assert.h>
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
#define my_unique(x) sort(a(x)),x.erase(unique(a(x)),x.end())
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
void debug_out() { cerr << '\n'; }
template<typename T, typename ...R> void debug_out (const T& f,const R& ...r) { cerr << f << " "; debug_out (r...); }
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#endif
#define print(x) write(x);

const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const int mod = 1e9 + 6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MXN = 3e5 + 7;

struct Suffix_Array {
    static const int N = 3e5 + 7;
    int n, len, s[N], M;
    int sa[N], rnk[N], height[N];
    int tmp_one[N], tmp_two[N], c[N];
    int dp[N][21];
    void init_str(char *str) {
        len = strlen(str);
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
    int cmp_suffix(char* pattern, int p){//判断是否为后缀p的前缀
        return strncmp(pattern, reinterpret_cast<const char *>(s + sa[p]), M);
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
int n, m;
int k;
char ar[MXN], br[MXN];

int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/cwolf9/CLionProjects/ccc/in.txt", "r", stdin);
    //freopen("/home/cwolf9/CLionProjects/ccc/out.txt", "w", stdout);
#endif
    int cas = 0;
    while(~scanf("%d", &k) && k) {
        scanf("%s%s", ar, br);
        n = strlen(ar);
        m = strlen(br);
        ar[n] = '#';
        memcpy(ar+n+1, br, m);
        ar[n+m+1] = '\0';
        SA.init_str(ar);
        SA.build_sa();
        for(int i = 0; i <= n + m + 1; ++i) SA.height[i] = max(SA.height[i] - k + 1, 0);
        vector<int> vs, is;
        LL ans = 0, sum = 0;
        //维护一个单调递增的栈
        //若段的左端点是最小的height值，则每一段height的贡献都是这一段height里的的最小值乘上这一段的数量
        //这个单调递增的栈把值push出去之后，并不是直接把它删去，对于能造成贡献的值的数量要累加上去
        for(int i = 2; i <= n + m + 1; ++i) {
            vs.eb(SA.height[i]);
            if(SA.sa[i-1] > n) {
                sum += SA.height[i];
                is.eb(1);
            }else is.eb(0);
            while(vs.size() > 2 && vs.back() <= vs[vs.size()-2]) {
                LL vsa = vs.back();
                int isa = is.back();
                vs.pop_back(); is.pop_back();
                sum -= is.back()*(vs.back() - vsa);
                is[is.size()-1] += isa;
                vs[vs.size()-1] = vsa;
            }
            if(SA.sa[i] < n) ans += sum;
//            debug(SA.height[i], SA.sa[i-1], SA.sa[i], vs.size(), ans, sum)
        }
        vs.clear(), is.clear();
        sum = 0;
        for(int i = 2; i <= n + m + 1; ++i) {
            vs.eb(SA.height[i]);
            if(SA.sa[i-1] < n) {
                sum += SA.height[i];
                is.eb(1);
            }else is.eb(0);
            while(vs.size() > 2 && vs.back() <= vs[vs.size()-2]) {
                LL vsa = vs.back();
                int isa = is.back();
                vs.pop_back(); is.pop_back();
                sum -= is.back()*(vs.back() - vsa);
                is[is.size()-1] += isa;
                vs[vs.size()-1] = vsa;
            }
            if(SA.sa[i] > n) ans += sum;
//            debug(SA.height[i], SA.sa[i-1], SA.sa[i], vs.size(), ans)
        }
        print(ans)
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << clock() << "ms" << endl;
#endif
    return 0;
}
//后缀数组(SA[i]存放排名第i大的后缀首字符的下标)
//名次数组（rank[i]存放suffix(i)的优先级(名次)）
//height数组：height[i]是Suffix(sa[i-1])和Suffix(sa[i])的最长公共前缀长度
/*SA,R,H的下标都是 0~n 其中多包括了一个空字符串*/

