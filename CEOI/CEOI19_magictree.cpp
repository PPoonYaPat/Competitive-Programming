#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//slope trick
int n,m,k,d[100001],w[100001];
vector<int> adj[100001];
map<int,ll> mp[100001]; //(x,y) : add y to position x.

void dfs(int x) {
    if (adj[x].size()) {
        int mnode=-1;

        //merge
        for (auto s : adj[x]) {
            dfs(s);
            if (mnode==-1) mnode=s;
            else {
                if (mp[mnode].size()<mp[s].size()) swap(s,mnode);
                for (auto it=mp[s].begin(); it!=mp[s].end(); ++it) mp[mnode][(*it).first]+=(*it).second; //add s to mnode
            }
        }

        auto it=mp[mnode].upper_bound(d[x]);
        ll sum=0;
        while (sum+(*it).second<=w[x] && it!=mp[mnode].end()) {
            sum+=(*it).second;
            auto h=it++;
            mp[mnode].erase(h);
        }
        if (it!=mp[mnode].end()) (*it).second=(*it).second+sum-w[x];
        mp[mnode][d[x]]+=w[x];

        swap(mp[x],mp[mnode]);

    } else {
        mp[x][d[x]]=w[x];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>k;
    for (int i=2; i<=n; ++i) {
        int x; cin>>x;
        adj[x].push_back(i);
    }
    for (int i=0; i<m; ++i) {
        int x; cin>>x;
        cin>>d[x]>>w[x];
    }
    dfs(1);

    ll ans=0;
    for (auto it=mp[1].begin(); it!=mp[1].end(); ++it) ans+=(*it).second;
    cout<<ans;
}