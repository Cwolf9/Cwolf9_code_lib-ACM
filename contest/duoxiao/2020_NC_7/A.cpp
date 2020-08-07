#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <stack>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <cassert>
using namespace std;
#define pb push_back
#define INF 1001001001
#define FOR(i,n) for(int (i)=0;(i)<(n);++(i))
#define FORI(i,n) for(int (i)=1;(i)<=(n);++(i))
#define mp make_pair
#define pii pair<int,int>
#define ll long long
#define vi vector<int>
#define SZ(x) ((int)((x).size()))
#define fi first
#define se second
#define wez(n) int (n); scanf("%d",&(n));
#define wez2(n,m) int (n),(m); scanf("%d %d",&(n),&(m));
#define wez3(n,m,k) int (n),(m),(k); scanf("%d %d %d",&(n),&(m),&(k));
inline void pisz(int n) { printf("%d\n",n); }
template<typename T,typename TT> ostream& operator<<(ostream &s,pair<T,TT> t) {return s<<"("<<t.first<<","<<t.second<<")";}
template<typename T> ostream& operator<<(ostream &s,vector<T> t){FOR(i,SZ(t))s<<t[i]<<" ";return s; }
#define DBG(vari) cerr<<#vari<<" = "<<(vari)<<endl;
#define ALL(t) t.begin(),t.end()
#define FOREACH(i,t) for (__typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define TESTS wez(testow)while(testow--)
#define REP(i,a,b) for(int (i)=(a);(i)<=(b);++i)
#define REPD(i,a,b) for(int (i)=(a); (i)>=(b);--i)
#define REMAX(a,b) (a)=max((a),(b));
#define REMIN(a,b) (a)=min((a),(b));
#define IOS ios_base::sync_with_stdio(0);
 
const int OFF = 8 * 30 + 10;
int dp[10][2 * OFF][2 * OFF];
 
void go (int n, int r) {
   vector<pii> pts;
   REP(x,-r,r) REP(y,-r,r) if (x*x + y*y <= r*r) pts.pb(mp(x,y));
   //DBG(pts)
   FOR(i,10) FOR(j,2*OFF) FOR(k,2*OFF) dp[i][j][k] = -INF;
   dp[0][0+OFF][0+OFF] = 0;
   FOR(i,n) {
      REP(sx,-n*r,n*r) REP(sy,-n*r,n*r) {
         if (-INF != dp[i][sx+OFF][sy+OFF]) {
            FOREACH(it,pts) {
               int x = it->fi, y = it->se;
               REMAX(dp[i+1][sx+x+OFF][sy+y+OFF], dp[i][sx+OFF][sy+OFF] + x*x + y*y);
            }
         }
      }
   }
   pair<int,pii> best;
   best.fi = -INF;
   REP(sx,-n*r,n*r) REP(sy,-n*r,n*r) if (-INF != dp[n][sx+OFF][sy+OFF]) {
      int cand = n * dp[n][sx+OFF][sy+OFF] - sx * sx - sy * sy;
      REMAX(best, mp(cand, mp(sx,sy)));
   }
   int sx = best.se.fi, sy = best.se.se;
   printf("%d\\n", best.fi);
//    REPD(i,n,1) {
//       // dp[i][sx][sy] == res
//       FOREACH(it,pts) {
//          int x = it->fi, y = it->se;
//          if (dp[i][sx+OFF][sy+OFF] == dp[i-1][sx-x+OFF][sy-y+OFF] + x*x + y*y) {
//             printf("%d %d\\n", x, y);
//             sx -= x;
//             sy -= y;
//             break;
//          }
//       }
//    }
}
 
int smain () {
   REP(n,1,8) REP(r,1,30) {
      printf("res[%d][%d] = \"", n, r);
      go(n, r);
      //DBG(mp(n,r))
      printf("\";\n");
   }
}

string res[10][33];
 
int main () {
res[1][1] = "0\n";
res[1][2] = "0\n";
res[1][3] = "0\n";
res[1][4] = "0\n";
res[1][5] = "0\n";
res[1][6] = "0\n";
res[1][7] = "0\n";
res[1][8] = "0\n";
res[1][9] = "0\n";
res[1][10] = "0\n";
res[1][11] = "0\n";
res[1][12] = "0\n";
res[1][13] = "0\n";
res[1][14] = "0\n";
res[1][15] = "0\n";
res[1][16] = "0\n";
res[1][17] = "0\n";
res[1][18] = "0\n";
res[1][19] = "0\n";
res[1][20] = "0\n";
res[1][21] = "0\n";
res[1][22] = "0\n";
res[1][23] = "0\n";
res[1][24] = "0\n";
res[1][25] = "0\n";
res[1][26] = "0\n";
res[1][27] = "0\n";
res[1][28] = "0\n";
res[1][29] = "0\n";
res[1][30] = "0\n";
res[2][1] = "4\n";
res[2][2] = "16\n";
res[2][3] = "36\n";
res[2][4] = "64\n";
res[2][5] = "100\n";
res[2][6] = "144\n";
res[2][7] = "196\n";
res[2][8] = "256\n";
res[2][9] = "324\n";
res[2][10] = "400\n";
res[2][11] = "484\n";
res[2][12] = "576\n";
res[2][13] = "676\n";
res[2][14] = "784\n";
res[2][15] = "900\n";
res[2][16] = "1024\n";
res[2][17] = "1156\n";
res[2][18] = "1296\n";
res[2][19] = "1444\n";
res[2][20] = "1600\n";
res[2][21] = "1764\n";
res[2][22] = "1936\n";
res[2][23] = "2116\n";
res[2][24] = "2304\n";
res[2][25] = "2500\n";
res[2][26] = "2704\n";
res[2][27] = "2916\n";
res[2][28] = "3136\n";
res[2][29] = "3364\n";
res[2][30] = "3600\n";
res[3][1] = "8\n";
res[3][2] = "32\n";
res[3][3] = "76\n";
res[3][4] = "130\n";
res[3][5] = "224\n";
res[3][6] = "312\n";
res[3][7] = "416\n";
res[3][8] = "554\n";
res[3][9] = "722\n";
res[3][10] = "896\n";
res[3][11] = "1064\n";
res[3][12] = "1248\n";
res[3][13] = "1512\n";
res[3][14] = "1746\n";
res[3][15] = "2016\n";
res[3][16] = "2264\n";
res[3][17] = "2600\n";
res[3][18] = "2888\n";
res[3][19] = "3218\n";
res[3][20] = "3584\n";
res[3][21] = "3912\n";
res[3][22] = "4344\n";
res[3][23] = "4712\n";
res[3][24] = "5138\n";
res[3][25] = "5612\n";
res[3][26] = "6062\n";
res[3][27] = "6536\n";
res[3][28] = "6984\n";
res[3][29] = "7520\n";
res[3][30] = "8084\n";
res[4][1] = "16\n";
res[4][2] = "64\n";
res[4][3] = "144\n";
res[4][4] = "256\n";
res[4][5] = "400\n";
res[4][6] = "576\n";
res[4][7] = "784\n";
res[4][8] = "1024\n";
res[4][9] = "1296\n";
res[4][10] = "1600\n";
res[4][11] = "1936\n";
res[4][12] = "2304\n";
res[4][13] = "2704\n";
res[4][14] = "3136\n";
res[4][15] = "3600\n";
res[4][16] = "4096\n";
res[4][17] = "4624\n";
res[4][18] = "5184\n";
res[4][19] = "5776\n";
res[4][20] = "6400\n";
res[4][21] = "7056\n";
res[4][22] = "7744\n";
res[4][23] = "8464\n";
res[4][24] = "9216\n";
res[4][25] = "10000\n";
res[4][26] = "10816\n";
res[4][27] = "11664\n";
res[4][28] = "12544\n";
res[4][29] = "13456\n";
res[4][30] = "14400\n";
res[5][1] = "24\n";
res[5][2] = "96\n";
res[5][3] = "218\n";
res[5][4] = "384\n";
res[5][5] = "624\n";
res[5][6] = "880\n";
res[5][7] = "1188\n";
res[5][8] = "1572\n";
res[5][9] = "2014\n";
res[5][10] = "2496\n";
res[5][11] = "2984\n";
res[5][12] = "3520\n";
res[5][13] = "4224\n";
res[5][14] = "4870\n";
res[5][15] = "5616\n";
res[5][16] = "6336\n";
res[5][17] = "7224\n";
res[5][18] = "8056\n";
res[5][19] = "9008\n";
res[5][20] = "9984\n";
res[5][21] = "10942\n";
res[5][22] = "12080\n";
res[5][23] = "13144\n";
res[5][24] = "14326\n";
res[5][25] = "15624\n";
res[5][26] = "16896\n";
res[5][27] = "18184\n";
res[5][28] = "19488\n";
res[5][29] = "20968\n";
res[5][30] = "22480\n";
res[6][1] = "36\n";
res[6][2] = "144\n";
res[6][3] = "324\n";
res[6][4] = "576\n";
res[6][5] = "900\n";
res[6][6] = "1296\n";
res[6][7] = "1764\n";
res[6][8] = "2304\n";
res[6][9] = "2916\n";
res[6][10] = "3600\n";
res[6][11] = "4356\n";
res[6][12] = "5184\n";
res[6][13] = "6084\n";
res[6][14] = "7056\n";
res[6][15] = "8100\n";
res[6][16] = "9216\n";
res[6][17] = "10404\n";
res[6][18] = "11664\n";
res[6][19] = "12996\n";
res[6][20] = "14400\n";
res[6][21] = "15876\n";
res[6][22] = "17424\n";
res[6][23] = "19044\n";
res[6][24] = "20736\n";
res[6][25] = "22500\n";
res[6][26] = "24336\n";
res[6][27] = "26244\n";
res[6][28] = "28224\n";
res[6][29] = "30276\n";
res[6][30] = "32400\n";
res[7][1] = "48\n";
res[7][2] = "192\n";
res[7][3] = "432\n";
res[7][4] = "768\n";
res[7][5] = "1224\n";
res[7][6] = "1740\n";
res[7][7] = "2356\n";
res[7][8] = "3102\n";
res[7][9] = "3954\n";
res[7][10] = "4896\n";
res[7][11] = "5872\n";
res[7][12] = "6960\n";
res[7][13] = "8280\n";
res[7][14] = "9564\n";
res[7][15] = "11016\n";
res[7][16] = "12456\n";
res[7][17] = "14160\n";
res[7][18] = "15816\n";
res[7][19] = "17666\n";
res[7][20] = "19584\n";
res[7][21] = "21500\n";
res[7][22] = "23688\n";
res[7][23] = "25808\n";
res[7][24] = "28122\n";
res[7][25] = "30624\n";
res[7][26] = "33120\n";
res[7][27] = "35664\n";
res[7][28] = "38266\n";
res[7][29] = "41200\n";
res[7][30] = "44076\n";
res[8][1] = "64\n";
res[8][2] = "256\n";
res[8][3] = "576\n";
res[8][4] = "1024\n";
res[8][5] = "1600\n";
res[8][6] = "2304\n";
res[8][7] = "3136\n";
res[8][8] = "4096\n";
res[8][9] = "5184\n";
res[8][10] = "6400\n";
res[8][11] = "7744\n";
res[8][12] = "9216\n";
res[8][13] = "10816\n";
res[8][14] = "12544\n";
res[8][15] = "14400\n";
res[8][16] = "16384\n";
res[8][17] = "18496\n";
res[8][18] = "20736\n";
res[8][19] = "23104\n";
res[8][20] = "25600\n";
res[8][21] = "28224\n";
res[8][22] = "30976\n";
res[8][23] = "33856\n";
res[8][24] = "36864\n";
res[8][25] = "40000\n";
res[8][26] = "43264\n";
res[8][27] = "46656\n";
res[8][28] = "50176\n";
res[8][29] = "53824\n";
res[8][30] = "57600\n";
 
wez2(n,r);
cout << res[n][r];
}
