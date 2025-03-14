#include <bits/stdc++.h>
using namespace std;

int n,sm,bg,a[2001];
int dp[2001][2001];

bool check(int w) {

    for (int i=0; i<n; ++i) {
        int preb=(int)(upper_bound(a,a+n,a[i]-2*w)-a)-1;
        int pres=(int)(upper_bound(a,a+n,a[i]-w)-a)-1;

        if (pres!=-1) dp[i][0]=dp[pres][0]+1;
        else dp[i][0]=1;

        for (int j=1; j<=bg; ++j) {
            if (preb==-1) dp[i][j]=0;
            else dp[i][j]=min(dp[preb][j-1],dp[pres][j]+1);
        }
    }

    if (dp[n-1][bg]<=sm) return true;
    else return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>sm>>bg;
    for (int i=0; i<n; ++i) cin>>a[i];
    sort(a,a+n);

    if (sm+bg>=n) {
        cout<<1;
        return 0;
    }

    int l=1,r=1e9,ans=1e9;
    while (l<=r) {
        int mid=(l+r)/2;
        if (check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
}