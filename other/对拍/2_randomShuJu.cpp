#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i, s, t) for(int i = (s), LIM=(t); i < LIM; ++i)
#define per(i, s, t) for(int i = (s), LIM=(t); i >= LIM; --i)
using namespace std;
typedef long long LL;
typedef long long int64;
const int MXN =1e6;
const int MXE =300;
mt19937 rng(time(NULL));//std::clock()
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

int randint(int a, int b, int ip = 3) {
	if(a > b) swap(a, b);
	if(ip == 1) return ((rand() << 15) ^ rand()) % (b - a + 1) + a;
	else if(ip == 2) return ((rand() << 16) + rand()) % (b - a + 1) + a;
	else if(ip == 3) return rng() % (b - a + 1) + a;
	else return rng() % (b - a + 1) + a;
}
int randint64(int64 a, int64 b, int ip = 1) {
	if(a > b) swap(a, b);
	if(ip == 1) return rng64() % (b - a + 1) + a;
}
void randstr(int len) {
	rep(i, 0, len) {
		putchar(rng() % 26 + 'a');
	}
	putchar('\n');
}
int main() {
#ifndef ONLINE_JUDGE
    //freopen("E://ADpan//in.in", "r", stdin);
    //freopen("E://ADpan//out.out", "w", stdout);  
#endif
	srand(time(0));
    int tim = 1;
    printf("%d\n", tim);
    while(tim--) {
		int n, m;
		n = randint(1, 5);
		printf("%d\n", n);
		rep(i, 0, n) {
			int len = randint(1, 7);
			randstr(len);
			len = randint(1, n + 2);
			printf("%d\n", len);
		}
	}
	return 0;
} 
/*
//int a=()%n+1; 
int main(){
    srand(time(0));  
    int a,b,c;  
    //a = (rand() << 16) + rand();  
    //b = (rand() << 16) + rand();  
    //c = (rand() << 16) + rand(); 
    LL d=rand();
    int n=max(rand()%N,1);
	printf("%d %d %lld\n",n,max(rand()%N,1),(d*d)%M );
	for(int i=0;i<n;++i){
		d=rand();
		if(i!=n-1) printf("%lld ",max((d*d)%M,1LL) );
		else printf("%lld\n",max((d*d)%M,1LL) );
	}
    return 0;  
}
*/
