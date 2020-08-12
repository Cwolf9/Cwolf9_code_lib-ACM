#define LH_LOCAL
// #define LLDO
#include <bits/stdc++.h>
#define fi first
#define se second
#define o2(x) (x) * (x)
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define rep(i,s,t) for(register int i=s;i<t;++i)
#define per(i,s,t) for(register int i=s;i>=t;--i)
#define iis std::ios::sync_with_stdio(false);cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
inline int64 read() {
    int64 x = 0;int f = 0;char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch =
    getchar(); return x = f ? -x : x;
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#ifdef LH_LOCAL
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
#else
#define debug(...) ;
#endif
#ifdef LLDO
    const char ptout[] = "%lld";
#else
    const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {printf(ptout, f);putchar('\n');}
template <typename T, typename... R>
void print(const T &f, const R &... r) {printf(ptout, f);putchar(' ');print(r...);}

const int INF = 0x3f3f3f3f;
const int mod = 998244353;// 998244353
const int MOD = 1e9 + 7;// 998244353
const int MXN = 1e6 + 5;
int n, m;

int main() {
#ifdef LH_LOCAL
    freopen("D:in.in", "r", stdin);
    // freopen("D:out.out", "w", stdout);
#endif
    
    return 0;
}
/*
蜘蛛侠和蝙蝠侠是美国的超级英雄，而且在电影里面，蜘蛛侠是一个正义且充满正能量的形象，
经常行侠仗义和打击犯罪，低调地不露脸地维护城市乃至世界的安全。用一句诗句来形容就是：事了拂衣去，深藏身与名。
我觉得用侠来形容蜘蛛侠非常合适。因为侠本义是指武艺高强，肯见义勇为，舍己助人的品行。
The Charm of Wuxia Culture指通过自己的能力不求回报地去帮助比自己弱小的人，对社会作出贡献.
我个人感觉可能还有一个原因是，蜘蛛侠读起来比较顺口，而蜘蛛人有点拗口。
中国文化中的侠的蜘蛛侠都是喜欢伸张正义，用自己的能力为社会做贡献，是一种追求和理想。
不同之处在于蜘蛛侠是神奇的超能力，弘扬个人英雄主义，而中国文化的侠是靠的武功和人格魅力，离不开集体的作用。
Spider-Man and Batman are American superheroes, and in the movie, Spider-Man is a justice boy full of positive energy.
Spider-Man and Batman often act chivalrously and fight crimes, and maintain the safety of the city and the world in a low-key and not showing their face. To use a verse to describe it is: When things happen, go away, hide your body and name.
I think it is very appropriate to describe Spider-Man as a Xia. Because the original meaning of Xia refers to the character of high martial arts, willing to do what is right, and sacrifice oneself to help others.
The Charm of Wuxia Culture refers to helping people who are weaker than themselves through their own abilities without asking for return, and making contributions to society.
I personally feel that there may be another reason that Spider-Man reads more smoothly, while Spider-Man is a little confusing.
Spider-Man and Xia in Chinese culture both like to do justice and use their abilities to contribute to society, which is a pursuit and ideal.
The difference is that Spider-Man is a magical superpower and promotes personal heroism, while the Chinese cultural Xia relies on martial arts and personality charm. It is inseparable from the collective role.
*/