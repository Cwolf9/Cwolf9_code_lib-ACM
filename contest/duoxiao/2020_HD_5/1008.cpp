/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
using namespace std;
#pragma optimize("-O3")
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;

void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int64 ksm(int64 a, int b, int Mod) {int64 res = 1;for(; b; b>>=1, a=a*a%Mod) {if(b&1) res = res * a % Mod;}return res;}
int all, cnt;
void dfs(deque<int> vs, int aim) {
    if(vs.size() == 1) {
        cnt += (vs.front() == aim);
        ++ all;
        return ;
    }
    vs.pop_front();
    for(int x: vs) {
        deque<int> q;
        for(int y: vs) {
            if(x == y) continue;
            else q.push_back(y);
        }
        dfs(q, aim);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    deque<int> vs = deque<int>{1,2,3,4,5,6,7,8,9,10,11};
    for(int i = 3; i <= 9; i += 2) {
        vs.clear();
        for(int j = 1; j <= i; ++j) vs.push_back(j);
        printf("%d: ", i);
        for(int j = 1; j <= i / 2; ++j) printf("0  ");
        for(int x = vs.size()/2; x <= vs.size(); ++ x){
            all = cnt = 0;
            dfs(vs, x);
            int g = __gcd(cnt, all);
            cnt /= g; all /= g;
            printf("%lld ", (int64)cnt*ksm(all, mod-2, mod)%mod);
        }
        printf("\n");
    }
    debug(ksm(2, mod - 2, mod))
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    // system("pause");
#endif
    return 0;
}