#include "train.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int n;
bool c[5005],charge[5005],vis[5005];
vector<int> adj[5005],radj[5005],ans;

void dfs(int x) {
	for (auto s : adj[x]) {
		if (!vis[s] && !charge[s]) {
			vis[s]=true;
			dfs(s);
		}
	}
}

void rdfs(int x) {
	vis[x]=true;
	ans[x]=0;
	for (auto s : radj[x]) {
		if (!vis[s]) {
			rdfs(s);
		}
	}
}

std::vector<int> who_wins(std::vector<int> a, std::vector<int> r, std::vector<int> u, std::vector<int> v) {

	n=a.size();
	for (int i=0; i<n; ++i) charge[i]=r[i], c[i]=a[i], ans.push_back(1);

	for (int i=0; i<u.size(); ++i) {
		adj[u[i]].push_back(v[i]);
		radj[v[i]].push_back(u[i]);
	}

	for (int i=0; i<n; ++i) {
		if (charge[i]) continue;

		memset(vis,0,sizeof(vis));
		dfs(i);
		if (!vis[i]) continue;

		memset(vis,0,sizeof(vis));
		rdfs(i);
	}

	return ans;
}
