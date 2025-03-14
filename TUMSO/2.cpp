#include <bits/stdc++.h>
using namespace std;

int mx=500000;
int val[500001];
vector<int> comp[500001];
bool notPrime[500001];

void solve() {
    long long ans=0;
    int n,m; cin>>n>>m;

    for (int y=2; y<=n; ++y) {
        int c=m-(m%y);
        for (int x=1; x<y; ++x) if (c%x==0) ++ans;
    }

    cout<<ans<<"\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    for (int i=2; i<=500000; ++i) {
        if (!notPrime[i]) {
            for (int j=2; j<=500000/i; ++j) comp[i*j].push_back(i), notPrime[i*j]=true;
        }
    }

    int t; cin>>t;
    while (t--) solve();
}
