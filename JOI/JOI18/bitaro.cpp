#include <bits/stdc++.h>
using namespace std;

struct A {
    int node, cnt;
} d[100001][355];

int n,m,q;
const int sq=320;
vector<int> adj[100001];
bool have[100001];

void merge(int a, int b) {
    int x=0,y=0;
    vector<int> vis;
    vector<A> temp;

    while (d[a][x].node && d[b][y].node) {
        if (d[a][x].cnt+1 > d[b][y].cnt) temp.push_back({d[a][x].node,d[a][x].cnt+1}), ++x;
        else temp.push_back(d[b][y++]);
    }

    while (d[a][x].node) temp.push_back({d[a][x].node,d[a][x].cnt+1}), ++x;
    while (d[b][y].node) temp.push_back(d[b][y++]);

    int idx=0;
    for (int i=0; i<temp.size(); ++i) {
        if (idx>sq) break;
        if (!have[temp[i].node]) {
            have[temp[i].node]=true;
            vis.push_back(temp[i].node);
            d[b][idx++]=temp[i];
        }
    }

    for (auto s : vis) have[s]=false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>q;
    for (int i=1; i<=n; ++i) d[i][0]={i,0};
    for (int i=0; i<m; ++i) {
        int x,y;
        cin>>x>>y;
        adj[y].push_back(x);
    }

    for (int i=1; i<=n; ++i) {
        for (auto s : adj[i]) merge(s,i);
    }

    while (q--) {
        int x,k; cin>>x>>k;
        int c[100001];
        for (int i=1; i<=k; ++i) cin>>c[i], have[c[i]]=true;

        if (k<=sq) {
            int ans=-1;
            for (int i=0; i<=sq; ++i) {
                if (d[x][i].node==0) break;
                if (!have[d[x][i].node]) {
                    ans=d[x][i].cnt;
                    break;
                }
            }
            cout<<ans<<"\n";
        } else {
            int dp[100001];
            memset(dp,-1,sizeof(dp));
            for (int i=1; i<=x; ++i) {
                if (!have[i]) dp[i]=0;
                else dp[i]=-1;
                for (auto s : adj[i]) if (dp[s]!=-1) dp[i]=max(dp[i],dp[s]+1);
            }
            cout<<dp[x]<<"\n";
        }
        for (int i=1; i<=k; ++i) have[c[i]]=false;

    }
}
