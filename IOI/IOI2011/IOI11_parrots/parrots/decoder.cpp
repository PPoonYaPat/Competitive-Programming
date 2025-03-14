#include "decoder.h"
#include "decoderlib.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> ans,group[128];

void decode(int N, int len, int X[]) {
  ans.clear();
  for (int i=0; i<128; ++i) group[i].clear();
  for (int i=0; i<len; ++i) group[X[i]/2].push_back(X[i]%2);
  for (int i=0; i<128; ++i) {
    if (group[i].size()==0) break;
    if (group[i].size()==1) {
      ans.push_back(group[i][0]);
      ans.push_back(group[i][0]);
    } else {
      if (group[i][0]==group[i][1]) {
        ans.push_back(0);
        ans.push_back(1);
      } else {
        ans.push_back(1);
        ans.push_back(0);
      }
    }
  }
  for (int i=0; i+7<ans.size(); i+=8) {
    int res=0,mul=1;
    for (int j=0; j<8; ++j) {
      if (ans[i+j]==1) res+=mul;
      mul*=2;
    }
    output(res);
  }
}
