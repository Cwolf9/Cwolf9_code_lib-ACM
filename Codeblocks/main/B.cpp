#include <bits/stdc++.h>
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
using namespace std;
const int MXN = 2e5 + 5;
int n;
char ar[MXN];
void work() {
    scanf("%s", ar);
    n = strlen(ar);
    printf("%d\n", n);
}
int main() {
    //ios::sync_with_stdio(false);cin.tie(0);
    int tim;
    cin >> tim;
    for(int cas = 1; cas <= tim; ++ cas) work();
    return 0;
}