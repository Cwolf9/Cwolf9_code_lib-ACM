/*
链接
https://ac.nowcoder.com/acm/contest/5667/H
题意
1. 插入一个x
2. 删除一个x
3. 询问是否有两个数可以和x形成三角形

思路
动态开点权值线段树
对于查询只有三种情况，x是三边之中最大的，x是三边之中第二大的，x是三边之中最小的

备注

*/
#pragma comment(linker, "/STACK:102400000,102400000")
//#include<bits/stdc++.h>
#include <assert.h>
#include<unordered_map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
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
typedef long long int64;
typedef unsigned long long uint64;
typedef pair<int, int> pii;
// mt19937 rng(time(NULL));
// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 generator(std::clock());
// shuffle(arr, arr + n, generator);
inline int64 read() {
    int64 x = 0;
    int f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x = f ? -x : x;
}
inline void write(int64 x, bool f) {
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
#define LLDO
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
const int64 BASE[] = {1572872831, 1971536491};
const int64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int MOD = 1e9 + 7;  // 998244353
const int MXN = 2e5 + 5;
const int MXE = 2e6 + 6;
const int MXR = 1000000001;
int n, m;
int noprime[MXN], pp[MXN], pcnt, mindiv[MXN];
int phi[MXN], mu[MXN];
void init_prime() {
    noprime[0] = noprime[1] = 1;
    mu[1] = 1; phi[1] = 1;
    for(int i = 2; i < MXN; ++i) {
        if(!noprime[i]) pp[pcnt++] = i, phi[i] = i-1, mu[i] = -1, mindiv[i] = i;
        for(int j = 0; j < pcnt && pp[j] * i < MXN; ++j) {
            noprime[pp[j]*i] = 1;
            mindiv[pp[j]*i] = pp[j];
            //phi[pp[j]*i] = (pp[j]-1)*phi[i];
            mu[pp[j]*i] = -mu[i];
            if(i % pp[j] == 0) {
                //phi[pp[j]*i] = pp[j]*phi[i];
                mu[pp[j]*i] = 0;
                break;
            }
        }
    }
}
int ar[100];
int main() {
#ifndef ONLINE_JUDGE
    freopen("D:in.in", "r", stdin);
    freopen("D:out.out", "w", stdout);
#endif
    // init_prime();
    int tim = read();
    while(tim --) {
        int a = read(), b = read(), c = read(), d = read();
        int flag = 0;
        if(a < b) {
            if(c < d && d > b) flag = 0;
            else flag = 1;
        }else if(a == b) {
            if(c > d) flag = 1;
        }else {
            if(c > a && c > d) flag = 1;
        }

        printf("%s\n", flag?"AB//CD":"AB//DC");
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
