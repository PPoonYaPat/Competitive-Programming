#include "stations.h"
#include "stub.cpp"
#include <bits/stdc++.h>
using namespace std;

vector<int> adj[1001],A;
int ans[1001],cnt;

void dfs(int x, int par, int level) {
    if (level%2==0) ans[x]=++cnt;
    for (auto s : adj[x]) {
        if (s!=par) dfs(s,x,level+1);
    }
    if (level%2==1) ans[x]=++cnt;
}

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
    cnt=0;
    A.clear();
    for (int i=0; i<n; ++i) adj[i].clear();

    for (int i=0; i<n-1; ++i) {
        adj[u[i]].push_back(v[i]);
        adj[v[i]].push_back(u[i]);
    }
    dfs(0,0,0);
    for (int i=0; i<n; ++i) A.push_back(ans[i]);
    return A;
}

int find_next_station(int s, int t, vector<int> c) {
    if (s==1) {
        int ans;
        for (int i=c.size()-1; i>=0; --i) if (t<=c[i]) ans=c[i];
        return ans;
    }

    if (s>c[0]) {
        if (c.size()==1) return c[0];
        if (t<c[1] || t>s) return c[0];

        int ans;
        for (int i=1; i<c.size(); ++i) if (t>=c[i]) ans=c[i];
        return ans;

    } else {
        if (c.size()==1) return c[0];
        if (t<s || t>c[c.size()-2]) return c.back();

        int ans;
        for (int i=c.size()-2; i>=0; --i) if (t<=c[i]) ans=c[i];
        return ans;
    }
}
/*
1
5 10
0 1
1 2
1 3
2 4
4
4 0 2
3 4 1
2 0 1
4 1 2
*/
