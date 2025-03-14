#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n,m,ed=2000005;
ll ans;
pii nxt[2000010];
bool vis[2000010];
priority_queue<ll> q;

ll dfs(int x) {
    if (vis[x]) return 0;
    vis[x]=true;
    return nxt[x].second+dfs(nxt[x].first);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=0; i<ed; ++i) nxt[i]=pii(i+1,0);
    for (int i=0; i<n; ++i) {
        int a,b; cin>>a>>b;
        nxt[a]=pii(b+1,1);
        nxt[b]=pii(a+1,1);
    }

    ans=dfs(0);
    for (int i=0; i<ed; ++i) if (!vis[i]) q.push(dfs(i));
    while (m--) {
        if (q.size()) ans+=(q.top()+2), q.pop();
        else q.push(1), ++ans;
    }
    cout<<ans;
}