#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

ll n,m,k;
ll dis[100010];
bool vis[100010];
vector<pii> adj[100010];
priority_queue<pii, vector<pii>, greater<pii>> q;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=0; i<n; ++i) dis[i]=LLONG_MAX;
    for (int i=0; i<m; ++i) {
        ll a,b,w; cin>>a>>b>>w;
        adj[a].push_back(pii(b,w));
        adj[b].push_back(pii(a,w));
    }
    cin>>k;
    while (k--) {
        ll a,b; cin>>a>>b;
        adj[n].push_back(pii(a,b));
        adj[a].push_back(pii(n,b));
    }

    dis[n]=0;
    q.push(pii(dis[n],n));

    while (!q.empty()) {
        int node=q.top().second; q.pop();

        if (vis[node]) continue;
        vis[node]=true;

        if (node==0) {
            cout<<dis[node];
            return 0;
        }

        for (auto s : adj[node]) {
            if (dis[s.first]>dis[node]+s.second) {
                dis[s.first]=dis[node]+s.second;
                q.push(pii(dis[s.first],s.first));
            }
        }
    }
}
