#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int MXN = 1e3 + 5;
class Solution {
public:
    /**
     * 
     * @param niuniu int整型vector 牛牛占领的p个星球的编号
     * @param niumei int整型vector 牛妹占领的q个星球的编号
     * @param path int整型vector<vector<>> m条隧道，每条隧道有三个数分别是ui,vi,wi。ui,vi分别是隧道的两边星球的编号，wi是它们之间的距离
     * @param nn int整型 星球个数n
     * @return int整型
     */
    vector<pair<int,int> > mp[200005];
    int dis[200005];
    int Length(vector<int>& niuniu, vector<int>& niumei, vector<vector<int> >& path, int nn) {
        // write code here
        for(vector<int> &x: path) {
            mp[x[0]].emplace_back(make_pair(x[1], x[2]));
            mp[x[1]].emplace_back(make_pair(x[0], x[2]));
        }
        priority_queue<pair<int,int>,vector<pair<int,int>> ,greater<pair<int,int>> >Q;
        vector<int> vis(nn + 1, 0);
        vector<int> dis(nn + 1, 2000000002);
        for(int x: niuniu) {
            dis[x] = 0;
            Q.push(make_pair(dis[x],x));
        }
        while(!Q.empty()){
            pair<int,int> a=Q.top();Q.pop();
            int u=a.second;
            if(vis[u])continue;
            vis[u]=1;
            for(int i=0; i < mp[u].size(); ++i){
                int v=mp[u][i].first;
                if(vis[v])continue;
                if(dis[v]>dis[u]+mp[u][i].second){
                    dis[v]=dis[u]+mp[u][i].second;
                    Q.push(make_pair(dis[v],v));
                }
            }
        }
        int ans = 2000000002;
        for(int x: niumei) {
            ans = min(ans, dis[x]);
        }
        if(ans == 2000000002) ans = -1;
        return ans;
    }
};
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif

#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

