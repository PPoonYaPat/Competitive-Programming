#include "grader.h"
#include "decoder.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int nn,hh,pp[1005];
vector<int> v;
vector<pii> adjj[1005][36];

void dfs(int x, int par, int val, int gr) {
   hops(gr,x,val);
   for (auto s : adjj[x][gr]) {
      if (s.first!=par) dfs(s.first,x,val+s.second,gr); 
   }
}

void decode(int nv, int nh) {
   nn=nv; hh=nh;
   for (int i=1; i<nn; ++i) {
      int sum=0;
      for (int j=0; j<10; ++j) {
         if (decode_bit()==1) sum+=(1<<j);
      }
      pp[i]=sum;
   }

   for (int i=0; i<((nn-1)*hh+2)/3; ++i) {
      int sum=0;
      for (int j=0; j<5; ++j) if (decode_bit()==1) sum+=(1<<j);
      v.push_back(sum%3-1); sum/=3;
      v.push_back(sum%3-1); sum/=3;
      v.push_back(sum%3-1);
   }

   int idx=0;
   for (int i=0; i<hh; ++i) {
      for (int j=1; j<nn; ++j) {
         adjj[j][i].push_back({pp[j],v[idx]});
         adjj[pp[j]][i].push_back({j,-v[idx]});
         ++idx;
      }
   }

   for (int i=0; i<hh; ++i) dfs(i,i,0,i);
}
