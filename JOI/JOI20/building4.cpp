#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

const int inf=1e9;
int n,a[1000001],b[1000001];
pii dp[1000001][2];

pii merge(pii a, pii b) {return pii(min(a.first,b.first),max(a.second,b.second));}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=0; i<2*n; ++i) cin>>a[i];
    for (int i=0; i<2*n; ++i) cin>>b[i];

    dp[0][0]=pii(0,0);
    dp[0][1]=pii(1,1);
    for (int i=1; i<2*n; ++i) {
        dp[i][0]=pii(inf,-inf);
        if (a[i]>=a[i-1]) dp[i][0]=merge(dp[i][0],dp[i-1][0]);
        if (a[i]>=b[i-1]) dp[i][0]=merge(dp[i][0],dp[i-1][1]);

        dp[i][1]=pii(inf,-inf);
        if (b[i]>=a[i-1]) dp[i][1]=merge(dp[i][1],dp[i-1][0]);
        if (b[i]>=b[i-1]) dp[i][1]=merge(dp[i][1],dp[i-1][1]);
        dp[i][1]=pii(dp[i][1].first+1,dp[i][1].second+1);
    }

    if (dp[2*n-1][0].first<=n && n<=dp[2*n-1][0].second) {
        string ans="A";
        int cnt=n, last=a[2*n-1];

        for (int i=2*n-2; i>=0; --i) {
            if (cnt==0) ans+='A';
            else {
                if (a[i]<=last && dp[i][0].first<=cnt && cnt<=dp[i][0].second) ans+='A', last=a[i];
                else ans+='B', --cnt, last=b[i];
            }
        }
        reverse(ans.begin(),ans.end());
        cout<<ans;
        return 0;
    }

    if (dp[2*n-1][1].first<=n && n<=dp[2*n-1][1].second) {
        string ans="B";
        int cnt=n-1, last=b[2*n-1];

        for (int i=2*n-2; i>=0; --i) {
            if (cnt==0) ans+='A';
            else {
                if (a[i]<=last && dp[i][0].first<=cnt && cnt<=dp[i][0].second) ans+='A', last=a[i];
                else ans+='B', --cnt, last=b[i];
            }
        }
        reverse(ans.begin(),ans.end());
        cout<<ans;
        return 0;
    }

    cout<<-1;
}