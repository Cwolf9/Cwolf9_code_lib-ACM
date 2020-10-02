#include<bits/stdc++.h>
using namespace std;
const int MXN = 1e5 + 5;
int n;
struct Triangle {
    int val[3];//三角形边权
    double grey;
    bool operator<(const Triangle&B) const {
        return grey < B.grey;
    }
}ar[MXN];
int dp[MXN][3], ans;
set<int> ndp[MXN];
vector<int> vs;
int get_id(int x) {
    return lower_bound(vs.begin(), vs.end(), x) - vs.begin() + 1;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= 3; ++j) scanf("%d", &ar[i].val[j]), vs.emplace_back(ar[i].val[j]);
        scanf("%lf", &ar[i].grey);
    }
    //将三角形按灰度值排序
    sort(ar + 1, ar + n + 1);
    //离散化三角形边权值
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    //初始化答案为1
    ans = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= 3; ++j) {
            ar[i].val[j] = get_id(ar[i].val[j]);
            //保存暂时更新的dp值
            if(ndp[ar[i].val[j]].empty()) dp[i][j] = 1;
            else dp[i][j] = *(--ndp[ar[i].val[j]].end()) + 1;
            ans = max(ans, dp[i][j]);
        }
        //将灰度值相同的三角形一并更新
        int ti = i;
        while(i < n && fabs(ar[i + 1].grey - ar[ti].grey) < 1e-8) {
            ++ i;
            for(int j = 1; j <= 3; ++j) {
                ar[i].val[j] = get_id(ar[i].val[j]);
                //保存暂时更新的dp值
                if(ndp[ar[i].val[j]].empty()) dp[i][j] = 1;
                else dp[i][j] = *(--ndp[ar[i].val[j]].end()) + 1;
            }
        }
        for(int j = ti; j <= i; ++j) {
            ndp[ar[j].val[1]].insert(max(dp[j][2], dp[j][3]));
            ndp[ar[j].val[2]].insert(max(dp[j][1], dp[j][3]));
            ndp[ar[j].val[3]].insert(max(dp[j][1], dp[j][2]));
        }
    }
    printf("%d\n", ans);
#ifndef ONLINE_JUDGE
    // cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}