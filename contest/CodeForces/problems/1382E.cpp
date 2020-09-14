/*
原长度为n的数组，权值[1, n+1]，输入一个我猜的输入，有x个数字猜对了位置，有y个数猜对了它确实存在(对应y数组是只算一次)

先处理恰好匹配的x个，再处理错位的y个。
注意先要让出现次数最多的数字的出现次数尽可能小，这样才能保证有解一定能求出解来。
注意已经匹配的不能用去错位置换。
如果先处理错位的y个，再处理恰好匹配的x个，会出现无解的情况，因为可能有一个数字出现次数特别多，导致无法完成y个错位。
*/
#pragma comment(linker, "/STACK:102400000,102400000")
#include <assert.h>
#include <bits/stdc++.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#define fi first
#define se second
#define endl '\n'
#define o2(x) (x) * (x)
#define BASE_MAX 31
#define mk make_pair
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(a, b) memset((a), (b), sizeof((a)))
#define iis                           \
    std::ios::sync_with_stdio(false); \
    cin.tie(0)
#define my_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())
using namespace std;
#pragma optimize("-O3")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline LL read() {
    LL x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(LL x, bool f) {
    if (x == 0) {
        putchar('0');
        if (f) putchar('\n');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[23];
    int l = 0;
    while (x != 0) s[l++] = x % 10 + 48, x /= 10;
    while (l) putchar(s[--l]);
    if (f) putchar('\n');
}
int lowbit(int x) { return x & (-x); }
template <class T>
T big(const T &a1, const T &a2) {
    return a1 > a2 ? a1 : a2;
}
template <class T>
T sml(const T &a1, const T &a2) {
    return a1 < a2 ? a1 : a2;
}
template <typename T, typename... R>
T big(const T &f, const R &... r) {
    return big(f, big(r...));
}
template <typename T, typename... R>
T sml(const T &f, const R &... r) {
    return sml(f, sml(r...));
}
void debug_out() { cout << '\n'; }
template <typename T, typename... R>
void debug_out(const T &f, const R &... r) {
    cout << f << " ";
    debug_out(r...);
}
#define debug(...) cout << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__);
// #define LLDO
#ifdef LLDO
const char ptout[] = "%lld";
#else
const char ptout[] = "%d";
#endif
template <typename T>
void print(const T &f) {
    printf(ptout, f);
    putchar('\n');
}
template <typename T, typename... R>
void print(const T &f, const R &... r) {
    printf(ptout, f);
    putchar(' ');
    print(r...);
}

const int HMOD[] = {1000000009, 1004535809};
const LL BASE[] = {1572872831, 1971536491};
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
int n, m, k;
int ar[MXN], is[MXN], num[MXN], br[MXN], bid[MXN];
vector<int> mp[MXN];
priority_queue<pair<int, int> > pq;
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    int tim = read();
    while (tim--) {
        n = read(), m = read(), k = read() - m;
        for (int i = 1; i <= n + 1; ++i) {
            is[i] = num[i] = bid[i] = 0;
            mp[i].clear();
        }
        int aim = 0, flag = 1;
        for (int i = 1; i <= n; ++i) {
            ar[i] = read();
            br[i] = ar[i];
            ++ num[ar[i]];
            mp[ar[i]].eb(i);
        }
        while(!pq.empty()) pq.pop();
        for (int i = 1; i <= n + 1; ++i) {
            if (num[i]) pq.push(mk(num[i], i));
            else aim = i;
        }
        while(m > 0) {
            pii u = pq.top(); pq.pop();
            for(; m > 0 && (int)mp[u.se].size() > 0; ) {
                is[mp[u.se].back()] = bid[mp[u.se].back()] = 1;
                // debug(mp[u.se].back())
                mp[u.se].pop_back();
                -- m;
                break;
            }
            if(mp[u.se].size()) pq.push(mk(mp[u.se].size(), u.se));
        }
        while(m == 0 && k > 0) {
            if((int)pq.size() == 0) {
                flag = 0;
                break;
            }else if((int)pq.size() == 1) {
                int tmp = pq.top().se, pos;
                // debug(tmp)
                for(int i = 1; i <= n && k > 0; ++i) {
                    if(is[i] && bid[i] == 0 && ar[i] != tmp && br[i] != tmp && (int)mp[tmp].size() > 0) {
                        pos = mp[tmp].back();
                        is[pos] = 1;
                        br[pos] = br[i];
                        br[i] = tmp;
                        mp[tmp].pop_back();
                        -- k;
                    }
                }
                if(k > 0) flag = 0;
                break;
            }
            pii u = pq.top(); pq.pop();
            pii v = pq.top(); pq.pop();
            for(; k > 0 && (int)mp[v.se].size() > 0; ) {
                // debug(k, mp[u.se].size(), mp[v.se].size(), u.se)
                if(k == 1) {
                    // int tmp = u.se, pos;
                    // for(int i = 1; i <= n && k > 0; ++i) {
                    //     if(is[i] && bid[i] == 0 && ar[i] != tmp && br[i] != tmp && (int)mp[tmp].size() > 0) {
                    //         pos = mp[tmp].back();
                    //         is[pos] = 1;
                    //         br[pos] = br[i];
                    //         br[i] = tmp;
                    //         mp[tmp].pop_back();
                    //         -- k;
                    //     }
                    // }
                    if(k > 0) {
                        swap(br[mp[u.se].back()], br[mp[v.se].back()]);
                        br[mp[v.se].back()] = aim;
                        is[mp[u.se].back()] = 1;
                        mp[u.se].pop_back();
                        mp[v.se].pop_back();
                        -- k;
                    }
                }else {
                    swap(br[mp[u.se].back()], br[mp[v.se].back()]);
                    is[mp[u.se].back()] = is[mp[v.se].back()] = 1;
                    mp[u.se].pop_back();
                    mp[v.se].pop_back();
                    k -= 2;
                }
            }
            if(mp[v.se].size()) pq.push(mk(mp[v.se].size(), v.se));
            if(mp[u.se].size()) pq.push(mk(mp[u.se].size(), u.se));
        }
        for(int i = 1; i <= n; ++i) if(is[i] == 0) br[i] = aim;
        if(flag == 0 || m > 0) printf("NO\n");
        else {
            printf("YES\n");
            for(int i = 1; i <= n; ++i) {
                printf("%d%c", br[i], " \n"[i == n]);
            }
        }
    }
#ifndef ONLINE_JUDGE
    cout << "time cost:" << 1.0 * clock() / CLOCKS_PER_SEC << "ms" << endl;
    system("pause");
#endif
    return 0;
}
