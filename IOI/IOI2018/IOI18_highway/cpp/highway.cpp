#include "highway.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n,m,u,v,disU[90001],disV[90001],con;
ll Base,a,b;
vector<int> w;
vector<pii> adj[90001],Edge;
bool vis[90001];

void F(int* dis, int start) {
    memset(vis,0,sizeof(vis));
    for (int i=0; i<n; ++i) dis[i]=1e9;

    queue<int> q;
    q.push(start);
    dis[start]=0;

    while (!q.empty()) {
        int node=q.front();
        q.pop();

        if (vis[node]) continue;
        vis[node]=true;

        for (auto s : adj[node]) {
            if (dis[s.first]>dis[node]+1) {
                dis[s.first]=dis[node]+1;
                q.push(s.first);
            }
        }
    }
}

int f(int* dis1, int* dis2, int start) {
    memset(vis,0,sizeof(vis));

    queue<int> q;
    vector<int> edge,temp;
    for (int i=0; i<m; ++i) temp.push_back(0);

    q.push(start);
    vis[start]=true;

    while (!q.empty()) {
        int node=q.front();
        q.pop();

        for (auto s : adj[node]) {
            if (vis[s.first]) temp[s.second]=1;
            else if (dis1[s.first]>=dis2[s.first]) temp[s.second]=1;
            else {
                vis[s.first]=true;
                edge.push_back(s.second);
                q.push(s.first);
            }
        }
    }
    temp[con]=0;

    int l=-1, r=edge.size()-1;
    while (l<r) {
        int mid=(l+r+1)/2;

        for (int i=0; i<edge.size(); ++i) {
            if (i<mid) temp[edge[i]]=0;
            else temp[edge[i]]=1;
        }

        if (ask(temp)==Base) r=mid-1;
        else l=mid;
    }

    if (l==-1) return start;
    if (dis1[Edge[edge[l]].first]<dis1[Edge[edge[l]].second]) return Edge[edge[l]].second;
    else return Edge[edge[l]].first;
}

void find_pair(int N, vector<int> U, vector<int> V, int A, int B) {
    m=U.size();
    n=N; a=A; b=B;

    for (int i=0; i<m; ++i) {
        w.push_back(0);
        adj[U[i]].push_back({V[i],i});
        adj[V[i]].push_back({U[i],i});
        Edge.push_back({U[i],V[i]});
    }
    Base=ask(w);

    int l=0, r=m-1;
    while (l<r) {
        int mid=(l+r)/2;
        for (int i=0; i<m; ++i) {
            if (i<=mid) w[i]=0;
            else w[i]=1;
        }
        if (ask(w)==Base) r=mid;
        else l=mid+1;
    }

    u=U[l];
    v=V[l];
    con=l;

    F(disU,u);
    F(disV,v);

    answer(f(disU,disV,u),f(disV,disU,v));
}
