#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long LL;

const int MXN = 1e6 + 6;
const int MXT = 5e5 + 5;

int pr[MXN/2], noprime[MXN], pcnt;
int yinzi[MXN/2], top;
void prime_init() {
    noprime[0] = noprime[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pr[pcnt++] = i; 
        for(int j = 0; j < pcnt && i * pr[j] < MXN; ++j) {
            noprime[i*pr[j]] = 1;
            if(i % pr[j] == 0) break;
        }
    }
}

LL a, b, n;

void calc(LL _) {
    LL t = sqrt(_);
    top = 0;
    for(int i = 0; i < pcnt; ++i) {
        if(_ % pr[i] == 0) {
            yinzi[top++] = pr[i];
            while(_ % pr[i] == 0) _ /= pr[i];
        }
        if(_ == 1) break;
    }
    if(_ != 1) yinzi[top++] = _;
}
LL get_ans(LL a) {
    int State = 1 << top;
    LL ans = 0;
    for(int i = 0; i < State; ++i) {
        LL tot = 1, cnt;
        int num = 0;
        for(int j = 0; j < top; ++j) {
            if(i&(1<<j)) {
                ++num;
                tot *= yinzi[j];
            }
        }
        cnt = a/tot;
        if(num%2 == 0) {
            ans += cnt;
        }else {
            ans -= cnt;
        }
    }
    return ans;
}
int main(int argc, char const *argv[]) {
    prime_init();
    int tim, cas = 0;
    scanf("%d", &tim);
    while(tim--) {
        scanf("%lld%lld%lld", &a, &b, &n);
        calc(n);
        printf("Case #%d: %lld\n", ++cas, get_ans(b) - get_ans(a-1));
    }
    return 0;
}