#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifndef ONLINE_JUDGE
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif

const double eps = 1e-8;
const double pi = acos(-1);

const int maxn = 4096 + 7;
int n;
int r[20000];
int rr[20000];
double ff[2][20000];

int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
    }
    sort(r + 1, r + n);
    int k = 0, buf = 1;
    while (buf < n) {
        buf <<= 1;
        k++;
    }
    int bol = 1;
    if (buf != n) {
        bol <<= 1;
        int ju = buf - n;
        for (int i = 0; i < ju; i++) {
            rr[i * 2] = r[i];
            rr[i * 2 + 1] = r[i];
        }
        for (int i = ju; i < n; i++) {
            rr[i + ju] = r[i];
        }
    } else {
        for (int i = 0; i < n; i++) {
            rr[i] = r[i];
        }
    }
    for (int i = 0; i <= buf; i++) {
        ff[0][i] = 1;
    }
    int ttt = 0;
    for (int kk = 2; kk <= buf; kk <<= 1) {
        int len =(kk>>1);
        ttt = 1 - ttt;
        for (int i = 0; i < buf; i++) {
            ff[ttt][i] = 0;
        }
        for (int st = 0; st < buf; st += kk) {
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) {
                    double u=ff[1 - ttt][st + i] * ff[1 - ttt][st + len + j];
                    ff[ttt][st + i] += u * rr[st + i] /(rr[st + i] + rr[st + len + j]);
                    ff[ttt][st + len + j] += u * rr[st + len + j] /(rr[st + i] + rr[st + len + j]);
                    // debug(len,kk,st,u,rr[st + i],rr[st + len + j])
                }
            }
            // for (int i = 0; i < buf; i++) {
            //     printf("%lf ", ff[ttt][i]);
            // }
            // printf("\n");
        }
    }
    printf("%lf", ff[ttt][0] * bol);

    return 0;
}
