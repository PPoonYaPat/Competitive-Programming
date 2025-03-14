#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n;
ll dp[200001][4]; // 00 -> left mask : grow upward/downward, right mask : include free upedge or not
vector<pii> adj[200001];

void dfs(int x, int par, int w) {

    ll sum=0;
    vector<pii> best[4];

    for (auto s : adj[x]) {
        if (s.first==par) continue;
        dfs(s.first,x,s.second);

        sum+=dp[s.first][0];
        for (int i=0; i<4; ++i) best[i].push_back(pii(dp[s.first][i]-dp[s.first][0],s.first));
    }

    for (int i=0; i<4; ++i) sort(best[i].begin(),best[i].end(),greater<pii>());

    if (best[0].size()) {
        dp[x][0]=max(sum,sum+best[1][0].first+w);
        dp[x][1]=sum+w;
        dp[x][2]=max(sum+best[2][0].first,sum+best[3][0].first+w);
        dp[x][3]=sum+best[2][0].first+w;

        if (best[0].size()>=2) {
            if (best[1][0].second==best[3][0].second) dp[x][2]=max({dp[x][2],sum+best[1][1].first+best[3][0].first,sum+best[1][0].first+best[3][1].first});
            else dp[x][2]=max(dp[x][2],sum+best[1][0].first+best[3][0].first);

            if (best[1][0].second==best[3][0].second) dp[x][3]=max({dp[x][3],sum+best[1][1].first+best[3][0].first+w,sum+best[1][0].first+best[3][1].first+w});
            else dp[x][3]=max(dp[x][3],sum+best[1][0].first+best[3][0].first+w);

            dp[x][2]=max(dp[x][2],sum+best[1][0].first+best[1][1].first);
            dp[x][3]=max(dp[x][3],sum+best[1][0].first+best[1][1].first+w);
        }

    } else {
        dp[x][0]=0;
        dp[x][1]=w;
        dp[x][2]=-1e15;
        dp[x][3]=-1e15;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=0; i<n-1; ++i) {
        int a,b,w;
        cin>>a>>b>>w;
        adj[a].push_back(pii(b,w));
        adj[b].push_back(pii(a,w));
    }
    dfs(1,0,0);
    cout<<max(dp[1][1],dp[1][3]);
}