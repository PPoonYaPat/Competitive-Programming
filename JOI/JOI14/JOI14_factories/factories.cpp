#include "factories.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

vector<pii> adj[500001];
int par[500001],level[500001],p[500001][20],sz[500001];
ll dis[500001][20],d[500001],fact[500001];
bool mark[500001];

void dfs(int x, int parent) {
    p[x][0]=parent;
    level[x]=level[parent]+1;
    for (int i=1; i<20; ++i) {
        p[x][i]=p[p[x][i-1]][i-1];
    }

    for (auto s : adj[x]) {
        if (s.first==parent) continue;
        d[s.first]=d[x]+s.second;
        dfs(s.first,x);
    }
}

int lca(int x, int y) {
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];
    for (int i=0; i<20; ++i) {
        if (dif&(1<<i)) x=p[x][i];
    }

    if (x==y) return x;

    for (int i=19; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            x=p[x][i];
            y=p[y][i];
        }
    }
    return p[x][0];
}

ll dist(int x, int y) {
    return d[x]+d[y]-2*d[lca(x,y)];
}

int dfs_sz(int x, int parent) {
    int cnt=1;
    for (auto s : adj[x]) {
        if (s.first==parent || mark[s.first]) continue;
        cnt+=dfs_sz(s.first,x);
    }
    sz[x]=cnt;
    return cnt;
}

int find_cen(int x, int parent, int cnt) {
    for (auto s : adj[x]) {
        if (!mark[s.first] && s.first!=parent && sz[s.first]>cnt/2) return find_cen(s.first,x,cnt);
    }
    return x;
}

int decompose(int x, int parent) {
    int centroid=find_cen(x,x,dfs_sz(x,x));
    mark[centroid]=true;
    par[centroid]=parent;

    for (auto s : adj[centroid]) {
        if (!mark[s.first]) decompose(s.first,centroid);
    }

    return centroid;
}

void make_dis(int n) {
    for (int i=0; i<n; ++i) {
        int idx=0,m=i;
        while (m!=-1) {
            dis[i][idx++]=dist(i,m);
            m=par[m];
        }
    }
}

void add(int x) {
    int m=x,idx=0;
    while (m!=-1) {
        fact[m]=min(fact[m],dis[x][idx++]);
        m=par[m];
    }
}

ll find(int x) {
    int idx=0,m=x;
    ll mmin=1e15;
    while (m!=-1) {
        mmin=min(mmin,fact[m]+dis[x][idx++]);
        m=par[m];
    }
    return mmin;
}

void clear(int x) {
    while (x!=-1) {
        fact[x]=1e15;
        x=par[x];
    }
}

void Init(int n, int A[], int B[], int D[]) {
    for (int i=0; i<n-1; ++i) {
        adj[A[i]].push_back(pii(B[i],D[i]));
        adj[B[i]].push_back(pii(A[i],D[i]));
    }
    for (int i=0; i<n; ++i) fact[i]=1e15;
    dfs(0,-1); //root is 0
    decompose(0,-1);
    make_dis(n);
}

ll Query(int S, int X[], int T, int Y[]) {
    for (int i=0; i<S; ++i) add(X[i]);
    ll ans=1e15;
    for (int i=0; i<T; ++i) ans=min(ans,find(Y[i]));
    for (int i=0; i<S; ++i) clear(X[i]);
    return ans;
}
/*
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m;
    cin>>n>>m;
    int A[100],B[100],C[100];
    for (int i=0; i<n-1; ++i) {
        cin>>A[i]>>B[i]>>C[i];
    }
    Init(n,A,B,C);
    while (m--) {
        int s,t,x[100],y[100];
        cin>>s>>t;
        for (int i=0; i<s; ++i) cin>>x[i];
        for (int i=0; i<t; ++i) cin>>y[i];
        cout<<Query(s,x,t,y)<<"\n";
    }
} */
/*
7 1
0 1 4
1 2 4
2 3 5
2 4 6
4 5 5
1 6 3
1 1
2
5
*/
