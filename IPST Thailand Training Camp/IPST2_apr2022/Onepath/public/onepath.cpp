#include "onepath.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int level[100001],sz[100001],p[100001][17],N;
vector<int> adj[100001];
vector<pii> vv;

void dfs(int x, int par) {
    level[x]=level[par]+1;
    sz[x]=1;

    p[x][0]=par;
    for (int i=1; i<17; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (auto s : adj[x]) {
        if (s==par) continue;
        if (level[s]) vv.push_back(pii(s,x));
        else {
            dfs(s,x);
            sz[x]+=sz[s];
        }
    }
}

int lca(int x, int y) {
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];

    for (int i=0; i<17; ++i) {
        if (dif&(1<<i)) x=p[x][i];
    }

    if (x==y) return x;

    for (int i=16; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            x=p[x][i];
            y=p[y][i];
        }
    }
    return p[x][0];
}

bool s[1<<18],lz[1<<18];

void push_lz(int l, int r, int idx) {
    if (!lz[idx]) return;
    s[idx]=true;
    if (l!=r) lz[2*idx]=lz[2*idx+1]=true;
    lz[idx]=false;
}

void update(int l, int r, int idx, int x, int y) {
    push_lz(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        lz[idx]=true;
        push_lz(l,r,idx);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y);
        update(mid+1,r,2*idx+1,x,y);
        s[idx]=(s[2*idx] || s[2*idx+1]);
    }
}

bool query(int l, int r, int idx, int x, int y) {
    push_lz(l,r,idx);
    if (x>r || y<l) return false;
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return query(l,mid,2*idx,x,y) || query(mid+1,r,2*idx+1,x,y);
}


int idx[100001],par_group[100001],cnt;
bool vis[100001];

void hld(int x, int par, int pg) {
    if (vis[x]) return;
    vis[x]=true;

    int mnode=0, mmax=0;

    idx[x]=cnt++;
    par_group[x]=pg;

    for (auto s : adj[x]) {
        if (s==par || level[s]<level[x]) continue;
        if (mmax<sz[s]) {
            mmax=sz[s];
            mnode=s;
        }
    }

    if (mnode) hld(mnode,x,pg);
    for (auto s : adj[x]) {
        if (s==par || level[s]<level[x] || s==mnode) continue;
        hld(s,x,s);
    }
}

bool is_dangerous(int u, int v) {
    int LCA=lca(u,v);

    while (par_group[u]!=par_group[LCA]) {
        if (query(0,N-1,1,idx[par_group[u]],idx[u])) return false;
        u=p[par_group[u]][0];
    }
    if (u!=LCA && query(0,N-1,1,idx[LCA]+1,idx[u])) return false;

    while (par_group[v]!=par_group[LCA]) {
        if (query(0,N-1,1,idx[par_group[v]],idx[v])) return false;
        v=p[par_group[v]][0];
    }
    if (v!=LCA && query(0,N-1,1,idx[LCA]+1,idx[v])) return false;

    return true;
}

void build_road(int u, int v) {
    int LCA=lca(u,v);

    while (par_group[u]!=par_group[LCA]) {
        update(0,N-1,1,idx[par_group[u]],idx[u]);
        u=p[par_group[u]][0];
    }
    if (u!=LCA) update(0,N-1,1,idx[LCA]+1,idx[u]);

    while (par_group[v]!=par_group[LCA]) {
        update(0,N-1,1,idx[par_group[v]],idx[v]);
        v=p[par_group[v]][0];
    }
    if (v!=LCA) update(0,N-1,1,idx[LCA]+1,idx[v]);
}

void initialize(int n, int m, int q, vector<pair<int,int>> R) {
    N=n;
    for (auto s : R) {
        adj[s.first].push_back(s.second);
        adj[s.second].push_back(s.first);
    }

    dfs(0,0);
    hld(0,0,0);
    for (auto s : vv) build_road(s.first,s.second);
}
/*
8 8 9
0 1
1 2
3 1
2 3
4 3
6 4
4 5
5 7
1 7 6
1 3 5
1 0 6
1 2 7
2 4 7
1 3 5
1 3 6
2 2 6
1 3 6

8 8 1
0 1
1 2
3 1
2 3
4 3
6 4
4 5
5 7
1 2 7
*/
