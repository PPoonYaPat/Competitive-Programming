#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mx=250;
int n,r,q,group[200005],pos[25005],in[200005],out[200005],cc;
ll ans[805][25005];
vector<int> adj[200005],g[25005],v[25005];

void dfs1(int x) {
    in[x]=++cc;
    v[group[x]].push_back(in[x]);
    for (auto s : adj[x]) dfs1(s);
    out[x]=cc;
}

void dfs2(int x, int gr, int c) {
    if (group[x]==gr) ++c;
    else ans[pos[gr]][group[x]]+=c;
    for (auto s : adj[x]) dfs2(s,gr,c);
}

int main() {
    cin>>n>>r>>q>>group[1];
    g[group[1]].push_back(1);
    for (int i=2; i<=n; ++i) {
        int a; cin>>a>>group[i];
        g[group[i]].push_back(i);
        adj[a].push_back(i);
    }
    dfs1(1);
    for (int i=1; i<=r; ++i) sort(v[i].begin(),v[i].end());
    int u=0;
    for (int i=1; i<=r; ++i) if (g[i].size()>mx) pos[i]=++u, dfs2(1,i,0);

    while (q--) {
        int a,b; cin>>a>>b;
        if (g[a].size()>mx) cout<<ans[pos[a]][b]<<endl;
        else {
            ll sum=0;
            for (auto s : g[a]) sum+=(upper_bound(v[b].begin(),v[b].end(),out[s])-lower_bound(v[b].begin(),v[b].end(),in[s]));
            cout<<sum<<endl;
        }
    }
}