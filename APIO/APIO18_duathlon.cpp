#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,m,disc[100001],low[100001],sz[200001],cnt,bcc_cnt;
vector<int> adj[100001],bcc[200001];
ll ans,N;

stack<int> st;

void tarjan(int x, int par) {
    st.push(x);
    low[x]=disc[x]=++cnt;
    ++N;

    for (auto s : adj[x]) {
        if (s==par) continue;
        if (disc[s]) low[x]=min(low[x],disc[s]);
        else {
            tarjan(s,x);
            low[x]=min(low[x],low[s]);

            if (low[s]>=disc[x]) {
                ++bcc_cnt;
                bcc[x].push_back(n+bcc_cnt);

                while (!bcc[n+bcc_cnt].size() || bcc[n+bcc_cnt].back()!=s) {
                    bcc[n+bcc_cnt].push_back(st.top());
                    st.pop();
                }
            }
        }
    }
}

void dfs(int x) {
    sz[x]= x>n ? 0 : 1;
    for (auto s : bcc[x]) {
        dfs(s);
        sz[x]+=sz[s];
        if (x>n) ans-=bcc[x].size()*sz[s]*(sz[s]-1);
    }
    if (x>n) ans-=bcc[x].size()*(N-sz[x])*(N-sz[x]-1);
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
            N=0;
            tarjan(i,0);
            ans+=N*(N-1)*(N-2);
            dfs(i);
        }
    }

    cout<<ans;
}
