#include "robinhood.h"
#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>

static int X, M;
static std::vector<int> AA;
static std::vector<std::pair<int, int>> Query;

int main() {
  assert(scanf("%d %d", &X, &M) == 2);
  for (int i = 0, v; i < X; ++i) {
    scanf("%d", &v);
    AA.emplace_back(v);
  }
  for (int i = 0, a, b; i < M; ++i) {
    scanf("%d %d", &a, &b);
    assert(a == 1 or a == 2);
    assert(b >= 0 and b < X);
    Query.emplace_back(a, b);
  }
  initialize(AA, M);
  for (auto k : Query) {
    if (k.first == 1)
      add(k.second);
    else
      printf("%d\n", ask(k.second));
  }
  return 0;
}
