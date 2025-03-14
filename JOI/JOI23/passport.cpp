#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,pos[200001],dis[3][1<<20];
bool vis[3][1<<20],leaf[1<<20];
vector<pii> adj[1<<20];

void build(int idx, int l, int r) {
    if (l==r) {
        pos[l]=idx;
        leaf[idx]=true;
    } else {
        adj[2*idx].push_back(pii(idx,0));
        adj[2*idx+1].push_back(pii(idx,0));

        int mid=(l+r)/2;
        build(2*idx,l,mid);
        build(2*idx+1,mid+1,r);
    }
}

void add(int l, int r, int idx, int x, int y, int i) {
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        adj[idx].push_back({pos[i],1});
    } else {
        int mid=(l+r)/2;
        add(l,mid,2*idx,x,y,i);
        add(mid+1,r,2*idx+1,x,y,i);
    }
}

priority_queue<pii, vector<pii>, greater<pii>> q;

void dij(int x) {
    while (!q.empty()) {
        int node=q.top().second;
        q.pop();

        if (vis[x][node]) continue;
        vis[x][node]=true;

        for (auto s : adj[node]) {
            if (dis[x][s.first]>dis[x][node]+s.second) {
                dis[x][s.first]=dis[x][node]+s.second;
                q.push({dis[x][s.first],s.first});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<(1<<20); ++i) dis[0][i]=dis[1][i]=dis[2][i]=1e9;

    cin>>n;
    build(1,1,n);
    for (int i=1; i<=n; ++i) {
        int l,r; cin>>l>>r;
        add(1,n,1,l,r,i);
    }

    dis[0][pos[1]]=0;
    q.push({0,pos[1]});
    dij(0);

    dis[1][pos[n]]=0;
    q.push({0,pos[n]});
    dij(1);

    for (int i=1; i<=4*n; ++i) {
        if (i==pos[1] || i==pos[n]) dis[2][i]=dis[0][i]+dis[1][i];
        else dis[2][i]=dis[0][i]+dis[1][i]-leaf[i];
        q.push({dis[2][i],i});
    }
    dij(2);

    int q; cin>>q;
    while (q--) {
        int x; cin>>x;
        if (dis[2][pos[x]]>=1e9) cout<<-1<<"\n";
        else cout<<dis[2][pos[x]]<<"\n";
    }
}