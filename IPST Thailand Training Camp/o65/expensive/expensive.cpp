#include "expensive.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

vector<pii> adj[1000001],v;
pii dis[1000001];
int p[1000001][21],level[1000001],mmin[1000001];
vector<int> leaf;

void dfs(int x, int par) {
    level[x]=level[par]+1;
    p[x][0]=par;
    for (int i=1; i<21; ++i) p[x][i]=p[p[x][i-1]][i-1];

    if (adj[x].size()==1) leaf.push_back(x);

    for (auto s : adj[x]) {
        if (s.first==par) continue;

        dis[s.first]=dis[x];
        if (s.second==1) dis[s.first].first++;
        else dis[s.first].second++;

        dfs(s.first,x);
    }
}

int lca(int x, int y) {
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];
    for (int i=0; i<21; ++i) {
        if (dif&(1<<i)) x=p[x][i];
    }

    if (x==y) return x;

    for (int i=20; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            x=p[x][i];
            y=p[y][i];
        }
    }
    return p[x][0];
}

void initialize(int n, int Q, vector<pair<int,int>> R, vector<int> C) {
    for (int i=0; i<R.size(); ++i) {
        adj[R[i].first].push_back({R[i].second,C[i]});
        adj[R[i].second].push_back({R[i].first,C[i]});
    }

    for (int i=0; i<n; ++i) {
        if (adj[i].size()>1) {
            dfs(i,i);
            break;
        }
    }

    memset(mmin,-1,sizeof(mmin));
    for (int i=0; i<leaf.size(); ++i) {
        for (int j=i+1; j<leaf.size(); ++j) {
            int a=leaf[i], b=leaf[j], LCA=lca(a,b);
            int x=dis[a].first+dis[b].first-2*dis[LCA].first;
            int y=dis[a].second+dis[b].second-2*dis[LCA].second;
            mmin[x]=max(mmin[x],y);
        }
    }

    for (int i=0; i<=1000000; ++i) {
        if (mmin[i]!=-1) {
            while (v.size() && v.back().second<=mmin[i]) v.pop_back();
            v.push_back({i,mmin[i]});
        }
    }
}

ll most_expensive(int A, int B) {
    ll mmax=0,a=A,b=B;
    for (auto s : v) mmax=max(mmax,a*s.first+b*s.second);
    return mmax;
}
/*
10 2
0 1 2
1 2 1
2 4 1
2 3 2
1 6 1
6 7 2
7 8 2
5 1 1
5 9 1
1 1
5 1
*/
