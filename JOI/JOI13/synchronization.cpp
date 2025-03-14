#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m,q,val[100001],level[100001],p[100001][18],line_val[100001],in[100001],out[100001],fen[100010],cnt;
pii line[200001];
bool active[100001];
vector<int> adj[100001];

void dfs(int x, int parent) {
    in[x]=++cnt;
    level[x]=level[parent]+1;
    p[x][0]=parent;
    for (int i=1; i<18; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (auto s : adj[x]) {
        if (s==parent) continue;
        dfs(s,x);
    }
    out[x]=cnt;
}

void update(int x, int val) {
    while (x<=n+5) {
        fen[x]+=val;
        x+=(x&-x);
    }
}

int find(int x) {
    int sum=0;
    while (x) {
        sum+=fen[x];
        x-=(x&-x);
    }
    return sum;
}

int f(int x) { //find leader of group
    int k=find(in[x]);
    for (int i=17; i>=0; --i) {
        if (p[x][i]!=0 && find(in[p[x][i]])==k) x=p[x][i];
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>q;
    for (int i=1; i<=n-1; ++i) {
        cin>>line[i].first>>line[i].second;
        adj[line[i].first].push_back(line[i].second);
        adj[line[i].second].push_back(line[i].first);
    }
    dfs(1,0);
    for (int i=1; i<=n; ++i) {
        val[i]=1;
        update(in[i],1);
        update(out[i]+1,-1);
    }

    while (m--) {
        int x; cin>>x;
        int a=line[x].first, b=line[x].second;
        if (level[a]>level[b]) swap(a,b);

        a=f(a);
        if (active[x]) {
            line_val[x]=val[b]=val[a];
            update(in[b],1);
            update(out[b]+1,-1);
        } else {
            val[a]=val[a]+val[b]-line_val[x];
            update(in[b],-1);
            update(out[b]+1,1);
        }
        active[x]=!active[x];
    }

    while (q--) {
        int x; cin>>x;
        cout<<val[f(x)]<<"\n";
    }
}
