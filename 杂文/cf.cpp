#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;
typedef long long LL;

const int MXN = 2e5 + 6;
const int MXE = 5e6 + 6;

int ar[MXN], pre[MXN], pos[25];
int ch[MXE][2], node, buf[MXE];
int ans, p, dp[25], n;
void ins(int n,int P) {
    int now = 0;
    for(int i = 0; i <=21; ++i) {
        pos[i] = n % 2;
        n /= 2;
    }
    for(int i = 21, x; i >= 0; --i) {
        x = pos[i];
        if(ch[now][x] == -1) {
            ch[now][x] = ++node;
            ch[node][0] = ch[node][1] = -1;
        }
        now = ch[now][x];
    }
    buf[now] = min(buf[now], P);
}
void Find(int n) {
    p = -1; ans = 0;
    int now = 0;
    for(int i = 0; i <=21; ++i) {
        pos[i] = n % 2;
        n /= 2;
    }
    for(int i = 21, x; i >= 0; --i) {
        x = pos[i];
        if(ch[now][1 - x] != -1) {
            if(x == 0) ans += dp[i];
            now = ch[now][1 - x];
        }else {
            if(x == 1) ans += dp[i];
            now = ch[now][x];
        }
    }
    p = buf[now] + 1;
}
int main(){
    dp[0] = 1;
    for(int i = 1; i <= 22; ++i) dp[i] = dp[i-1] * 2;
    while(~scanf("%d", &n)){
        node = 0;
        ch[0][0] = ch[0][1] = -1;
        memset(buf, 0x3f, sizeof(buf));
        for(int i = 1; i <= n; ++i) scanf("%d", &ar[i]);
        for(int i = 1; i <= n; ++i) pre[i] = pre[i-1] ^ ar[i], ins(pre[i], i);
        int tmp = pre[n], L = 1, R = n;
        for(int i = n; i >= 1; --i) {
            Find(pre[i]);
            ans ^= pre[i];
            if(p > i) continue;
            if(ans > tmp) {
                tmp = ans;
                R = i; L = p;
            }else if(ans == tmp && i < R) {
                R = i; L = p;
            }else if(ans == tmp && i == R && p > L) {
                L = p;
            }
        }
        printf("%d %d %d\n", tmp, L, R);
        for(int i = 1; i <= node; ++i) ch[i][0] = ch[i][1] = -1;
    }
    return 0;
}

