//https://www.cnblogs.com/TnT2333333/p/6868422.html
//http://www.cnblogs.com/jiu0821/p/4493497.html
int n, num;
LL ans;
int dp[MAXN];
void combine(int now) {
    int j;
    int temp = dp[now - 1] + dp[now];
    ans += (LL)temp;
    for(int i = now; i < num - 1; i++) dp[i] = dp[i + 1];
    num--;
    for(j = now - 1; j > 0 && dp[j - 1] < temp; j--) dp[j] = dp[j - 1];
    dp[j] = temp;
    while(j >= 2 && dp[j - 2] <= dp[j]) {
        int d = num - j;
        combine(j - 1);
        j = num - d;
    }
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &dp[i]);
    num = 1, ans = 0;
    for(int i = 1; i < n; i++){
        dp[num++] = dp[i];
        while(num>=3 && dp[num-3]<=dp[num-1]) combine(num - 2);
    }
    while(num > 1) combine(num - 1);
    printf("%lld\n", ans);
    return 0;
}