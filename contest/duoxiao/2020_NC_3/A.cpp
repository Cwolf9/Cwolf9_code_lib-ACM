/*
链接
https://ac.nowcoder.com/acm/contest/5668/A
题意
The game contains nn stages, numbered from 1 to n.
There are four types of stages (numbered from 0 to 3):
type 0: There are no fish and no clam in this stage.
type 1: There are no fish and one clam in this stage.
type 2: There are one fish and no clam in this stage.
type 3: There are one fish and one clam in this stage.
按顺序出现n和状态，每次你只能选择一个操作：
1.有鱼抓鱼
2.有鱼饵没有鱼用鱼饵抓鱼
3.有clam就用clam做鱼饵
4.啥都干不了
问最多抓几个鱼

思路
倒过来分析，有鱼抓鱼，没有鱼就用鱼饵抓鱼，没有鱼饵就像前面借一个鱼饵，当碰到只有clam的时候换一个鱼饵
答案等于抓的鱼的数量-还不了的鱼饵的数量

备注

*/
#include <bits/stdc++.h>

using namespace std;

char s[2000006];
int num;
int main(){
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
	int tim;
    scanf("%d", &tim);
    while(tim --) {
        int n;
        scanf("%d%s", &n, s);
        num = 0;
        int ans = 0;
        for(int i = n - 1; i >= 0; --i) {
            if(s[i] == '0') {
                ++ ans;
                ++ num;
            }else if(s[i] == '1') {
                if(num) -- num;
                else {
                    ++ ans;
                    ++ num;
                }
            }else if(s[i] == '2') {
                ++ ans;
            }else {
                ++ ans;
            }
        }
        printf("%d\n", ans - num);
    }
	return 0;
}