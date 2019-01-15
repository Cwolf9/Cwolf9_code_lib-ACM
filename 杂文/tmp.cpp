#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>
#define o2(x) (x)*(x)
#define lson rt<<1
#define rson rt<<1|1
#define fi first
#define se second
#define mme(a,b) memset((a),(b),sizeof((a)))
#define fuck(x) cout<<"* "<<x<<"\n"
#define iis std::ios::sync_with_stdio(false)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int MXN = 2e6 + 5;
const int mod = 1000000007;
int n, m, k;
int ar[MXN];

int main() {
    scanf("%d", &n);
    
    return 0;
}
int ask(int c,int d) {
    cout<<"? "<<c<<" "<<d<<"\n";
    fflush(stdout);
    int ans;
    cin >> ans;
    return ans;
}
int main() {
    int a = 0, b = 0, big = ask(0, 0);
    for(int i = 29; i >= 0; --i) {
        int f = ask(a^(1<<i), b), s = ask(a, b^(1<<i));
        if(f == s) {
            if(big == 1) {
                a ^= (1<<i);
            }else {
                b ^= (1<<i);
            }
            big = f;
        }else if(f == -1) {
            a ^= (1<<i);
            b ^= (1<<i);
        }
    }
    cout<<"! "<<a<<" "<<b<<"\n";
    return 0;
}
int MOD = 1e9+7;
void ADD(LL& x,LL v){x=(x+v)%MOD;if(x<0)x+=MOD;}
/*}}}*/
const int SIZE = 1e6+10;
struct AA{
    int x,y;
    AA(int x=0,int y=0):x(x),y(y){}
    bool operator==(const AA& b)const{return x==b.x&&y==b.y;}
    void scan(){R(x,y);}
}me,black[SIZE];
const int N = 666;
bool best(AA king){
    if(king.x<=0||king.y<=0||king.x>999||king.y>999)return 0;
    bool good=0;
    FOR(i,1,666){
        if(king==black[i])return 0;
        if(king.x==black[i].x||king.y==black[i].y)good=1;
    }
    return good;
}
void mov(int x ,int y){
    W(x,y);
    fflush(stdout);
}
void update(){
    int k,x,y;
    R(k,x,y);
    black[k]=AA(x,y);
}
void can_win(AA king){
    FOR(dx,-1,1)FOR(dy,-1,1){
        if(best(AA(king.x+dx,king.y+dy))){
            mov(king.x+dx,king.y+dy);
            exit(0);
        }
    }
}
int main(){
    me.scan();
    FOR(i,1,666)black[i].scan();
    AA O(500,500);
    while(!(me==O)){
        can_win(me);
        if(me.x>O.x)me.x--;
        else if(me.x<O.x)me.x++;
        
        if(me.y>O.y)me.y--;
        else if(me.y<O.y)me.y++;
        mov(me.x,me.y);
        update();
    }
    int cnt[4]={};
    FOR(i,1,666){
        int ty=0;
        if(black[i].x>me.x)ty|=1;
        if(black[i].y>me.y)ty|=2;
        cnt[ty]++;
    }
    int mi=min({cnt[0],cnt[1],cnt[2],cnt[3]});
    int dx,dy;
    if(mi==cnt[0]){
        dx=dy=1;
    }
    else if(mi==cnt[1]){
        dx=-1;
        dy=1;
    }
    else if(mi==cnt[2]){
        dx=1;
        dy=-1;
    }
    else{
        dx=dy=-1;
    }
    while(1){
        can_win(me);
        me.x+=dx;
        me.y+=dy;
        mov(me.x,me.y);
        update();
    }
    return 0;
}