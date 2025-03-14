#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,k,p[500001][20],group[500001],level[500001],mark[500001];
vector<int> adj1[500001],adj2[500001],g[500001];
set<int> temp[500001];
vector<pii> edge;
bool vis[500001];

void dfs1(int x, int par) {
    level[x]=level[par]+1;
    p[x][0]=par;
    for (int i=1; i<20; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (auto s : adj1[x]) {
        if (s==par) continue;
        dfs1(s,x);
    }
}

int lca(int x, int y) {
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];
    for (int i=0; i<20; ++i) {
        if (dif&(1<<i)) x=p[x][i];
    }
    if (x==y) return x;

    for (int i=19; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            x=p[x][i];
            y=p[y][i];
        }
    }
    return p[x][0];
}

void dfs2(int x, int par) {
    for (auto s : adj1[x]) {
        if (s==par) continue;
        dfs2(s,x);
        mark[x]+=mark[s];
    }
}

void dfs3(int x, int gr) {
    vis[x]=true;
    group[x]=gr;
    for (auto s : adj2[x]) {
        if (!vis[s]) dfs3(s,gr);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>k;
    for (int i=0; i<n-1; ++i) {
        int a,b; cin>>a>>b;
        adj1[a].push_back(b);
        adj1[b].push_back(a);
        edge.push_back(pii(a,b));
    }

    for (int i=1; i<=n; ++i) {
        int x; cin>>x;
        g[x].push_back(i);
    }

    dfs1(1,0);

    for (int i=1; i<=k; ++i) {
        for (int j=1; j<g[i].size(); ++j) {
            int LCA=lca(g[i][j],g[i][j-1]);
            ++mark[g[i][j]];
            ++mark[g[i][j-1]];
            mark[LCA]-=2;
        }
    }

    dfs2(1,0);

    for (int i=2; i<=n; ++i) {
        if (mark[i]>0) {
            adj2[i].push_back(p[i][0]);
            adj2[p[i][0]].push_back(i);
        }
    }

    int cnt=0;
    for (int i=1; i<=n; ++i) {
        if (!vis[i]) dfs3(i,++cnt);
    }

    for (auto s : edge) {
        if (group[s.first]==group[s.second]) continue;
        temp[group[s.first]].insert(group[s.second]);
        temp[group[s.second]].insert(group[s.first]);
    }

    int leaf=0;
    for (int i=1; i<=cnt; ++i) {
        if (temp[i].size()==1) ++leaf;
    }

    cout<<(leaf+1)/2;
}