//HDU5040_Instrusive最短路.cpp
//https://www.cnblogs.com/danceonly/p/3993061.html
/*
题意 ： 从'M' 到  'T' 最短路程，每次只能走四个方向，并且有一些摄像头每个时间点都会转变下方向(初始方向给出).你有一个box，你在没有罩box的情况下不能被照到，可以在点上等待，也可以罩着box走(时间会慢成3个单位)。

思路 ： 就是一个最短路问题，只要算出在当前时间点u->v最多要花多时间才能到就行了(最多是3)，用spfa跑。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> PII;
const int MAXN = 505;
const int dir[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1}; // N E S W
const int INF = 0x3f3f3f3f;

struct A {
    int x, y;
    A() {}
    A(int a, int b):x(a), y(b) {}
};

char maze[MAXN][MAXN];
int dis[MAXN][MAXN];
int vis[MAXN][MAXN];
int n;
int sx, sy, ex, ey;

PII change(int x, int y, int tim) {
    int add;
    if (maze[x][y] == 'N') add = 0;
    if (maze[x][y] == 'E') add = 1;
    if (maze[x][y] == 'S') add = 2;
    if (maze[x][y] == 'W') add = 3;
    add = (add + tim) % 4;
    return make_pair(x + dir[add][0], y + dir[add][1]);
}
int isok(int x, int y, int tim) {
    if (maze[x][y] == 'N' || maze[x][y] == 'S' || maze[x][y] == 'E' || maze[x][y] == 'W') {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        int X = x + dir[i][0];
        int Y = y + dir[i][1];
        if (maze[X][Y] == 'N' || maze[X][Y] == 'S' || maze[X][Y] == 'E' || maze[X][Y] == 'W') {
            PII tmp = change(X, Y, tim);
            if (tmp.first == x && tmp.second == y) return 0;
        }
    }
    return 1;
}
int calc(int nx, int ny, int nex, int ney, int tim) {
    for (int i = 0; i <= 2; i++) {
        if (isok(nx, ny, tim + i) && isok(nex, ney, tim + i)) {
            return i + 1;
        }
    }
    return 3;
}

int spfa() {
    queue<A> Q;
    memset(vis, 0, sizeof(vis));
    vis[sx][sy] = 1;
    Q.push(A(sx, sy));
    memset(dis, INF, sizeof(dis));
    dis[sx][sy] = 0;
    while (!Q.empty()) {
        A e = Q.front(); Q.pop();
        int X = e.x;
        int Y = e.y;
        int now = dis[X][Y];
        vis[X][Y] = 0;
        for (int i = 0; i < 4; i++) {
            int x = X + dir[i][0];
            int y = Y + dir[i][1];
            if (x <= 0 || y <= 0 || x > n || y > n || maze[x][y] == '#') {
                continue;
            }
            int d = calc(X, Y, x, y, now);
            if (dis[x][y] > now + d) {
                dis[x][y] = now + d;
                if (!vis[x][y]) {
                    vis[x][y] = 1;
                    Q.push(A(x, y));
                }
            }
        }
    }
    return dis[ex][ey] == INF ? -1 : dis[ex][ey];
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", maze[i] + 1);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (maze[i][j] == 'M') {
                    sx = i; sy = j;
                }
                if (maze[i][j] == 'T') {
                    ex = i; ey = j;
                }
            }
        }
        printf("Case #%d: %d\n", cas, spfa());
    }
    return 0;
}
/*
111
3
#S#
WM.
#WT
*/