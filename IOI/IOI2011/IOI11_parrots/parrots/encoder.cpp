#include "encoder.h"
#include "encoderlib.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> v;

void put(int x) {
  for (int i=0; i<8; ++i) {
    if (x&(1<<i)) v.push_back(1);
    else v.push_back(0);
  }
}

void encode(int N, int M[]) {
  v.clear();
  for (int i=0; i<N; ++i) put(M[i]);
  for (int i=0; i+1<v.size(); i+=2) {
    //consider bit i and i+1
    if (v[i]==v[i+1]) send(i+v[i]);
    else {
      send(i);
      if (v[i]==0) send(i);
      else send(i+1);
    }
  }
}
