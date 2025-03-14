#include "roadreverse.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m,k;
pii ma[100001][11],mi[100001][11];
int din[100001],line[100001],pos[100001];
vector<pii> edge1,edge2;
vector<int> adj[100001];
queue<int> q;
stack<int> st;

int count_roads(int N, int M, int K, vector<vector<int>> S, vector<pii> R) {
    n=N; m=M; k=K;

    for (int i=0; i<n; ++i) for (int j=0; j<k; ++j) mi[i][j]={INT_MAX,INT_MAX}, ma[i][j]={-1,-1};

    for (int i=0; i<S.size(); ++i) {
        ma[0][i]=mi[0][i]={0,0};
        int pre=0,now;
        for (int j=0; j<S[i].size(); ++j) {
            now=S[i][j];
            pos[now]=j+1;
            ma[now][i].first=mi[now][i].first=j+1;
            ++din[now];
            line[now]=i;
            adj[pre].push_back(now);
            edge1.push_back(pii(pre,now));
            pre=now;
        }
    }

    for (auto [u,v] : R) {
        edge2.push_back(pii(u,v));
        adj[u].push_back(v);
        ++din[v];
    }

    q.push(0);
    while (!q.empty()) {
        int node=q.front();
        st.push(node);
        q.pop();

        for (auto s : adj[node]) {
            for (int i=0; i<k; ++i) {
                if (line[s]==i) continue;
                if (ma[s][i].first<=ma[node][i].first) {
                    ma[s][i].second=ma[s][i].first;
                    ma[s][i].first=ma[node][i].first;

                } else ma[s][i].second=max(ma[s][i].second,ma[node][i].first);
            }
            if (--din[s]==0) q.push(s);
        }
    }

    while (!st.empty()) {
        int node=st.top();
        st.pop();

        if (node==0) continue;
        for (auto s : adj[node]) {
            for (int i=0; i<k; ++i) {
                if (line[node]==i) continue;
                if (mi[node][i].first>=mi[s][i].first) {
                    mi[node][i].second=mi[node][i].first;
                    mi[node][i].first=mi[s][i].first;
                } else mi[node][i].second=min(mi[node][i].second,mi[s][i].first);
            }
        }
    }

    int ans=0;
    for (auto [u,v] : edge1) {
        for (int i=0; i<k; ++i) {
            if (i==line[v]) continue;
            int mmax=ma[v][i].first, mmin=mi[u][i].first;
            if (mmax==ma[u][i].first) mmax=ma[v][i].second;
            if (mmin==mi[v][i].first) mmin=mi[v][i].second;
            if (mmin<=mmax) {
                ++ans;
                break;
            }
        }
    }

    for (auto [u,v] : edge2) {
        for (int i=0; i<k; ++i) {
            int mmax=ma[v][i].first, mmin=mi[u][i].first;
            if (mmax==ma[u][i].first) mmax=ma[v][i].second;
            if (mmin==mi[v][i].first) mmin=mi[v][i].second;
            if (mmin<=mmax) {
                ++ans;
                break;
            }
        }
    }

    return m-ans;
}

/*
8 12 2
4 1 7 5 6
3 2 3 4
0 7
3 1
3 5
5 4
2 4
*/
