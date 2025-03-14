#include "circuit.h"
#include "stub.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m,state[200005];
const ll mod=1e9+2022;
ll base[200005],sbt[200005];
vector<int> adj[200005];

void dfs1(int x) {
  sbt[x]=adj[x].size();
  for (auto s : adj[x]) {
    if (s>=n) {
      sbt[s]=1;
      continue;
    }
    dfs1(s);
    sbt[x]=(sbt[x]*sbt[s])%mod;
  }
}

void dfs2(int x, ll val) {
  if (x>=n) {
    base[x-n]=val;
    return;
  }

  int k=adj[x].size();
  ll pref[k+2],suff[k+2];
  pref[0]=1;
  suff[k]=1;

  for (int i=0; i<k; ++i) pref[i+1]=(pref[i]*sbt[adj[x][i]])%mod;
  for (int i=k-1; i>=0; --i) suff[i]=(suff[i+1]*sbt[adj[x][i]])%mod;

  for (int i=0; i<k; ++i) dfs2(adj[x][i],(((pref[i]*suff[i+1])%mod)*val)%mod);
}

ll s[1<<18],sum[1<<18];
bool lz[1<<18];

void build(int l, int r, int idx) {
  if (l==r) {
    sum[idx]=base[l];
    if (state[l]) s[idx]=base[l];
  } else {
    int mid=(l+r)/2;
    build(l,mid,2*idx);
    build(mid+1,r,2*idx+1);
    s[idx]=(s[2*idx]+s[2*idx+1])%mod;
    sum[idx]=(sum[2*idx]+sum[2*idx+1])%mod;
  }
}

void push(int l, int r, int idx) {
  if (lz[idx]) {
    s[idx]=(sum[idx]-s[idx]+mod)%mod;
    if (l!=r) {
      lz[2*idx]=!lz[2*idx];
      lz[2*idx+1]=!lz[2*idx+1];
    }
    lz[idx]=false;
  }
}

void update(int l, int r, int idx, int x, int y) {
  push(l,r,idx);
  if (x>r || y<l) return;
  if (x<=l && r<=y) {
    lz[idx]=true;
    push(l,r,idx);
  } else {
    int mid=(l+r)/2;
    update(l,mid,2*idx,x,y);
    update(mid+1,r,2*idx+1,x,y);
    s[idx]=(s[2*idx]+s[2*idx+1])%mod;
  }
}

void init(int N, int M, vector<int> P, vector<int> A) {
  n=N; m=M;
  for (int i=0; i<m; ++i) state[i]=A[i];
  for (int i=1; i<n+m; ++i) adj[P[i]].push_back(i);
  dfs1(0);
  dfs2(0,1);

  for (int i=0; i<m; ++i) cout<<i<<" "<<base[i]<<"\n";

  build(0,m-1,1);
}

int count_ways(int L, int R) {
  update(0,m-1,1,L-n,R-n);
  return s[1];
}
