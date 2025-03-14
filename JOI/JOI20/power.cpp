#include <bits/stdc++.h>
using namespace std;

int dp[200001],n,ans;
string pp;
vector<int> adj[200001];

void dfs(int x, int par) {
    int m=0;
    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs(s,x);
        dp[x]+=dp[s];
        m=max(m,dp[s]);
    }

    if (pp[x-1]=='1') {
        ans=max(ans,m+1);
        dp[x]=max(1,dp[x]-1);
    }
    ans=max(ans,dp[x]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=0; i<n-1; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cin>>pp;
    dfs(1,0);
    cout<<ans;
}
