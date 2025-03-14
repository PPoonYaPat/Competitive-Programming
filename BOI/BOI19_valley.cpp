#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n,m,q,st,p[100001][18],level[100001];
ll dis[100001],mmin[100001],near[100001]; //mmin[x]=near[x]-dis[x] -> x is the highest node in the path
ll val[100001][18];
bool shop[100001];
vector<pii> edge,adj[100001];

void dfs(int x, int par) {
    near[x]=1e18;
    if (shop[x]) near[x]=0;

    for (auto s : adj[x]) {
        if (s.first==par) continue;
        dis[s.first]=dis[x]+s.second;
        dfs(s.first,x);
        near[x]=min(near[x],near[s.first]+s.second);
    }

    mmin[x]=near[x]-dis[x];
}

void dfs2(int x, int par) {
    level[x]=level[par]+1;
    p[x][0]=par;
    val[x][0]=mmin[x];
    for (int i=1; i<18; ++i) {
        p[x][i]=p[p[x][i-1]][i-1];
        val[x][i]=min(val[x][i-1],val[p[x][i-1]][i-1]);
    }

    for (auto s : adj[x]) {
        if (s.first==par) continue;
        dfs2(s.first,x);
    }
}

pii lca(int x, int y) { //LCA,min
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];
    ll mi=LLONG_MAX;

    for (int i=0; i<18; ++i) {
        if (dif&(1<<i)) {
            mi=min(mi,val[x][i]);
            x=p[x][i];
        }
    }
    if (x==y) return pii(x,min(mi,val[x][0]));

    for (int i=17; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            mi=min({mi,val[x][i],val[y][i]});
            x=p[x][i];
            y=p[y][i];
        }
    }
    return pii(p[x][0],min({mi,val[x][1],val[y][1]}));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>q>>st;
    for (int i=0; i<n-1; ++i) {
        int a,b,w; cin>>a>>b>>w;
        adj[a].push_back(pii(b,w));
        adj[b].push_back(pii(a,w));
        edge.push_back(pii(a,b));
    }
    for (int i=0; i<m; ++i) {
        int s; cin>>s;
        shop[s]=true;
    }
    dfs(st,st);
    dfs2(st,st);

    while (q--) {
        int e,s; cin>>e>>s;
        int u=edge[e-1].first, v=edge[e-1].second;
        if (level[u]>level[v]) swap(u,v); //u-up, v-down

        pii res=lca(s,v);
        if (res.first!=v) cout<<"escaped\n";
        else if (res.second>1e16) cout<<"oo\n";
        else cout<<res.second+dis[s]<<"\n";
    }
}