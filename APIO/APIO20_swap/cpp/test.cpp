#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m;
vector<int> adj[100001];
map<pii,int> mp;

struct Edge{
    int u,v,w;
    bool operator < (const Edge &o) {return w<o.w;}
};

vector<Edge> edge;

int p[100001];

int find(int x) {
    while (x!=p[x]) x=p[x];
    return x;
}

void unite(int X, int Y) {
    int x=find(X), y=find(Y);

    if (x!=y) {
        adj[X].push_back(Y);
        adj[Y].push_back(X);

        p[x]=y;
    } else {
        cout<<"yes";
    }
}
int cnt=0;
bool vis[100020];
void dfs(int x, int par) {
    ++cnt;
    if (x==99998) return;
    if (vis[x]) return;
    vis[x]=true;

    for (auto s : adj[x]){
        if (s==par) continue;
        dfs(s,x);
    }
}

int main() {
/*
    freopen("in2.txt","r",stdin);
    freopen("out2.txt","w",stdout);
    cin>>n>>m;
    for (int i=0; i<m; ++i) {
        int a,b,w; cin>>a>>b>>w;
        edge.push_back({a,b,w});
    }
    sort(edge.begin(),edge.end());
    for (int i=0; i<n; ++i) p[i]=i;

    for (auto s : edge) unite(s.u,s.v);

    cout<<n<<" "<<m<<"\n";
    int cnt=0;
    for (int i=0; i<n; ++i) {
        for (auto s : adj[i]) {
            if (s>i) {
                cout<<i<<" "<<s<<"\n", ++cnt;
                assert(mp[pii(i,s)]==0);
                mp[pii(i,s)]=1;
            }
        }
    }
    assert(cnt==n-1); */

    freopen("out2.txt","r",stdin);
    cin>>n>>m;
    for (int i=0; i<n; ++i) p[i]=i;
    for (int i=0; i<m; ++i) {
        int a,b; cin>>a>>b;
        unite(a,b);
    }
}
