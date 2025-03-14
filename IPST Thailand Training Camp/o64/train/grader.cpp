#include "train.h"
#include <vector>
#include <cstdio>

using namespace std;

static int N,M;
static vector<int> S;
static vector<int> T;
static vector<int> C;

int main()
{
  scanf("%d %d",&N,&M);

  for(int i=0; i<M; i++) {
    int ss, tt, cc;
    scanf("%d %d %d",&ss,&tt,&cc);
    S.push_back(ss);
    T.push_back(tt);
    C.push_back(cc);
  }

  int result = find_min_cost(N,M,
			     S, T, C);

  printf("%d\n",result);
  return 0;
}
