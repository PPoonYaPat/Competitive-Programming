#include "island.h"
#include <bits/stdc++.h>
using namespace std;

void solve(int N, int L) {
  bool have[305];
  memset(have,0,sizeof(have));
  have[1]=true;
  for (int i=1; i<N; ++i) {
    int x=query(1,i);
    if (have[x]) continue;
    have[x]=true;
    for (int j=1; j<N; ++j) {
      int y=query(x,j);
      answer(x,y);
      if (have[y]) break;
      have[y]=true;
    }
  }
}