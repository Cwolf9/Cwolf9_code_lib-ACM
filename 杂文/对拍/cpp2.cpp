#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
#define all(x) x.begin(),x.end()
#define iis std::ios::sync_with_stdio(false)
#define mme(a,b) memset((a),(b),sizeof((a)))
using namespace std;
typedef long long LL;
typedef pair<LL,int> pii;
const int MXN = 1e6+7;
const int MXE = 4e6+1e5+7;
const int INF = 0x3f3f3f3f;

int n, m;
int sum[MXE];

void build(int l,int r,int rt){
    sum[rt] = 0;
    if(l == r){
        return;
    }
    int mid = (l + r) >> 1;
    build(l,mid,lson);build(mid+1,r,rson);
}
void update(int p,int c,int l,int r,int rt){
    if(l == r){
        sum[rt] += c;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) update(p, c, l, mid, lson);
    else update(p, c, mid + 1, r, rson);
    sum[rt] = sum[lson] + sum[rson];
}
int query(int p,int l,int r,int rt){
    if(l == r){
        return r;
    }
    int mid = (l + r) >> 1;
    if(p <= sum[lson]) return query(p, l, mid, lson);
    else return query(p - sum[lson], mid + 1, r, rson);
}
int ask(int L,int R,int l,int r,int rt){
    if(L <= l && r <= R){
        return sum[rt];
    }
    int mid = (l + r) >> 1;
    if(L > mid) return ask(L, R, mid + 1, r, rson);
    else if(R <= mid)return ask(L, R, l, mid, lson);
    else {
        return ask(L, mid, l, mid, lson)+ask(mid+1,R,mid+1,r,rson);
    }
}
struct lp{
    int l, r, newl;
}cw[MXN], a[MXN], b[MXN];
int ar[MXN*2];
bool cmp(const lp &a, const lp &b){
    if(a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}
bool cmp2(const lp &a, const lp &b){
    if(a.r == b.r) return a.l > b.l;
    return a.r < b.r;
}
int main(){
    scanf("%d%d", &n, &m);
        int k = 0;
        for(int i = 0; i < n; ++i){
            scanf("%d%d", &cw[i].l, &cw[i].r);
            --cw[i].r;
            ar[k++] = cw[i].l;
        }
        sort(ar, ar + k);
        k = unique(ar, ar + k) - ar;
        for(int i = 0; i < n; ++i){
            cw[i].newl = lower_bound(ar, ar + k, cw[i].l) - ar + 1;
            a[i] = cw[i];
            b[i] = cw[i];
        }
        sort(a, a + n, cmp);
        sort(b, b + n, cmp2);

        int j = 0, cnt = 0, ans = 0;
        for(int i = 0; i < n; ++i){
            while(j < n && a[j].l < b[i].r){
                update(a[j].newl, 1, 1, k, 1);
                ++j;
            }
            int tmp = ask(1, b[i].newl, 1, k, 1);
            if(tmp >= m){
                /*
                int p = query(m, 1, k, 1);
                if(ans < b[i].r - ar[p - 1] + 1){
                    ans = b[i].r - ar[p - 1] + 1;
                }
                */
                if(ans < b[i].r - b[i].l + 1){
                    ans = b[i].r - b[i].l + 1;
                }
            }
            update(b[i].newl, -1, 1, k, 1);
        }
        printf("%d\n", ans);
    
    return 0;
}