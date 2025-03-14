#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int n,m,p[200005],r[200005];
ll c[200005],cnt[200005];
vector<int> ans[200005],adj[200005];
vector<pii> v;

int find(int x) {
    while (x!=p[x]) x=p[x];
    return x;
}

int unite(int x, int y) {
    if (r[x]<r[y]) swap(x,y);
    p[y]=x;
    cnt[x]+=cnt[y];
    if (r[x]==r[y]) ++r[x];
    return x;
}

void add(int x) {
    for (auto s : adj[x]) {
        if (c[x]<c[s]) continue;
        int S=find(s), X=find(x);
        if (S!=X) {
            if (cnt[S]>=c[x]) {
                if (ans[X].size()<ans[S].size()) swap(ans[X],ans[S]);
                for (auto k : ans[S]) ans[X].push_back(k);
            }
            int h=unite(X,S);
            swap(ans[X],ans[h]);
        }
    }
}

bool Ans[200005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=1; i<=n; ++i) cin>>c[i], p[i]=i, cnt[i]=c[i], v.push_back(pii(c[i],i)), ans[i].push_back(i);
    for (int i=0; i<m; ++i) {
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    sort(v.begin(),v.end());
    for (auto s : v) add(s.second);
    for (auto s : ans[find(v.back().second)]) Ans[s]=true;
    for (int i=1; i<=n; ++i) {
        if (Ans[i]) cout<<1;
        else cout<<0;
    }
}