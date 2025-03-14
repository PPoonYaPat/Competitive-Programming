#include <bits/stdc++.h>
using namespace std;

int n,m,dp[3001][3],ans;
string s[3001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=1; i<=n; ++i) cin>>s[i], s[i]=" "+s[i];

    for (int i=2; i<=n+m; ++i) {
        memset(dp,0,sizeof(dp));
        int x=min(n,i-1),y=i-x,j=0;

        while (x>=1 && y<=m) {
            ++j;
            dp[j][0]=max({dp[j-1][0],dp[j-1][1],dp[j-1][2]});
            if (s[x][y]=='G') {
                if (x>1 && x<n && s[x-1][y]=='R' && s[x+1][y]=='W') dp[j][1]=max(dp[j-1][0],dp[j-1][1])+1;
                if (y>1 && y<m && s[x][y-1]=='R' && s[x][y+1]=='W') dp[j][2]=max(dp[j-1][0],dp[j-1][2])+1;
            }
            --x;
            ++y;
        }
        ans+=max({dp[j][0],dp[j][1],dp[j][2]});
    }
    cout<<ans;
}