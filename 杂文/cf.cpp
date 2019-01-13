vector<int> ids[N];
int d[N][N];

inline void solve() {
    fore(i, 0, m)
        ids[qs[i].x.x].push_back(i);
    li ans = -1;
    fore(l, 0, n) {//枚举起始点
        fore(r, l, n)
            d[0][r] = a[r] - a[l];
        //dp[i][j]表示加0次油到达j点的最小容量
        fore(k, 1, n + 1) {//枚举加油次数
            int opt = l;//最后一次加油的地方
            fore(r, l, n) {
                while(opt<r&&max(d[k - 1][opt],a[r]-a[opt])>=max(d[k - 1][opt + 1],a[r]-a[opt + 1]))
                    opt++;
                d[k][r] = max(d[k - 1][opt], a[r] - a[opt]);
            }
        }
        
        for(int id : ids[l])
            ans = max(ans, d[qs[id].y.y][qs[id].x.y] * 1ll * qs[id].y.x);
    }
    
    cout << ans << endl;
}
