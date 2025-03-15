#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct NN {
    int c,f,cost,mode; //1-buy core, 0-sell core
    bool operator < (const NN &o) const {
        if (f==o.f) return mode>o.mode;
        else return f>o.f;
    }
};

ll n,m,dp[100005];
vector<NN> v;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int i=1; i<=100000; ++i) dp[i]=-1e16;

    cin>>n;
    for (int i=0; i<n; ++i) {
        int c,f,cost;
        cin>>c>>f>>cost;
        v.push_back({c,f,cost,1});
    }
    cin>>m;
    for (int i=0; i<m; ++i) {
        int c,f,cost;
        cin>>c>>f>>cost;
        v.push_back({c,f,cost,0});
    }
    sort(v.begin(),v.end());

    for (auto s : v) {
        if (s.mode==1) for (int i=100000; i>=s.c; --i) dp[i]=max(dp[i],dp[i-s.c]-s.cost);
        else for (int i=0; i<=100000-s.c; ++i) dp[i]=max(dp[i],dp[i+s.c]+s.cost);
    }

    ll ans=0;
    for (int i=0; i<=100000; ++i) ans=max(ans,dp[i]);
    cout<<ans;
}