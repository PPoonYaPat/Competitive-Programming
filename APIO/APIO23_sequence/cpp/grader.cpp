#include "sequence.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("9.txt","r",stdin);

  int N;
  cin>>N;
  cout<<N<<"\n";

  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin>>A[i];
  }

  int result = sequence(N, A);
  printf("%d\n", result);
  return 0;
}
