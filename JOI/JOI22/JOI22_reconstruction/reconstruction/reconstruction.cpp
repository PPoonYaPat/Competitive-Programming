#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
    ll w,a,b;
    bool operator < (const Edge &o) const {return w<o.w;}
};

int n,m,bef[100005],aft[100005],p[505],r[505];
Edge edge[100005];
vector<Edge> v;

int find(int x) {
    while (x!=p[x]) x=p[x];
    return x;
}

void unite(int a, int b) {
    a=find(a); b=find(b);
    if (a!=b) {
        if (r[a]>r[b]) swap(a,b);
        p[a]=b;
        if (r[a]==r[b]) ++r[b];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=1; i<=m; ++i) cin>>edge[i].a>>edge[i].b>>edge[i].w;
    sort(edge+1,edge+m+1);

    for (int i=1; i<=m; ++i) {
        bef[i]=i-1;
        for (int j=1; j<=n; ++j) r[j]=1, p[j]=j;
        while (bef[i]) {
            unite(edge[bef[i]].a,edge[bef[i]].b);
            if (find(edge[i].a)==find(edge[i].b)) break;
            --bef[i];
        }
    }

    for (int i=1; i<=m; ++i) aft[i]=m+1;
    for (int i=1; i<=m; ++i) aft[bef[i]]=i;

    for (int i=1; i<=m; ++i) {
        if (bef[i]) v.push_back({(edge[i].w+edge[bef[i]].w)/2+1,-1ll,edge[i].w});
        else v.push_back({0,-1ll,edge[i].w});

        v.push_back({edge[i].w,2ll,-2*edge[i].w});

        if (aft[i]!=m+1) v.push_back({(edge[i].w+edge[aft[i]].w)/2+1,-1ll,edge[i].w});
    }
    sort(v.begin(),v.end());

    int q; cin>>q;
    int idx=0;
    ll cnt1=0,cnt2=0;
    while (q--) {
        ll x; cin>>x;
        while (idx<v.size() && v[idx].w<=x) {
            cnt1+=v[idx].a;
            cnt2+=v[idx].b;
            ++idx;
        }
        cout<<cnt1*x+cnt2<<"\n";
    }
}