/*
**链接**
传送门: [here]()
**题意**
**思路**
**备注**
*/
#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int MXN = 6e4 + 5;
const int MXE = 2e6 + 6;
int n, m;
vector<int> mp[MXN];
struct lp{
	int l,r,sum;
}cw[MXN*10];
int rt[MXN],tot;
void updat(int l,int r,int last,int &cur,int x){
	cw[++ tot] = cw[last];
	cur = tot;
	if(l == r) {
        ++ cw[cur].sum;
        return;
    }
	int mid=(l+r)>>1;
	if(x<=mid)updat(l,mid,cw[last].l,cw[cur].l,x);
	else updat(mid+1,r,cw[last].r,cw[cur].r,x);
    cw[cur].sum = cw[cw[cur].l].sum + cw[cw[cur].r].sum;
}
int quer(int l,int r,int last,int cur,int k){
    if(k < l || k > r) return 0;
	if(l==r) return max(0, cw[cur].sum-cw[last].sum);
	int mid=(l+r)>>1;
	if(k<=mid)return quer(l,mid,cw[last].l,cw[cur].l,k);
	else {
		int ans=quer(mid+1,r,cw[last].r,cw[cur].r,k);
		ans+=cw[cw[cur].l].sum-cw[cw[last].l].sum;
		return ans;
	}
}
int get(int l, int r, int L, int R) {
    // debug(quer(1, n, rt[l-1], rt[r], R))
    return quer(1, n, rt[l-1], rt[r], R) - quer(1, n, rt[l-1], rt[r], L-1);
}
int Qur(int a, int b) {
    if(a > b) swap(a, b);
    if(a == b) return 0;
    else if(a + 1 == b) return 1;
    else if(a == 1 && b == n) return 1;
    int res = b - a, ans = b - a;
    int tmp = get(a, b, a, b);
    // debug(tmp)
    ans = min(res - tmp, ans);
    res = n - res;
    // debug(ans, res, get(1, a, 1, a), get(1, a, b, n), get(b, n, b, n))
    tmp = get(1, a, 1, a) + get(1, a, b, n) + get(b, n, b, n);
    ans = min(res - tmp, ans);
    return ans;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    scanf("%d", &n);
    for(int i = 0; i < n - 3; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        if(a > b) swap(a, b);
        mp[a].eb(b);
    }
    for(int i = 1; i <= n; ++i) {
        rt[i] = rt[i - 1];
        for(int x: mp[i]) {
            updat(1, n, rt[i], rt[i], x);
            // debug(x)
        }
        // debug(i, quer(1, n, rt[0], rt[i], 5))
    }
    // rep(a, 1, n + 1) {
    //     rep(b, a + 1, n + 1) {
    //         // printf("%d %d %d\n", a, b, Qur(a, b));
    //     }
    // }
    scanf("%d", &m);
    while(m --) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", Qur(a, b));
    }
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
