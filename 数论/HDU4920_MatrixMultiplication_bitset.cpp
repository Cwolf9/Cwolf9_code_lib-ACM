//HDU4920_MatrixMultiplication_bitset.cpp
//https://www.cnblogs.com/danceonly/p/3894279.html
/*
题意 ：给两个n*n的矩阵A、B，要求算的A*B (答案对3取模)

（比赛的时候一直想不到怎么去消复杂度，在最后的时候想到了用三进制压几位状态(就是几位几位算)应该可以过的，可是敲完比赛也结束。(压6位是可以过的)


正解是bitset搞，第一次接触到bitset这个神器，用起来确实很炫酷。

方法是统计A矩阵mod3后1出现在哪些位置，2出现哪些位置，B也一样，只是A是以一行为一个“状态”， 而B是以一列为一个“状态”，然后&一下，最后.count()统计。

.count()函数似乎速度很快 0.0
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <string>

using namespace std;
const int MAXN = 805;
const int MOD = 3;
typedef int Mat[MAXN][MAXN];
Mat A, B, C;
bitset<MAXN> A1[MAXN], A2[MAXN], B1[MAXN], B2[MAXN];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) {
            A1[i].reset(); B1[i].reset();
            A2[i].reset(); B2[i].reset();
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &A[i][j]);
                A[i][j] %= MOD;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &B[i][j]);
                B[i][j] %= MOD;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (A[i][j] == 1) {
                    A1[i][j-1] = 1;
                }else if (A[i][j] == 2) {
                    A2[i][j-1] = 1;
                }
            }
        }
        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= n; i++) {
                if (B[i][j] == 1) {
                    B1[j][i-1] = 1;
                }else if (B[i][j] == 2){
                    B2[j][i-1] = 1;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int a = (A1[i]&B1[j]).count()+(A2[i]&B2[j]).count();
                int b = (A1[i]&B2[j]).count()+(A2[i]&B1[j]).count();
                C[i][j] = a + b * 2;
                printf("%d%c", C[i][j]%MOD, " \n"[j == n]);
            }
        }
    }
    return 0;
}