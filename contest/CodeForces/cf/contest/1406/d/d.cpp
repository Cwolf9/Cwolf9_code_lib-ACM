#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define lc rt << 1
#define rc (rt << 1) | 1
 
typedef long long LL;
const int maxn = 3e5 + 50;
int INF = 1e8;
int n, m;
LL sum = 0;
LL tree[maxn << 2], lazy[maxn << 2];
LL a[maxn], b[maxn];
void PushDown(int rt){
    tree[lc] += lazy[rt], tree[rc] += lazy[rt];
    lazy[lc] += lazy[rt];
    lazy[rc] += lazy[rt];
    lazy[rt] = 0;
}
void Build(int le, int ri, int rt){
    if(le == ri){
        tree[rt] = a[le];
        return ;
    }
    int mid = (le + ri) >> 1;
    Build(le, mid, lc);
    Build(mid + 1, ri, rc);
}
 
void Update(int le, int ri, int L, int R, LL val, int rt){
    if(L <= le && ri <= R){
        lazy[rt] += val;
        tree[rt] += val;
        return ;
    }
    PushDown(rt);
    int mid = (le + ri) >> 1;
    if(L <= mid) Update(le, mid, L, R, val, lc);
    if(R > mid) Update(mid + 1, ri, L, R, val, rc);
}
 
LL Query(int le, int ri, int pos, int rt){
    if(le == ri) {
        return tree[rt];
    }
    PushDown(rt);
    int mid = (le + ri) >> 1;
    if(pos <= mid) return Query(le, mid, pos, lc);
    else return Query(mid + 1, ri, pos, rc);
}
 
LL c[maxn]; //对应原数组和树状数组
int lowbit(int x){
    return x&(-x);
}
void updata(int i,LL k){    //在i位置加上k
    while(i <= n){
        c[i] += k;
        i += lowbit(i);
    }
}
LL getsum(int i){        //求A[1 - i]的和
    LL res = 0;
    while(i > 0){
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}
 
 
LL muQuery(int ip, int x){
	LL res = Query(1, n, 1, 1);
	LL sum2 = getsum(x);
	LL y = -(sum - res) / 2LL;
	LL ans = y + sum2;
	LL val = Query(1, n, x, 1);
	if(ip == 0){
		return ans;
	} else {
		return val - ans;
	}
}
void print() {
    printf("my print:\n");
    for(int i = 1; i <= n; ++i) printf("%lld ", muQuery(0, i)); printf("\n");
    for(int i = 1; i <= n; ++i) printf("%lld ", muQuery(1, i)); printf("\n");
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%I64d", &a[i]);
        if(a[i] > a[i - 1] && i > 1){
            sum += a[i] - a[i - 1];
            updata(i, a[i] - a[i - 1]);
        }
    }
    // printf("sum = %I64d\n", sum);
    LL y = -(sum - a[1]) / 2LL;
    printf("%I64d\n", max(sum + y, a[1] - y));
    Build(1, n, 1);
    int q;
    scanf("%d", &q);
    print();
    while(q--){
        int le, ri, x;
        scanf("%d%d%d", &le, &ri, &x);
        LL ple = Query(1, n, le, 1), pri = Query(1, n, ri, 1);
        Update(1, n, le, ri, x, 1);
        if(le != 1){
            LL nle = Query(1, n, le, 1);
            LL res = Query(1, n, le - 1, 1);
            if(ple >= res){
                if(nle >= res){
                    sum += nle - ple;
                    updata(le, nle - ple);
                } else {
                    sum -= ple - res;
                    updata(le, res - ple);
                }
            } else {
                if(nle >= res) {
                	sum += nle - res;
                	updata(le, nle - res);
                }
            }
        }
        if(ri != n){
            LL nri = Query(1, n, ri, 1);
            LL res = Query(1, n, ri + 1, 1);
            if(pri <= res){
                if(nri <= res){
                    sum += pri - nri;
                    updata(ri + 1, pri - nri);
                } else {
                    sum -= res - pri;
                    updata(ri + 1, pri - res);
                }
            } else {
                if(nri < res) {
                	sum += res - nri;
                	updata(ri + 1, res - nri);
                }
            }
        }
        printf("%I64d\n", max(muQuery(0, n), muQuery(1, 1)));
        print();
    }
    return 0;
}