#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
const int MXN = 6e5 + 7;
const int mod = 998244353;

int n, m;
int ar[MXN], sum[MXN];
int bs[35];
struct TRIE {
    int sum[MXN*40], cw[MXN*40][2], rt[MXN], tot;
    void init() {
        sum[0] = 0;cw[0][0] = cw[0][1] = 0;rt[0] = 0;tot = 0;
    }
    void insert(int old, int cur, int len) {//31
        int t = ++ tot; rt[cur] = t;
        cw[t][0] = cw[t][1] = 0;
        old = rt[old];
        for(int i = len-1; i >= 0; --i) {
            sum[t] = sum[old] + 1;
            cw[t][!bs[i]] = cw[old][!bs[i]];
            if(cw[t][bs[i]] == 0) cw[t][bs[i]] = ++ tot;
            t = cw[t][bs[i]]; old = cw[old][bs[i]];
        }
        sum[t] = sum[old] + 1;
    }
    LL query(int l, int r, int len) {
        LL ans = 0;
        l = rt[l], r = rt[r];
        for(int i = len-1; i >= 0; --i) {
            if(sum[cw[r][bs[i]]] - sum[cw[l][bs[i]]] > 0) {
                ans += (1LL << i);
                l = cw[l][bs[i]]; r = cw[r][bs[i]];
            }else {
                l = cw[l][!bs[i]]; r = cw[r][!bs[i]];
            }
        }
        return ans;
    }
}trie;

int main(int argc, char const *argv[]) {
    scanf("%d%d", &n, &m);
    trie.init();
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &ar[i]), sum[i] = sum[i-1] ^ ar[i];
        for(int j = 0; j < 31; ++j) bs[j] = ((sum[i] >> j)&1);
        trie.insert(i-1, i, 31);
    }
    char s[2]; int l, r, x;
    while(m --) {
        scanf("%s", s);
        if(s[0] == 'A') {
            scanf("%d", &x);
            ar[++n] = x;
            sum[n] = sum[n-1] ^ x;
            for(int j = 0; j < 31; ++j) bs[j] = ((sum[n] >> j)&1);
            trie.insert(n-1, n, 31);
        }else {
            scanf("%d%d%d", &l, &r, &x);
            if(l == r && l == 1) {
                printf("%d\n", sum[n]^x);
            }else {
                int ans = x ^ sum[n];
                for(int j = 0; j < 31; ++j) bs[j] = !((ans >> j)&1);
                printf("%lld\n", trie.query(max(l-2,0), r-1, 31));
            }
        }
    }
    return 0;
}