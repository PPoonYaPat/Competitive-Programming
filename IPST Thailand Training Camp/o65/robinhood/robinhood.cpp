#include "robinhood.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

pii s[1<<20]; //max,node
int n,a[500001],root;

void build(int l, int r, int idx) {
    if (l==r) s[idx]={a[l],l};
    else {
        int mid=(l+r)/2;
        build(l,mid,2*idx);
        build(mid+1,r,2*idx+1);
        s[idx]=max(s[2*idx],s[2*idx+1]);
    }
}

pii query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return pii(-1,-1);
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return max(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

vector<int> adj[500001];

int merge(int l, int r) {
    int node=query(0,n-1,1,l,r).second;
    if (l<=node-1) {
        int h=merge(l,node-1);
        adj[node].push_back(h);
        adj[h].push_back(node);
    }
    if (node+1<=r) {
        int h=merge(node+1,r);
        adj[node].push_back(h);
        adj[h].push_back(node);
    }
    return node;
}

int sz[500001],mmax[500001][25],lcen[500001],p[500001],pa[500001];
bool mark[500001],up[500001];

void dfs(int x, int par) {
    pa[x]=par;
    for (auto s : adj[x]) if (s!=par) dfs(s,x);
}

int find_sz(int x, int par) {
    sz[x]=1;
    for (auto s : adj[x]) {
        if (s==par || mark[s]) continue;
        find_sz(s,x);
        sz[x]+=sz[s];
    }
    return sz[x];
}

int find_cen(int x, int par, int siz) {
    for (auto s : adj[x]) if (s!=par && !mark[s] && sz[s]>siz/2) return find_cen(s,x,siz);
    return x;
}

void dfs_cen(int x, int par, int lev, int ma) {
    ma=max(ma,a[x]);
    mmax[x][lev]=ma;
    for (auto s : adj[x]) {
        if (s==par || mark[s]) continue;
        dfs_cen(s,x,lev,ma);
    }
}

void cen(int x, int lev, int par, bool mode) {
    int centroid=find_cen(x,x,find_sz(x,x));
    mark[centroid]=true;
    p[centroid]=par;
    up[centroid]=mode;
    lcen[centroid]=lev;

    dfs_cen(centroid,centroid,lcen[centroid],0);

    for (auto s : adj[centroid]) {
        if (!mark[s]) {
            if (s==pa[centroid]) cen(s,lev+1,centroid,1);
            else cen(s,lev+1,centroid,0);
        }
    }
}

pii val[500001]; //of the centroid : -a[poor]/2, max to centroid - a[poor]/2 (store min value)

void add(int v) {
    int idx=v;
    val[idx].first=min(val[idx].first,-a[v]/2);
    val[idx].second=min(val[idx].second,a[v]/2);

    int pre=idx;
    idx=p[idx];

    while (idx!=-1) {
        if (up[pre]) val[idx].second=min(val[idx].second,mmax[v][lcen[idx]]-a[v]/2);
        else val[idx].first=min(val[idx].first,-a[v]/2);
        pre=idx;
        idx=p[idx];
    }
}

int ask(int v) {
    int idx=v,mmin=min(a[idx]+val[idx].first,val[idx].second);

    int pre=idx;
    idx=p[idx];

    while (idx!=-1) {
        if (up[pre]) mmin=min(mmin,mmax[v][lcen[idx]]+val[idx].first);
        else mmin=min({mmin,val[idx].second,a[idx]+val[idx].first});
        pre=idx;
        idx=p[idx];
    }

    return mmin;
}

void initialize(vector<int> A, int M) {
    n=A.size();
    for (int i=0; i<n; ++i) a[i]=A[i], val[i]=pii(1e9,1e9);
    build(0,n-1,1);
    root=merge(0,n-1);
    dfs(root,root);
    cen(0,0,-1,0);
    add(0);
}
/*
7 5
2 400 2 10 200 0 20
2 2
1 5
2 3
1 6
2 4
*/