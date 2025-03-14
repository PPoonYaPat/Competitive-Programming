#include "werewolf.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

vector<int> adj[3001];
bool vis1[3001],vis2[3001];

vector<int> check_validity(int n, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {

    for (int i=0; i<X.size(); ++i) {
        adj[X[i]].push_back(Y[i]);
        adj[Y[i]].push_back(X[i]);
    }
    vector<int> Ans;
    for (int i=0; i<S.size(); ++i) {

        queue<int> q;
        memset(vis1,0,sizeof(vis1));
        memset(vis2,0,sizeof(vis2));

        if (S[i]>=L[i]) q.push(S[i]);
        while (!q.empty()) {
            int node=q.front();
            q.pop();

            if (vis1[node]) continue;
            vis1[node]=true;

            for (auto s : adj[node]) {
                if (s>=L[i]) q.push(s);
            }
        }

        if (E[i]<=R[i]) q.push(E[i]);
        while (!q.empty()) {
            int node=q.front();
            q.pop();

            if (vis2[node]) continue;
            vis2[node]=true;

            for (auto s : adj[node]) {
                if (s<=R[i]) q.push(s);
            }
        }

        int ans=0;
        for (int i=0; i<n; ++i) if (vis1[i]==true && vis2[i]==true) ans=1;
        Ans.push_back(ans);
    }
    for (int i=0; i<Ans.size(); ++i) if (Ans[i]==1) cout<<i<<" ";
    return Ans;
}
