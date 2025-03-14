#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int a[6],n,m,k;
ll dp[33][200001];
vector<pii> adj[200001];

void dij(ll *dis) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    bool vis[200001];
    memset(vis,0,sizeof(vis));
    for (int i=1; i<=n; ++i) q.push(pii(dis[i],i));
    while (!q.empty()) {
        ll node=q.top().second;
        q.pop();

        if (vis[node]) continue;
        vis[node]=true;

        for (auto s : adj[node]) {
            ll des=s.first, w=s.second;
            if (dis[des]>dis[node]+w) {
                dis[des]=dis[node]+w;
                q.push(pii(dis[des],des));
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<32; ++i) for (int j=1; j<=200000; ++j) dp[i][j]=1e18;
    cin>>n>>k>>m;
    for (int i=0; i<k; ++i) {
        cin>>a[i];
        dp[1<<i][a[i]]=0;
    }
    for (int i=0; i<m; ++i) {
        int a,b,w;
        cin>>a>>b>>w;
        adj[a].push_back(pii(b,w));
        adj[b].push_back(pii(a,w));
    }

    for (int bit=1; bit<(1<<k); ++bit) {
        for (int j=0; j<k; ++j) {
            if (!bit&(1<<j)) continue;
            for (int i=1; i<=n; ++i) dp[bit][i]=min(dp[bit][i],dp[(1<<j)][i]+dp[bit^(1<<j)][i]);
        }
        dij(dp[bit]);
    }

    ll ans=LLONG_MAX;
    for (int i=1; i<=n; ++i) ans=min(ans,dp[(1<<k)-1][i]);
    cout<<ans;
}