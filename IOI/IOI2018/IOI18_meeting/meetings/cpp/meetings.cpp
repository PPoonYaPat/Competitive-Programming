#include "meetings.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll s[30000],h[5005],mmax[5005][5005],sumL[5005][5005],sumR[5005][5005];
int n;


vector<long long> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
  n=H.size();
  assert(n<=5000);
  vector<ll> ans;
  for (int i=0; i<n; ++i) h[i]=H[i];
  
  for (int i=0; i<n; ++i) {
    mmax[i][i]=h[i];
    for (int j=i+1; j<n; ++j) mmax[i][j]=max(mmax[i][j-1],h[j]);
  }

  for (int r=0; r<n; ++r) {
    sumL[r][r]=h[r];
    for (int l=r-1; l>=0; --l) sumL[l][r]=sumL[l+1][r]+mmax[l][r];
  }

  for (int l=0; l<n; ++l) {
    sumR[l][l]=h[l];
    for (int r=l+1; r<n; ++r) sumR[l][r]=sumR[l][r-1]+mmax[l][r];
  }

  for (int i=0; i<L.size(); ++i) {
    ll mi=LLONG_MAX;
    for (int j=L[i]; j<=R[i]; ++j) mi=min(mi,sumL[L[i]][j]+sumR[j][R[i]]-h[j]);
    ans.push_back(mi);
  }
  return ans;
}
