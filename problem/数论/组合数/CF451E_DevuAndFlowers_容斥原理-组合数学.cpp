//CF451E_DevuAndFlowers_容斥原理-组合数学.cpp
//https://www.cnblogs.com/danceonly/p/3868760.html
/*
题意 ： 从n个箱子里面选择s朵花，问有多少种不同的选择。

《组合数学》上有类似的题目，大概在6.2章。(写一下主要是让自己记的深些- -b)

首先你得会算这样一个问题，就是把m个等价的物品放到n个不同的容器中的方法数为C(n+m-1, m-1)， 这个用挡板法很容易证明的。

然后假如每个箱子是无穷的多的话(或者>=s)，答案就是C(n+s-1, n-1);

然后算S{i}：就是限定第i个至少要拿f[i]+1朵花的前提下的方案数。

S{i, j}就是表示第i个和第j个分别要拿f[i]+1和f[j]+1朵花的方案数。

。。。

这个样的话最后的ans = C(n+s-1, n-1) - S{1}- S{2}...S{i},.. + S{1, 2} + S{i, j} ... - S{i, j, k}... // 这里就是用到容斥原理了。。

这道题目n比较小，所以就直接枚举好了，复杂度为O(n * 2^n)，小心他有的数据时10^14在乘法的时候不要爆了。
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef __int64 lld;
const int MOD = 1e9 + 7;

lld exgcd(lld a, lld b, lld &x, lld &y) {
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    lld ret = exgcd(b, a%b, y, x);
    y -= (a/b) * x;
    return ret;
}

lld Inv(lld a, lld MOD) {
    lld x, y;
    lld d = exgcd(a, MOD, x, y);
    return d == 1 ? (x%MOD+MOD)%MOD : printf("no\n");
}
lld calc(lld N, int M) {
    lld ret = 1;
    for (int i = 0; i < M; i++) {
        ret = ret * ((N-i)%MOD) % MOD * Inv(i+1, MOD) % MOD;
    }
    return ret;
}

lld s;
int n;
lld f[105];
int main() {
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    lld ret = 0;
    for (int i = 0; i < (1<<n); i++) {
        lld rem = s;
        int fg = 1;
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) {
                fg = -fg;
                rem -= (f[j] + 1);
            }
        }
        if (rem < 0) continue;
        ret += fg * calc(rem + n - 1, n - 1);
        ret %= MOD;
    }
    cout << (ret%MOD + MOD) % MOD << endl;
    return 0;
}