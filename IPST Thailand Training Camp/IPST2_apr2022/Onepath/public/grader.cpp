#include "onepath.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <utility>

static int n, m, q;
static std::vector<std::pair<int, int>> r;
static std::vector<int> t;
static std::vector<std::pair<int, int>> f;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  assert(std::cin >> n >> m >> q);
  for (int i = 0, u, v; i < m; ++i) {
    assert(std::cin >> u >> v);
    r.emplace_back(u, v);
  }
  for (int i = 0, x, y, z; i < q; ++i) {
    assert(std::cin >> x >> y >> z);
    t.emplace_back(x);
    f.emplace_back(y, z);
  }
  initialize(n, m, q, r);
  std::vector<bool> answer;
  for (int i = 0; i < q; ++i) {
    if (t[i] == 1) {
      answer.emplace_back(is_dangerous(f[i].first, f[i].second));
    } else {
      build_road(f[i].first, f[i].second);
    }
  }
  for (auto ans : answer) {
    std::cout << (ans ? "true" : "false") << std::endl;
  }
}