#include <bits/stdc++.h>
//#include "grader.cpp"
#include "switches.h"
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

struct nn {
    ll mmin,mmax;
} s1[1<<19],s2[1<<19];

int n,m,k;
const int mx=100000;
ll a[50001],dis[50010][21];
multiset<ll> ms_mmin[100010],ms_mmax[100010];


bool vis[50010][21];
vector<pii> adj[50001];
priority_queue<pii, vector<pii>, greater<pii>> q;

void dij(int x) {
    for (int i=0; i<=n; ++i) q.push(pii(dis[i][x],i));
    while (!q.empty()) {
        int node=q.top().second;
        q.pop();

        if (vis[node][x]) continue;
        vis[node][x]=true;

        for (auto s : adj[node]) {
            ll des=s.first, w=s.second;
            if (dis[des][x]>dis[node][x]+w) {
                dis[des][x]=dis[node][x]+w;
                q.push(pii(dis[des][x],des));
            }
        }
    }
}

void update1(int l, int r, int idx, int x, ll val1, ll val2) {
    if (x>r || x<l) return;
    if (l==r) {
        ll ans1=min(val1,s1[idx].mmin), ans2=min(val2,s1[idx].mmax);
        s1[idx]={ans1,ans2};
    } else {
        int mid=(l+r)/2;
        update1(l,mid,2*idx,x,val1,val2);
        update1(mid+1,r,2*idx+1,x,val1,val2);

        s1[idx].mmax=min(s1[2*idx].mmax,s1[2*idx+1].mmax);
        s1[idx].mmin=min(s1[2*idx].mmin,s1[2*idx+1].mmin);
    }
}

void update2(int l, int r, int idx, int x, ll val1, ll val2) {
    if (x>r || x<l) return;
    if (l==r) {
        s2[idx]={val1,val2};
    } else {
        int mid=(l+r)/2;
        update2(l,mid,2*idx,x,val1,val2);
        update2(mid+1,r,2*idx+1,x,val1,val2);

        s2[idx].mmax=min(s2[2*idx].mmax,s2[2*idx+1].mmax);
        s2[idx].mmin=min(s2[2*idx].mmin,s2[2*idx+1].mmin);
    }
}

nn query1(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {LLONG_MAX,LLONG_MAX};
    if (x<=l && r<=y) return s1[idx];

    int mid=(l+r)/2;
    nn ll=query1(l,mid,2*idx,x,y), rr=query1(mid+1,r,2*idx+1,x,y);
    return {min(ll.mmin,rr.mmin),min(ll.mmax,rr.mmax)};
}

nn query2(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {LLONG_MAX,LLONG_MAX};
    if (x<=l && r<=y) return s2[idx];

    int mid=(l+r)/2;
    nn ll=query2(l,mid,2*idx,x,y), rr=query2(mid+1,r,2*idx+1,x,y);
    return {min(ll.mmin,rr.mmin),min(ll.mmax,rr.mmax)};
}

long long minimum_energy(int N, int M, int K, vector<int> A, vector<int> L, vector<int> R, vector<int> C){
    n=N; m=M; k=K;
    for (int i=0; i<n; ++i) a[i]=A[i];
    for (int i=0; i<=50005; ++i) for (int j=0; j<=20; ++j) dis[i][j]=LLONG_MAX;

    for (int i=0; i<n; ++i) {
        adj[i].push_back(pii(i+1,A[i]));
        adj[i+1].push_back(pii(i,A[i]));
    }
    for (int i=0; i<m; ++i) {
        adj[L[i]].push_back(pii(R[i]+1,C[i]));
        adj[R[i]+1].push_back(pii(L[i],C[i]));
    }
    dis[0][0]=0;
    dij(0);

    for (int i=1; i<=k; ++i) {
        //reset segment
        for (int j=0; j<1<<19; ++j) s1[j]=s2[j]={LLONG_MAX,LLONG_MAX};

        //make new segment
        update1(0,mx,1,a[0],dis[0][i-1]-a[0]*a[0],dis[0][i-1]+a[0]*a[0]);

        for (int j=1; j<=n; ++j) {
            ms_mmax[a[j-1]].insert(dis[j][i-1]+a[j-1]*a[j-1]);
            ms_mmin[a[j-1]].insert(dis[j][i-1]-a[j-1]*a[j-1]);
            update2(0,mx,1,a[j-1],*(ms_mmin[a[j-1]].begin()),*(ms_mmax[a[j-1]].begin()));
        }

        //find dis
        dis[0][i]=0;
        for (int j=1; j<=n; ++j) {

            update1(0,mx,1,a[j],dis[j][i-1]-a[j]*a[j],dis[j][i-1]+a[j]*a[j]);

            ms_mmax[a[j-1]].erase(ms_mmax[a[j-1]].find(dis[j][i-1]+a[j-1]*a[j-1]));
            ms_mmin[a[j-1]].erase(ms_mmin[a[j-1]].find(dis[j][i-1]-a[j-1]*a[j-1]));

            ll ans1=LLONG_MAX, ans2=LLONG_MAX;
            if (ms_mmin[a[j-1]].size()) ans1=*(ms_mmin[a[j-1]].begin());
            if (ms_mmax[a[j-1]].size()) ans2=*(ms_mmax[a[j-1]].begin());

            update2(0,mx,1,a[j-1],ans1,ans2);

            dis[j][i]=dis[j][i-1];
            ans1=query1(0,mx,1,1,a[j-1]).mmin; ans2=query2(0,mx,1,1,a[j]).mmin;
            if (ans1!=LLONG_MAX) dis[j][i]=min(dis[j][i],ans1+a[j-1]*a[j-1]);
            if (ans2!=LLONG_MAX) dis[j][i]=min(dis[j][i],ans2+a[j]*a[j]);
            dis[j][i]=min(dis[j][i],query1(0,mx,1,a[j-1]+1,mx).mmax-a[j-1]*a[j-1]);
            dis[j][i]=min(dis[j][i],query2(0,mx,1,a[j]+1,mx).mmax-a[j]*a[j]);

        }

        dij(i);
    }

    return dis[n][k];
}
/*
6 4 0
1 3 8 8 5 9
0 1 5
1 4 6
2 3 4
3 5 3
15

6 4 2
1 3 8 8 5 9
0 1 5
1 4 6
2 3 4
3 5 3

10 4 2
8 3 4 2 9 10 4 1 11 7
3 8 11
1 4 8
6 9 9
8 9 4
*/
