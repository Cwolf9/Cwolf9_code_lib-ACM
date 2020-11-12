//https://www.bilibili.com/video/av95075590/
//O(log^2) t 100 abpq 1e9
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 998244353;
int ksm(int a, int b, int modd) {
    int res = 1;
    for (; b > 0; b >>= 1, a = (LL)a * a % modd) {
        if (b & 1) res = (LL)res * a % modd;
    }
    return res;
}
int a, b, p, q;
struct Data {
    LL f;//$Sigma_{i=0}^{n} floor((a*i+b)/c)$
};
LL get(LL a, LL b, LL c, LL n) {
    Data ans, tmp;
    if(n < 0) return 0;
    if (a == 0) {
        ans.f = (n + 1) * (b / c);
        return ans.f;
    }
    if (a >= c || b >= c) {
        tmp.f = get(a % c, b % c, c, n);
        ans.f = (tmp.f + (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1));
        return ans.f;
    }
    LL m = (a * n + b) / c;
    tmp.f = get(c, c - b - 1, a, m - 1);
    ans.f = (n * m - tmp.f);
    return ans.f;
}
LL check(int l, int r) {
    return get(p, q-l, q, b) - get(p, q-l, q, a - 1) - (get(p, q-(r + 1), q, b) - get(p, q-(r + 1), q, a - 1));
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:/in.in", "r", stdin);
#endif
    int tim;
    scanf("%d", &tim);
    while (tim--) {
        scanf("%d%d%d%d", &a, &b, &p, &q);
        int gc = __gcd(p, q);
        p /= gc, q /= gc;
        p %= q;
        if(q & 1) p <<= 1, q <<= 1;
        int hq = q / 2;
        int L = 0, R = hq, mid, ans = hq;
        while(L <= R) {
            mid = (L + R) >> 1;
            int l = hq - mid, r = min(hq + hq - 1, hq + mid);
            if(check(l, r) > 0) {
                ans = mid;
                R = mid - 1;
            }else {
                L = mid + 1;
            }
        }
        L = a, R = b, gc = b;
        int l = hq - ans, r = min(hq + hq - 1, hq + ans);
        while(L <= R) {
            mid = (L + R) >> 1;
            if(get(p, q-l, q, mid) - get(p, q-l, q, a - 1) - 
            (get(p, q-(r + 1), q, mid) - get(p, q-(r + 1), q, a - 1)) > 0) {
                gc = mid;
                R = mid - 1;
            }else L = mid + 1;
        }
        printf("%d\n", gc);
    }
    return 0;
}