#include "islandparty.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n,sz[100001],cl[100001],cnt,p[100001];
ll dis[100001][20],a[100001];
vector<int> adj[100001];
bool mark[100001];
vector<pii> v[100001]; //version, index : version t means consider the case that XOR 0 to t-1

struct NN {
    ll val1,val2;
    int cnt;
} node[2000000];

int find_sz(int x, int par) {
    sz[x]=1;
    for (auto s : adj[x]) {
        if (s==par || mark[s]) continue;
        find_sz(s,x);
        sz[x]+=sz[s];
    }
    return sz[x];
}

int find_cen(int x, int par, int n) {
    for (auto s : adj[x]) if (s!=par && !mark[s] && sz[s]>n/2) return find_cen(s,x,n);
    return x;
}

void dfs_cen(int x, int par, int lev, ll m) {
    m=m^a[x];
    dis[x][lev]=m;
    for (auto s : adj[x]) {
        if (s==par || mark[s]) continue;
        dfs_cen(s,x,lev,m);
    }
}

void sol(int x, int par) {
    int centroid=find_cen(x,x,find_sz(x,x));
    mark[centroid]=true;
    p[centroid]=par;
    cl[centroid]=cl[par]+1;

    dfs_cen(centroid,centroid,cl[centroid],0);

    for (auto s : adj[centroid]) {
        if (mark[s]) continue;
        sol(s,centroid);
    }
}

void add(int st) {
    int now=st, ver=st+1;

    while (now!=-1) {
        int bef=v[now].back().second;

        ++cnt;
        node[cnt].cnt=node[bef].cnt+1;
        node[cnt].val1=node[bef].val1^dis[st][cl[now]];
        if (p[now]!=-1) node[cnt].val2=node[bef].val2^dis[st][cl[now]-1];
        v[now].push_back(pii(ver,cnt));

        now=p[now];
    }
}

int f(int st, int ver) {
    if (st==-1) return -1;
    auto it=upper_bound(v[st].begin(),v[st].end(),pii(ver,INT_MAX)); --it;
    return (*it).second;
}

ll find(int ver, int st) {
    int now=st, idx=f(now,ver);

    ll ans=node[idx].val1;
    int pre=idx;
    now=p[now]; idx=f(now,ver);

    while (now!=-1) {
        ans^=(node[idx].val1^node[pre].val2);
        if ((node[idx].cnt-node[pre].cnt)%2==1) ans^=(dis[st][cl[now]]^a[now]);

        pre=idx;
        now=p[now];
        idx=f(now,ver);
    }
    return ans;
}

void init(int N, int T, std::vector<long long> A, std::vector<int> U, std::vector<int> V) {
    n=N; cnt=n-1;
    for (int i=0; i<n-1; ++i) {
        adj[U[i]].push_back(V[i]);
        adj[V[i]].push_back(U[i]);
    }
    for (int i=0; i<n; ++i) {
        a[i]=A[i];
        v[i].push_back(pii(0,i));
        node[i].cnt=0;
        node[i].val1=0;
        node[i].val2=0;
    }
    sol(0,-1);
    for (int i=0; i<n; ++i) add(i);
}

long long find_drunkenness(int L, int R, int X) {
    return find(R+1,X)^find(L,X);
}
/*
5 1
5 7 8 2 0
4 3
3 1
3 2
0 3
2 4 0

5 4
5 7 8 2 0
4 3
3 1
3 2
0 3
2 4 0
0 1 3
2 3 1
4 4 2
*/
