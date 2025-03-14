#include "meetings.h"
#include "grader.cpp"
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

int rt;
vector<int> temp[2005];

bool comp(int a, int b) {
  if (Query(rt,a,b)==a) return true;
  else return false;
}

void find(int root) {
  if (temp[root].size()==0) return;
  vector<int> v,path;
  swap(v,temp[root]);
  int sz=v.size(), ed=v[rand()%sz];

  for (auto s : v) {
    if (s==ed) continue;
    int h=Query(root,ed,s);
    if (h==s) path.push_back(s);
    else temp[h].push_back(s);
  }

  rt=root;
  sort(path.begin(),path.end(),comp); //root path ed
  path.push_back(ed);

  Bridge(min(root,path[0]),max(root,path[0]));
  for (int i=1; i<path.size(); ++i) Bridge(min(path[i],path[i-1]),max(path[i],path[i-1]));

  find(root);
  for (auto s : path) find(s);
}

void Solve(int N) {
  srand(time(0));
  for (int i=1; i<N; ++i) temp[0].push_back(i);
  find(0);
}
