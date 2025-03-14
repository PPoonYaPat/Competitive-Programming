#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod=1e9+7;
int n,lim,a[105];
ll dp[105][105][1005][3];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>lim;
    for (int i=1; i<=n; ++i) cin>>a[i];
    sort(a+1,a+n+1);

    if (n==1) {
        cout<<1;
        return 0;
    }

    dp[1][1][0][0]=1;
    dp[1][1][0][1]=2;

    for (int i=2; i<=n; ++i) {
        for (int j=1; j<i; ++j) {
            for (int k=0; k<=lim; ++k) {
                for (int e=0; e<3; ++e) {
                    //consider value from dp[i-1][j][k][e]
                    int nw=k+(a[i]-a[i-1])*(2*j-e);
                    if (nw>lim) continue;

                    //insert to middle component
                    dp[i][j][nw][e]=(dp[i][j][nw][e]+dp[i-1][j][k][e]*(2*j-e))%mod;

                    //insert to rim component
                    dp[i][j][nw][e+1]=(dp[i][j][nw][e+1]+dp[i-1][j][k][e]*(2-e))%mod;

                    //merge 2 component
                    dp[i][j-1][nw][e]=(dp[i][j-1][nw][e]+dp[i-1][j][k][e]*(j-1))%mod;

                    //create new middle component
                    dp[i][j+1][nw][e]=(dp[i][j+1][nw][e]+dp[i-1][j][k][e]*(j+1-e))%mod;

                    //create new rim component
                    dp[i][j+1][nw][e+1]=(dp[i][j+1][nw][e+1]+dp[i-1][j][k][e]*(2-e))%mod;
                    
                }
            }
        }
    }

    ll ans=0;
    for (int k=0; k<=lim; ++k) ans=(ans+dp[n][1][k][2])%mod;
    cout<<ans;
}