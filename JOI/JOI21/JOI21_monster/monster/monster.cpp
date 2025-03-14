#include "monster.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int val[1005][1005];
vector<int> v;

void rev(int l, int r) {
  while (l<r) {
    swap(v[l],v[r]);
    ++l; --r;
  }
}

int Q(int a, int b) {
  if (val[a][b]==-1) {
    int k=Query(a,b);
    val[a][b]=k;
    val[b][a]=1-k;
  }
  return val[a][b];
}

vector<int> merge_sort(int l, int r) {
  if (l==r) return {l};

  int mid=(l+r)/2;
  vector<int> L=merge_sort(l,mid), R=merge_sort(mid+1,r), res;

  int idL=0, idR=0;
  while (idL<L.size() && idR<R.size()) {
    if (!Q(L[idL],R[idR])) res.push_back(L[idL++]);
    else res.push_back(R[idR++]);
  }

  while (idL<L.size()) res.push_back(L[idL++]);
  while (idR<R.size()) res.push_back(R[idR++]);
  return res;
}

vector<int> Solve(int N) {
  memset(val,-1,sizeof(val));
  int n=N;
  v=merge_sort(0,n-1);
  
  int cntA=0, cntB=0, st;
  for (int i=0; i<n; ++i) {
    if (i==0) continue;
    if (Q(v[0],v[i])) {
      ++cntA;
      if (cntA>1) break; 
    }
  }
  for (int i=0; i<n; ++i) {
    if (i==1) continue;
    if (Q(v[1],v[i])) {
      ++cntB;
      if (cntB>1) break;
    }
  }

  if (cntA==1 && cntB==1) st=1;
  else if (cntA==1) st=0;
  else {
    for (int i=2; i<n; ++i) {
      if (!Q(v[0],v[i])) {
        if (Q(v[i-1],v[i-3])) st=i-2;
        else st=i-1;
        break;
      }
    }
  }

  rev(0,st);
  int idx=st+1;
  while (idx<n) {
    int x=idx-1;
    while (!Q(v[x],v[idx]) && idx<n) ++idx;
    rev(x+1,idx);
    ++idx;
  }

  vector<int> ans(n);
  for (int i=0; i<n; ++i) ans[v[i]]=i;
  return ans;
}
