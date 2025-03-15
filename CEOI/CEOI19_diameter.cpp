#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n,q,in[100005],out[100005],mx;
ll W,d[100005],val[100005];
vector<pii> adj[100005];
pii edge[100005];
vector<int> v;

struct node {
    ll ans,suff,pref,lca,depth;
} s[2000000];

ll lz[2000000];

node merge(node a, node b) {
    node res;
    res.depth=max(a.depth,b.depth); //d[x]
    res.lca=min(a.lca,b.lca); //d[y]
    res.pref=max({a.pref,b.pref,b.depth-2*a.lca}); //d[x]-2d[y]
    res.suff=max({a.suff,b.suff,a.depth-2*b.lca}); //-2d[y]+d[z]
    res.ans=max({a.ans,b.ans,a.depth+b.pref,a.suff+b.depth}); //d[x]-2d[y]+d[z]
    return res;
}

void push(int l, int r, int idx) {
    if (lz[idx]==0) return;

    s[idx].depth+=lz[idx];
    s[idx].lca+=lz[idx];
    s[idx].suff-=lz[idx];
    s[idx].pref-=lz[idx];

    if (l!=r) {
        lz[2*idx]+=lz[idx];
        lz[2*idx+1]+=lz[idx];
    }
    lz[idx]=0;
}

void build(int l, int r, int idx) {
    if (l==r) {
        s[idx].depth=d[v[l]];
        s[idx].lca=d[v[l]];
        s[idx].pref=-d[v[l]];
        s[idx].suff=-d[v[l]];
        s[idx].ans=-2e18-5;
    } else {
        int mid=(l+r)/2;
        build(l,mid,2*idx);
        build(mid+1,r,2*idx+1);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

void update(int l, int r, int idx, int x, int y, ll val) {
    push(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        lz[idx]+=val;
        push(l,r,idx);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y,val);
        update(mid+1,r,2*idx+1,x,y,val);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

void dfs(int x, int par) {
    in[x]=v.size();
    v.push_back(x);
    for (auto s : adj[x]) {
        if (s.first==par) continue;
        d[s.first]=d[x]+s.second;
        dfs(s.first,x);
        v.push_back(x);
    }
    out[x]=v.size()-1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>q>>W;
    for (int i=0; i<n-1; ++i) {
        int a,b; ll w;
        cin>>a>>b>>w;
        adj[a].push_back(pii(b,w));
        adj[b].push_back(pii(a,w));
        edge[i]=pii(a,b);
        val[i]=w;
    }
    dfs(1,0);
    mx=v.size()-1;
    build(0,mx,1);
    
    ll bef=0;
    while (q--) {
        ll x,w; cin>>x>>w;
    
        x=(x+bef)%(n-1);
        w=(w+bef)%W;

        int a=edge[x].first, b=edge[x].second;
        if (d[a]>d[b]) swap(a,b);
        update(0,mx,1,in[b],out[b],w-val[x]);
        val[x]=w;

        bef=max(s[1].ans,s[1].depth);
        cout<<bef<<"\n";
    }
}