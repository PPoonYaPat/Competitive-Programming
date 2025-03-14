#include "landlord.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

int main(){
  int Q,N,M,a,b,x;
  char c[2005];
  assert(scanf("%d %d %d",&N,&M,&Q)==3);
  vector<vector<int> >K;
  vector<int>tp;
  for(int i=0;i<N;i++){
    tp.clear();
    assert(scanf("%s",c)==1);
    for(int j=0;j<M;j++){
      x=c[j]-'0';
      assert(x<=1&&x>=0);
      tp.push_back(x);
    }
    K.push_back(tp);
  }
  landlord(N,M,K);
  for(int i=0;i<Q;i++){
    assert(scanf("%d %d",&a,&b)==2);
    printf("%d\n",house(a,b));
  }
}
