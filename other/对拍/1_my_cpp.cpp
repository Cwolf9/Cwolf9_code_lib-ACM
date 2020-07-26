#include <bits/stdc++.h>
using namespace std;

int n, ans, ar[1005];
int main(int argc, char const *argv[]){
    int tim;
    //scanf("%d", &tim);
    tim = 1;
    while(tim --) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            scanf("%d", &ar[i]);
        }
        ans = 0;
        for(int i = 0, j, mmax; i < n - 1; ++i) {
            mmax = ar[i];
            for(j = i + 1; j < n; ++j) {
                if(ar[j] > mmax) ans = max(ans, j - i);
                mmax = max(mmax, ar[j]);
                if(ar[j] < ar[i]) break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}