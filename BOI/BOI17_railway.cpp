#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m,k,ord[100001],p[100001][18],cnt,sum[100001],level[100001];
vector<int> adj[100001],ans;
map<pii,int> mp;

void dfs(int x, int par) {
    level[x]=level[par]+1;
    p[x][0]=par;
    for (int i=1; i<=17; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs(s,x);
    }

    ord[x]=++cnt;
}

int lca(int x, int y) {
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];
    for (int i=0; i<=17; ++i) {
        if (dif&(1<<i)) x=p[x][i];
    }
    if (x==y) return x;

    for (int i=17; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            x=p[x][i];
            y=p[y][i];
        }
    }
    return p[x][0];
}

int dfs_ans(int x, int par) {
    int cnt=sum[x];
    for (auto s : adj[x]) {
        if (s==par) continue;
        cnt+=dfs_ans(s,x);
    }
    if (cnt>=k) ans.push_back(mp[pii(min(x,par),max(x,par))]);
    return cnt;
}

void solve() {
    vector<pii> v;
    int s; cin>>s;
    for (int i=1; i<=s; ++i) {
        int x; cin>>x;
        v.push_back(pii(ord[x],x));
    }
    sort(v.begin(),v.end());

    int LCA=v[0].second;
    for (int i=1; i<s; ++i) {
        int llca=lca(v[i-1].second,v[i].second);
        --sum[llca];
        ++sum[v[i].second];

        if (level[llca]<level[LCA]) {
            ++sum[LCA];
            --sum[llca];
            LCA=llca;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin>>n>>m>>k;
    for (int i=1; i<=n-1; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        if (a>b) swap(a,b);
        mp[pii(a,b)]=i;
    }
    dfs(1,0);
    while (m--) solve();
    dfs_ans(1,0);
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<"\n";
    for (auto s : ans) cout<<s<<" ";
}