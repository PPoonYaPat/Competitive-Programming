#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m,st,ed,dis[30001];
bool vis[30001];
set<int> s[30001];
vector<pii> adj[30001];
priority_queue<pii, vector<pii>, greater<pii>> q;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=0; i<m; ++i) {
        int a,b; cin>>a>>b;
        s[a].insert(b);
        if (i==0) st=a;
        if (i==1) ed=a;
    }

    for (int i=0; i<n; ++i) {
        for (auto it=s[i].begin(); it!=s[i].end(); ++it) {
            int power=*it;

            //forward
            for (int j=1; j<=n; ++j) {
                int nxt=i+power*j;
                if (nxt>n-1) break;

                adj[i].push_back(pii(nxt,j));
                if (s[nxt].find(power)!=s[nxt].end()) break;
            }

            //backward
            for (int j=1; j<=n; ++j) {
                int nxt=i+power*(-j);
                if (nxt<0) break;

                adj[i].push_back(pii(nxt,j));
                if (s[nxt].find(power)!=s[nxt].end()) break;
            }
        }
    }

    memset(dis,0x3f,sizeof(dis));
    dis[st]=0;
    q.push(pii(0,st));

    while (!q.empty()) {
        int node=q.top().second;
        q.pop();

        if (vis[node]) continue;
        vis[node]=true;

        if (node==ed) {
            cout<<dis[ed];
            return 0;
        }

        for (auto k : adj[node]) {
            int des=k.first, w=k.second;
            if (dis[des]>dis[node]+w) {
                dis[des]=dis[node]+w;
                q.push(pii(dis[des],des));
            }
        }
    }
    cout<<-1;
}