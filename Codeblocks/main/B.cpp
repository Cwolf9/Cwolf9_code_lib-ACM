#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 10005;
const int INF = 0x3f3f3f3f;
int n, m, tot, vt, vs;
int d[N], head[N];
char mp[55][55];
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
struct lp {
    int to, w, nex;
    lp() {}
    lp(int a, int b, int c) {
        to = a;
        w = b;
        nex = c;
    }
} cw[N << 2];
inline void add(int a, int b, int c) {
    cw[++tot] = lp(b, c, head[a]);
    head[a] = tot;
    cw[++tot] = lp(a, 0, head[b]);
    head[b] = tot;
}
bool bfs() {
    memset(d, -1, sizeof(d));
    queue<int> Q;
    Q.push(vt);
    d[vt] = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i != -1; i = cw[i].nex) {
            int v = cw[i].to;
            if (cw[i ^ 1].w && d[v] == -1) {
                d[v] = d[u] + 1;
                Q.push(v);
            }
        }
    }
    return d[vs] != -1;
}
int dfs(int x, int f) {
    if (x == vt || f == 0) return f;
    int use = 0, w;
    for (int i = head[x]; i != -1; i = cw[i].nex) {
        int to = cw[i].to;
        if (d[to] == d[x] - 1 && cw[i].w) {
            w = dfs(to, min(cw[i].w, f - use));
            cw[i].w -= w, cw[i ^ 1].w += w;
            use += w;
            if (use == f) return f;
        }
    }
    return use;
}
void input() {
    scanf("%s", mp[0]);
    n = strlen(mp[0]);
    for (int i = 1; i < n; ++i) scanf("%s", mp[i]);
    tot = -1;
    memset(head, -1, sizeof(head));  
    
    vs = 0, vt = n * n + 1;
}
int main() {
    input();
    int ans = 0, sum = 0, dian = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mp[i][j] == 'O') {
                add(vs, i * n + j + 1, 1);
                for (int x = 0; x < 4; ++x) {
                    int px = dir[x][0] + i, py = dir[i][1] + j;
                    if (px >= 0 && px < n && py >= 0 && py < n &&
                        mp[px][py] == '.') {
                        add(i * n + j + 1, px * n + py + 1, INF);
                    }
                }
            } else if (mp[i][j] == '.') {
                add(i * n + j + 1, vt, 1);
                ++sum;
            }
        }
    }
    cout << sum << endl;
    while (bfs()) ans += dfs(vs, INF);
    cout << ans << endl;
    /*for(int i = 0; i <= tot; ++i) {
        if(cw[i].to == vt && cw[i].w == 0) -- dian;
    }*/
    printf("%d\n", sum - ans);
    return 0;
}