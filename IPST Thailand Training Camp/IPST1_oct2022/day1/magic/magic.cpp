#include "magic.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tu;

int change[200001],dis[200001][11];
bool vis[200001][11];
vector<pii> adj[200001];
priority_queue<tu, vector<tu>, greater<tu>> pq; //dis, node, free

vector<int> magic(int N, int M,int Q, vector<int>U, vector<int> V, vector<vector<int> >q){
	reverse(q.begin(),q.end());

	for (int i=0; i<Q; ++i) {
		if (q[i][0]==0) change[q[i][1]]=i+1;
	}

	for (int i=0; i<M; ++i) {
		adj[V[i]].push_back(pii(U[i],change[i]));
	}

	memset(dis,0x3f,sizeof(dis));
	dis[0][0]=0;
	pq.push(tu(0,0,0));

	while (!pq.empty()) {
		int node=get<1>(pq.top()), tic=get<2>(pq.top());
		pq.pop();

		if (vis[node][tic]) continue;
		vis[node][tic]=true;

		for (auto s : adj[node]) {
			int des=s.first, w=s.second;

			if (dis[des][tic]>max(dis[node][tic],w)) {
				dis[des][tic]=max(dis[node][tic],w);
				pq.push(tu(dis[des][tic],des,tic));
			}

			if (w!=0 && tic<10 && dis[des][tic+1]>dis[node][tic]) {
				dis[des][tic+1]=dis[node][tic];
				pq.push(tu(dis[des][tic+1],des,tic+1));
			}
		}
	}

	vector<int> ans;
	for (int i=0; i<Q; ++i) {
		if (q[i][0]==1) {
			int city=q[i][1], mag=q[i][2],mmin=INT_MAX;
			for (int j=0; j<=mag; ++j) mmin=min(mmin,dis[city][j]);

			if (mmin<i+1) ans.push_back(1);
			else ans.push_back(0);
		} else ans.push_back(-1);
	}

	reverse(ans.begin(),ans.end());

	return ans;
}

/*
3 2 5
1 0
2 1
0 0
1 1 0
1 1 1
0 1
1 2 2
*/
