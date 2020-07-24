#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int MXN = 1e3 + 5;
int n, m, k;
int du[MXN];
inline int lowbit(int x) {
    return x & (-x);
}
vector<int> tree[MXN], ori[MXN];
void insewrt(int x, int v, int id) {
    int N = du[id] + 2;
    ori[id][x] = v;
    while (x <= N) {
        tree[id][x] = ori[id][x];
        v = lowbit(x);
        for (int i = 1; i < v; i <<= 1) {
            tree[id][x] = max(tree[id][x], tree[id][x - i]);
        }
        x += lowbit(x);
    }
}
int query(int x, int y, int id) {
    int ans = 0;
    while (y >= x) {
        ans = max(ans, ori[id][y]);
        for (--y; y - lowbit(y) >= x; y -= lowbit(y)) {
            ans = max(ans, tree[id][y]);
        }
    }
    return ans;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    srand(time(NULL));
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 1; i <= 500; ++i) {
            ori[i].clear();
            ori[i].shrink_to_fit();
            tree[i].clear();
            tree[i].shrink_to_fit();
        }
        int id = rand()%500 + 1;
        du[id] = n - 1;
        tree[id].resize(du[id] + 5);
        ori[id].resize(du[id] + 5);
        for(int i = 0, x; i <= du[id]; ++i) {
            scanf("%d", &x);
            insewrt(i + 1, x, id);
        }
        char s[2];
        int x, y;
        while(m --) {
            scanf("%s", s);
            scanf("%d%d", &x, &y);
            if(s[0] == 'U') {
                insewrt(x, y, id);
            }else {
                printf("%d\n", query(x, y, id));
            }
        }
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

