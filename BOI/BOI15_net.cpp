#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[500001],leaf;
vector<pair<int,int>> ans;

void dfs(int x, int par) {
    for (auto s : adj[x]) if (s!=par) dfs(s,x);
    if (adj[x].size()==1) leaf.push_back(x);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=0; i<n-1; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i=1; i<=n; ++i) {
        if (adj[i].size()>1) {
            dfs(i,0);
            break;
        }
    }
    if (leaf.size()%2==0) {
        for (int i=0; i<leaf.size()/2; ++i) ans.push_back({leaf[i],leaf[i+leaf.size()/2]});
    } else {
        for (int i=0; i<leaf.size()/2; ++i) ans.push_back({leaf[i],leaf[i+1+leaf.size()/2]});
        ans.push_back({leaf[leaf.size()/2],leaf[0]});
    }
    cout<<ans.size()<<"\n";
    for (auto s : ans) cout<<s.first<<" "<<s.second<<"\n";
}
