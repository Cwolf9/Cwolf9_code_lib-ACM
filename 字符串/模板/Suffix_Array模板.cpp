/*
https://blog.csdn.net/YxuanwKeith/article/details/50636898
https://sea96.github.io/2017/05/05/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84/
https://www.cnblogs.com/Running-Time/p/5450483.html
*/
/*
 *后缀数组，倍增算法实现，复杂度O(nlogn)
 *sa[i]: 第i小的后缀是在字符串位置，即后缀sa[i]
 *rank[i]: 后缀i在sa数组下标，即第rank[i]小
 *height[i]: LCP(suffix(sa[i-1], sa[i]))
 */
//后缀数组(SA[i]存放排名第i大的后缀首字符的下标)
//名次数组（rank[i]存放Suffix(i)的优先级(名次)）
//height数组：height[i]是Suffix(sa[i-1])和Suffix(sa[i])的最长公共前缀长度
//SA,R,H的下标都是 0~n 其中多包括了一个空字符串

struct Suffix_Array {
    static const int N = 3e5 + 7;
    int n, len, s[N], M;
    int sa[N], rnk[N], height[N];
    int tmp_one[N], tmp_two[N], c[N];
    int dp[N][21];
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
    int cmp_suffix(char* pattern, int p){//判断是否为后缀p的前缀
        return strncmp(pattern, reinterpret_cast<const char *>(s + sa[p]), M);
        //return strncmp(pattern, yuan + sa[p], M);
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
int Suffix_Array::RMQ_query(int l, int r) {//看自己需求自由变换
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
    for (i=0; i<n; ++i) c[x[i]=s[i]]++;//此时第一关键字是x[i]，第二关键字是i
    for (i=1; i<m; ++i) c[i] += c[i-1];
    for (i=n-1; i>=0; --i) sa[--c[x[i]]] = i;//排第几的后缀是i
    for (j=1; j<=n; j<<=1) {//y就是第二关键字从小到大的位置
        //y[i]表示第二关键字排名为i的数，第一关键字的位置
        for (p=0, i=n-j; i<n; ++i) y[p++] = i;//这些数的第二关键字为0
        for (i=0; i<n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;//按rank顺序，1<<(j+1)的第二半的rank。sa[i]把自己交给了sa[i]-j
        //现在第二关键字已经有序，在此基础上按第一关键字排序
        for (i=0; i<m; ++i) c[i] = 0;
        for (i=0; i<n; ++i) c[x[y[i]]]++;
        for (i=1; i<m; ++i) c[i] += c[i-1];
        for (i=n-1; i>=0; --i) sa[--c[x[y[i]]]] = y[i];//排第几的后缀是y[i]
        std::swap (x, y);
        for (p=1, x[sa[0]]=0, i=1; i<n; ++i) {//排完序后更新第一关键字
            x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+j] == y[sa[i]+j] ? p - 1 : p++);
        }
        if(p >= n) break;
        m=p;
    }
    calc_height(n-1);
    RMQ_init(n);
}








/*
    *后缀数组，DC3算法实现，复杂度O(n)
*/
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

struct DC3 {
    static const int N = 1e6 + 5;
    int sa[N * 3], height[N], rnk[N];;
    int wa[N], wb[N], wv[N], c[N];
    int dp[N][24];
    int c0(int *r, int a, int b) {
        return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
    }
    int c12(int k, int *r, int a, int b) {
        if (k == 2) return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
        else return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
    }
    void _sort(int *r, int *a, int *b, int n, int m) {
        int i;
        for (i = 0; i < n; i++) wv[i] = r[a[i]];
        for (i = 0; i < m; i++) c[i] = 0;
        for (i = 0; i < n; i++) c[wv[i]]++;
        for (i = 1; i < m; i++) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--) b[--c[wv[i]]] = a[i];
        return;
    }
    //dc3.dc3(s, dc3.sa, len + 1, 256);
    //dc3.calheight(s, len);
    void dc3(int *r, int *sa, int n, int m) {
        int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
        r[n] = r[n + 1] = 0;
        for (i = 0; i < n; i++) if (i % 3 != 0) wa[tbc++] = i;
        _sort(r + 2, wa, wb, tbc, m);
        _sort(r + 1, wb, wa, tbc, m);
        _sort(r, wa, wb, tbc, m);
        for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
            rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
        if (p < tbc) dc3(rn, san, tbc, p);
        else for (i = 0; i < tbc; i++) san[rn[i]] = i;
        for (i = 0; i < tbc; i++) if (san[i] < tb) wb[ta++] = san[i] * 3;
        if (n % 3 == 1) wb[ta++] = n - 1;
        _sort(r, wb, wa, ta, m);
        for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
        for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
            sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
        for (; i < ta; p++) sa[p] = wa[i++];
        for (; j < tbc; p++) sa[p] = wb[j++];
        return;
    }
    void calheight(int *r, int n) {
        int i, j, k = 0;
        for (i = 1; i <= n; i++) rnk[sa[i]] = i;
        for (i = 0; i < n; height[rnk[i++]] = k)
            for (k ? k-- : 0, j = sa[rnk[i] - 1]; r[i + k] == r[j + k]; k++);
        RMQ_init(n + 1);
    }
    int RMQ_query(int l, int r) {
        l = rnk[l], r = rnk[r];
        if (l > r) swap(l, r);
        l++;
        int k = 0;
        while (1 << (k + 1) <= r - l + 1) k++;
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
    void RMQ_init(int n) {
        for (int i = 0; i < n; ++i) dp[i][0] = height[i];
        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                dp[i][j] = std::min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}dc3;