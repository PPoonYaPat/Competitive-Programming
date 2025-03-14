#include "twohomes.h"
#include <iostream>
#include <cstdlib>

static int N,M,Q,S,T;
static std::vector<std::vector<int>> R;

static const int MAX_N = 1000;
static std::vector<std::pair<int,int>> edges;
static std::vector<int> adj2[MAX_N];
static std::vector<int> adjedge[MAX_N];

static std::vector<bool> usable;
static bool visited[MAX_N];
static int qcount;

static bool dfs(int u)
{
  visited[u] = true;
  if(u == T) {
    return true;
  }

  int d = adj2[u].size();
  for(int i=0; i<d; i++) {
    int e = adjedge[u][i];
    int v = adj2[u][i];
    if(usable[e]) {
      if(!visited[v]) {
	bool res = dfs(v);
	if(res)
	  return res;
      }
    }
  }
  return false;
}

bool is_reachable(std::vector<int> C)
{
  qcount++;
  if(qcount > Q) {
    std::cout << "Too many queries\n";
    exit(0);
  }

  for(int i=0; i<M; i++)
    usable[i] = true;
  for(int i=0; i<N; i++)
    visited[i] = false;

  for(int c : C) {
    if((c < 0) || (c >= M)) {
      std::cout << "call to is_reachable error\n";
      exit(0);
    }

    usable[c] = false;
  }

  return dfs(S);
}

int main()
{
  std::cin >> N >> M >> Q >> S >> T;

  int ecount = 0;
  for(int i=0; i<M; i++) {
    int u,v;
    std::cin >> u >> v;
    R.push_back({u,v});

    edges.push_back(std::make_pair(u,v));
    usable.push_back(true);

    adj2[u].push_back(v);
    adj2[v].push_back(u);

    adjedge[u].push_back(ecount);
    adjedge[v].push_back(ecount);

    ecount++;
  }

  qcount = 0;
  auto answer = find_homes(N, M ,R);

  if(((answer.first == S) && (answer.second == T)) ||
     ((answer.first == T) && (answer.second == S))) {
    std::cout << "Correct\n";
  } else {
    std::cout << "Incorrect\n";
  }

  return 0;
}
