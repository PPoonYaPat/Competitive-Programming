#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
typedef tuple<ll,int,int,ll> tu;

ll disS[100001],disT[100001],disU[100001],disV[100001],minU1[100001],minU2[100001];
vector<pii> adj[100001];
int n,m,s,t,u,v;

bool check(int x, int y, ll val) { //check if x and y are on the same shortest path
    return min(disS[x]+disT[y],disS[y]+disT[x])!=disS[t]-val;
}

void dij(int start, ll *dis) {
    for (int i=1; i<=n; ++i) dis[i]=1e18;
    bool vis[100001]; memset(vis,0,sizeof(vis));
    priority_queue<pii, vector<pii>, greater<pii>> q;

    dis[start]=0;
    q.push(pii(0,start));

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

void dij2(int start, ll *dis, ll *minU) {

    for (int i=1; i<=n; ++i) dis[i]=1e18;
    bool vis[100001]; memset(vis,0,sizeof(vis));
    priority_queue<pii, vector<pii>, greater<pii>> q;

    dis[start]=0;
    minU[start]=disU[start];
    q.push(pii(0,start));

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
                minU[des]=min(minU[node],disU[des]);
            } else if (dis[des]==dis[node]+w) {
                q.push(pii(dis[des],des));
                minU[des]=min(minU[node],minU[des]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>s>>t>>u>>v;
    for (int i=1; i<=n; ++i) minU1[i]=1e18,minU2[i]=1e18;
    minU1[u]=0; minU2[u]=0;
    for (int i=0; i<m; ++i) {
        int a,b,w;
        cin>>a>>b>>w;
        adj[a].push_back(pii(b,w));
        adj[b].push_back(pii(a,w));
    }
    dij(u,disU);
    dij(v,disV);
    dij2(s,disS,minU1);
    dij2(t,disT,minU2);

    ll ans=LLONG_MAX;
    for (int i=1; i<=n; ++i) {
        if (disS[i]+disT[i]==disS[t]) ans=min(ans,min(minU1[i],minU2[i])+disV[i]);
    }
    cout<<min(ans,disU[v]);
}