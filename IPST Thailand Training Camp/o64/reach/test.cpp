#include "reach.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[100001];
bool mark[100010];

void initialize(int N) {
    n=N;
    for (int i=0; i<N-1; ++i) adj[i].push_back(i+1);
}

void add_arc(int u, int v) {
    adj[u].push_back(v);
}

bool is_reachable(int u, int v, int t) {
    queue<int> q;
    if (u!=0) q.push(0);

    memset(mark, 0, sizeof(mark));
    while (!q.empty()) {
        int node=q.front();
        q.pop();
        mark[node]=1;

        if (node==t) return true;

        for (auto s : adj[node]) {
            if (!mark[s] && (s<u || s>v)) q.push(s);
        }
    }
    return false;
}
/*
9 11
1 2 4
1 3 6
1 4 7
1 5 6
1 6 8
2 1 4 5
2 3 3 8
2 4 5 6
2 5 6 7
2 1 7 7
2 3 8 2
*/

