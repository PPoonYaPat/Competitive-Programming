#include "findhome.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int dis[301][301];
vector<int> adj[301];
bool vis[301];

int find_home(int n, int m, vector<pair<int,int>> R) {

    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            if (i==j) dis[i][j]=0;
            else dis[i][j]=1e9;
        }
    }

    for (int i=0; i<m; ++i) {
        dis[R[i].first][R[i].second]=dis[R[i].second][R[i].first]=1;
        adj[R[i].first].push_back(R[i].second);
        adj[R[i].second].push_back(R[i].first);
    }

    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            for (int k=0; k<n; ++k) {
                dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
            }
        }
    }

    int mmin=INT_MAX, node;
    for (int i=0; i<n; ++i) {
        int mmax=0;
        for (auto s : adj[i]) {
            int cnt=0;
            for (int j=0; j<n; ++j) if (dis[i][j]==1+dis[s][j]) ++cnt;
            mmax=max(mmax,cnt);
        }

        if (mmin>mmax) {
            mmin=mmax;
            node=i;
        }
    }

    int now=check(node);

    while (1) {

        for (int i=0; i<n; ++i) if (dis[node][i]!=1+dis[now][i]) vis[i]=true;

        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                if (i==j) dis[i][j]=0;
                else dis[i][j]=1e9;
            }
        }

        for (int i=0; i<m; ++i) {
            if (vis[R[i].first] || vis[R[i].second]) continue;
            dis[R[i].first][R[i].second]=dis[R[i].second][R[i].first]=1;
            adj[R[i].first].push_back(R[i].second);
            adj[R[i].second].push_back(R[i].first);
        }

        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                for (int k=0; k<n; ++k) {
                    if (vis[i] || vis[j] || vis[k]) continue;
                    dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
                }
            }
        }

        int mmin=INT_MAX, nxt;

        for (int i=0; i<n; ++i) {
            if (vis[i]) continue;

            int mmax=0;
            for (auto s : adj[i]) {
                if (vis[s]) continue;

                int cnt=0;
                for (int j=0; j<n; ++j) if (dis[i][j]==1+dis[s][j] && !vis[j]) ++cnt;
                mmax=max(mmax,cnt);

            }

            if (mmin>mmax) {
                mmin=mmax;
                nxt=i;
            }
        }

        node=nxt;
        now=check(nxt);

        if (now==nxt) return nxt;
    }
}

/*
7 6 9 0
0 1
1 2
2 3
3 4
4 5
5 6
0 0 1 2 3 4 5
*/
