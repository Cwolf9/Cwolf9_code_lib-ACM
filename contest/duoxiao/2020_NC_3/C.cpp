/*
链接
https://ac.nowcoder.com/acm/contest/5668/C
题意
给你一个固定的二十个点来描述一个左手或者右手的情况，上帝可以把它任意旋转或者平移
坐标输入时6位小数的浮点数，范围不超过100，输入按顺时针或者逆时针顺序给你，要你判断
是左手还是右手
思路
找到最长的两个直角边，和另一个随便不是直角边的点，判断一下叉积的正负即可
备注

*/
#include <bits/stdc++.h>
#define fuck(x) cout<<'['<<#x<<' '<<(x)<<"]\n"
using namespace std;
typedef long long LL;
typedef long long db;
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);

const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int MX = 1e6 + 5;
const double eps = 1e-9;
struct lp {
    db x, y;
    bool operator<(const lp&b) const {
        if(x == b.x) return y < b.y;
        return x < b.x;
    }
    lp operator+(lp p){return {x+p.x,y+p.y};}
    lp operator-(lp p){return {x-p.x,y-p.y};}
    db operator *(lp s) {return x * s.x + y * s.y;}
    db operator ^(lp s) {return x * s.y - y * s.x;}
    db dot(lp p) {return x*p.x+y*p.y;}
    db det(lp p) {return x*p.y-y*p.x;}
} cw[MX];
inline int sign(db a) {return a < -eps?-1:a>eps;}
db cross(lp a, lp b, lp c) {
    return ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}
db get(int i, int k) {
    return (cw[i].x-cw[k].x)*(cw[i].x-cw[k].x)+(cw[i].y-cw[k].y)*(cw[i].y-cw[k].y);
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int T, n; scanf("%d",&T);
    while(T--) {
        n = 20;
        char s[20];
        for(int i = 0; i < n; ++i) {
            long long ans = 0;
            int f = 1;
            scanf("%s", s);
            int len = strlen(s);
            for(int i = 0; i < len; ++i) {
                if(isdigit(s[i]))ans = ans * 10 + s[i] - '0';
                else if(s[i] == '-') f = -1;
            }
            cw[i].x = ans * f;
            ans = 0;
            f = 1;
            scanf("%s", s);
            len = strlen(s);
            for(int i = 0; i < len; ++i) {
                if(isdigit(s[i]))ans = ans * 10 + s[i] - '0';
                else if(s[i] == '-') f = -1;
            }
            cw[i].y = ans * f;
            // debug(cw[i].x, cw[i].y)
        }
        int pos = 0, pos2 = 0, flag = 1, pos3 = 0, pos4 = 0;
        long long Mx = 0;
        for(int i = 0; i < n; ++i) {
            flag = 0;
            for(int j = 0; j < n; ++j) {
                if(i == j) continue;
                if((abs(i-j) == 1 || abs(i-j) == n - 1) && get(i, j) > Mx) {
                    Mx = get(i, j);
                    pos = i, pos2 = j;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            if((i != pos && ((abs(i - pos2) == 1) || abs(i - pos2) == n-1))) {
                pos3 = i;
            }
        }
        for(int i = 0; i < n; ++i) {
            if((i != pos2 && ((abs(i - pos) == 1)||abs(i - pos) == n-1))) {
                pos4 = i;
            }
        }
        // debug(pos, pos2, pos3, pos4)
        lp x, y;
        if(get(pos2, pos3) > get(pos, pos4)) {
            // debug(pos3)
            x = cw[pos3] - cw[pos];
            y = cw[pos2] - cw[pos];
            if(sign(x.det(y)) > 0) flag = 1;
            else flag = -1;
        }else {
            // debug(pos4)
            x = cw[pos4] - cw[pos2];
            y = cw[pos] - cw[pos2];
            if(sign(x.det(y)) > 0) flag = 1;
            else flag = -1;
        }
        printf("%s\n", flag<0?"right":"left");
    }
    return 0;
}