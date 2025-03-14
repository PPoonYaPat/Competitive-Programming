#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m;
ll w[300001],ans;
vector<int> adj[300001];
priority_queue<ll> q[300001];

void dfs(int x) {

    if (adj[x].size()==0) {
        q[x].push(w[x]);
        q[x].push(w[x]);
        return;
    }

    for (auto s : adj[x]) {
        dfs(s);
        if (q[s].size()>q[x].size()) swap(q[s],q[x]);
        while (!q[s].empty()) q[x].push(q[s].top()), q[s].pop();
    }

    for (int i=1; i<adj[x].size(); ++i) q[x].pop();
    ll a=q[x].top()+w[x]; q[x].pop();
    ll b=q[x].top()+w[x]; q[x].pop();
    q[x].push(a); q[x].push(b);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=2; i<=n+m; ++i) {
        int u; cin>>u>>w[i];
        adj[u].push_back(i);
    }
    for (int i=1; i<=n+m; ++i) ans+=w[i];
    dfs(1);

    q[1].pop();
    while (!q[1].empty()) ans-=q[1].top(), q[1].pop();
    cout<<ans;
}