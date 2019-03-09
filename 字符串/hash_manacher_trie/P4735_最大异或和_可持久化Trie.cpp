#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
const int MXN = 1e6 + 7;
const int mod = 998244353;

int n, m;
int ar[MXN], sum[MXN];
int bs[35];
struct TRIE {
    int sum[MXN], cw[MXN][2], rt[MXN], tot;
    void init() {
        tot = 0; cw[0][0] = cw[0][1] = 0; rt[0] = 0; sum[0] = 0;
    }
    void insert(int old, int cur, int len) {//31
        int t = ++ tot;
        cw[t][0] = cw[t][1] = 0; rt[cur] = t;
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
        for(int j = 0; j < 31; ++j) bs[j] = (sum[i] >> j);
        trie.insert(i-1, i, 31);
    }
    char s[2]; int l, r, x;
    while(m --) {
        scanf("%s", s);
        if(s[0] == 'A') {
            scanf("%d", &x);
            ar[++n] = x;
            sum[n] = sum[n-1] ^ x;
            for(int j = 0; j < 31; ++j) bs[j] = (sum[n] >> j);
            trie.insert(n-1, n, 31);
        }else {
            scanf("%d%d%d", &l, &r, &x);
            LL ans = x ^ sum[n];
            -- l, -- r;
            for(int j = 0; j < 31; ++j) bs[j] = !(ans >> j);
            printf("%lld\n", trie.query(l, r, 31));
        }
    }
    return 0;
}