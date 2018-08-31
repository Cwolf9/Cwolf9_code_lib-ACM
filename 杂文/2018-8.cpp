#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define iis std::ios::sync_with_stdio(false)
#define mme(a,b) memset((a),(b),sizeof((a)))
using namespace std;
typedef long long LL;
typedef pair<LL,int> pii;
const int MXN = 1e5+7;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int n, m;
struct lp{
  LL d, p;
  int id;
  friend bool operator <(const lp &a, const lp &b){
    return a.d<b.d;
  }
}A;
struct lh{
  LL st, ed;
  friend bool operator <(const lh &a, const lh &b){
    return a.st<b.st;
  }
}B;
struct fuck{
  LL first, second, d;//first 是需要时间，second是id，d是考试时间
  friend bool operator <(const fuck &a, const fuck &b){
    return a.first>b.first;
  }
}a;
struct HH{
  LL first, second, d;//first 是需要时间，second是id，d是考试时间
  int id;
}cw[N];
bool cmp1(const HH &a, const HH &b){
  return a.first<b.first;
}
bool cmp2(const HH &a, const HH &b){
  return a.d<b.d;
}
priority_queue<lp>q1;
priority_queue<lh>q2;
priority_queue<fuck> >Q;
int main(){
#ifndef ONLINE_JUDGE
    //freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
  while(~scanf("%d", &n)&&n){
    while(!q1.empty())q1.pop();
    while(!q2.empty())q2.pop();
    while(!Q.empty())Q.pop();
    for(int i = 0; i < n; ++i){
      scanf("%I64d%I64d", &A.d,&A.p);
      A.id = i + 1;
      q1.push(A);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; ++i){
      scanf("%I64d%I64d", &B.st,&B.ed);
      q2.push(B);
    }
    std::vector<int> ans;
    LL tmp = q1.top().d;
    while(q2.size()&&q2.top().st>tmp)q2.pop();
    while(!q1.empty()){
      A = q1.top();q1.pop();
      LL d = A.d, p = A.p;
      int id = A.id;
      LL tim = 0; tmp = 0;
      if(q1.size() == 0){
        tim = d - 1;
        tmp = 0;
      }else{
        tmp = q1.top().d;
        tim = d - tmp - 1;
      }
      if(p == 0LL){
        ans.push_back(id);
      }else{
        a.first = p;a.second = id;a.d = d;
        Q.push(a);
      }
      while(q2.size() && q2.top().st > tmp){
        B = q2.top();q2.pop();
        tim -= (B.ed - B.st + 1);
      }
      while(Q.size()){
        fuck hh = Q.top();
        if(tim >= hh.first){
          Q.pop();
          tim -= hh.first;
          ans.push_back(hh.second);
        }else{
          hh.first -= tim;
          Q.pop();
          tim = 0;
          Q.push(hh);
          break;
        }
      }
    }
    int k = 0;
    while(Q.size()){
      a = Q.top();Q,pop();
      cw[k].first = a.first;
      cw[k].second = a.second;
      cw[k].d = a.d;
      ++k;
    }
    if(k){
      sort(cw,cw+k);
      int cnt = 0;
      for(int i = 0; i < k; ++i){

      }
    }
    sort(ans.begin(), ans.end());
    int len = ans.size();
    printf("%d\n", len);
    if(len==0){
      printf("\n");
    }else{
      for(int i = 0; i < len; ++i){
        if(i == len - 1)printf("%d\n", ans[i]);
        else printf("%d ", ans[i]);
      }
    }
  }
  return 0;
}
