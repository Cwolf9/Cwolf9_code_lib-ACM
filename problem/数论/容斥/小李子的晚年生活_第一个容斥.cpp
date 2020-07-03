vector<int>ve;
void rongchi(ll n) {
    ll ans = n*(n+1)*(2*n+1)/6;
    int m = n; ve.clear();
    for (int i = 2 ; i*i <= n ; i ++) {
        if (m % i == 0) {
            ve.push_back(i);
            while(m % i == 0) m /= i;
        }
    }
    if (m != 1) ve.push_back(m);

    for (int i = 1 ; i < (1<<ve.size()) ; i ++) {
        ll tot = 1; int cnt = 0;
        for (int j = 0 ; j < ve.size() ; j ++) {
            if (i & (1<<j)) {
                tot *= ve[j];
                cnt++;
            }
        }
        ll tmp = n / tot;
        if (cnt & 1) {
            ans -= tot*tot*((tmp*(tmp+1)*(tmp*2+1)/6));
        }
        else ans += tot*tot*((tmp*(tmp+1)*(tmp*2+1)/6));
    }
    cout << ans << endl;
}
void solve(){
    ll n ;
    while(cin >> n) {
        rongchi(n);
    }
}
