#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m,p[100001][18],mmin[100001],root,dis[100001],pos[100001];
vector<int> adj[100001],ord;
priority_queue<int, vector<int>, greater<int>> q;
bool emp[100001]; //less than cnt and empty (also in q)

int dfs(int x, int par) {
    mmin[x]=x;
    dis[x]=dis[par]+1;
    for (auto s : adj[x]) {
        if (s==par) continue;
        mmin[x]=min(mmin[x],dfs(s,x));
    }
    return mmin[x];
}

void dfs_ord(int x, int par) {
    vector<pii> v;
    for (auto s : adj[x]) {
        if (s==par) continue;
        v.push_back(pii(mmin[s],s));
    }
    sort(v.begin(),v.end());
    for (auto s : v) dfs_ord(s.second,x);
    ord.push_back(x);
}

void dfs_par(int x, int par) {
    for (int i=1; i<=17; ++i) p[x][i]=p[p[x][i-1]][i-1];
    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs_par(s,x);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=1; i<=n; ++i) {
        int x; cin>>x;
        p[i][0]=x;
        adj[x].push_back(i);
        if (x==0) root=x;
    }

    dfs(root,root);
    dfs_ord(root,root);
    dfs_par(root,root);

    for (int i=0; i<n; ++i) pos[ord[i]]=i;
    pos[0]=100010;

    int cnt=-1;
    while (m--) {
        int mode,x; cin>>mode>>x;
        if (mode==1) {
            int ans=-1;
            while (!q.empty() && x) {
                --x;
                ans=ord[q.top()];
                emp[q.top()]=false;
                q.pop();
            }
            cnt+=x;
            if (x) cout<<ord[cnt]<<"\n";
            else cout<<ans<<"\n";

        } else {
            int y=x;
            for (int i=17; i>=0; --i) if (!emp[pos[p[x][i]]] && pos[p[x][i]]<=cnt) x=p[x][i];
            cout<<dis[y]-dis[x]<<"\n";

            emp[pos[x]]=true;
            q.push(pos[x]);
        }
    }
}