#include <bits/stdc++.h>
//#include "grader.cpp";
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n,level[100001];
ll val[100001][11],mmax[100001][11][17],p[100001][17],sum[100001],c[100001];
vector<int> adj[100001];

void dfs1(int x, int par) {
    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs1(s,x);
        for (int i=1; i<=10; ++i) val[x][i]=max(val[x][i],val[s][i-1]+c[x]+c[s]);
    }
 }

 void dfs2(int x, int par) {
    if (x) for (int i=1; i<=10; ++i) val[x][i]=max(val[x][i],val[par][i-1]+c[x]+c[par]);
    for (auto s : adj[x]) if (s!=par) dfs2(s,x);
 }

 void dfs3(int x, int par) {
    sum[x]=c[x]+sum[par];
    for (auto s : adj[x]) if (s!=par) dfs3(s,x);
 }

 void dfs_lca(int x, int par) {
    level[x]=level[par]+1;
    p[x][0]=par;

    for (int i=1; i<17; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (int j=0; j<=10; ++j) mmax[x][j][0]=val[x][j];
    for (int i=1; i<=16; ++i) {
        for (int j=0; j<=10; ++j) {
            mmax[x][j][i]=max(mmax[x][j][i-1],mmax[p[x][i-1]][j][i-1]);
        }
    }

    for (auto s : adj[x]) if (s!=par) dfs_lca(s,x);
 }

 ll lca(int x, int y, int poww) {
    int a=x, b=y;

    ll ma[11];
    memset(ma,0,sizeof(ma));

    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];

    for (int i=0; i<=16; ++i) {
        if (dif&(1<<i)) {
            for (int j=0; j<=10; ++j) ma[j]=max(ma[j],mmax[x][j][i]);
            x=p[x][i];
        }
    }

    if (x!=y) {
        for (int i=16; i>=0; --i) {
            if (p[x][i]!=p[y][i]) {
                for (int j=0; j<=10; ++j) ma[j]=max(ma[j],mmax[x][j][i]);
                for (int j=0; j<=10; ++j) ma[j]=max(ma[j],mmax[y][j][i]);
                x=p[x][i];
                y=p[y][i];
            }
        }
        for (int j=0; j<=10; ++j) ma[j]=max(ma[j],mmax[x][j][1]);
        for (int j=0; j<=10; ++j) ma[j]=max(ma[j],mmax[y][j][0]);
        x=p[x][0];
    } else for (int j=0; j<=10; ++j) ma[j]=max(ma[j],mmax[x][j][0]);

    ll dp[11];
    memset(dp,0,sizeof(dp));

    dp[0]=ma[0];
    for (int i=1; i<=10; ++i) {
        for (int j=0; j<i; ++j) dp[i]=max(dp[i],dp[j]+ma[i-j]);
    }

    return dp[poww]+sum[a]+sum[b]-2*sum[x]+c[x];
 }

void initialize(int N, int Q, vector<int> W, vector<pii> R) {
    n=N;
    for (int i=0; i<n; ++i) c[i]=W[i];
    for (int i=0; i<n-1; ++i) {
        adj[R[i].first].push_back(R[i].second);
        adj[R[i].second].push_back(R[i].first);
    }

    for (int i=1; i<=10; ++i) {
        dfs1(0,0);
        dfs2(0,0);
    }
    dfs3(0,0);
    dfs_lca(0,0);
}


long long query(int A, int B, int X) {
    return lca(A,B,X/2);
}
/*
8 3
1 5 1 2 1 11 1 1
0 2
2 1
2 3
3 4
3 7
5 4
5 6
0 7 5
6 2 2
1 6 0
*/
