#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,pos[100001],ans_min,st=1,sz[100001],mov[100001];
long long ans_max;
vector<int> adj[100001];

void dfs_min(int x, int par) {
    for (auto s : adj[x]) if (s!=par) dfs_min(s,x);
    if (pos[x]==x) {
        if (x==st) swap(pos[x],pos[adj[x][0]]);
        else swap(pos[x],pos[par]);
        ans_min+=2;
    }
}

int dfs_sz(int x, int par) {
    sz[x]=1;
    for (auto s : adj[x]) if (s!=par) sz[x]+=dfs_sz(s,x);
    ans_max+=2*min(sz[x],n-sz[x]);
    return sz[x];
}

int cen(int x, int par) {
    for (auto s : adj[x]) if (s!=par && sz[s]>n/2) return cen(s,x);
    return x;
}

vector<int> group[100001];

void dfs(int x, int par, int idx) {
    group[idx].push_back(x);
    for (auto s : adj[x]) if (s!=par) dfs(s,x,idx);
}

void sol_max() {
    dfs_sz(1,0);
    int centroid=cen(1,0);
    for (int i=0; i<adj[centroid].size(); ++i) dfs(adj[centroid][i],centroid,i+1);
    group[0].push_back(centroid);

    vector<pii> v;
    for (int i=0; i<=adj[centroid].size(); ++i) v.push_back(pii(group[i].size(),i));
    sort(v.begin(),v.end());

    int siz=v.size();
    queue<int> q;
    for (int i=0; i<siz-1; ++i) {
        int n1=v[i].second, n2=v[i+1].second;
        for (int j=0; j<group[n1].size(); ++j) swap(mov[group[n1][j]],mov[group[n2][j]]);
        if (i!=siz-2) for (auto s : group[n1]) q.push(s);
    }

    for (int i=group[v[siz-2].second].size(); i<group[v[siz-1].second].size(); ++i) {
        swap(mov[group[v[siz-1].second][i]],mov[q.front()]);
        q.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=1; i<=n; ++i) pos[i]=i, mov[i]=i;
    for (int i=0; i<n-1; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i=1; i<=n; ++i) if (adj[i].size()>1) st=i;
    dfs_min(st,0);
    sol_max();
    cout<<ans_min<<" "<<ans_max<<"\n";
    for (int i=1; i<=n; ++i) cout<<pos[i]<<" ";
    cout<<"\n";
    for (int i=1; i<=n; ++i) cout<<mov[i]<<" ";
}