//UVALive5964_LCM_Extreme.cpp
//https://www.cnblogs.com/danceonly/p/3870670.html
/*
题意 ： 求∑lcm(i, j) (其中1 <= i < j <= n) n <= 5 * 10 ^ 6

做contest的时候一开始看到这道题目我想到贾教的线筛那篇论文上好像是讲到过这个的，然后就去翻了...到最后还是不理解怎么做 - -b

思路 ： 其实蛮简答的，首先你处理出这么一个数组sum[i]表示与i互质且比i小的数之和，那么sum[i] = (1+i)*i/2 - ∑sum[i/d] (其中d是i的所有非1约数)

这个可以利用类似筛素数筛的复杂度为O(n*log(n))。然后,所求的答案ans[n] = ans[n-1] + ∑sum[n/d]*d*n/d(其中d是n的所有约数) 这个递推式可以这样理解：sum[n/d]所求的和的那些数肯定和n是互质的，那么的话他们乘上d与n求gcd的话肯定就是d了，那么他们和n求lcm的话就是sum[n/d] * d(最大公约数) * n/d了，这个也是可以通过筛素数的方式地推出来的。

所以总体复杂度是O(n*log(n) + T)
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef unsigned long long lld;
const int MAXN = 5 * 1000005;
lld sum[MAXN];
lld ans[MAXN];

void solve(int N) {
    sum[0] = 0;
    for (int i = 1; i <= N; i++) {
        sum[i] = sum[i - 1] + i;
    }
    sum[1] = 0;
    for (int i = 2; i <= N; i++) {
        sum[i] -= i;
        for (int j = 2; j * i <= N; j++) {
            sum[j * i] -= sum[i] * j;
        }
    }
    memset(ans, 0, sizeof(ans));
    ans[1] = 0;
    for (int i = 2; i <= N; i++) {
        ans[i] += ans[i-1];
        for (int j = 1; i * j <= N; j++) {
            ans[j * i] += sum[i] * i * j;
        }
    }
}

int main() {
    solve(5000000);
    int T; scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        int n; scanf("%d", &n);
        printf("Case %d: %llu\n", cas, ans[n]);
    }
    return 0;
}