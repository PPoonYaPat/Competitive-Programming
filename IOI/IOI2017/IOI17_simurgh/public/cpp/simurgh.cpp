#include "simurgh.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
 
struct Edge {
	int a,idx,mode;
};
 
int n,m,deg[505],cnt;
vector<int> adj2[505],comp[505];
vector<pii> edge,adj[505];
int mat[505][505],ans[250010];
 
int p[505],r[505];
bool vis[505];


void reset() {
	cnt=0;
	for (int i=0; i<n; ++i) p[i]=i, r[i]=1, adj2[i].clear(), comp[i].clear(), vis[i]=false;
}

void dfs(int x) {
	vis[x]=true;
	comp[cnt].push_back(x);
	for (auto s : adj2[x]) if (!vis[s]) dfs(s);
}
 
int find(int x) {
	while (x!=p[x]) x=p[x];
	return x; 
} 
 
void unite(int x, int y) {
	x=find(x); y=find(y);
	if (r[x]<r[y]) swap(x,y);
	p[y]=x;
	if (r[x]==r[y]) ++r[x];
}
 
void solve1(int x) {
	vector<int> v;
	int ma=0;
	reset();
 
	for (int i=0; i<m; ++i) {
		if (edge[i].first==x || edge[i].second==x) continue;

		if (find(edge[i].first)!=find(edge[i].second)) {

			adj2[edge[i].first].push_back(edge[i].second);
			adj2[edge[i].second].push_back(edge[i].first);

			unite(edge[i].first,edge[i].second);
			v.push_back(i);
		}
	}
 
	for (int i=0; i<n; ++i) if (!vis[i] && i!=x) dfs(i), ++cnt;

	for (int i=0; i<cnt; ++i) {
		//consider edge from x to comp[i]

		//add edge to every comp except comp[i]
		for (int j=0; j<cnt; ++j) {
			if (j==i) continue;
			for (auto s : comp[j]) {
				if (mat[s][x]!=-1) {
					v.push_back(mat[s][x]);
					break;
				} 
			}
		}

		//consider every edge to comp[i]
		vector<pii> temp;
		int ma=0,mi=INT_MAX;
		for (auto s : comp[i]) {
			if (ma-mi==1 && ans[mat[s][x]]!=-1) continue;
			if (mat[s][x]!=-1) {
				v.push_back(mat[s][x]);
				int h=count_common_roads(v);
				ma=max(ma,h);
				mi=min(mi,h);
				temp.push_back(pii(h,mat[s][x]));
				v.pop_back();
			}
		}

		for (auto s : temp) {
			if (s.first==ma) ans[s.second]=1;
			else ans[s.second]=0;
		}

		for (int j=0; j<cnt-1; ++j) v.pop_back();
	}
	
	
}
 
 
vector<int> find_roads(int N, vector<int> u, vector<int> v) {
	n=N;
	m=u.size();
	memset(mat,-1,sizeof(mat));
	memset(ans,-1,sizeof(ans));

	for (int i=0; i<m; ++i) {
		edge.push_back(pii(u[i],v[i]));
		adj[u[i]].push_back(pii(v[i],i));
		adj[v[i]].push_back(pii(u[i],i));
		mat[u[i]][v[i]]=mat[v[i]][u[i]]=i;
	}
	
	vector<int> Ans;
	for (int i=0; i<n; ++i) solve1(i);
	for (int i=0; i<m; ++i) if (ans[i]==1) Ans.push_back(i);
	return Ans;
}