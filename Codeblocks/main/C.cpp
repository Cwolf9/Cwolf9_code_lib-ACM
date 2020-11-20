#include <bits/stdc++.h>
#define rep(i, s, t) for(register int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(register int i = (s), LIM=(t); i >= LIM; --i)
using namespace std;
const int MXN = 2e5 + 5;
int n, m;
void work() {
    string ar;
    cin >> ar;
    n = ar.length();
    int ans = 0, a = 0, b = 0;
    for(int i = 0; i < n; ++i) {
        if(ar[i] == '(') ++ a;
        else if(ar[i] =='[') ++ b;
        else if(ar[i] == ')' && a) ++ ans, -- a;
        else if(ar[i] == ']' && b) ++ ans, -- b;
    }
    printf("%d\n", ans);
}
int main() {
    ios::sync_with_stdio(false);cin.tie(0);
    int tim;
    cin >> tim;
    for(int cas = 1; cas <= tim; ++ cas) work();
    return 0;
}
