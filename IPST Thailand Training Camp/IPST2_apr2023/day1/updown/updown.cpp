#include "updown.h"
#include <bits/stdc++.h>
//#include "grader.cpp"
using namespace std;
typedef pair<int,int> pii;

vector<pii> adj[1000001][2]; //0 less, 1 more
int cnt[1000001],yay;

vector<int> group[2000001];
int pos[1000001][2];
bool vis[1000001][2];
int have[1000001];
map<pii,vector<int>> mp;

vector<int> updown(int N, int M, vector<int> U, vector<int> V) {
    vector<int> ans;
    for (int i=0; i<M; ++i) {
        if (U[i]>V[i]) swap(U[i],V[i]);
        adj[U[i]][0].push_back(pii(V[i],1));
        adj[V[i]][1].push_back(pii(U[i],0));
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<2; ++j) {
            if (!vis[i][j]) {
                    ++yay;
                queue<pii> q;
                q.push(pii(i,j));

                while (!q.empty()) {
                    int node=q.front().first, mode=q.front().second;
                    q.pop();

                    if (vis[node][mode]) continue;
                    vis[node][mode]=true;

                    if (pos[node][1-mode]!=yay) group[yay].push_back(node);
                    pos[node][mode]=yay;

                    for (auto s : adj[node][mode]) {
                        if (!vis[s.first][s.second]) q.push(pii(s.first,s.second));
                    }
                }

            }
        }
    }

    for (int i=0; i<N; ++i) mp[pii(min(pos[i][0],pos[i][1]),max(pos[i][0],pos[i][1]))].push_back(i);

    for (int i=0; i<N; ++i) {
        int x=pos[i][0], y=pos[i][1];
        if (x>y) swap(x,y);

        if (x==y) ans.push_back(group[x].size()-1);
        else ans.push_back((group[x].size()-1)+(group[y].size()-1)-(mp[pii(x,y)].size()-1));
    }
    return ans;
}
/*
5 4
0 1
1 2
2 3
2 4

4 4
0 1
1 2
2 3
3 0

5 5
0 1
1 2
2 3
3 4
4 0
*/
