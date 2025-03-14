#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int,int> tu;
typedef pair<int,int> pii;

int n,m,dis[200001];
vector<pii> adj[100001];
int par[100001][17], mmax[100001][17], level[100001];
vector<tu> v;

void dfs(int x, int parent, int w) {
    level[x]=level[parent]+1;
    par[x][0]=parent;
    mmax[x][0]=w;

    for (int i=1; i<=16; ++i) {
        mmax[x][i]=max(mmax[x][i-1],mmax[par[x][i-1]][i-1]);
        par[x][i]=par[par[x][i-1]][i-1];
    }

    for (auto s : adj[x]) {
        if (s.first==parent) continue;
        dfs(s.first,x,s.second);
    }
}

int lca(int x, int y) {
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y],ans=0;

    for (int i=16; i>=0; --i) {
        if (dif&(1<<i)) {
            ans=max(ans,mmax[x][i]);
            x=par[x][i];
        }
    }

    if (x==y) return ans;

    for (int i=16; i>=0; --i) {
        if (par[x][i] != par[y][i]) {
            ans=max(ans,mmax[x][i]);
            ans=max(ans,mmax[y][i]);
            x=par[x][i];
            y=par[y][i];
        }
    }
    return max({ans,mmax[x][0],mmax[y][0]});
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;

    for (int i=1; i<=m; ++i) {
        int a,b,w;
        cin>>a>>b>>w;
        if (i<=n-1) {
            adj[a].push_back(pii(b,w));
            adj[b].push_back(pii(a,w));
        } else v.push_back(make_tuple(w,a,b,i));
    }
    dfs(1,0,0);

    vector<pii> want;
    multiset<int> have;

    for (auto s : v) {
        int w=get<0>(s);
        int a=get<1>(s);
        int b=get<2>(s);
        int idx=get<3>(s);

        want.push_back(pii(lca(a,b)+1,idx));
        have.insert(w);
    }

    for (auto s : want) {
        int wa=s.first, idx=s.second;
        auto it=have.lower_bound(wa);

        if (it==have.end()) {
            cout<<0;
            return 0;
        }

        dis[idx]=*it;
        have.erase(it);
    }

    cout<<1<<"\n";
    for (int i=n; i<=m; ++i) cout<<dis[i]<<"\n";
}

