#include <bits/stdc++.h>
using namespace std;

int n,sz[200005],level[200005],p[200005][19];
vector<int> adj[200005],group[200005];

void dfs_sz(int x, int par) {
    sz[x]=1;
    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs_sz(s,x);
        sz[x]+=sz[s];
    }
}

int find_cen(int x, int par) {
    for (auto s : adj[x]) if (s!=par && sz[s]>n/2) return find_cen(s,x);
    return x;
}

void dfs(int x, int par) {
    p[x][0]=par;
    level[x]=level[par]+1;
    group[sz[x]].push_back(x);
    for (int i=1; i<19; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (auto s : adj[x]) if (s!=par) dfs(s,x);
}

int lca(int x, int y) {
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];
    for (int i=0; i<19; ++i) {
        if (dif&(1<<i)) {
            x=p[x][i];
        }
    }
    if (x==y) return x;

    for (int i=18; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            x=p[x][i];
            y=p[y][i];
        }
    }
    return p[x][0];
}

int dis(int x, int y) {
    return level[x]+level[y]-2*level[lca(x,y)];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=0; i<n-1; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs_sz(1,0);
    int cen=find_cen(1,0);
    dfs_sz(cen,0);
    dfs(cen,0);

    vector<int> ans(n+1,1);
    int x=cen,y=cen,dia=0;
    for (int i=n/2; i>=1; --i) {
        for (auto s : group[i]) {
            int d1=dis(s,x), d2=dis(s,y);
            if (d1<d2) swap(d1,d2), swap(x,y);
            if (d1>dia) dia=d1, y=s;
        }
        ans[2*i]=dia+1;
    }

    for (int i=1; i<=n; ++i) cout<<ans[i]<<"\n";
}