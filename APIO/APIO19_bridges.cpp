#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int sq=1000,MX=100001;
int n,m,q,p[MX],sz[MX],a[MX],b[MX],w[MX],mode[MX],x[MX],y[MX],ans[MX];
stack<int> st;
vector<int> join[MX];

int find(int x) {
    while (x!=p[x]) x=p[x];
    return x;
}

void unite(int x, int y) {
    x=find(x); y=find(y);
    if (x==y) return;
    if (sz[x]<sz[y]) swap(x,y);
    p[y]=x;
    sz[x]+=sz[y];
    st.push(y);
}

void backward(int x) {
    while (st.size()>x) {
        int node=st.top();
        st.pop();
        sz[p[node]]-=sz[node];
        p[node]=node;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for (int i=1; i<=m; ++i) cin>>a[i]>>b[i]>>w[i];
    cin>>q;
    for (int i=0; i<q; ++i) cin>>mode[i]>>x[i]>>y[i];

    for (int k=0; k<q; k+=sq) {
        int l=k, r=min(q-1,k+sq-1);

        vector<int> ask,unchange,change;
        bool dif[100001];
        memset(dif,0,sizeof(dif));
        for (int i=1; i<=n; ++i) sz[i]=1,p[i]=i;

        for (int i=l; i<=r; ++i) {
            if (mode[i]==1) { //change
                dif[x[i]]=true;
                change.push_back(i); //collect round
            } else ask.push_back(i);
        }

        for (int i=1; i<=m; ++i) {
            if (!dif[i]) unchange.push_back(i); //collect edge
        }

        for (int i=l; i<=r; ++i) {
            if (mode[i]==2) {
                for (auto s : change) {
                    if (w[x[s]]>=y[i]) join[i].push_back(x[s]);
                }
            } else w[x[i]]=y[i];
        }

        sort(ask.begin(),ask.end(), [&](int a, int b){return y[a]>y[b];});
        sort(unchange.begin(),unchange.end(), [&](int a, int b){return w[a]>w[b];});

        int idx=0;
        for (auto i : ask) {
            //weight of the car is y[i] from city x[i]
            while (idx<unchange.size() && w[unchange[idx]]>=y[i]) unite(a[unchange[idx]],b[unchange[idx]]), ++idx;

            int pre=st.size();
            for (auto s : join[i]) unite(a[s],b[s]);
            ans[i]=sz[find(x[i])];
            backward(pre);
        }
    }

    for (int i=0; i<q; ++i) if (mode[i]==2) cout<<ans[i]<<"\n";
}
