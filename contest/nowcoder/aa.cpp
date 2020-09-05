#include<bits/stdc++.h>
using namespace std;
mt19937 rng(time(NULL));
void gao(int n, int k) {
    map<int, int> mp;
    while(k > 0) {
        int rd = rng() % 16 + 1;
        if(mp[rd] == 0) {
            printf("%d\n", rd);
            -- k;
        }
        mp[rd] = 1;
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    gao(16, 4);
    return 0;
}