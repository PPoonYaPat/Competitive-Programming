#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m,mark1[100001],mark2[100001],dis[100001],k[100001],st_edge[100001];
vector<pii> adj[100001];
bool vis[100001],use[100001];
string ans;

void dfs(int x) {
    vis[x]=true;
    for (auto s : adj[x]) {
        if (use[s.second]) continue;
        use[s.second]=true;
        if (vis[s.first]) {
            ++mark2[x];
            --mark2[s.first];
            ans[s.second]='B';
        } else {
            dfs(s.first);

            if (mark2[s.first] || mark1[s.first]==0) ans[s.second]='B';
            else if (mark1[s.first]>0) {
                if (st_edge[s.second]==x) ans[s.second]='L';
                else ans[s.second]='R';
            } else if (mark1[s.first]<0) {
                if (st_edge[s.second]==x) ans[s.second]='R';
                else ans[s.second]='L';
            }

            mark2[x]+=mark2[s.first];
            mark1[x]+=mark1[s.first];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=0; i<m; ++i) {
        int a,b; cin>>a>>b;
        ans+=" ";
        adj[a].push_back(pii(b,i));
        adj[b].push_back(pii(a,i));
        st_edge[i]=a;
    }
    int k; cin>>k;
    while (k--) {
        int a,b; cin>>a>>b;
        mark1[a]++;
        mark1[b]--;
    }

    for (int i=1; i<=n; ++i) if (!vis[i]) dfs(i);
    cout<<ans;
}