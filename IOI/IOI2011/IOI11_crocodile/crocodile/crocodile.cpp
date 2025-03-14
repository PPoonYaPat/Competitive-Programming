#include "crocodile.h"
#include "grader.cpp"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

pii dis[100001]; //first,second
vector<pii> adj[100001];
priority_queue<pii, vector<pii>, greater<pii>> q; //dis,node

int travel_plan(int n, int m, int R[][2], int L[], int k, int P[]) {
    for (int i=0; i<n; ++i) dis[i]={LLONG_MAX,LLONG_MAX};
    for (int i=0; i<m; ++i) {
        ll a=R[i][0], b=R[i][1], w=L[i];
        adj[a].push_back(pii(b,w));
        adj[b].push_back(pii(a,w));
    }
    for (int i=0; i<k; ++i) {
        int x=P[i];
        dis[x]={0,0};
        q.push({0,x});
    }
    while (!q.empty()) {
        ll d=q.top().first, node=q.top().second;
        q.pop();

        if (d>dis[node].second) continue;

        for (auto s : adj[node]) {
            ll des=s.first, w=s.second;

            ll now=dis[des].second;
            if (dis[des].first>d+w) {
                dis[des].second=dis[des].first;
                dis[des].first=d+w;
            } else if (dis[des].second>d+w) dis[des].second=d+w;

            if (dis[des].second<now) q.push({dis[des].second,des});
        }
    }
    return dis[0].second;
}
