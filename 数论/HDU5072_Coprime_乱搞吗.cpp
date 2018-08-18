//HDU5072_Coprime_乱搞吗.cpp
//https://www.cnblogs.com/danceonly/p/4043963.html
/*
求n个不同的数(<=1e5)中有多少组三元组(a, b, c)两两不互质或者两两互质。

做法：

假定a < b < c

(x, y, z)表示a和b之间的关系是X,a和c之间是Y,b和c之间关系是Z，X,Y,Z∈{0， 1}, 这里0代表不互质，1代表互质

考虑到正的来做有点难，可以反的来做这题，总共(a,b,c)之间有8种关系

我们可以求出其它6种，然后减一下就行了。

先排序。

A = {在b前与c互质的数量 * 在c前与c不互质的数量} + {在c后与c互质的数量 * 在c后与c不互质的数量}；

B = {在b前与b互质的数量 * 在b后与b互质的数量} + {在b前与b不互质的数量 * 在b后与b不互质的数量};

Sum = 总共有多少组三元组;

那么其实我们所求的答案就是(B - A + Sum) / 2 ; 这个建议自己推一下，也不是很复杂

至于求在c前与c互质OR不互质的数量的话可以用容次搞搞，复杂度是可以过的。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
typedef __int64 lld;
const int MAXN = 100005;

int a[MAXN];
int cnt[MAXN];
vector<int> prime[MAXN];
int check[MAXN] = {0};
int n;
lld ans[MAXN][2];

int calc(vector<int> arr) {
    int m = arr.size();
    int sum = 0;
    for (int i = 1; i < (1 << m); i++) {
        int fg = -1, ret = 1;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                ret *= arr[j]; fg = -fg;
            }
        }
        sum = sum + fg * cnt[ret];
        cnt[ret] += 1;
    }
    return sum;
}

void work() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        ans[i][0] = calc(prime[a[i]]);
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = n; i >= 1; i--) {
        ans[i][1] = calc(prime[a[i]]);
    }
    lld Sum = (lld)n * (n-1) * (n-2) / 6;
    lld A = 0;
    lld B = 0;
    for (int i = 1; i <= n; i++) {
        A += ans[i][0] * (i-1 - ans[i][0]);
        A += ans[i][1] * (n-i - ans[i][1]);
        B += ans[i][0] * ans[i][1];
        B += (i-1 - ans[i][0]) * (n-i - ans[i][1]);
    }
    printf("%I64d\n", B-A+Sum >> 1);
    return ;
}

int main() {
    for (int i = 2; i <= 1e5; i++) {
        if (!check[i]) {
            for (int j = 1; j * i <= 1e5; j++) {
                check[j * i] = 1;
                prime[j*i].push_back(i);
            }
        }
    }
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) work();
    return 0;
}