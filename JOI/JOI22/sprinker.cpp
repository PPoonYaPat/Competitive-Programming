#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,q,p[200001];
ll h[200001],mul[200001][42],mod;
vector<int> adj[200001];

void dfs(int x, int par) {
    p[x]=par;
    for (auto s : adj[x]) if (s!=par) dfs(s,x);
}

void add(int node, int dis, ll val) {
    while (node!=0 && dis!=-1) {
        mul[node][dis]=(mul[node][dis]*val)%mod;
        node=p[node];
        --dis;
    }
}

void find(int node) {
    int dis=0;
    ll ans=h[node];
    while (dis<=40 && node!=0) {
        ans=(ans*mul[node][dis])%mod;
        ans=(ans*mul[node][dis+1])%mod;
        ++dis; node=p[node];
    }
    for (int i=dis+1; i<=40; ++i) { //distance can higher than root
        ans=(ans*mul[1][i])%mod;
    }
    cout<<ans<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>mod;
    for (int i=1; i<=n; ++i) {
        for (int j=0; j<=41; ++j) mul[i][j]=1;
    }
    for (int i=0; i<n-1; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i=1; i<=n; ++i) cin>>h[i];
    dfs(1,0);
    cin>>q;
    while (q--) {
        int mode; cin>>mode;
        if (mode==1) {
            int node,dis;
            ll w;
            cin>>node>>dis>>w;
            add(node,dis,w);
        } else {
            int node; cin>>node;
            find(node);
        }
    }
}