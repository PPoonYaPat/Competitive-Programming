#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,st,ed;
ll dp[2005][2005],mod=1e9+7;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>st>>ed;
    dp[1][1]=1;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=i; ++j) {
            if (i+1==st || i+1==ed) {
                dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
                dp[i+1][j+1]=(dp[i+1][j+1]+dp[i][j])%mod;
            } else {
                dp[i+1][j+1]=(dp[i+1][j+1]+dp[i][j]*(j+1-(i+1>st)-(i+1>ed)))%mod;
                dp[i+1][j-1]=(dp[i+1][j-1]+dp[i][j]*(j-1))%mod;
            }
        }
    }
    cout<<dp[n][1];
}