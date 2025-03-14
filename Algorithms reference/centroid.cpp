#include <bits/stdc++.h>
using namespace std;

int sz[200001];
vector<int> adj[200001];
bool mark[200001];
 
int find_sz(int x, int par) {
    sz[x]=1;
    for (auto s : adj[x]) {
        if (s==par || mark[s]) continue;
        sz[x]+=find_sz(s,x);
    }
    return sz[x];
}
 
int cen(int x, int par, int n) {
    for (auto s : adj[x]) {
        if (s!=par && !mark[s] && sz[s]>n/2) return cen(s,x,n);
    }
    return x;
}
 
void sol(int x) {
    int centroid=cen(x,x,find_sz(x,x));
    mark[centroid]=true;

    //do some algorithms / dfs
 
    for (auto s : adj[centroid]) if (!mark[s]) sol(s);
}