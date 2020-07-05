#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
void debug_out() { cerr << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cerr << f << " ";
    debug_out(r...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int MXN = 601;
int n, m;
int mp[MXN][MXN], up[MXN][MXN];
bool vis[MXN][MXN];
struct lp {
    int id, x, y;
}A, B;
vector<lp> eg;
bool cmp(const lp&a, const lp& b) {
    return a.id < b.id;
}
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0 ,-1};
void bfs(int st, int ed) {
    if(vis[st][ed]) return ;
    queue<lp> Q;
    int hd = mp[st][ed];
    up[st][ed] = hd;
    A.id = 0, A.x = st, A.y = ed;
    Q.push(A);
    while(!Q.empty()) {
        // if(tim >= 500*500) break;
        B = Q.front(); Q.pop();
        // debug(B.x, B.y, B.id, up[B.x][B.y])
        if(vis[B.x][B.y]) continue;
        vis[B.x][B.y] = true;
        for(int i = 0; i < 4; ++i) {
            int px = B.x + dir[i][0], py = B.y + dir[i][1];
            if(px < 1 || py < 1 || px > n || py > n || vis[px][py]) continue;
            if(B.id == 0) {
                A.x = px, A.y = py;
                if(mp[px][py] > hd) {
                    up[px][py] = mp[px][py];
                    A.id = 1;
                }else {
                    up[px][py] = hd;
                    A.id = 0;
                }
            }else if(B.id == 1 && mp[px][py] >= mp[B.x][B.y]) {
                A.x = px, A.y = py;
                up[px][py] = mp[px][py];
                A.id = 1;
            }
            Q.push(A);
        }
    }
}
int main() {
#ifndef ONLINE_JUDGE
    // freopen("E://ADpan//in.in", "r", stdin);
    // freopen("E://ADpan//out.out", "w", stdout);
#endif
    // iis;
    int tim = read();
    while (tim--) {
        n = read(), m = read();
        int tmp_max = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                mp[i][j] = read();
                tmp_max = max(tmp_max, mp[i][j]);
                vis[i][j] = 0;
            }
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                up[i][j] = tmp_max;
            }
        }
        eg.clear();
        for(int i = 0, a, b; i < m; ++i) {
            a = read(), b = read();
            A.id = mp[a][b];
            A.x = a;
            A.y = b;
            eg.emplace_back(A);
        }
        sort(eg.begin(), eg.end(), cmp);
        for(lp v: eg) {
            bfs(v.x, v.y);
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) printf("%d%c", up[i][j] - mp[i][j], " \n"[j == n]);
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}