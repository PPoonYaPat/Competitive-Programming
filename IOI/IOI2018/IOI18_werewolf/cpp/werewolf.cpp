#include "werewolf.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int p[200001],r[200001],cnt,in[200001],out[200001],pa[2][200001],va[2][200001],c[200001],top[2];
vector<int> adj[200001];
vector<pii> Adj[2][200001];

int find(int x) {
    while (x!=p[x]) x=p[x];
    return x;
}

void unite(int x, int y, int val, int mode) {
    x=find(x); y=find(y);
    if (x==y) return;

    if (r[x]>r[y]) {
        p[y]=x;
        Adj[mode][x].push_back(pii(y,val));
    } else if (r[x]<r[y]) {
        p[x]=y;
        Adj[mode][y].push_back(pii(x,val));
    } else {
        p[x]=y; ++r[y];
        Adj[mode][y].push_back(pii(x,val));
    }
}

int f0(int x, int bound) {
    if (bound>=va[0][x]) {
        while (x!=pa[0][x] && va[0][pa[0][x]]<=bound) x=pa[0][x];
        x=pa[0][x];
    }

    int l=0,r=Adj[0][x].size()-1;
    if (r==-1) return -1;
    if (Adj[0][x][0].second>bound) return -1;

    while (l<r) { //find the last element that not over bound
        int mid=(l+r+1)/2;
        if (Adj[0][x][mid].second<=bound) l=mid;
        else r=mid-1;
    }

    return Adj[0][x][l].first;
}

int f1(int x, int bound) {
    if (bound<=va[1][x]) {
        while (x!=pa[1][x] && va[1][pa[1][x]]>=bound) x=pa[1][x];
        x=pa[1][x];
    }

    int l=0,r=Adj[1][x].size()-1;
    if (r==-1) return -1;
    if (Adj[1][x][0].second<bound) return -1;

    while (l<r) { //find the last element that at least bound
        int mid=(l+r+1)/2;
        if (Adj[1][x][mid].second>=bound) l=mid;
        else r=mid-1;
    }

    return Adj[1][x][l].first;
}

void dfs(int x, int par, int mode) { //dfs in werewolf
    pa[mode][x]=par;
    if (!mode) c[x]=++cnt,in[x]=c[par];

    for (auto s : Adj[mode][x]) {
        va[mode][s.first]=s.second;
        dfs(s.first,x,mode);
    }

    if (!mode) out[x]=cnt;
}

struct N {
    int in,out,idx;
};
vector<N> v[200001];
set<int> temp[200001];
vector<int> ans;

void dfs_ans(int x) { //find answer in human
    temp[x].insert(c[x]);

    for (auto k : Adj[1][x]) {
        int s=k.first;
        dfs_ans(s);

        if (temp[x].size()<temp[s].size()) swap(temp[s],temp[x]);
        for (auto h : temp[s]) temp[x].insert(h);

        for (auto h : v[s]) {
            if (*(temp[x].lower_bound(h.in))<=h.out && temp[x].lower_bound(h.in)!=temp[x].end()) ans[h.idx]=1;
            else ans[h.idx]=0;
        }
    }
}

vector<int> check_validity(int n, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
    for (int i=0; i<X.size(); ++i) {
        adj[X[i]].push_back(Y[i]);
        adj[Y[i]].push_back(X[i]);
    }
    for (int i=0; i<S.size(); ++i) ans.push_back(0);

    for (int i=0; i<n; ++i) p[i]=i,r[i]=1;
    for (int i=0; i<n; ++i) { //werewolf
        for (auto s : adj[i]) {
            if (s<i) unite(i,s,i,0);
        }
    }
    top[0]=find(0);
    va[0][top[0]]=n-1;
    dfs(top[0],top[0],0);

    for (int i=0; i<n; ++i) p[i]=i,r[i]=1;
    for (int i=n-1; i>=0; --i) { //human
        for (auto s : adj[i]) {
            if (s>i) unite(i,s,i,1);
        }
    }
    top[1]=find(0);
    dfs(top[1],top[1],1);

    for (int i=0; i<S.size(); ++i) {
        if (S[i]<L[i] || E[i]>R[i]) ans[i]=0;
        else {
            int s=f1(S[i],L[i]), e=f0(E[i],R[i]);

            if (s==-1 && e==-1) ans[i]=0;
            else if (s==-1) {
                if (c[S[i]]>=in[e] && c[S[i]]<=out[e]) ans[i]=1;
                else ans[i]=0;
            } else if (e==-1) v[s].push_back({c[E[i]],c[E[i]],i});
            else v[s].push_back({in[e],out[e],i});
        }
    }

    Adj[1][n].push_back({top[1],0});
    dfs_ans(n);

    for (int i=0; i<ans.size(); ++i) if (ans[i]==1) cout<<i<<" ";

    return ans;
}
