#include "grader.h"
#include "encoder.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> adj[1005];
int n,h,p[1005],dis[1005][36];
bool vis[1005];

void dfs(int x, int par) {
  p[x]=par;
  vis[x]=true;
  for (auto s : adj[x]) if (!vis[s]) dfs(s,x);
}

void encode(int nv, int nh, int ne, int *v1, int *v2){
  n=nv; h=nh;
  for (int i=0; i<ne; ++i) {
    adj[v1[i]].push_back(v2[i]);
    adj[v2[i]].push_back(v1[i]);
  }

  dfs(0,0);
  for (int i=1; i<n; ++i) {
    for (int j=0; j<10; ++j) {
      if (p[i]&(1<<j)) encode_bit(1);
      else encode_bit(0);
    }
  }

  vector<int> v;
  memset(dis,-1,sizeof(dis));
  for (int i=0; i<h; ++i) {
    dis[i][i]=0;
    queue<int> q;
    q.push(i);

    while (!q.empty()) {
      int node=q.front();
      q.pop();
      for (auto s : adj[node]) {
        if (dis[s][i]==-1) {
          dis[s][i]=dis[node][i]+1;
          q.push(s);
        }
      }
    }

    for (int j=1; j<n; ++j) v.push_back(dis[p[j]][i]-dis[j][i]+1);
  }

  while (v.size()%3) v.push_back(0);

  for (int i=0; i<v.size(); i+=3) {
    int sum=v[i]+3*v[i+1]+9*v[i+2];
    for (int j=0; j<5; ++j) {
      if (sum&(1<<j)) encode_bit(1);
      else encode_bit(0);
    }
  }
}
