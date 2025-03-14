#include "twohomes.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

vector<pii> adj[1001];
vector<int> v,ans;
bool vis[1001],block[2501];
int sz[1001],n;

void dfs(int x, int par) {
    vis[x]=true;
    for (auto s : adj[x]) {
        if (s.first==par) continue;
        if (vis[s.first]) {
            if (!block[s.second]) v.push_back(s.second), block[s.second]=true;
        }
        else dfs(s.first,x);
    }
}

void dfs_sz(int x, int par) {
    sz[x]=1;
    for (auto s : adj[x]) {
        if (s.first==par || block[s.second]) continue;
        dfs_sz(s.first,x);
        sz[x]+=sz[s.first];
    }
}

int edge,mmin,up,down;

void dfs_sz2(int x, int par, int val) {
    for (auto s : adj[x]) {
        if (s.first==par || block[s.second]) continue;

        if (mmin>max(val-sz[s.first],sz[s.first])) {
            mmin=max(val-sz[s.first],sz[s.first]);
            edge=s.second;
            up=x;
            down=s.first;
        }

        dfs_sz2(s.first,x,val);
    }
}

vector<int> temp;
int level[1001];

void dfs2(int x, int par) {
    for (auto s : adj[x]) {
        if (s.first==par || block[s.second]) continue;
        temp.push_back(s.second);
        dfs2(s.first,x);
    }
}

void dfs3(int x, int par) {
    level[x]=level[par]+1;
    for (auto s : adj[x]) {
        if (s.first==par || block[s.second]) continue;
        dfs3(s.first,x);
    }
}

void check2(int node) {
    temp.clear();
    mmin=INT_MAX;
    dfs_sz(node,node);
    dfs_sz2(node,node,sz[node]);

    int u=up,d=down;
    if (level[d]<level[u]) swap(u,d);

    if (sz[node]==1) {
        ans.push_back(node);
        return;
    }

    for (auto s : v) temp.push_back(s);
    temp.push_back(edge);
    block[edge]=true;

    if (is_reachable(temp)) check2(u);
    else check2(d);
}

void check1(int node) {
    temp.clear();
    mmin=INT_MAX;
    dfs_sz(node,node);
    dfs_sz2(node,node,sz[node]);

    int u=up, d=down;

    for (auto s : v) temp.push_back(s);
    temp.push_back(edge);
    block[edge]=true;

    if (is_reachable(temp)) {
        dfs2(down,down);
        if (is_reachable(temp)) check1(u);
        else check1(d);
    } else {
        dfs3(u,u);
        dfs3(d,d);
        check2(u);
        check2(d);
    }
}

pair<int,int> find_homes(int N, int M, vector<vector<int>> R) {
    n=N;
    for (int i=0; i<M; ++i) {
        adj[R[i][0]].push_back(pii(R[i][1],i));
        adj[R[i][1]].push_back(pii(R[i][0],i));
    }
    dfs(0,0);
    check1(0);

    return pii(ans[0],ans[1]);
}
