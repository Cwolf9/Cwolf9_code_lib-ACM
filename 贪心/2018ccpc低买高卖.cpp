//卖比买赚钱，假设每天都在卖（那么每天都在赚钱）
//不妨假设每到新的一天，都把当天的股票卖掉
//那因为现在一点股票都没有，所有至少有一天要买入，
//那就需要在今天或今天的前某天把其当天的卖出改成持有，或者持有改成买入 
#include<bits/stdc++.h>
#define mme(a,b) memset((a),(b),sizeof((a)))
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
 /*
对于当前价格B而言，只要前面有比这个价格低的价格A，那么当前情况A买入B卖出一定盈利
但是A买入B卖出不一定是最优解，所以为了有后悔药吃，就再push两个B进入优先队列，一个表示卖出，一个表示买入。
每天都卖出，每次累加差值就可以了。累加很多个差分值肯定会得到最优解的。
因为A买入B卖出B买入C卖出 和 A买入C卖出 效果一样
*/
int main() {
#ifndef ONLINE_JUDGE
    freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  int tim;
  int n;
  scanf("%d", &tim);
  while(tim--){
  scanf("%d",&n);
    priority_queue<pair<int,int>>q;
    LL ans = 0;
    int tot = 0;
    for(int i = 0, x; i < n; ++i){
      scanf("%d",&x);
      q.push(make_pair(-x,1));//买入
      q.push(make_pair(-x,2));//卖出
      LL tmp=x+q.top().first;
      //printf("%lld ",tmp); 
      if(q.top().second == 1)tot+=2;
      //printf("*%lld\n", tmp);
      ans += tmp;
      q.pop(); 
    }
    printf("%lld %d\n",ans,tot);
  }
  return 0;
}