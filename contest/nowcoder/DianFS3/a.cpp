// /*

// */
// #pragma comment(linker, "/STACK:102400000,102400000")
// //#include<bits/stdc++.h>
// #include <assert.h>
// #include <algorithm>
// #include <cstdio>
// #include <cstring>
// #include <ctime>
// #include <iostream>
// #include <map>
// #include <queue>
// #include <set>
// #include <vector>
// #define fi first
// #define se second
// #define endl '\n'
// #define o2(x) (x) * (x)
// #define BASE_MAX 31
// #define mk make_pair
// #define eb emplace_back
// #define SZ(x) ((int)(x).size())
// #define all(x) (x).begin(), (x).end()
// #define clr(a, b) memset((a), (b), sizeof((a)))
// #define iis                           \
//     std::ios::sync_with_stdio(false); \
//     cin.tie(0)
// #define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
// using namespace std;
// #pragma optimize("-O3")
// typedef long long int64;
// typedef unsigned long long uint64;
// typedef pair<int, int> pii;
// // mt19937 rng(time(NULL));
// // mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// // mt19937_64 generator(std::clock());
// // shuffle(arr, arr + n, generator);
// inline int64 read() {
//     int64 x = 0;int f = 0;char ch = getchar();
//     while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
//     while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
//     return x = f ? -x : x;
// }
// inline void write(int64 x, bool f) {
//     if (x == 0) {putchar('0');if (f) putchar('\n');return;}
//     if (x < 0) { putchar('-');x = -x;}
//     static char s[23];int l = 0;
//     while (x != 0) s[l++] = x % 10 + 48, x /= 10;
//     while (l) putchar(s[--l]);
//     if (f) putchar('\n');
// }
// int lowbit(int x) { return x & (-x); }
// template <class T>
// T big(const T &a1, const T &a2) {return a1 > a2 ? a1 : a2;}
// template <class T>
// T sml(const T &a1, const T &a2) {return a1 < a2 ? a1 : a2;}
// template <typename T, typename... R>
// T big(const T &f, const R &... r) {return big(f, big(r...));}
// template <typename T, typename... R>
// T sml(const T &f, const R &... r) {return sml(f, sml(r...));}
// void debug_out() { cout << '\n'; }
// template <typename T, typename... R>
// void debug_out(const T &f, const R &... r) {cout << f << " ";debug_out(r...);}
// #define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
// #define LLDO
// #ifdef LLDO
// const char ptout[] = "%lld";
// #else
// const char ptout[] = "%d";
// #endif
// template <typename T>
// void print(const T &f) {printf(ptout, f);putchar('\n');}
// template <typename T, typename... R>
// void print(const T &f, const R &... r) {printf(ptout, f);putchar(' ');print(r...);}

// const int HMOD[] = {1000000009, 1004535809};
// const int64 BASE[] = {1572872831, 1971536491};
// const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
// const int INF = 0x3f3f3f3f;
// const int mod = 55566677;
// const int MOD = 1e9 + 7;  // 998244353
// const int MXN = 1e6 + 5;
// const int MXE = 2e6 + 6;
// int n, m, k;
// struct Point {
//     int x;
//     int y;
// };
// class Solution {
// public:
//     /**
//      * 返回牛牛所能得到的字典序最小的排列
//      * @param n int整型 
//      * @param m int整型 
//      * @param perm int整型vector 
//      * @param Pair Point类vector 
//      * @return int整型vector
//      */
//     static const int MXN = 1e5 + 5;
//     int fa[MXN], id[MXN], inde, ar[MXN];
//     vector<int> vs[MXN], val[MXN];
//     int Fi(int x) {
//         return fa[x] == x?x:fa[x] = Fi(fa[x]);
//     }
//     vector<int> solve(int n, int m, vector<int>& perm, vector<Point>& Pair) {
//         // write code here
//         for(int i = 1; i <= n; ++i) fa[i] = i;
//         for(Point a: Pair) {
//             int px = Fi(a.x), py = Fi(a.y);
//             if(px != py) {
//                 fa[px] = py;
//             }
//         }
//         for(int i = 1; i <= n; ++i) {
//             int pa = Fi(i);
//             if(id[pa] == 0) {
//                 id[pa] = ++ inde;
//             }
//             vs[id[pa]].emplace_back(i);
//             val[id[pa]].emplace_back(perm[i - 1]);
//         }
//         for(int i = 1; i <= inde; ++i) sort(val[i].begin(), val[i].end());
//         for(int i = 1; i <= inde; ++i) {
//             for(int j = 0; j < val[i].size(); ++j) {
//                 ar[vs[i][j]] = val[i][j];
//             }
//         }
//         vector<int> ans;
//         for(int i = 1; i <= n; ++i) ans.emplace_back(ar[i]);
//         return ans;
//     }
// }ss;
// int main() {
// #ifndef ONLINE_JUDGE
//     freopen("D:in.in", "r", stdin);
//     freopen("D:out.out", "w", stdout);
// #endif
//     vector<int> a;
//     a.eb(5);
//     a.eb(2);
//     a.eb(3);
//     a.eb(4);
//     a.eb(1);
//     vector<Point> b;
//     b.eb(Point{2,4});
//     b.eb(Point{1,4});
//     b.eb(Point{3,4});
//     vector<int> ans = ss.solve(5, 3, a, b);
//     for(int x: ans) debug(x);
// #ifndef ONLINE_JUDGE
//     cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
//     system("pause");
// #endif
//     return 0;
// }
#include<bits/stdc++.h>
#define lowbit(x) x&-x
using namespace std;
typedef long long ll;
const int MAX = 2e5 + 10;
//建立虚树点数tot < 2n, 空间开两倍

int n, w[MAX];
ll ans;

//树状数组
int c[MAX];
void upd(int p, int k) { for (; p <= n; p += lowbit(p)) c[p] += k; }
int query(int p) { int res = 0; for (; p; p -= lowbit(p)) res += c[p]; return res; }

int mindiv[MAX];
void sieve(int siz) {//筛mindiv
    for (int i = 2; i <= siz; i++)
        if (!mindiv[i])
            for (int j = i; j <= siz; j += i)
                if (!mindiv[j])
                    mindiv[j] = i;
}

int lcadep[MAX], dep[MAX];
int st[MAX], top, tot;//stack, top, tot:虚树点数
vector<int> g[MAX];//虚树
void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }

void buildVirtualTree() {
    tot = n; st[top = 1] = 1;
    for (int i = 2; i <= n; i++) {
        dep[i] = dep[i - 1] + 1; int j = i;
        for (; j != mindiv[j]; j /= mindiv[j]) dep[i]++;
        lcadep[i] = query(n) - query(j - 1);
        for (j = i; j != 1; j /= mindiv[j]) upd(mindiv[j], 1);
        // printf("%d %d %d\n", i, dep[i], lcadep[i]);
    }
    //建树
    for (int i = 2; i <= n; i++) {
        while (top > 1 && dep[st[top - 1]] >= lcadep[i])
            add_edge(st[top - 1], st[top]), top--;
        if (dep[st[top]] != lcadep[i]) {
            dep[++tot] = lcadep[i];
            add_edge(tot, st[top]);
            st[top] = tot;
        }
        st[++top] = i;
    }
    while (top > 1) add_edge(st[top - 1], st[top]), top--;
}

void dfs(int u, int fa) {
    ans += 1ll * w[u] * dep[u];//ans最开始是rt = 1时的答案
    for (auto &v: g[u])
        if (v != fa) {
            dfs(v, u);
            w[u] += w[v];
        }
}

void dfs2(int u, int fa) {//如果rt移动之后答案变小就一直移动下去，直到答案不在变小
    for (auto &v: g[u])
        if (v != fa) {
            //rt从u转移到v的代价
            //+(w[1] - w[v]) - w[v]
            if (w[1] - 2 * w[v] < 0) {
                ans += 1ll * (w[1] - 2 * w[v]) * (dep[v] - dep[u]);//一步的代价*距离
                dfs2(v, u);
            }
        }
}

void init() {
    ans = top = 0;
    for (int i = 1; i <= tot; i++) g[i].clear(), c[i] = w[i] = lcadep[i] = dep[i] = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    sieve(1e5);
    while (~scanf("%d", &n)) {
        init();
        for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
        buildVirtualTree();
        int rt = 1; dfs(rt, 0); dfs2(rt, 0);
        printf("%lld\n", ans);
    }

    return 0;
}
/*
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

const int M = 100000;

static inline int get_exp(int p, int n) {
  int result = 0;
  while (n >= p) {
    result += (n /= p);
  }
  return result;
}

struct Entry {
  int exp, index, size;
};

struct Oracle {
  void add(const std::vector<int> &primes, int k, int n, int c) {
    // for (int i = 0; i < k; ++i) {
    //   result += 1LL * c * get_exp(primes[i], n);
    // }
    queries.push_back({k, n, c});
  }

  long long sum(int m, const std::vector<int> &primes) {
    long long result = 0;
    int processed = queries.size();
    std::vector<int> count(m);
    for (int i = 0; i < static_cast<int>(primes.size()) && primes[i] < m; ++i) {
      while (processed && queries[processed - 1].i == i) {
        int sum = 0;
        const auto &query = queries[--processed];
        for (int j = query.n; j > 0; j -= j & -j) {
          sum += count[j];
        }
        result += 1LL * sum * query.c;
      }
      int p = primes[i];
      for (long long pk = p; pk < m; pk *= p) {
        for (int d = pk; d < m; d += pk) {
          for (int j = d; j < m; j += j & -j) {
            count[j]++;
          }
        }
      }
    }
    return result;
  }

  struct Query {
    int i, n, c;
  };

  long long result = 0;
  std::vector<Query> queries;
};

template <typename OracleT> void solve() {
  static int sum[M + 2], maxdiv[M + 1];
  std::vector<int> primes;
  static Entry entries[M + 2];

  memset(maxdiv, -1, sizeof(maxdiv));
  for (int d = 2; d < M; ++d) {
    if (maxdiv[d] == -1) {
      maxdiv[d] = primes.size();
      primes.push_back(d);
    }
    for (int p : primes) {
      if (1LL * d * p >= M) {
        break;
      }
      maxdiv[d * p] = maxdiv[d];
      if (d % p == 0) {
        break;
      }
    }
  }
  int m;
  while (scanf("%d", &m) == 1) {
    sum[0] = sum[++m] = 0;
    for (int i = 1; i < m; ++i) {
      scanf("%d", sum + i);
    }
    for (int i = m; i--;) {
      sum[i] += sum[i + 1];
    }
    int k = 0;
    while (k < static_cast<int>(primes.size()) && primes[k] < m) {
      k++;
    }
    std::vector<std::pair<int, int>> dividens(m - 2);
    for (int i = 2; i < m; ++i) {
      dividens[i - 2] = std::make_pair(maxdiv[i], i);
    }
    std::sort(dividens.begin(), dividens.end(),
              std::greater<std::pair<int, int>>());
    int low = 1, high = m; // [low, high)
    long long result = 0;
    OracleT oracle;
    for (int j = 0; k--;) {
      int p = primes[k];
      int count = 1;
      entries[0] = {get_exp(p, low), low, sum[low]};
      int outSize = sum[0] - (sum[low] - sum[high]);
      if (entries[0].exp) {
        count = 2;
        entries[1] = entries[0];
        entries[0] = {0, -1, outSize};
      } else {
        entries[0].size += outSize;
      }
      while (j < m - 1 && dividens[j].first == k) {
        int d = dividens[j++].second;
        if (low < d && d <= high) {
          entries[count - 1].size -= sum[d];
          entries[count++] = {get_exp(p, d), d, sum[d]};
        }
      }
      entries[count - 1].size -= sum[high];
      entries[count].index = high;
      int total = 0, pivot = 0;
      while ((total + entries[pivot].size) * 2 <= sum[0]) {
        total += entries[pivot++].size;
      }
      for (int i = low; i < entries[pivot].index; ++i) {
        oracle.add(primes, k, i, sum[i] - sum[i + 1]);
      }
      for (int i = entries[pivot + 1].index; i < high; ++i) {
        oracle.add(primes, k, i, sum[i] - sum[i + 1]);
      }
      for (int i = 0; i < count; ++i) {
        result += 1LL * std::abs(entries[i].exp - entries[pivot].exp) *
                  entries[i].size;
      }
      low = entries[pivot].index, high = entries[pivot + 1].index;
      if (entries[pivot].size * 2 <= sum[0]) {
        for (int i = low; i < high; ++i) {
          oracle.add(primes, k, i, sum[i] - sum[i + 1]);
        }
        break;
      }
    }
    printf("%lld\n", result + oracle.sum(m, primes));
  }
}

#ifndef NO_MAIN
int main() { 
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    solve<Oracle>(); 
}
#endif
*/
