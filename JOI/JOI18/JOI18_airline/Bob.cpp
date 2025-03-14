#include "Boblib.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int st,nx,re[1020];
vector<int> adj[1020];
bool mark[1020];

void dfs(int x, int par, int val) {
	int nxt=-1;
	for (auto s : adj[x]) {
		if (s==par || s==st) continue;
		if (mark[s]) re[s]+=val;
		else nxt=s;
	}
	if (nxt!=-1) dfs(nxt,x,val*2);
}

void Bob(int n, int m, int C[], int D[] ){
	vector<pii> v;
	for (int i=0; i<m; ++i) {
		adj[C[i]].push_back(D[i]);
		adj[D[i]].push_back(C[i]);
	}
	for (int i=0; i<n; ++i) {
		if (adj[i].size()==n-2) {
			bool have[1050];
			memset(have,0,sizeof(have));
			have[i]=true;
			for (auto s : adj[i]) have[s]=true;
			for (int j=0; j<n; ++j) if (!have[j] && adj[j].size()==n-12) {
				st=i;
				nx=j;
			}
		}
	}

	for (auto s : adj[nx]) mark[s]=true;
	
	int p=-1;
	for (int i=0; i<n; ++i) if (i!=st && i!=nx && !mark[i]) {
		int cnt=0;
		for (auto s : adj[i]) if (!mark[s]) ++cnt;
		if (cnt==2) {
			if (p==-1) p=i;
			else if (adj[i].size()>adj[p].size()) p=i;
		}
	}
	dfs(p,p,1);

	for (int i=0; i<m; ++i) {
		if (mark[C[i]] && mark[D[i]]) {
			v.push_back({re[C[i]],re[D[i]]});
		}
	}

	InitMap(n-12,v.size());
	for (auto s : v) MakeMap(s.first,s.second);
}

