#include<bits/stdc++.h>
using namespace std;
const int MXN = 1e6 + 6;
const int INF = 0x3f3f3f3f;

int x, y;
struct lp {
    int x, y;
}cw[MXN];
int mp[1001][1001], flag;
void go(int X, int Y,int ip = 0) {
    x = X, y = Y;
    cout<<x<<y<<"\n";
    fflush(stdout);
    int k;
    cin>>k;
    if(ip || k <= 0) {
        cin>>k>>k;
        flag = 1; return;
    }
    cin>>cw[k].x>>cw[k].y;
}
void check() {
    for(int i = -1; i <= 1; ++i) {
        for(int j = -1; j <= 1; ++j) {
            if(x + i <= 0 || y + j <= 0 || x + i > 999 || y + j > 999) continue;
            for(int k = 1; k <= 666; ++k) {
                if(x+i == cw[k].x) {
                    go(x+i, y, 1);
                    return;
                }
                if(y+j == cw[k].y) {
                    go(x, y+j, 1);
                    return;
                }
            }
        }
    }
}
int main() {
    cin>>x>>y;
    for(int i = 1; i <= 666; ++i) cin>>cw[i].x>>cw[i].y;
    while(x < 500 && flag == 0) go(x+1, y);
    while(x > 500 && flag == 0) go(x-1, y);
    while(y < 500 && flag == 0) go(x, y+1);
    while(y > 500 && flag == 0) go(x, y-1);
    if(flag) return 0;
    int cnt[4]={0,};
    for(int i = 1; i <= 666; ++i) {
        mp[cw[i].x][cw[i].y] = i;
        if(cw[i].x <= 500 && cw[i].y <= 500) ++cnt[0];
        if(cw[i].x >= 500 && cw[i].y <= 500) ++cnt[1];
        if(cw[i].x <= 500 && cw[i].y >= 500) ++cnt[2];
        if(cw[i].x >= 500 && cw[i].y >= 500) ++cnt[3];
    }
    int cc = min(min(cnt[0],cnt[1]),min(cnt[2],cnt[3]));
    while(flag == 0) {
        check();
        if(flag) break;
        if(cc == cnt[0]) {
            go(x+1, y+1);
        }else if(cc == cnt[1]) {
            go(x-1, y+1);
        }else if(cc == cnt[2]) {
            go(x+1, y-1);
        }else {
            go(x-1, y-1);
        }
    }
    return 0;
}
