#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ll;
const int maxn = 101;

ll vis[maxn];
ll fd[maxn];
ll len_d[maxn],len_h[maxn];
ll pre_d[maxn],pre_h[maxn];

int getkth(int k) {
    for(int i=0;i<20;i++) {
        if(vis[i] == 0) k--;
        if(k == 0) return i;    
    }
    return 0;
}

ll getans_1(ll t) {
    t--;
    if(t == 0) return 0;
    int len = -1;
    for(int i=0;i<20;i++) vis[i] = 0;
    for(int i=1;i<=10;i++) {
        if(pre_d[i] >= t) {
            len = i;
            break;
        }
    }
    if(len == -1) return -1;
    t -= pre_d[len-1];
    ll ans = 0;
    fd[len] = 1;
    for(int i=len-1;i>=1;i--) fd[i] = fd[i+1] * (10-i);
    for(int i=1;i<=len;i++) {
        if(i == 1) {
            for(int j=1;j<=9;j++) {
                if(j * fd[i] >= t) {
                    vis[j] = 1;
                    ans = ans*10+j;
                    t -= (j-1)*fd[i];
                    break;
                }
            }
        } 
        else {
            for(int j=1;j<=11-i;j++) {
                if(j * fd[i] >= t) {
                    int g = getkth(j);
                    vis[g] = 1;
                    ans = ans*10+g;
                    t -= (j-1)*fd[i];
                    break;
                }
            }
        }
    }
    return ans;
}

ll getans_2(ll t) {
    t--;
    if(t == 0) return 0;
    int len = -1;
    for(int i=0;i<20;i++) vis[i] = 0;
    for(int i=1;i<=10;i++) {
        if(pre_h[i] >= t) {
            len = i;
            break;
        }
    }
    if(len == -1) return -1;
    t -= pre_h[len-1];
    ll ans = 0;
    fd[len] = 1;
    for(int i=len-1;i>=1;i--) fd[i] = fd[i+1] * (16-i);
    for(int i=1;i<=len;i++) {
        if(i == 1) {
            for(int j=1;j<=15;j++) {
                if(j * fd[i] >= t) {
                    vis[j] = 1;
                    ans = ans*16+j;
                    t -= (j-1)*fd[i];
                    break;
                }
            }
        } 
        else {
            for(int j=1;j<=17-i;j++) {
                if(j * fd[i] >= t) {
                    int g = getkth(j);
                    vis[g] = 1;
                    ans = ans*16+g;
                    t -= (j-1)*fd[i];
                    break;
                }
            }
        }
    }
    return ans;
}

ll stringtoll(string s) {
    ll ans = 0;
    for(int i=0;i<s.size();i++) {
        if(s[i]>='a' && s[i]<='f') ans = ans*16+s[i]-'a'+10;
        else ans=ans*16+s[i]-'0';
    }
    return ans;
}

string lltostring(ll x) {
    string res;
    if(x == 0) res += '0';
    while(x != 0) {
        int g = x%16;
        if(g <= 9) res += '0'+g;
        else res += 'a'+g-10;
        x /= 16;
    }
    reverse(res.begin(),res.end());
    return res;
}
ll getansh(ll x) {
    if(x < 0) return (ll)0;
    ll l = 1, r = pre_h[16], mid, ans;
    while(l <= r) {
        mid = (l%2 + r %2)/2  + l /2 + r /2;
        ll tmp = getans_2(mid);
        if(tmp <= x) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}
ll getansd(ll x) {
    if(x < 0) return (ll)0;
    ll l = 1, r = pre_d[16], mid, ans;
    while(l <= r) {
        mid = (l%2 + r %2)/2  + l /2 + r /2;
        ll tmp = getans_1(mid);
        if(tmp != -1 && tmp <= x) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    // cout << ans << endl;
    return ans;
}
int main() {
    len_d[1] = 9;
    len_h[1] = 15;
    for(int i=2;i<=16;i++) {
        if(i <= 10) len_d[i] = len_d[i-1]*(11-i);
        len_h[i] = len_h[i-1]*(17-i);
    }
    for(int i=1;i<=16;i++) {
        pre_d[i] = pre_d[i-1] + len_d[i];
        pre_h[i] = pre_h[i-1] + len_h[i];
    }
    int t;
    scanf("%d",&t);
    ll cnt;
    while(t--) {
        char op1;
        int op2;
        scanf(" %c%d",&op1,&op2);
        if(op2 == 0) {
            if(op1 == 'h') {
                string s, ss;
                cin>>s >> ss;
                ll vs = stringtoll(s), vss = stringtoll(ss);
                cnt = getansh(vss) - getansh(vs - 1);
                cout << lltostring(cnt) << "\n";
            }
            else {
                ll vs, vss;
                cin >> vs >> vss;
                // cout << vs << " " << vss << "\n";
                cnt = getansd(vss) - getansd(vs - 1);
                printf("%llu\n", cnt);
            }
            
        }
        else {
            if(op1 == 'h') {
                string s;
                cin >> s;
                ll ans = getans_2(stringtoll(s));
                if(ans == -1) printf("-\n");
                else cout<<lltostring(ans)<<"\n";
            }
            else {
                ll m;
                cin>>m;
                ll ans = getans_1(m);
                if(ans == -1) printf("-\n");
                else printf("%llu\n", ans);
            }
        }
    }
    return 0;
}