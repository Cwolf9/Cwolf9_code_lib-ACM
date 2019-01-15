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

#include<bits/stdc++.h>
#define o2(x) (x)*(x)
#define lson rt<<1
#define rson rt<<1|1
#define fi first
#define se second
#define mme(a,b) memset((a),(b),sizeof((a)))
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int MXN = 2e6 + 5;
const int mod = 1000000007;
int n, m, k;
int ar[MXN];

int main() {
    scanf("%d", &n);
    
    return 0;
}
int ask(int c,int d) {
    cout<<"? "<<c<<" "<<d<<"\n";
    fflush(stdout);
    int ans;
    cin >> ans;
    return ans;
}
int main() {
    int a = 0, b = 0, big = ask(0, 0);
    for(int i = 29; i >= 0; --i) {
        int f = ask(a^(1<<i), b), s = ask(a, b^(1<<i));
        if(f == s) {
            if(big == 1) {
                a ^= (1<<i);
            }else {
                b ^= (1<<i);
            }
            big = f;
        }else if(f == -1) {
            a ^= (1<<i);
            b ^= (1<<i);
        }
    }
    cout<<"! "<<a<<" "<<b<<"\n";
    return 0;
}
