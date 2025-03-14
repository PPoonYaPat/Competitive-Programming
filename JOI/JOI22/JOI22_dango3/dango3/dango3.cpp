#include "dango3.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int n,m;

bool check(int want, vector<int> temp, vector<int> a) {
  vector<int> h; //element that in a but not in temp
  for (auto s : a) {
    auto it=lower_bound(temp.begin(),temp.end(),s);
    if (it==temp.end() || *it!=s) h.push_back(s);
  }
  if (Query(h)>=want) return true;
  else return false;
}

void find(int l, int r, vector<int> a) {
  if (l==r) Answer(a);
  else {
    int mid=(l+r)/2;
    vector<int> temp1,temp2;

    for (auto s : a) {
      temp1.push_back(s);
      if (!check(r-mid,temp1,a)) {
        temp1.pop_back();
        temp2.push_back(s);
      }
    }

    find(l,mid,temp1);
    find(mid+1,r,temp2);
  }
}

void Solve(int N, int M) {
  n=N; m=M;
  vector<int> v;
  for (int i=1; i<=n*m; ++i) v.push_back(i);
  find(1,m,v);
}
