#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m,disc[500001],low[500001],cnt,ans;
bool vis[500001];
vector<int> adj[500001];

void tarjan(int x, int par) {
    disc[x]=low[x]=++cnt;

    for (auto s : adj[x]) {
        if (s==par) continue;
        if (disc[s]) low[x]=min(low[x],disc[s]);
        else {
            tarjan(s,x);
            low[x]=min(low[x],low[s]);
            if (low[s]>disc[x]) ++ans;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=0; i<m; ++i) {
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i=1; i<=n; ++i) {
        if (!disc[i]) {
            ++ans;
            tarjan(i,0);
        }
    }

    cout<<ans;
}
/*
7 7
1 2
2 3
3 1
2 4
5 6
6 7
7 5
*/
