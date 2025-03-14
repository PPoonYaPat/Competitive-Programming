#include "swap.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,pg[100001],r[100001],lp[100001],LCA;
vector<pii> adj[100001],Adj[100001];
vector<int> add[100001], del[100001];

bool comp(pii a, pii b) {return a.second<b.second;}

struct Edge{
    int u,v,w;
    bool operator < (const Edge &o) {return w<o.w;}
};
vector<Edge> edge,bridge;

int find(int x) {
    while (pg[x]!=x) x=pg[x];
    return x;
}

void unite(int X, int Y, int w) {
    int x=find(X), y=find(Y);

    if (x!=y) {
        adj[X].push_back(pii(Y,w));
        adj[Y].push_back(pii(X,w));

        if (r[x]<r[y]) swap(x,y);
        pg[y]=x;
        if (r[x]==r[y]) ++r[x];
    } else {
        bridge.push_back({X,Y,w});
    }
}

int p[100001][18],level[100001],mmax[100001][18],mmin[100001];

void dfs1(int x, int par) {
    level[x]=level[par]+1;
    p[x][0]=par;

    for (int i=1; i<18; ++i) {
        p[x][i]=p[p[x][i-1]][i-1];
        mmax[x][i]=max(mmax[x][i-1],mmax[p[x][i-1]][i-1]);
    }

    for (auto s : adj[x]) if (s.first!=par) {
        mmax[s.first][0]=s.second;
        dfs1(s.first,x);
    }
}

int lca(int X, int Y, int mode) {
    int ma=-INT_MAX;
    if (level[X]<level[Y]) swap(X,Y);
    int x=X, y=Y;

    int dif=level[x]-level[y];
    for (int i=0; i<18; ++i) {
        if (dif&(1<<i)) {
            ma=max(ma,mmax[x][i]);
            x=p[x][i];
        }
    }

    if (x!=y) {
        for (int i=17; i>=0; --i) {
            if (p[x][i]!=p[y][i]) {
                ma=max({ma,mmax[x][i],mmax[y][i]});
                x=p[x][i];
                y=p[y][i];
            }
        }
        ma=max({ma,mmax[x][0],mmax[y][0]});
        LCA=p[x][0];
    } else {
        LCA=Y;
    }

    int mi=min({lp[X],lp[Y],mmin[X],mmin[Y]});
    if (mode==0) return ma;
    else return max(ma,mi);
}

multiset<int> temp[100001];
void dfs2(int x, int par) {
    for (auto s : add[x]) temp[x].insert(s);

    for (auto s : adj[x]) {
        if (s.first==par) continue;
        dfs2(s.first,x);

        if (temp[s.first].size()>temp[x].size()) swap(temp[s.first],temp[x]);
        for (auto h : temp[s.first]) temp[x].insert(h);
    }

    if (temp[x].size()) lp[x]=*(temp[x].begin());
    else lp[x]=INT_MAX;

    for (auto s : del[x]) temp[x].erase(temp[x].find(s)), temp[x].erase(temp[x].find(s));
}

void dfs3(int x, int par) {
    if (Adj[x].size()<3) mmin[x]=INT_MAX;
    else mmin[x]=Adj[x][2].second;

    for (auto s : adj[x]) {
        if (s.first==par) continue;
        dfs3(s.first,x);
        mmin[x]=min(mmin[x],max(s.second,mmin[s.first]));
    }
}

void dfs4(int x, int par) {
    for (auto s : adj[x]) {
        if (s.first==par) continue;
        mmin[s.first]=min(mmin[s.first],max(s.second,mmin[x]));
        dfs4(s.first,x);
    }
}

void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) {
    n=N;
    for (int i=0; i<M; ++i) {
        edge.push_back({U[i],V[i],W[i]});
        Adj[U[i]].push_back(pii(V[i],W[i]));
        Adj[V[i]].push_back(pii(U[i],W[i]));
    }
    sort(edge.begin(),edge.end());
    for (int i=0; i<n; ++i) pg[i]=i;
    for (auto s : edge) unite(s.u,s.v,s.w);
    for (int i=0; i<n; ++i) sort(Adj[i].begin(),Adj[i].end(),comp);

    //find mmax
    mmax[0][0]=INT_MAX;
    dfs1(0,0);

    //find loop
    for (auto s : bridge) {
        int ma=max(lca(s.u,s.v,0),s.w);
        add[s.u].push_back(ma);
        add[s.v].push_back(ma);
        del[LCA].push_back(ma);
    }
    dfs2(0,0);

    //find mmin
    dfs3(0,0);
    dfs4(0,0);
}

int getMinimumFuelCapacity(int X, int Y) {
    int mx=lca(X,Y,1);
    if (mx==INT_MAX) return -1;
    return mx;
}
/*
11 14
0 1 3
0 5 5
1 2 2
2 3 1
2 4 4
5 6 6
6 8 7
6 9 3
5 7 2
7 10 4
4 8 108
2 6 1002
5 10 300
4 1 408
0
*/
