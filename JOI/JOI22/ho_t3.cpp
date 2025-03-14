#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld,ld> pii;

int n,k;
ld ans=1e9,a[505],b[505],dp[505][505],ss[505];
vector<pii> v;

void check(ld want) {
    for (int i=0; i<=n; ++i) for (int j=0; j<=n; ++j) dp[i][j]=1e9;
    dp[0][0]=0;

    for (int i=0; i<=k; ++i) {
        if (i) {
            for (int j=0; j<=want; ++j) {
                if (j!=0 && b[i]!=1e9) dp[i][j]=min(dp[i][j],dp[i-1][j-1]+b[i]/j); //choose B
                if (j!=want) dp[i][j]=min(dp[i][j],dp[i-1][j]+a[i]/(want+1)); //choose A
            }
        }

        if (dp[i][(int)(want)]<1000000) ans=min(ans,dp[i][(int)(want)]+ss[i]/(want+1));
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>k;
    for (int i=0; i<n; ++i) {
        ld a,b; cin>>a>>b;
        if (b!=-1) v.push_back(pii(b,a));
        else v.push_back(pii(1e9,a));
    }
    sort(v.begin(),v.end());
    for (int i=1; i<=n; ++i) a[i]=v[i-1].second, b[i]=v[i-1].first;
    for (int i=0; i<=k; ++i) {
        ld sum=0;
        priority_queue<ld> q;
        for (int j=i+1; j<=n; ++j) {
            q.push(a[j]);
            sum+=a[j];
            if (q.size()>k-i) {
                sum-=q.top();
                q.pop();
            }
        }
        ss[i]=sum;
    }
    for (int i=0; i<=k; ++i) check(i);
    cout<<setprecision(15)<<ans;
}