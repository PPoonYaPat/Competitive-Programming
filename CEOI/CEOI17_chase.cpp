#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,k;
ll val[100005],dp[100005][105][2],ans,sum[100005];
vector<int> adj[100005];

void dfs(int x, int par) {
    dp[x][1][1]=sum[x];
    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs(s,x);
        for (int i=1; i<=k; ++i) {
            dp[x][i][0]=max({dp[x][i][0],dp[x][i-1][0],dp[s][i][0],dp[s][i-1][0]+sum[x]-val[par]});
            dp[x][i][1]=max({dp[x][i][1],dp[x][i-1][1],dp[s][i][1],dp[s][i-1][1]+sum[x]-val[s]});
        }
    }

    ll mmax[105];
    memset(mmax,0,sizeof(mmax));

    for (auto s : adj[x]) if (s!=par) {
        for (int i=0; i<=k; ++i) {
            ans=max(ans,dp[s][i][1]+mmax[k-i]); //dont use at x
            if (i!=k && i!=0) ans=max(ans,dp[s][i][1]+sum[x]-val[s]+mmax[k-i-1]); //use at x in the middle
        }
        for (int i=0; i<=k; ++i) mmax[i]=max(mmax[i],dp[s][i][0]);
    }

    memset(mmax,0,sizeof(mmax));
    reverse(adj[x].begin(),adj[x].end());

    for (auto s : adj[x]) if (s!=par)  {
        for (int i=0; i<=k; ++i) {
            ans=max(ans,dp[s][i][1]+mmax[k-i]); //dont use at x
            if (i!=k && i!=0) ans=max(ans,dp[s][i][1]+sum[x]-val[s]+mmax[k-i-1]); //use at x in the middle
        }
        for (int i=0; i<=k; ++i) mmax[i]=max(mmax[i],dp[s][i][0]);
    }
    if (k) ans=max(ans,mmax[k-1]+sum[x]); //use x as a start point
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>k;
    for (int i=1; i<=n; ++i) cin>>val[i];
    for (int i=0; i<n-1; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i=1; i<=n; ++i) {
        for (auto s : adj[i]) sum[i]+=val[s];
    }
    dfs(1,0);
    cout<<ans;
}