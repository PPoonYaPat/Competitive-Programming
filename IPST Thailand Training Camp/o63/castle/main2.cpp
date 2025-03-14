#include <bits/stdc++.h>
#include "castle.h"
#include "castle.cpp"
using namespace std;
typedef pair<int,int> pii;

int n,m,Q,y;
vector<int> A,B,v;
vector<pii> adj[10010];
bool broke[10200],vis[10001];

void dfs(int x, int par) {
    if (vis[x]) return;
    vis[x]=true;

    for (auto s : adj[x]) {
        if (s.first==par || broke[s.second]) continue;
        dfs(s.first,x);
    }
}

int main() {

    freopen("in.txt","r",stdin);
    freopen("in.txt","a",stdout);

    castle_init(n,m,Q,y);
    castle_read_map(A,B);

    for (int i=0; i<m; ++i) {
        adj[A[i]].push_back({B[i],i});
        adj[B[i]].push_back({A[i],i});
    }

    while (Q--) {
        int mode,st,ed;
        castle_read_event(mode,st,ed);

        if (mode==1) {
            broke[st]=true;
        } else {
            memset(vis,0,sizeof(vis));
            dfs(st,-1);
            if (vis[ed]) castle_answer2(1);
            else castle_answer2(0);
        }
    }
}

/*
3 3 6 1
0 1
0 2
1 2
2 1 1
1 1 0
2 2 0
1 2 0
2 2 0
2 0 1

6 7 6 1
1 2
2 5
1 0
0 3
0 4
1 5
1 4
1 4 0
1 3 0
2 1 5
2 3 4
1 6 0
2 4 5
*/



